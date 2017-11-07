#include <stdio.h>
#include <stdlib.h>   // atoi, free, posix_memalign, _Exit, EXIT_SUCCESS/FAILURE
#include <stdint.h>
#include "simd.h"
#include "environ.h"  // detectCPU, detectSIMD, printSysconf
#include "timers.h"

#include <iostream>
using std::cout;
using std::endl;


#define FREE(p) while(0) { if(p) { free(p); p = NULL; } }

#define FUNC_VERSION 0
#define OO_VERSION 2
#define CLASSIC_VERSION 1
#define VALIDATE_VERSIONS 1
#define NUM_THREADS 1

#define N 16
#define DATATYPE 0 // 0 = int32, 1 = flt32, 2 = flt64

#if DATATYPE == 0
#   define VCLASS int32_v
#   define VTYPE SIMD_INT
#   define STYPE int32_t
#   define vadd(a,b) simd_add_32(a,b)
#elif DATATYPE == 1
#   define VCLASS flt32_v
#   define VTYPE SIMD_FLT
#   define STYPE float
#   define vadd(a,b) simd_add(a,b)
#elif DATATYPE == 2
#   define VCLASS flt64_v
#   define VTYPE SIMD_DBL
#   define STYPE double
#   define vadd(a,b) simd_add(a,b)
#endif


/*!
 *  \todo Move this defnition of omp_enabled to .cpp definition file, placed here temporarily to prevent multiple definition error
 */
bool SYSCONF::omp_enabled = false;
int32_t SYSCONF::omp_threads = 1;
size_t int32_v::L2_nelems = (size_t)SYSCONF::getL2LineSz() / sizeof(int32_t);


int main(int argc, char *argv[])
{
    long int timer[2];
    double elapsed = 0.0;

    int result = 0;
    const size_t alignment = SIMD_WIDTH_BYTES;
    STYPE *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

    size_t n = N;
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    detectCPU();
    detectSIMD();
    SYSCONF::printSysconf();

    cout << "Alignment: " << alignment << endl;
    cout << "Num. elems: " << n << endl;

    // Initialize
    if (posix_memalign((void **)&A, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);
    if (posix_memalign((void **)&B, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    for (size_t i = 0; i < n; ++i) {
        A[i] = 15;
        B[i] = i;
    }

    // Run
#if FUNC_VERSION == 1
    if (posix_memalign((void **)&C1, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    tic(timer);

    VTYPE va = simd_load(A);
    VTYPE vb = simd_load(B);
    VTYPE vc = vadd(va, vb);
    simd_store(C1, vc);

    elapsed = toc(timer);
    cout << "Elapsed time (func version): " << elapsed << " seconds" << endl;
#endif


#if CLASSIC_VERSION == 1
    if (posix_memalign((void **)&C2, alignment, n * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    tic(timer);

    #pragma omp parallel for default(shared) schedule(static) num_threads(NUM_THREADS) if(NUM_THREADS > 1)
    for (size_t i = 0; i < n; ++i) {
        C2[i] = A[i] + B[i];
    }

    elapsed = toc(timer);
    cout << "Elapsed time (classic version): " << elapsed << " seconds" << endl;
#endif


#if OO_VERSION == 1
    SYSCONF::set_omp(NUM_THREADS);
    SYSCONF::omp_settings();

    tic(timer);

    C1 = VCLASS::add(A, B, n);

    elapsed = toc(timer);
    cout << "Elapsed time (OO version): " << elapsed << " seconds" << endl;
#endif


#if OO_VERSION == 2
    SYSCONF::set_omp(NUM_THREADS);
    SYSCONF::omp_settings();

    tic(timer);

    C1 = VCLASS::add2(A, B, n);

    elapsed = toc(timer);
    cout << "Elapsed time (OO2 version): " << elapsed << " seconds" << endl;
#endif


#if VALIDATE_VERSIONS == 1
    // Validate
    for (size_t i = 0; i < n; ++i) {
        if (C1[i] != C2[i])
            result += 1;
        if (n <= (2 * (SYSCONF::getL2LineSz() / sizeof(*A))))
            cout << C1[i] << " == " << C2[i] << endl;
    }
#endif


    FREE(A);
    FREE(B);
    FREE(C1);
    FREE(C2);

    return result;
}

#undef STYPE
#undef VTYPE
#undef VCLASS

