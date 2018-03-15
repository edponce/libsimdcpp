#include <stdio.h>
#include <stdlib.h>   // atoi, malloc, free, posix_memalign, _Exit, EXIT_SUCCESS/FAILURE
#include <stdint.h>
#include "simd.h"
#include "environ.h"  // detectCPU, detectSIMD, printSysconf
#include "timers.h"

#if defined(_OPENMP)
#   include <omp.h>
#endif

#include <iostream>
using std::cout;
using std::endl;

#define FREE(p) do { if(p) { free(p); p = NULL; } } while(0)

#define CLASSIC_VERSION 1
#define FUNC_VERSION 0
#define OO_VERSION 1
#define VALIDATE_VERSIONS 1
#define NUM_THREADS 2
#define ELEM_OFFS 0

#define N 16
#define DATATYPE 0 // 0 = int32, 1 = flt32, 2 = flt64

#if DATATYPE == 0
#   define VCLASS int32_v
#   define VTYPE SIMD_INT
#   define STYPE int32_t
#   define vadd(a,b) simd_add_32(a,b)
#   define SIMD_STREAMS SIMD_STREAMS_32
#elif DATATYPE == 1
#   define VCLASS flt32_v
#   define VTYPE SIMD_FLT
#   define STYPE float
#   define vadd(a,b) simd_add(a,b)
#   define SIMD_STREAMS SIMD_STREAMS_32
#elif DATATYPE == 2
#   define VCLASS flt64_v
#   define VTYPE SIMD_DBL
#   define STYPE double
#   define vadd(a,b) simd_add(a,b)
#   define SIMD_STREAMS SIMD_STREAMS_64
#endif


/*!
 *  \todo Move this definition of omp_enabled to .cpp definition file, placed here temporarily to prevent multiple definition error
 */
bool SYSCONF::omp_enabled; // = false;
int32_t SYSCONF::omp_threads; // = 1;
size_t SYSCONF::L1l_elems_i32;
size_t SYSCONF::L1c_elems_i32;
size_t SYSCONF::L2l_elems_i32;
size_t SYSCONF::L2c_elems_i32;
size_t SYSCONF::page_sz;


int main(int argc, char *argv[])
{
    long int timer[2];
    double elapsed = 0.0;

    const size_t alignment = SIMD_WIDTH_BYTES;
    STYPE *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

    cout << "Usage: " << argv[0] << " [n] [elem_offs]" << endl;
    size_t n = N;
    size_t elem_offs = ELEM_OFFS;
    if (argc > 1)
        n = atoi(argv[1]);
    if (argc > 2)
        elem_offs = atoi(argv[2]);

    detectCPU();
    detectSIMD();
    SYSCONF::initSysconf();
    SYSCONF::printSysconf();

    cout << "Alignment: " << alignment << endl;
    cout << "Num. elems: " << n << endl;
    cout << "Elem offset: " << elem_offs << endl;

    // Initialize
    if (posix_memalign((void **)&A, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);
    if (posix_memalign((void **)&B, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);


    for (size_t i = 0; i < n; ++i) {
        A[i] = i + 1.3;
        B[i] = i + 2.5;
    }

#if CLASSIC_VERSION == 1
    tic(timer);

    if (posix_memalign((void **)&C2, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    #pragma omp parallel for simd default(shared) schedule(static) num_threads(NUM_THREADS) if(NUM_THREADS > 1)
    for (size_t i = elem_offs; i < n; ++i) {
        C2[i] = A[i] + B[i];
    }

    elapsed = toc(timer);
    cout << "Elapsed time (classic version): " << elapsed << " seconds" << endl;
#endif


#if FUNC_VERSION == 1
    if (posix_memalign((void **)&C1, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    tic(timer);

    const size_t rem = (n - elem_offs) & (SIMD_STREAMS - 1);
    size_t ii;
    for (ii = elem_offs; ii < (elem_offs + rem); ++ii) {
        C1[ii] = A[ii] + B[ii];
    }
    for (; ii < n; ii+=SIMD_STREAMS) {
        VTYPE va = simd_load(&A[ii]);
        VTYPE vb = simd_load(&B[ii]);
        VTYPE vc = vadd(va, vb);
        simd_store(&C1[ii], vc);
    }

    elapsed = toc(timer);
    cout << "Elapsed time (func version): " << elapsed << " seconds" << endl;
#endif


#if OO_VERSION == 1
    SYSCONF::set_omp(NUM_THREADS);
    SYSCONF::omp_settings();

    tic(timer);

    C1 = add(&A[elem_offs], &B[elem_offs], n - elem_offs);

    elapsed = toc(timer);
    cout << "Elapsed time (OO version): " << elapsed << " seconds" << endl;
#endif


#if VALIDATE_VERSIONS == 1 && (CLASSIC_VERSION + FUNC_VERSION + OO_VERSION) > 1
    // Validate
    int result = 0;
    for (size_t i = elem_offs; i < n; ++i) {
        if (C1[i] != C2[i])
            result += 1;
        if (n <= (2 * (SYSCONF::getL2LineSz() / sizeof(*A))))
            cout << C1[i] << " == " << C2[i] << endl;
    }

    cout << "Incorrect entries: " << result << endl;
#endif


    FREE(A);
    FREE(B);
    FREE(C1);
    FREE(C2);

    return EXIT_SUCCESS;
}

#undef STYPE
#undef VTYPE
#undef VCLASS

