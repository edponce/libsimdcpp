#include "simd.h"
#if defined(SIMD_MODE)


#include <stdio.h>
#include <stdlib.h>      // free
#include <stdint.h>
#include <math.h>        // sqrt, abs, floor, ceil
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] + arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] - arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        float *arr_A = NULL, *arr_B = NULL, *arr_C = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_load(arr_C);
        vc = simd_fmadd(va, vb, vc);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] + arr_C[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_load(arr_C);
        vc = simd_fmadd(va, vb, vc);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] + arr_C[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_B = NULL, *arr_C = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_load(arr_C);
        vc = simd_fmsub(va, vb, vc);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] - arr_C[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_B = NULL, *arr_C = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vb = simd_load(arr_B);
        SIMD_DBL vc = simd_load(arr_C);
        vc = simd_fmsub(va, vb, vc);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i] - arr_C[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    return test_result;
}


int32_t test_simd_mul(void)
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
        SIMD_INT vc = simd_mul_16(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_mul_32(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_mul_64(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_mul_16(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_mul_32(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_mul_64(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_FLT vc = simd_mul(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] * arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems1 = SIMD_STREAMS_16;
        const int32_t num_elems2 = SIMD_STREAMS_32;
        const TEST_TYPES test_type1 = TEST_I16;
        const TEST_TYPES test_type2 = TEST_I32;
        int16_t *arr_A = NULL, *arr_B = NULL;
        int32_t *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type1, (void **)&arr_A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&arr_B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&arr_C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&arr_C2, num_elems2, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_i16_32(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems2; ++i)
            arr_C2[i] = (int32_t)arr_A[i*2] * (int32_t)arr_B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)arr_C1, (void *)arr_C2, num_elems2);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems1 = SIMD_STREAMS_32;
        const int32_t num_elems2 = SIMD_STREAMS_64;
        const TEST_TYPES test_type1 = TEST_I32;
        const TEST_TYPES test_type2 = TEST_I64;
        int32_t *arr_A = NULL, *arr_B = NULL;
        int64_t *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type1, (void **)&arr_A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&arr_B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&arr_C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&arr_C2, num_elems2, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_i32_64(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems2; ++i)
            arr_C2[i] = (int64_t)arr_A[i*2] * (int64_t)arr_B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)arr_C1, (void *)arr_C2, num_elems2);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems1 = SIMD_STREAMS_16;
        const int32_t num_elems2 = SIMD_STREAMS_32;
        const TEST_TYPES test_type1 = TEST_U16;
        const TEST_TYPES test_type2 = TEST_U32;
        uint16_t *arr_A = NULL, *arr_B = NULL;
        uint32_t *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type1, (void **)&arr_A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&arr_B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&arr_C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&arr_C2, num_elems2, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_u16_32(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems2; ++i)
            arr_C2[i] = (uint32_t)arr_A[i*2] * (uint32_t)arr_B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)arr_C1, (void *)arr_C2, num_elems2);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems1 = SIMD_STREAMS_32;
        const int32_t num_elems2 = SIMD_STREAMS_64;
        const TEST_TYPES test_type1 = TEST_I32;
        const TEST_TYPES test_type2 = TEST_I64;
        uint32_t *arr_A = NULL, *arr_B = NULL;
        uint64_t *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type1, (void **)&arr_A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&arr_B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&arr_C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&arr_C2, num_elems2, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_INT vc = simd_mul_u32_64(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems2; ++i)
            arr_C2[i] = (uint64_t)arr_A[i*2] * (uint64_t)arr_B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)arr_C1, (void *)arr_C2, num_elems2);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    return test_result;
}


int32_t test_simd_div_sqrt(void)
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
        SIMD_FLT vc = simd_div(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] / arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_DBL vc = simd_div(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] / arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vc = simd_sqrt(va);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = sqrt(arr_A[i]);

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_DBL vc = simd_sqrt(va);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = sqrt(arr_A[i]);

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    return test_result;
}


