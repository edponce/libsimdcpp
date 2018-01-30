#include <stdlib.h>  // posix_memalign, rand
#include <stdint.h>
#include <limits.h>  // limits of fundamental integral types
#include <float.h>   // floating-point epsilons
#include <math.h>    // fabs
#include "test_utils.h"


void create_empty_array(const TEST_TYPES test_type, void ** const arr, const int num_elems, const int alignment)
{
    switch (test_type) {
        case TEST_I8:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(int8_t));
            break;
        case TEST_I16:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(int16_t));
            break;
        case TEST_I32:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(int32_t));
            break;
        case TEST_I64:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(int64_t));
            break;
        case TEST_U8:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(uint8_t));
            break;
        case TEST_U16:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(uint16_t));
            break;
        case TEST_U32:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(uint32_t));
            break;
        case TEST_U64:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(uint64_t));
            break;
        case TEST_FLT:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(float));
            break;
        case TEST_DBL:
            posix_memalign((void **)arr, alignment, num_elems * sizeof(double));
            break;
    }
}


void create_test_array(const TEST_TYPES test_type, void ** const arr, const int num_elems, const int alignment)
{
    switch (test_type) {
        case TEST_I8:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int8_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int8_t *)*arr)[i] = (int8_t)(rand() % SCHAR_MAX);
            break;
        case TEST_I16:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int16_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int16_t *)*arr)[i] = (int16_t)(rand() % SHRT_MAX);
            break;
        case TEST_I32:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int32_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int32_t *)*arr)[i] = (int32_t)(rand() % INT_MAX);
            break;
        case TEST_I64:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(int64_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int64_t *)*arr)[i] = (int64_t)(rand() % LONG_MAX);
            break;
        case TEST_U8:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint8_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint8_t *)*arr)[i] = (uint8_t)(rand() % UCHAR_MAX);
            break;
        case TEST_U16:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint16_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint16_t *)*arr)[i] = (uint16_t)(rand() % USHRT_MAX);
            break;
        case TEST_U32:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint32_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint32_t *)*arr)[i] = (uint32_t)(rand() % UINT_MAX);
            break;
        case TEST_U64:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(uint64_t)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint64_t *)*arr)[i] = (uint64_t)(rand() % ULONG_MAX);
            break;
        case TEST_FLT:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(float)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((float *)*arr)[i] = (float)(rand() % RAND_MAX) / RAND_MAX;
            break;
        case TEST_DBL:
            if (!posix_memalign((void **)arr, alignment, num_elems * sizeof(double)))
                for (int32_t i = 0; i < num_elems; ++i)
                    ((double *)*arr)[i] = (double)(rand() % RAND_MAX) / RAND_MAX;
            break;
    }
}


int validate_test_arrays(const TEST_TYPES test_type, const void * const arr1, const void * const arr2, const int num_elems)
{
    int num_failed = 0;

    switch (test_type) {
        case TEST_I8:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((int8_t *)arr1)[i] != ((int8_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_I16:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((int16_t *)arr1)[i] != ((int16_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_I32:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((int32_t *)arr1)[i] != ((int32_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_I64:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((int64_t *)arr1)[i] != ((int64_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_U8:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((uint8_t *)arr1)[i] != ((uint8_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_U16:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((uint16_t *)arr1)[i] != ((uint16_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_U32:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((uint32_t *)arr1)[i] != ((uint32_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_U64:
            for (int32_t i = 0; i < num_elems; ++i)
                if (((uint64_t *)arr1)[i] != ((uint64_t *)arr2)[i])
                    num_failed++;
            break;
        case TEST_FLT:
            for (int32_t i = 0; i < num_elems; ++i)
                if (fabs(((float *)arr1)[i] - ((float *)arr2)[i]) > FLT_EPSILON)
                    num_failed++;
            break;
        case TEST_DBL:
            for (int32_t i = 0; i < num_elems; ++i)
                if (fabs(((double *)arr1)[i] - ((double *)arr2)[i]) > DBL_EPSILON)
                    num_failed++;
            break;
    }

    return num_failed;
}

