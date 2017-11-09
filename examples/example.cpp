#include <stdio.h>
#include <stdlib.h>   // free, posix_memalign, _Exit, EXIT_SUCCESS/FAILURE
#include "simd.h"
#include "environ.h"  // detectCPU, detectSIMD


int main()
{
    int result = 0;
    const int alignment = SIMD_WIDTH_BYTES;
    const int num_elems = SIMD_STREAMS_32;
    int *arr_A = NULL, *arr_B = NULL, *arr_C = NULL;

    detectCPU();
    detectSIMD();

    printf("Alignment: %d\n", alignment);
    printf("Num. elems: %d\n", num_elems);

    if (posix_memalign((void **)&arr_A, alignment, num_elems * sizeof(int)))
        _Exit(EXIT_FAILURE);
    if (posix_memalign((void **)&arr_B, alignment, num_elems * sizeof(int)))
        _Exit(EXIT_FAILURE);
    if (posix_memalign((void **)&arr_C, alignment, num_elems * sizeof(int)))
        _Exit(EXIT_FAILURE);

    for (int i = 0; i < num_elems; ++i) {
        arr_A[i] = 1;
        arr_B[i] = i;
    }

    SIMD_INT va = simd_load(arr_A);
    SIMD_INT vb = simd_load(arr_B);

    SIMD_INT vc = simd_add_32(va, vb);

    simd_store(arr_C, vc);

    for (int i = 0; i < num_elems; ++i) {
        if (arr_C[i] != (arr_A[i] + arr_B[i]))
            result += 1;
        else
            printf("%d\n", arr_C[i]);
    }

    free(arr_A); arr_A = NULL;
    free(arr_B); arr_B = NULL;
    free(arr_C); arr_C = NULL;

    return result;
}

