#include <stdio.h>
#include <stdlib.h>    // posix_memalign
#include "simd.h"


int main()
{
    int result = 0;
    int mflag = 0;
    const int alignment = SIMD_WIDTH_BYTES;
    const int num_elems = SIMD_STREAMS_32;
    int *arr_A = NULL, *arr_B = NULL, *arr_C = NULL;

    printf("Alignment: %d\n", alignment);
    printf("Num. elems: %d\n", num_elems);

    mflag = posix_memalign((void **)&arr_A, alignment, num_elems * sizeof(int));
    mflag = posix_memalign((void **)&arr_B, alignment, num_elems * sizeof(int));
    mflag = posix_memalign((void **)&arr_C, alignment, num_elems * sizeof(int));

    for (int i = 0; i < num_elems; ++i) {
        arr_A[i] = 1;
        arr_B[i] = i;
    }

    SIMD_INT va = simd_load(arr_A);
    SIMD_INT vb = simd_load(arr_B);

    SIMD_INT vc = simd_add_i32(va, vb);

    simd_store(arr_C, vc);

    for (int i = 0; i < num_elems; ++i) {
        if (arr_C[i] != (arr_A[i] + arr_B[i]))
            result += 1;
        else
            printf("%d\n", arr_C[i]);
    }

    free(arr_A);
    free(arr_B);
    free(arr_C);

    return result;
}

