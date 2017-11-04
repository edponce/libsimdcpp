#ifndef _TEST_SUITE_H
#define _TEST_SUITE_H


/*!
 *  \addtogroup Testsuite Testsuite
 *  \brief Test suite control 
 *  \{
 *
 *
 *  \}
 */


#include "test_simd.h"


// Setup handler of tests to run
typedef int (*test_handler)();
struct TEST_T {
    test_handler test_func;
    const char *test_name;
};


// Array of test cases
struct TEST_T TESTS[] =
{
    { test_simd_add_sub, "Add/subtract signed/unsigned 16/32/64-bit integers and single/double-precision floating-point numbers" },
    { test_simd_fm_add_sub, "Fused multiply-add/subtract single/double-precision floating-point numbers" },
    { test_simd_mul, "Multiply signed/unsigned 16/32/64-bit integers and single/double-precision floating-point numbers" },
    { test_simd_div_sqrt, "Divide/sqrt single/double-precision floating-point numbers" },
    { test_simd_logic, "Logical and/or/xor for integers and floating-point numbers" },
    { test_simd_shift, "Shift left/right 16/32/64/128-bit integers" },
    { test_simd_merge, "Merge low/high parts from pair of integers/floating-point numbers" },
    { test_simd_pack, "Pack 8/16/32-bit integers and single-precision floating-point numbers" },
    { test_simd_shuffle, "Shuffle 16/32/64-bit integers and single/double-precision floating-point numbers" },
    //{ test_simd_cvt_i32_fp, "Convert 32-bit integers to 32/64-bit floating-point" },
    //{ test_simd_cvt_u64_fp, "Convert unsigned 64-bit integers to 32/64-bit floating-point" },
    //{ test_simd_set_32, "Broadcast 32-bit integers to all elements" },
    //{ test_simd_loadstore, "Aligned loads/stores" },
    //{ test_simd_loadstoreu, "Unaligned loads/stores" }
};


const int MAX_WORKERS = 4;
const int RUNS_PER_TEST = 10;


int test_suite(const struct TEST_T * const, const int, const int);
pid_t create_workers(int * const, const int);
int manager_main(int * const, int * const, const int, const int);
int worker_main(int * const, int * const, const struct TEST_T * const, const int);
int cancel_workers(int * const, const int);


#endif  // _TEST_SUITE_H

