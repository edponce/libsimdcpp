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


#include <sys/types.h> // pid_t
#include "test_simd.h"


// Setup handler of tests to run
typedef int (*test_handler)(int, int);
struct TEST_T {
    test_handler test_func;
    const char *test_name;
};


// Array of test cases
struct TEST_T TESTS[] =
{
    //{ test_simd_add_classic, "(Dummy warm-up) Add signed 32-bit integers" },
    { test_simd_add_classic, "(Classic) Add signed 32-bit integers" },
    { test_simd_add_func, "(SIMD function) Add signed 32-bit integers" },
    { test_simd_add_oo, "(SIMD OO) Add signed 32-bit integers" },
    //{ test_simd_loop_dependence_classic, "(Classic) Loop dependence" },
    //{ test_simd_loop_dependence, "(SIMD) Loop dependence" },
    //{ test_simd_loop_dependence2, "(SIMD) Loop dependence 2" },
};


const int MAX_WORKERS = 1;
const int RUNS_PER_TEST = 2;


int test_suite(const struct TEST_T * const, const int, const int);
pid_t create_workers(int * const, const int);
int manager_main(int * const, int * const, const int, const int);
int worker_main(int * const, int * const, const struct TEST_T * const, const int);
int cancel_workers(int * const, const int);


#endif  // _TEST_SUITE_H

