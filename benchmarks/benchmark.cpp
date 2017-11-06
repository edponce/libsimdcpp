#include <stdio.h>
#include <stdlib.h>   // free, posix_memalign, _Exit, EXIT_SUCCESS/FAILURE
#include "simd.h"
#include "environ.h"  // detectCPU, detectSIMD, printSysconf
#include "timers.h"


#define FREE(p) while(0) { if(p) { free(p); p = NULL; } }

#define FUNC_VERSION 0
#define OO_VERSION 1
#define CLASSIC_VERSION 0
#define VALIDATE_VERSIONS 0
#define NUM_THREADS 4

#define N 100000000
#define DATATYPE 2 // 0 = int32, 1 = flt32, 2 = flt64

#if DATATYPE == 0
#   define VCLASS int32_v
#   define VTYPE SIMD_INT
#   define STYPE int32_t
#   define vadd(a,b) simd_add_32(a,b)
#   define PRI "%d"
#elif DATATYPE == 1
#   define VCLASS flt32_v
#   define VTYPE SIMD_FLT
#   define STYPE float
#   define vadd(a,b) simd_add(a,b)
#   define PRI "%f"
#elif DATATYPE == 2
#   define VCLASS flt64_v
#   define VTYPE SIMD_DBL
#   define STYPE double
#   define vadd(a,b) simd_add(a,b)
#   define PRI "%f"
#endif


/*!
 *  \todo Move this defnition of omp_enabled to .cpp definition file, placed here temporarily to prevent multiple definition error
 */
uint32_t SYSCONF::omp_enabled = 0;
int32_t SYSCONF::omp_threads = 1;


int main()
{
    long int timer[2];
    double elapsed = 0.0;

    int result = 0;
    const int alignment = SIMD_WIDTH_BYTES;
    const int num_elems = VCLASS::get_nstreams() * N;
    STYPE *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

    detectCPU();
    detectSIMD();
    SYSCONF::printSysconf();

    printf("Alignment: %d\n", alignment);
    printf("Num. elems: %d\n", num_elems);

    // Initialize
    if (posix_memalign((void **)&A, alignment, num_elems * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);
    if (posix_memalign((void **)&B, alignment, num_elems * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    for (int i = 0; i < num_elems; ++i) {
        A[i] = 1;
        B[i] = i;
    }

    // Run
#if FUNC_VERSION == 1
    tic(timer);

    if (posix_memalign((void **)&C1, alignment, num_elems * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    VTYPE va = simd_load(A);
    VTYPE vb = simd_load(B);
    VTYPE vc = vadd(va, vb);
    simd_store(C1, vc);

    elapsed = toc(timer);
    printf("Elapsed time (func version): %f seconds\n", elapsed);
#endif


#if CLASSIC_VERSION == 1
    tic(timer);

    if (posix_memalign((void **)&C2, alignment, num_elems * sizeof(STYPE)))
        _Exit(EXIT_FAILURE);

    #pragma omp parallel for default(shared) schedule(static) num_threads(NUM_THREADS)
    for (int i = 0; i < num_elems; ++i) {
        C2[i] = A[i] + B[i];
    }

    elapsed = toc(timer);
    printf("Elapsed time (classic version): %f seconds\n", elapsed);
#endif


#if OO_VERSION == 1
    SYSCONF::set_omp(NUM_THREADS);
    SYSCONF::omp_settings();

    tic(timer);

    C1 = VCLASS::add(A, B, num_elems);

    elapsed = toc(timer);
    printf("Elapsed time (OO version): %f seconds\n", elapsed);
#endif


#if VALIDATE_VERSIONS == 1
    // Validate
    for (int i = 0; i < num_elems; ++i) {
        if (C1[i] != C2[i])
            result += 1;
        if (num_elems < 9)
            printf(PRI " == " PRI "\n", C1[i], C2[i]);
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