int32_t test_simd_logic(void)
{

    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

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
        SIMD_INT vc = simd_and(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] & arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type1 = TEST_FLT;
        const TEST_TYPES test_type2 = TEST_I32;
        float *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;
        int32_t *arr_B = NULL;

        create_test_array(test_type1, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type2, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type1, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type1, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_FLT vc = simd_and(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i) {
            int32_t *iA = (int32_t *)&arr_A[i];
            int32_t iC = *iA & arr_B[i];
            float *fC = (float *)&iC;
            arr_C2[i] = *fC;
        }

        test_result += validate_test_arrays(test_type1, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type1 = TEST_DBL;
        const TEST_TYPES test_type2 = TEST_I64;
        double *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;
        int64_t *arr_B = NULL;

        create_test_array(test_type1, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type2, (void **)&arr_B, num_elems, alignment);
        create_test_array(test_type1, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type1, (void **)&arr_C2, num_elems, alignment);

        SIMD_DBL va = simd_load(arr_A);
        SIMD_INT vb = simd_load(arr_B);
        SIMD_DBL vc = simd_and(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i) {
            int64_t *iA = (int64_t *)&arr_A[i];
            int64_t iC = *iA & arr_B[i];
            double *fC = (double *)&iC;
            arr_C2[i] = *fC;
        }

        test_result += validate_test_arrays(test_type1, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_or(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] | arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_xor(va, vb);
        simd_store(arr_C1, vc);

        for (int32_t i = 0; i < num_elems; ++i)
            arr_C2[i] = arr_A[i] ^ arr_B[i];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    return test_result;
}


int32_t test_simd_shift(void)
{

    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft < (SIMD_WIDTH_BITS / num_elems); ++shft) {
            SIMD_INT vc = simd_sll_16(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < num_elems; ++i)
                arr_C2[i] = arr_A[i] << shft;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft < (SIMD_WIDTH_BITS / num_elems); ++shft) {
            SIMD_INT vc = simd_sll_32(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < num_elems; ++i)
                arr_C2[i] = arr_A[i] << shft;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft < (SIMD_WIDTH_BITS / num_elems); ++shft) {
            SIMD_INT vc = simd_sll_64(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < num_elems; ++i)
                arr_C2[i] = arr_A[i] << shft;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_U8;
        uint8_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft <= num_elems; ++shft) {
            SIMD_INT vc = simd_sll_128(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = shft; i < num_elems; ++i)
                arr_C2[i] = arr_A[i - shft];
            for (int32_t i = 0; i < shft; ++i)
                arr_C2[i] = 0;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft < (SIMD_WIDTH_BITS / num_elems); ++shft) {
            SIMD_INT vc = simd_srl_16(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < num_elems; ++i)
                arr_C2[i] = arr_A[i] >> shft;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft < (SIMD_WIDTH_BITS / num_elems); ++shft) {
            SIMD_INT vc = simd_srl_32(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < num_elems; ++i)
                arr_C2[i] = arr_A[i] >> shft;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft < (SIMD_WIDTH_BITS / num_elems); ++shft) {
            SIMD_INT vc = simd_srl_64(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < num_elems; ++i)
                arr_C2[i] = arr_A[i] >> shft;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_U8;
        uint8_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);

        for (int32_t shft = 0; shft <= num_elems; ++shft) {
            SIMD_INT vc = simd_srl_128(va, shft);
            simd_store(arr_C1, vc);

            for (int32_t i = 0; i < (num_elems - shft); ++i)
                arr_C2[i] = arr_A[i + shft];
            for (int32_t i = num_elems - shft; i < num_elems; ++i)
                arr_C2[i] = 0;

            test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);
        }

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    return test_result;
}


int32_t test_simd_merge(void)
{
    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

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
        SIMD_INT vc = simd_merge_lo(va, vb);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i) {
            arr_C2[i] = arr_A[i];
            arr_C2[i + mid] = arr_B[i];
        }

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_FLT vc = simd_merge_lo(va, vb);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i) {
            arr_C2[i] = arr_A[i];
            arr_C2[i + mid] = arr_B[i];
        }

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_DBL vc = simd_merge_lo(va, vb);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i) {
            arr_C2[i] = arr_A[i];
            arr_C2[i + mid] = arr_B[i];
        }

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
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
        SIMD_INT vc = simd_merge_hi(va, vb);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i) {
            arr_C2[i] = arr_A[i + mid];
            arr_C2[i + mid] = arr_B[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

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
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i) {
            arr_C2[i] = arr_A[i + mid];
            arr_C2[i + mid] = arr_B[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

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
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i) {
            arr_C2[i] = arr_A[i + mid];
            arr_C2[i + mid] = arr_B[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_B);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    return test_result;
}


int32_t test_simd_pack(void)
{
    int32_t test_result = 0;
    const int32_t alignment = SIMD_WIDTH_BYTES;

    {
        const int32_t num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_I8;
        int8_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vc = simd_pack_8(va);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i)
            arr_C2[i] = arr_A[i * 2];
        for (int32_t i = mid, j = 1; i < num_elems; ++i, j+=2)
            arr_C2[i] = arr_A[j];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vc = simd_pack_16(va);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i)
            arr_C2[i] = arr_A[i * 2];
        for (int32_t i = mid, j = 1; i < num_elems; ++i, j+=2)
            arr_C2[i] = arr_A[j];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_INT va = simd_load(arr_A);
        SIMD_INT vc = simd_pack_32(va);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i)
            arr_C2[i] = arr_A[i * 2];
        for (int32_t i = mid, j = 1; i < num_elems; ++i, j+=2)
            arr_C2[i] = arr_A[j];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
    }

    {
        const int32_t num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *arr_A = NULL, *arr_C1 = NULL, *arr_C2 = NULL;

        create_test_array(test_type, (void **)&arr_A, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C1, num_elems, alignment);
        create_test_array(test_type, (void **)&arr_C2, num_elems, alignment);

        SIMD_FLT va = simd_load(arr_A);
        SIMD_FLT vc = simd_pack(va);
        simd_store(arr_C1, vc);

        const int32_t mid = num_elems / 2;
        for (int32_t i = 0; i < mid; ++i)
            arr_C2[i] = arr_A[i * 2];
        for (int32_t i = mid, j = 1; i < num_elems; ++i, j+=2)
            arr_C2[i] = arr_A[j];

        test_result += validate_test_arrays(test_type, (void *)arr_C1, (void *)arr_C2, num_elems);

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
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

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
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

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
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

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
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

        FREE(arr_A);
        FREE(arr_C1);
        FREE(arr_C2);
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

        FREE(arr_A);
        FREE(arr_B);
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

        FREE(arr_A);
        FREE(arr_B);
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

        FREE(arr_A);
        FREE(arr_B);
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

        FREE(arr_A);
        FREE(arr_B);
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

        FREE(arr_A);
        FREE(arr_B);
    }

    return test_result;
}


#endif  // SIMD_MODE

