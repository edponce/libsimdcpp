#include <stdlib.h>  // posix_memalign, rand
#include <stdint.h>
#include <limits.h>  // limits of fundamental integral types
#include <float.h>   // floating-point epsilons
#include <math.h>    // fabs
#include "test_utils.h"


/*!
 *  \brief Array allocation and initialization
 */
void create_test_array(const int32_t arr_type, void ** const arr, const int32_t num_elems, const int32_t alignment)
{
    switch (arr_type) {
        case TEST_I8:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int8_t))) {
                int8_t *parr = (int8_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % SCHAR_MAX;
            }
            break;
        case TEST_I16:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int16_t))) {
                int16_t *parr = (int16_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % SHRT_MAX;
            }
            break;
        case TEST_I32:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int32_t))) {
                int32_t *parr = (int32_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % INT_MAX;
            }
            break;
        case TEST_I64:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int64_t))) {
                int64_t *parr = (int64_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % LONG_MAX;
            }
            break;
        case TEST_U8:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint8_t))) {
                uint8_t *parr = (uint8_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % UCHAR_MAX;
            }
            break;
        case TEST_U16:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint16_t))) {
                uint16_t *parr = (uint16_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % USHRT_MAX;
            }
            break;
        case TEST_U32:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint32_t))) {
                uint32_t *parr = (uint32_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % UINT_MAX;
            }
            break;
        case TEST_U64:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint64_t))) {
                uint64_t *parr = (uint64_t *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = rand() % ULONG_MAX;
            }
            break;
        case TEST_FLT:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(float))) {
                float *parr = (float *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = (rand() % RAND_MAX) / (float)RAND_MAX;
            }
            break;
        case TEST_DBL:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(double))) {
                double *parr = (double *)*arr;
                for (int32_t i = 0; i < num_elems; ++i)
                    parr[i] = (rand() % RAND_MAX) / (double)RAND_MAX;
            }
            break;
    }
}


/*!
 *  \brief Validate test by comparing pair of data arrays
 *  \return Number of elements that differ
 */
int32_t validate_test_arrays(const int32_t arr_type, const void * const arr1, const void * const arr2, const int32_t num_elems)
{
    int32_t num_failed = 0;

    switch (arr_type) {
        case TEST_I8:
            {
                int8_t *parr1 = (int8_t *)arr1, *parr2 = (int8_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_I16:
            {
                int16_t *parr1 = (int16_t *)arr1, *parr2 = (int16_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_I32:
            {
                int32_t *parr1 = (int32_t *)arr1, *parr2 = (int32_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_I64:
            {
                int64_t *parr1 = (int64_t *)arr1, *parr2 = (int64_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_U8:
            {
                uint8_t *parr1 = (uint8_t *)arr1, *parr2 = (uint8_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_U16:
            {
                uint16_t *parr1 = (uint16_t *)arr1, *parr2 = (uint16_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_U32:
            {
                uint32_t *parr1 = (uint32_t *)arr1, *parr2 = (uint32_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_U64:
            {
                uint64_t *parr1 = (uint64_t *)arr1, *parr2 = (uint64_t *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (parr1[i] != parr2[i])
                        num_failed++;
            }
            break;
        case TEST_FLT:
            {
                float *parr1 = (float *)arr1, *parr2 = (float *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (fabs(parr1[i] - parr2[i]) > FLT_EPSILON)
                        num_failed++;
            }
            break;
        case TEST_DBL:
            {
                double *parr1 = (double *)arr1, *parr2 = (double *)arr2;
                for (int32_t i = 0; i < num_elems; ++i)
                    if (fabs(parr1[i] - parr2[i]) > DBL_EPSILON)
                        num_failed++;
            }
            break;
    }

    return num_failed;
}

