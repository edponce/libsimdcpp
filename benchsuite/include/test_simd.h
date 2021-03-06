#ifndef _TEST_SIMD_H
#define _TEST_SIMD_H


#include "simd.h"
#if defined(SIMD_MODE)


int test_simd_add_classic(int, int);
int test_simd_add_func(int, int);
int test_simd_add_oo(int, int);
int test_simd_loop_dependence_classic(int, int);
int test_simd_loop_dependence(int, int);
int test_simd_loop_dependence2(int, int);


#endif  // SIMD_MODE


#endif  // _TEST_SIMD_H

