#include "simd.h"
#if defined(SIMD_MODE)


#include <stdio.h>
#include <stdlib.h>      // free
#include <stdint.h>
#include <limits.h>      // limits of fundamental integral types
#include "test_utils.h"
#include "test_simd.h"


int32_t test_simd_add_sub(void)
{
    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_add_16(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_add_32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_add_64(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_add_16(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_add_32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_add_64(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_add(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_add(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_sub_16(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_sub_32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_sub_64(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_sub_16(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_sub_32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_sub_64(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_sub(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_sub(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


int32_t test_simd_fm_add_sub(void)
{
    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_load(arr_C1);
        vc = simd_fmadd(va, vb, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] + arr_C1[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_load(arr_C1);
        vc = simd_fmadd(va, vb, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] + arr_C1[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_load(arr_C1);
        vc = simd_fmsub(va, vb, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] - arr_C1[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_load(arr_C1);
        vc = simd_fmsub(va, vb, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] - arr_C1[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


int32_t test_simd_mul(void)
{
    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mullo_i32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_i32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_i64(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }
/*
    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_u32(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_u64(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }
*/
    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_mul(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_mul(va, vb);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


// Merge low parts from pair of registers
int test_simd_merge_lo()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_merge_lo(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = arr_A[i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    // Float
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_merge_lo(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = arr_A[i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    // Double
    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_merge_lo(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = arr_A[i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = arr_B[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


// Merge high parts from pair of registers
int test_simd_merge_hi()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_merge_hi(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = arr_A[num_elems/2 + i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = arr_B[num_elems/2 + i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    // Float
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_merge_hi(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = arr_A[num_elems/2 + i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = arr_B[num_elems/2 + i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    // Double
    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_merge_hi(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = arr_A[num_elems/2 + i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = arr_B[num_elems/2 + i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


// Pack and merge the low 32-bits of 64-bit integers
int test_simd_packmerge_lo()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        long int *arr_A = NULL, *arr_B = NULL;
        int *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(TEST_I64, (void **)&arr_A, SIMD_STREAMS_64, alignment);
        create_test_array(TEST_I64, (void **)&arr_B, SIMD_STREAMS_64, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_packmerge_lo(va, vb);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = ((int *)arr_A)[2*i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = ((int *)arr_B)[2*i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


// Convert 32-bit integer to 32/64-bit floating-point
int test_simd_cvt_i32_fp()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Float
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        int *arr_A = NULL;
        float *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(TEST_I32, (void **)&arr_A, SIMD_STREAMS_32, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_FLT vc = simd_cvt_i32_f32(va);

        for (int i = 0; i < num_elems; ++i)
            arr_C2[i] = (float)arr_A[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    // Double
    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        int *arr_A = NULL;
        double *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(TEST_I32, (void **)&arr_A, SIMD_STREAMS_32, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_DBL vc = simd_cvt_i32_f64(va);

        for (int i = 0; i < num_elems; ++i)
            arr_C2[i] = (double)arr_A[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


// Convert unsigned 64-bit integer to 32/64-bit floating-point
int test_simd_cvt_u64_fp()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Float
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        unsigned long int *arr_A = NULL;
        float *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(TEST_U64, (void **)&arr_A, SIMD_STREAMS_64, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_FLT vc = simd_cvt_u64_f32(va);

        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[i] = (float)arr_A[i];
        for (int i = 0; i < num_elems/2; ++i)
            arr_C2[num_elems/2 + i] = 0.0;

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    // Double
    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        unsigned long int *arr_A = NULL;
        double *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(TEST_U64, (void **)&arr_A, SIMD_STREAMS_64, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_DBL vc = simd_cvt_u64_f64(va);

        for (int i = 0; i < num_elems; ++i)
            arr_C2[i] = (double)arr_A[i];

        simd_store(arr_C1, vc);
        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_C1); arr_C1 = NULL;
        free(arr_C2); arr_C2 = NULL;
    }

    return test_result;
}


// Broadcast 32-bit integers to all elements
int test_simd_set_32()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int *arr_A = NULL, *arr_B = NULL;
        const int val = rand() % INT_MAX;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);

        SIMD_INT va = simd_set(val);

        for (int i = 0; i < num_elems; ++i)
            arr_B[i] = val;

        simd_store(arr_A, va);
        test_result += validate_test_arrays(test_type, (void *)arr_A, (void *)arr_B, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
    }

    return test_result;
}


int32_t test_simd_loadstore(void)
{
    int32_t test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *arr_A = NULL, *arr_B = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        simd_store(arr_B, va);
        test_result += validate_test_arrays(test_type, (void *)arr_A, (void *)arr_B, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
    }

    // Float
    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);

        simd_store(arr_B, va);
        test_result += validate_test_arrays(test_type, (void *)arr_A, (void *)arr_B, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
    }

    return test_result;
}


int32_t test_simd_loadstoreu(void)
{
    int32_t test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *arr_A = NULL, *arr_B = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        simd_store(arr_B, va);
        test_result += validate_test_arrays(test_type, (void *)arr_A, (void *)arr_B, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
    }

    // Float
    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);

        simd_store(arr_B, va);
        test_result += validate_test_arrays(test_type, (void *)arr_A, (void *)arr_B, num_elems);

        free(arr_A); arr_A = NULL;
        free(arr_B); arr_B = NULL;
    }

    return test_result;
}


#endif  // SIMD_MODE

