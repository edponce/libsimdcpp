#include "simd.h"
#if defined(SIMD_MODE)


#include <stdio.h>
#include <stdlib.h>      // free, NULL
#include <stdint.h>
#include <math.h>        // sqrt, abs, floor, ceil
#include <limits.h>      // limits of fundamental integral types
#include "test_utils.h"
#include "test_simd.h"
#include "timers.h"

#if defined(_OPENMP)
#   include <omp.h>
#endif


// Deallocate dynamic memory and nullify pointer
#define FREE(p) do { if(p) { free(p); p = NULL; } } while(0)


int test_simd_add_classic(int num_elems, int offset_elems)
{
    long int timer[2];
    double elapsed = 0.0;

    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;
    const int streams = SIMD_STREAMS_32;

    {
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C = NULL;

        if (num_elems <= 0)
            num_elems = streams;
        if (offset_elems < 0 || offset_elems >= num_elems)
            offset_elems = 0;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_empty_array(test_type, (void **)&C, num_elems, alignment);

        elapsed = 0.0;
        tic(timer);

        #pragma omp parallel for default(shared) schedule(static)
        for (int i = offset_elems; i < num_elems; ++i)
            C[i] = A[i] + B[i];

        elapsed = toc(timer);
        printf("(Classic) Elapsed time is %f seconds for %d elements, offset by %d elements\n", elapsed, num_elems, offset_elems);

        FREE(A);
        FREE(B);
        FREE(C);
    }

    return test_result;
}


int test_simd_add_func(int num_elems, int offset_elems)
{
    long int timer[2];
    double elapsed = 0.0;

    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;
    const int streams = SIMD_STREAMS_32;

    {
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        if (num_elems <= 0)
            num_elems = streams;
        if (offset_elems < 0 || offset_elems >= num_elems)
            offset_elems = 0;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_empty_array(test_type, (void **)&C2, num_elems, alignment);
        create_empty_array(test_type, (void **)&C1, num_elems, alignment);

        elapsed = 0.0;

        // Are arrays aligned?
        int a_aligned = 1;
        if ((size_t)(A + offset_elems) & (alignment - 1))
            a_aligned = 0;

        int b_aligned = 1;
        if ((size_t)(B + offset_elems) & (alignment - 1))
            b_aligned = 0;
        //

        if (!a_aligned)
            printf("A is not aligned\n");

        if (!b_aligned)
            printf("B is not aligned\n");

        // If A and B are aligned and there is a remainder
        const int rem = (num_elems - offset_elems) & (streams - 1);
        if (rem)
            printf("Remainder elements: %d\n", rem);


        int i;
        // A aligned
        if (a_aligned) {
            // A aligned, B aligned
            if (b_aligned) {
                // No remainder
                if (!rem) {
                    tic(timer);
                    for (i = 0; i < num_elems; i+=streams) {
                        SIMD_INT va = simd_load(&A[i]);
                        SIMD_INT vb = simd_load(&B[i]);
                        SIMD_INT vc = simd_add_32(va, vb);
                        simd_store(&C1[i], vc);
                    }
                    elapsed = toc(timer);
                // Yes remainder
                } else {
                    tic(timer);
                    for (i = 0; i < (num_elems - rem); i+=streams) {
                        SIMD_INT va = simd_load(&A[i]);
                        SIMD_INT vb = simd_load(&B[i]);
                        SIMD_INT vc = simd_add_32(va, vb);
                        simd_store(&C1[i], vc);
                    }
                    for (; i < num_elems; ++i) {
                        C1[i] = A[i] + B[i];
                    }
                    elapsed = toc(timer);
                }
            // A aligned, B not aligned
            } else {
                // No remainder
                if (!rem) {
                    printf("incomplete\n");
                // Yes remainder
                } else {
                    printf("incomplete\n");
                }
            }
        // A not aligned
        } else {
            // A not aligned, B aligned
            if (b_aligned) {
                // No remainder
                if (!rem) {
                    printf("incomplete\n");
                // Yes remainder
                } else {
                    printf("incomplete\n");
                }
            // A not aligned, B not aligned
            } else {
                // No remainder
                if (!rem) {
                    printf("incomplete\n");
                // Yes remainder
                } else {
                    printf("incomplete\n");
                }
            }
        }


/*
        tic(timer);
        for (i = offset_elems; i < (offset_elems + rem); ++i) {
            C1[i] = A[i] + B[i];
        }
        for (; i < num_elems; i+=streams) {
            SIMD_INT va = simd_load(&A[i]);
            SIMD_INT vb = simd_load(&B[i]);
            SIMD_INT vc = simd_add_32(va, vb);
            simd_store(&C1[i], vc);
        }
        elapsed = toc(timer);
*/

        printf("(SIMD function) Elapsed time is %f seconds for %d elements, offset by %d elements\n", elapsed, num_elems, offset_elems);

        for (int i = offset_elems; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)&C1[offset_elems], (void *)&C2[offset_elems], num_elems - offset_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_add_oo(int num_elems, int offset_elems)
{
    long int timer[2];
    double elapsed = 0.0;

    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;
    const int streams = SIMD_STREAMS_32;

    {
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        if (num_elems <= 0)
            num_elems = streams;
        if (offset_elems < 0 || offset_elems >= num_elems)
            offset_elems = 0;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_empty_array(test_type, (void **)&C2, num_elems, alignment);

        elapsed = 0.0;
        tic(timer);

        C1 = add(&A[offset_elems], &B[offset_elems], num_elems - offset_elems);

        elapsed = toc(timer);
        printf("(SIMD OO) Elapsed time is %f seconds for %d elements, offset by %d elements\n", elapsed, num_elems, offset_elems);

        for (int i = offset_elems; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)&C1[offset_elems], (void *)&C2[offset_elems], num_elems - offset_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


#endif  // SIMD_MODE

