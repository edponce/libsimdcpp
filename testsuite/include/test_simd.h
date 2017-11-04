#ifndef _TEST_SIMD_H
#define _TEST_SIMD_H


#include "simd.h"
#if defined(SIMD_MODE)


/*!
 *  \addtogroup Testsuite Testsuite
 *  \{
 *
 *    \defgroup Testcases Test cases
 *    \brief Test cases
 *    \{
 *
 *  \fn int test_simd_add_sub(void)
 *  \brief Add and subtract test cases
 *  Add/subtract signed/unsigned 16/32/64-bit integers and single/double-precision floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_fm_add_sub(void)
 *  \brief Fused-multiply add and subtract test cases
 *  Fused multiply-add/subtract single/double-precision floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_mul(void)
 *  \brief Multiply test cases
 *  Multiply signed/unsigned 16/32/64-bit integers and single/double-precision floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_div_sqrt(void)
 *  \brief Divide and square root test cases
 *  Divide/sqrt single/double-precision floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_logic(void)
 *  \brief Logical test cases
 *  Logical and/or/xor for integers and floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_shift(void)
 *  \brief Shift test cases
 *  Shift left/right 16/32/64/128-bit integers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_merge(void)
 *  \brief Merge test cases
 *  Merge low/high parts from pair of integers/floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_pack(void)
 *  \brief Pack test cases
 *  Pack 8/16/32-bit integers and single-precision floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *
 *  \fn int test_simd_shuffle(void)
 *  \brief Shuffle test cases
 *  Shuffle 16/32/64-bit integers and single/double-precision floating-point numbers
 *  \return Test result, 0 = PASSED and # = FAILED
 *
 *    \}
 *
 *  \}
 */


int test_simd_add_sub(void);
int test_simd_fm_add_sub(void);
int test_simd_mul(void);
int test_simd_div_sqrt(void);
int test_simd_logic(void);
int test_simd_shift(void);
int test_simd_merge(void);
int test_simd_pack(void);
int test_simd_shuffle(void);
//int test_simd_cvt_i32_fp();
//int test_simd_cvt_u64_fp();
//int test_simd_set_32();
//int test_simd_loadstore(void);
//int test_simd_loadstoreu(void);


#endif  // SIMD_MODE


#endif  // _TEST_SIMD_H

