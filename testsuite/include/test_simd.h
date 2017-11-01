#ifndef _TEST_SIMD_H
#define _TEST_SIMD_H


#include "simd.h"
#if defined(SIMD_MODE)


int test_simd_loadstore();
int test_simd_add(void);
int test_simd_sub(void);
int test_simd_fmadd(void);
int test_simd_fmsub(void);
int test_simd_mul_u64();
int test_simd_packmerge_lo();
int test_simd_cvt_i32_fp();
int test_simd_cvt_u64_fp();
int test_simd_merge_lo();
int test_simd_merge_hi();
int test_simd_set_32();


#endif  // SIMD_MODE


#endif  // _TEST_SIMD_H

