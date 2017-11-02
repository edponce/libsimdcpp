#ifndef _TEST_SIMD_H
#define _TEST_SIMD_H


#include "simd.h"
#if defined(SIMD_MODE)


int test_simd_add_sub(void);
int test_simd_fm_add_sub(void);
int test_simd_mul(void);
int test_simd_div_sqrt(void);
int test_simd_logic(void);
int test_simd_shift(void);
int test_simd_merge_lo();
int test_simd_merge_hi();
int test_simd_packmerge_lo();
int test_simd_cvt_i32_fp();
int test_simd_cvt_u64_fp();
int test_simd_set_32();
int test_simd_loadstore(void);
int test_simd_loadstoreu(void);


#endif  // SIMD_MODE


#endif  // _TEST_SIMD_H

