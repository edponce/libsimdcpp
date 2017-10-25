#ifndef _SCALAR_H
#define _SCALAR_H


/*
 *  Support '_t' C datatypes
 */
#include <stdint.h>


/*
 *  Compiler and architecture specific settings
 */
#include "compiler_attributes.h"
#include "compiler_intrinsics.h"


/*
 *  Include supporting header files based on compiler and architecture
 *  NOTE: currently only support x86_64, GCC and Intel compilers
 */
/*
#if defined(__clang__)
#elif defined(__GNUC__)
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
#else
    #error "Compiler/architecture is not supported."
#endif
*/


/*
 *  Disable SIMD for scalar mode, no vector units
 *  Define constants required for SIMD module to function properly.
 */
const int SIMD_WIDTH_BYTES = 8;
const int SIMD_STREAMS_16 = 1;
const int SIMD_STREAMS_32 = 1;
const int SIMD_STREAMS_64 = 1;
typedef int SIMD_INT;
typedef float SIMD_FLT;
typedef double SIMD_DBL;


/*
 *  Interface Legend
 *
 *  simd_*_iXX = signed XX-bit integers
 *  simd_*_uXX = unsigned XX-bit integers
 *  simd_*_fXX = floating-point XX-bit elements
 *  simd_*_XX  = unsigned/signed XX-bit integers
 *  simd_*_XX  = (set functions) specifies width to consider for integer types
 *  simd_*     = datatype obtained from function overloading and parameters
 */


/**************************
 *  Arithmetic intrinsics
 **************************/


/********************************
 *  Integral logical intrinsics
 ********************************/


/*****************************
 *  Shift/Shuffle intrinsics
 *****************************/


/*******************
 *  Set intrinsics
 *******************/


/***********************
 *  Convert intrinsics
 ***********************/


/********************
 *  Load intrinsics
 ********************/


/*******************************
 *  Store intrinsics
 *******************************/


#endif  // _SCALAR_H

