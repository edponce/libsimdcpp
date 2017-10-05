#ifndef _TEST_SUITE_H
#define _TEST_SUITE_H


// Setup handler of tests to run
typedef int (*test_handler)();
struct TEST_T {
    test_handler test_func;
    const char *test_name;
};


// Header files for test cases
#include "test_simd.h"


// Array of test cases
struct TEST_T TESTS[] =
{
    { test_simd_loadstore, "Aligned loads/stores" },
    { test_simd_fmadd, "Fused multiply-add" },
    { test_simd_mul_u64, "64-bit integer multiply" },
    { test_simd_packmerge_i32, "Pack and merge 32-bit integers" },
    { test_simd_cvt_i32_fp, "Convert 32-bit integers to 32/64-bit floating-point" },
    { test_simd_cvt_u64_fp, "Convert unsigned 64-bit integers to 32/64-bit floating-point" },
    { test_simd_merge_lo, "Merge low parts from pair of registers" },
    { test_simd_merge_hi, "Merge high parts from pair of registers" }
};


//////////////////////////////


#define MAX_WORKERS 4
#define MAX_RUNS_PER_TEST 10


int test_suite(const struct TEST_T * const, const int, const int);
pid_t create_workers(int * const, const int);
int manager_main(int * const, int * const, const int, const int);
int worker_main(int * const, int * const, const struct TEST_T * const, const int);
int cancel_workers(int * const, const int);


#endif  // _TEST_SUITE_H

