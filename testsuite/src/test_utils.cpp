#include <stdlib.h>      // posix_memalign, rand
#include <stdint.h>
#include <limits.h>      // limits of fundamental integral types
#include <float.h>       // floating-point epsilons
#include "test_utils.h"


void create_test_array(const int32_t arr_type, void ** const arr, const int32_t num_elems, const int32_t alignment)
{
    int32_t mflag = -1;

    // Array allocation and initialization
    switch (arr_type) {
        case TEST_U16:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(uint16_t));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint16_t *)*arr)[i] = rand() % USHRT_MAX;
            break;
        case TEST_U32:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(uint32_t));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint32_t *)*arr)[i] = rand() % UINT_MAX;
            break;
        case TEST_U64:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(uint64_t));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((uint64_t *)*arr)[i] = rand() % ULONG_MAX;
            break;
        case TEST_I16:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(int16_t));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int16_t *)*arr)[i] = rand() % SHRT_MAX;
            break;
        case TEST_I32:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(int));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int32_t *)*arr)[i] = rand() % INT_MAX;
            break;
        case TEST_I64:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(int64_t));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((int64_t *)*arr)[i] = rand() % LONG_MAX;
            break;
        case TEST_FLT:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(float));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((float *)*arr)[i] = (rand() % RAND_MAX) / (float)RAND_MAX;
            break;
        case TEST_DBL:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(double));
            if (!mflag)
                for (int32_t i = 0; i < num_elems; ++i)
                    ((double *)*arr)[i] = (rand() % RAND_MAX) / (double)RAND_MAX;
    }
}


// Validate test
int32_t validate_test_arrays(const int32_t arr_type, const void * const arr1, const void * const arr2, const int32_t num_elems)
{
    int32_t num_failed = 0;

    switch (arr_type) {
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
        case TEST_FLT:
            for (int32_t i = 0; i < num_elems; ++i)
                if ((((float *)arr1)[i] - ((float *)arr2)[i]) > FLT_EPSILON)
                    num_failed++;
            break;
        case TEST_DBL:
            for (int32_t i = 0; i < num_elems; ++i)
                if ((((double *)arr1)[i] - ((double *)arr2)[i]) > DBL_EPSILON)
                    num_failed++;
    }

    return num_failed;
}

