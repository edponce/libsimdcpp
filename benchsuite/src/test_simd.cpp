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
    //const int streams = SIMD_STREAMS_32;

    {
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C = NULL;
        int32_t *pA = NULL, *pB = NULL, *pC = NULL;

        create_test_array(test_type, (void **)&A, num_elems + offset_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems + offset_elems, alignment);
        create_empty_array(test_type, (void **)&C, num_elems, alignment);

        pA = A + offset_elems;
        pB = B + offset_elems;
        pC = C;

        elapsed = 0.0;
        tic(timer);

        #pragma omp parallel for simd default(shared) schedule(static)
        for (int i = 0; i < num_elems; ++i)
            pC[i] = pA[i] + pB[i];

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
        int32_t *pA = NULL, *pB = NULL, *pC1 = NULL, *pC2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems + offset_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems + offset_elems, alignment);
        create_empty_array(test_type, (void **)&C2, num_elems, alignment);

        pA = A + offset_elems;
        pB = B + offset_elems;
        pC2 = C2;


//        printf("offset elems: %d\n", offset_elems);

        // Are arrays aligned?
        int a_alignment = ((size_t)pA & (alignment - 1)) / sizeof(*pA);
        int b_alignment = ((size_t)pB & (alignment - 1)) / sizeof(*pB);
//        printf("A left alignment: %d elements\n", a_alignment);
//        printf("B left alignment: %d elements\n", b_alignment);

        int a_offs = (streams - a_alignment) % streams;
        int b_offs = (streams - b_alignment) % streams;
//        printf("A right alignment: %d elements\n", a_offs);
//        printf("B right alignment: %d elements\n", b_offs);

        int a_aligned = (!a_offs) ? (1) : (0);
        int b_aligned = (!b_offs) ? (1) : (0);
//        printf("A aligned? %d\n", a_aligned);
//        printf("B aligned? %d\n", b_aligned);

        // If there is a remainder after reaching an alignment point
        const int rem = (num_elems - a_offs) & (streams - 1);
//        printf("Remainder elements: %d\n", rem);

        int i;

        // A aligned
        if (a_aligned) {
            // A aligned, B aligned
            if (b_aligned) {
                // No remainder
                if (!rem) {
                    printf("A aligned, B aligned, no remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems, alignment);
                    pC1 = C1;

                    elapsed = 0.0;
                    tic(timer);
                    for (i = 0; i < num_elems; i+=streams) {
                        SIMD_INT va = simd_load(&pA[i]);
                        SIMD_INT vb = simd_load(&pB[i]);
                        SIMD_INT vc = simd_add_32(va, vb);
                        simd_store(&pC1[i], vc);
                    }
                    elapsed = toc(timer);
                // Yes remainder
                } else {
                    printf("A aligned, B aligned, yes remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems, alignment);
                    pC1 = C1;

                    elapsed = 0.0;
                    tic(timer);
                    for (i = 0; i < (num_elems - rem); i+=streams) {
                        SIMD_INT va = simd_load(&pA[i]);
                        SIMD_INT vb = simd_load(&pB[i]);
                        SIMD_INT vc = simd_add_32(va, vb);
                        simd_store(&pC1[i], vc);
                    }
                    for (; i < num_elems; ++i) {
                        pC1[i] = pA[i] + pB[i];
                    }
                    elapsed = toc(timer);
                }
            // A aligned, B not aligned
            } else {
                // No remainder
                if (!rem) {
                    printf("A aligned, B not aligned, no remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems, alignment);
                    pC1 = C1 + a_alignment;
                // Yes remainder
                } else {
                    printf("A aligned, B not aligned, yes remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems, alignment);
                    pC1 = C1 + a_alignment;
                }
            }
        // A not aligned
        } else {
            // A not aligned, B aligned
            if (b_aligned) {
                // No remainder
                if (!rem) {
                    printf("(incomplete) A not aligned, B aligned, no remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems, alignment);
                    pC1 = C1 + a_alignment;
                // Yes remainder
                } else {
                    printf("(incomplete) A not aligned, B aligned, yes remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems, alignment);
                    pC1 = C1 + a_alignment;
                }
            // A not aligned, B not aligned
            } else {
                // No remainder
                if (!rem) {
                    printf("A not aligned, B not aligned, no remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems + a_alignment, alignment);
                    pC1 = C1 + a_alignment;

                    elapsed = 0.0;
                    tic(timer);
                    for (i = 0; i < a_offs; ++i) {
                        pC1[i] = pA[i] + pB[i];
                    }
                    for (; i < (num_elems - rem); i+=streams) {
                        SIMD_INT va = simd_load(&pA[i]);
                        SIMD_INT vb = simd_load(&pB[i]);
                        SIMD_INT vc = simd_add_32(va, vb);
                        simd_store(&pC1[i], vc);
                    }
                    elapsed = toc(timer);
                // Yes remainder
                } else {
                    printf("A not aligned, B not aligned, yes remainder\n");
                    create_empty_array(test_type, (void **)&C1, num_elems + a_alignment, alignment);
                    pC1 = C1 + a_alignment;

                    elapsed = 0.0;
                    tic(timer);
                    for (i = 0; i < a_offs; ++i) {
                        pC1[i] = pA[i] + pB[i];
                    }
                    for (; i < (num_elems - rem); i+=streams) {
                        SIMD_INT va = simd_load(&pA[i]);
                        SIMD_INT vb = simd_load(&pB[i]);
                        SIMD_INT vc = simd_add_32(va, vb);
                        simd_store(&pC1[i], vc);
                    }
                    for (; i < num_elems; ++i) {
                        pC1[i] = pA[i] + pB[i];
                    }
                    elapsed = toc(timer);
                }
            }
        }

        printf("(SIMD function) Elapsed time is %f seconds for %d elements, offset by %d elements\n", elapsed, num_elems, offset_elems);

//        printf("C2 ");
        for (int i = 0; i < num_elems; ++i) {
            pC2[i] = pA[i] + pB[i];
//            printf("%d ", pC2[i]);
        }
//        printf("\n");

        test_result += validate_test_arrays(test_type, (void *)pC1, (void *)pC2, num_elems);

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
    //const int streams = SIMD_STREAMS_32;

    {
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;
        int32_t *pA = NULL, *pB = NULL;

        create_test_array(test_type, (void **)&A, num_elems + offset_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems + offset_elems, alignment);
        create_empty_array(test_type, (void **)&C2, num_elems, alignment);

        pA = A + offset_elems;
        pB = B + offset_elems;

        elapsed = 0.0;
        tic(timer);

        C1 = add(pA, pB, num_elems);

        elapsed = toc(timer);
        printf("(SIMD OO) Elapsed time is %f seconds for %d elements, offset by %d elements\n", elapsed, num_elems, offset_elems);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = pA[i] + pB[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


#endif  // SIMD_MODE

