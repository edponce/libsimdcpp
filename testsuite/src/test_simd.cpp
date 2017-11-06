#include "simd.h"
#if defined(SIMD_MODE)


#include <stdio.h>
#include <stdlib.h>      // free, NULL
#include <stdint.h>
#include <math.h>        // sqrt, abs, floor, ceil
#include <limits.h>      // limits of fundamental integral types
#include "test_utils.h"
#include "test_simd.h"

#include <iostream>
using std::cout;
using std::endl;


// Deallocate dynamic memory and nullify pointer
#define FREE(p) free(p); p = NULL


int test_simd_add_sub()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_add_16(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_add_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_add_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_add_16(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_add_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_add_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_add(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_add(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] + B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_sub_16(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_sub_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_sub_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_sub_16(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_sub_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_sub_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_sub(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_sub(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] - B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_fm_add_sub()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_load(C);
        vc = simd_fmadd(va, vb, vc);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i] + C[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_load(C);
        vc = simd_fmadd(va, vb, vc);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i] + C[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_load(C);
        vc = simd_fmsub(va, vb, vc);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i] - C[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_load(C);
        vc = simd_fmsub(va, vb, vc);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i] - C[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_mul()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_16(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_16(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_mul(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_mul(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] * B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems1 = SIMD_STREAMS_16;
        const int num_elems2 = SIMD_STREAMS_32;
        const TEST_TYPES test_type1 = TEST_I16;
        const TEST_TYPES test_type2 = TEST_I32;
        int16_t *A = NULL, *B = NULL;
        int32_t *C1 = NULL, *C2 = NULL;

        create_test_array(test_type1, (void **)&A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&C2, num_elems2, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_i16_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems2; ++i)
            C2[i] = (int32_t)A[i*2] * (int32_t)B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)C1, (void *)C2, num_elems2);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems1 = SIMD_STREAMS_32;
        const int num_elems2 = SIMD_STREAMS_64;
        const TEST_TYPES test_type1 = TEST_I32;
        const TEST_TYPES test_type2 = TEST_I64;
        int32_t *A = NULL, *B = NULL;
        int64_t *C1 = NULL, *C2 = NULL;

        create_test_array(test_type1, (void **)&A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&C2, num_elems2, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_i32_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems2; ++i)
            C2[i] = (int64_t)A[i*2] * (int64_t)B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)C1, (void *)C2, num_elems2);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems1 = SIMD_STREAMS_16;
        const int num_elems2 = SIMD_STREAMS_32;
        const TEST_TYPES test_type1 = TEST_U16;
        const TEST_TYPES test_type2 = TEST_U32;
        uint16_t *A = NULL, *B = NULL;
        uint32_t *C1 = NULL, *C2 = NULL;

        create_test_array(test_type1, (void **)&A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&C2, num_elems2, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_u16_32(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems2; ++i)
            C2[i] = (uint32_t)A[i*2] * (uint32_t)B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)C1, (void *)C2, num_elems2);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems1 = SIMD_STREAMS_32;
        const int num_elems2 = SIMD_STREAMS_64;
        const TEST_TYPES test_type1 = TEST_I32;
        const TEST_TYPES test_type2 = TEST_I64;
        uint32_t *A = NULL, *B = NULL;
        uint64_t *C1 = NULL, *C2 = NULL;

        create_test_array(test_type1, (void **)&A, num_elems1, alignment);
        create_test_array(test_type1, (void **)&B, num_elems1, alignment);
        create_test_array(test_type2, (void **)&C1, num_elems2, alignment);
        create_test_array(test_type2, (void **)&C2, num_elems2, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_mul_u32_64(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems2; ++i)
            C2[i] = (uint64_t)A[i*2] * (uint64_t)B[i*2];

        test_result += validate_test_arrays(test_type2, (void *)C1, (void *)C2, num_elems2);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_div_sqrt()
{

    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_div(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] / B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_div(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] / B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_sqrt(va);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = sqrt(A[i]);

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vc = simd_sqrt(va);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = sqrt(A[i]);

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_logic()
{

    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_and(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] & B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type1 = TEST_FLT;
        const TEST_TYPES test_type2 = TEST_I32;
        float *A = NULL, *C1 = NULL, *C2 = NULL;
        int32_t *B = NULL;

        create_test_array(test_type1, (void **)&A, num_elems, alignment);
        create_test_array(test_type2, (void **)&B, num_elems, alignment);
        create_test_array(test_type1, (void **)&C1, num_elems, alignment);
        create_test_array(test_type1, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_FLT vc = simd_and(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i) {
            int32_t *iA = (int32_t *)&A[i];
            int32_t iC = *iA & B[i];
            float *fC = (float *)&iC;
            C2[i] = *fC;
        }

        test_result += validate_test_arrays(test_type1, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type1 = TEST_DBL;
        const TEST_TYPES test_type2 = TEST_I64;
        double *A = NULL, *C1 = NULL, *C2 = NULL;
        int64_t *B = NULL;

        create_test_array(test_type1, (void **)&A, num_elems, alignment);
        create_test_array(test_type2, (void **)&B, num_elems, alignment);
        create_test_array(test_type1, (void **)&C1, num_elems, alignment);
        create_test_array(test_type1, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_DBL vc = simd_and(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i) {
            int64_t *iA = (int64_t *)&A[i];
            int64_t iC = *iA & B[i];
            double *fC = (double *)&iC;
            C2[i] = *fC;
        }

        test_result += validate_test_arrays(test_type1, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_or(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] | B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_xor(va, vb);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = A[i] ^ B[i];

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_shift()
{

    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        int32_t n = (SIMD_WIDTH_BITS / num_elems);
        for (int32_t shft = 0; shft < n; ++shft) {
            SIMD_INT vc = simd_sll_16(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < num_elems; ++i)
                C2[i] = A[i] << shft;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        int32_t n = (SIMD_WIDTH_BITS / num_elems);
        for (int32_t shft = 0; shft < n; ++shft) {
            SIMD_INT vc = simd_sll_32(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < num_elems; ++i)
                C2[i] = A[i] << shft;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        int32_t n = (SIMD_WIDTH_BITS / num_elems);
        for (int32_t shft = 0; shft < n; ++shft) {
            SIMD_INT vc = simd_sll_64(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < num_elems; ++i)
                C2[i] = A[i] << shft;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_U8;
        uint8_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        for (int32_t shft = 0; shft <= num_elems; ++shft) {
            SIMD_INT vc = simd_sll_128(va, shft);
            simd_store(C1, vc);

            for (int i = shft; i < num_elems; ++i)
                C2[i] = A[i - shft];
            for (int i = 0; i < shft; ++i)
                C2[i] = 0;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_U16;
        uint16_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        int32_t n = (SIMD_WIDTH_BITS / num_elems);
        for (int32_t shft = 0; shft < n; ++shft) {
            SIMD_INT vc = simd_srl_16(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < num_elems; ++i)
                C2[i] = A[i] >> shft;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_U32;
        uint32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        int32_t n = (SIMD_WIDTH_BITS / num_elems);
        for (int32_t shft = 0; shft < n; ++shft) {
            SIMD_INT vc = simd_srl_32(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < num_elems; ++i)
                C2[i] = A[i] >> shft;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_U64;
        uint64_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        int32_t n = (SIMD_WIDTH_BITS / num_elems);
        for (int32_t shft = 0; shft < n; ++shft) {
            SIMD_INT vc = simd_srl_64(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < num_elems; ++i)
                C2[i] = A[i] >> shft;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_U8;
        uint8_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        for (int32_t shft = 0; shft <= num_elems; ++shft) {
            SIMD_INT vc = simd_srl_128(va, shft);
            simd_store(C1, vc);

            for (int i = 0; i < (num_elems - shft); ++i)
                C2[i] = A[i + shft];
            for (int i = num_elems - shft; i < num_elems; ++i)
                C2[i] = 0;

            test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);
        }

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_merge()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_merge_lo(va, vb);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i];
            C2[i + mid] = B[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_merge_lo(va, vb);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i];
            C2[i + mid] = B[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_merge_lo(va, vb);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i];
            C2[i + mid] = B[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vb = simd_load(B);
        SIMD_INT vc = simd_merge_hi(va, vb);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = B[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vb = simd_load(B);
        SIMD_FLT vc = simd_merge_hi(va, vb);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = B[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *B = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vb = simd_load(B);
        SIMD_DBL vc = simd_merge_hi(va, vb);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = B[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(B);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_pack()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_I8;
        int8_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_pack_8(va);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i * 2];
            C2[i + mid] = A[i * 2 + 1];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_pack_16(va);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i * 2];
            C2[i + mid] = A[i * 2 + 1];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_pack_32(va);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i * 2];
            C2[i + mid] = A[i * 2 + 1];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_pack(va);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i * 2];
            C2[i + mid] = A[i * 2 + 1];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    return test_result;
}


int test_simd_shuffle()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, XCHG);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_8;
        const TEST_TYPES test_type = TEST_I8;
        int8_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, XCHG8);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; i+=2) {
            C2[i] = A[i + 1];
            C2[i + 1] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_16;
        const TEST_TYPES test_type = TEST_I16;
        int16_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, XCHG16);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; i+=2) {
            C2[i] = A[i + 1];
            C2[i + 1] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, XCHG32);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; i+=2) {
            C2[i] = A[i + 1];
            C2[i + 1] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_I64;
        int64_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, XCHG64);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; i+=2) {
            C2[i] = A[i + 1];
            C2[i + 1] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, DUPL);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i];
            C2[i + mid] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_INT vc = simd_shuffle(va, DUPH);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = A[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_shuffle(va, XCHG);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_shuffle(va, XCHG32);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; i+=2) {
            C2[i] = A[i + 1];
            C2[i + 1] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_shuffle(va, XCHG64);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; i+=2) {
            ((double *)C2)[i] = ((double *)A)[i + 1];
            ((double *)C2)[i + 1] = ((double *)A)[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_shuffle(va, DUPL);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i];
            C2[i + mid] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_FLT va = simd_load(A);
        SIMD_FLT vc = simd_shuffle(va, DUPH);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = A[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vc = simd_shuffle(va, XCHG);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vc = simd_shuffle(va, XCHG64);
        simd_store(C1, vc);

        for (int i = 0; i < num_elems; i+=4) {
            C2[i] = A[i + 1];
            C2[i + 1] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vc = simd_shuffle(va, DUPL);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i];
            C2[i + mid] = A[i];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        double *A = NULL, *C1 = NULL, *C2 = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_DBL va = simd_load(A);
        SIMD_DBL vc = simd_shuffle(va, DUPH);
        simd_store(C1, vc);

        const int mid = num_elems / 2;
        for (int i = 0; i < mid; ++i) {
            C2[i] = A[i + mid];
            C2[i + mid] = A[i + mid];
        }

        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
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
        int *A = NULL;
        float *C1 = NULL, *C2 = NULL;

        create_test_array(TEST_I32, (void **)&A, SIMD_STREAMS_32, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_FLT vc = simd_cvt_i32_f32(va);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = (float)A[i];

        simd_store(C1, vc);
        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    // Double
    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        int *A = NULL;
        double *C1 = NULL, *C2 = NULL;

        create_test_array(TEST_I32, (void **)&A, SIMD_STREAMS_32, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_DBL vc = simd_cvt_i32_f64(va);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = (double)A[i];

        simd_store(C1, vc);
        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
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
        long int *A = NULL;
        float *C1 = NULL, *C2 = NULL;

        create_test_array(TEST_U64, (void **)&A, SIMD_STREAMS_64, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_FLT vc = simd_cvt_i64_f32(va);

        for (int i = 0; i < num_elems/2; ++i)
            C2[i] = (float)A[i];
        for (int i = 0; i < num_elems/2; ++i)
            C2[num_elems/2 + i] = 0.0;

        simd_store(C1, vc);
        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
    }

    // Double
    {
        const int num_elems = SIMD_STREAMS_64;
        const TEST_TYPES test_type = TEST_DBL;
        long int *A = NULL;
        double *C1 = NULL, *C2 = NULL;

        create_test_array(TEST_U64, (void **)&A, SIMD_STREAMS_64, alignment);
        create_test_array(test_type, (void **)&C1, num_elems, alignment);
        create_test_array(test_type, (void **)&C2, num_elems, alignment);

        SIMD_INT va = simd_load(A);
        SIMD_DBL vc = simd_cvt_i64_f64(va);

        for (int i = 0; i < num_elems; ++i)
            C2[i] = (double)A[i];

        simd_store(C1, vc);
        test_result += validate_test_arrays(test_type, (void *)C1, (void *)C2, num_elems);

        FREE(A);
        FREE(C1);
        FREE(C2);
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
        int *A = NULL, *B = NULL;
        const int val = rand() % INT_MAX;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);

        SIMD_INT va = simd_set(val);

        for (int i = 0; i < num_elems; ++i)
            B[i] = val;

        simd_store(A, va);
        test_result += validate_test_arrays(test_type, (void *)A, (void *)B, num_elems);

        FREE(A);
        FREE(B);
    }

    return test_result;
}


int test_simd_loadstore()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        simd_store(B, va);
        test_result += validate_test_arrays(test_type, (void *)A, (void *)B, num_elems);

        FREE(A);
        FREE(B);
    }

    // Float
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);

        SIMD_FLT va = simd_load(A);

        simd_store(B, va);
        test_result += validate_test_arrays(test_type, (void *)A, (void *)B, num_elems);

        FREE(A);
        FREE(B);
    }

    return test_result;
}


int test_simd_loadstoreu()
{
    int test_result = 0;
    const int alignment = SIMD_WIDTH_BYTES;

    // Integer
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_I32;
        int32_t *A = NULL, *B = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);

        SIMD_INT va = simd_load(A);

        simd_store(B, va);
        test_result += validate_test_arrays(test_type, (void *)A, (void *)B, num_elems);

        FREE(A);
        FREE(B);
    }

    // Float
    {
        const int num_elems = SIMD_STREAMS_32;
        const TEST_TYPES test_type = TEST_FLT;
        float *A = NULL, *B = NULL;

        create_test_array(test_type, (void **)&A, num_elems, alignment);
        create_test_array(test_type, (void **)&B, num_elems, alignment);

        SIMD_FLT va = simd_load(A);

        simd_store(B, va);
        test_result += validate_test_arrays(test_type, (void *)A, (void *)B, num_elems);

        FREE(A);
        FREE(B);
    }

    return test_result;
}


#endif  // SIMD_MODE

