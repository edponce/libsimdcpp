#include <stdlib.h>      // posix_memalign, rand
#include <limits.h>      // limits of fundamental integral types
#include <float.h>       // floating-point epsilons
#include "test_utils.h"


void create_test_array(const int arr_type, void ** const arr, const int num_elems, const int alignment)
{
    int mflag = -1;

    // Array allocation and initialization
    switch (arr_type) {
        case TEST_U16:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(unsigned short int));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((unsigned short int *)*arr)[i] = rand() % USHRT_MAX;
            break;
        case TEST_U32:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(unsigned int));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((unsigned int *)*arr)[i] = rand() % UINT_MAX;
            break;
        case TEST_U64:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(unsigned long int));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((unsigned long int *)*arr)[i] = rand() % ULONG_MAX;
            break;
        case TEST_I16:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(short int));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((short int *)*arr)[i] = rand() % SHRT_MAX;
            break;
        case TEST_I32:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(int));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((int *)*arr)[i] = rand() % INT_MAX;
            break;
        case TEST_I64:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(long int));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((long int *)*arr)[i] = rand() % LONG_MAX;
            break;
        case TEST_FLT:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(float));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((float *)*arr)[i] = (rand() % RAND_MAX) / (float)RAND_MAX;
            break;
        case TEST_DBL:
            mflag = posix_memalign((void **)arr, alignment, num_elems * sizeof(double));
            if (!mflag)
                for (int i = 0; i < num_elems; ++i)
                    ((double *)*arr)[i] = (rand() % RAND_MAX) / (double)RAND_MAX;
    }
}


// Validate test
int validate_test_arrays(const int arr_type, const void * const arr1, const void * const arr2, const int num_elems)
{
    int num_failed = 0;

    switch (arr_type) {
        case TEST_U16:
            for (int i = 0; i < num_elems; ++i)
                if (((unsigned short int *)arr1)[i] != ((unsigned short int *)arr2)[i])
                    num_failed++;
            break;
        case TEST_U32:
            for (int i = 0; i < num_elems; ++i)
                if (((unsigned int *)arr1)[i] != ((unsigned int *)arr2)[i])
                    num_failed++;
            break;
        case TEST_U64:
            for (int i = 0; i < num_elems; ++i)
                if (((unsigned long int *)arr1)[i] != ((unsigned long int *)arr2)[i])
                    num_failed++;
            break;
        case TEST_I16:
            for (int i = 0; i < num_elems; ++i)
                if (((short int *)arr1)[i] != ((short int *)arr2)[i])
                    num_failed++;
            break;
        case TEST_I32:
            for (int i = 0; i < num_elems; ++i)
                if (((int *)arr1)[i] != ((int *)arr2)[i])
                    num_failed++;
            break;
        case TEST_I64:
            for (int i = 0; i < num_elems; ++i)
                if (((long int *)arr1)[i] != ((long int *)arr2)[i])
                    num_failed++;
            break;
        case TEST_FLT:
            for (int i = 0; i < num_elems; ++i)
                if ((((float *)arr1)[i] - ((float *)arr2)[i]) > FLT_EPSILON)
                    num_failed++;
            break;
        case TEST_DBL:
            for (int i = 0; i < num_elems; ++i)
                if ((((double *)arr1)[i] - ((double *)arr2)[i]) > DBL_EPSILON)
                    num_failed++;
    }

    return num_failed;
}

