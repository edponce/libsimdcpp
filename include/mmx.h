#ifndef _MMX_H
#define _MMX_H


/*
 *  Support '_t' C datatypes
 */
#include <stdint.h>


/*
 *  Compiler and architecture specific settings
 */
#include "compiler_attributes.h"
#include "compiler_builtins.h"


/*
 *  Include supporting header files based on compiler and architecture
 */
#if defined(__clang__)
    //#include <x86intrin.h>
    #include <mmintrin.h>
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
    #include <mmintrin.h>
#elif defined(__GNUC__)
    //#include <x86intrin.h>
    #include <mmintrin.h>
#else
    #error "Compiler/architecture is not supported."
#endif


/*
 *  MMX 64-bit wide vector units
 *  Define constants required for SIMD module to function properly.
 *  NOTE: MMX only supports integer operations of 32 bits or less.
 *        To provide a single API, the 64-bit operations are actually an exact
 *        copy of its 32-bit implementation. Also, there is no support for
 *        unsigned integers, so signed integers are always assumed.
 *        Floating-point operations simply use float and double scalar datatypes.
 */
const int32_t SIMD_WIDTH_BITS = 64;
const int32_t SIMD_WIDTH_BYTES = SIMD_WIDTH_BITS / 8;
const int32_t SIMD_STREAMS_16 = SIMD_WIDTH_BYTES / 2;
const int32_t SIMD_STREAMS_32 = SIMD_WIDTH_BYTES / 4;
const int32_t SIMD_STREAMS_64 = SIMD_WIDTH_BYTES / 8;
typedef __m64  SIMD_INT;
typedef float  SIMD_FLT;
typedef double SIMD_DBL;


#define _SIMD_ALIGNED_ SIMD_ALIGNED(SIMD_WIDTH_BYTES)


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
/*!
 *  Add/sub for signed/unsigned 16/32/64-bit integers
 *  Does not use saturation arithmetic (wraps around)
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_add_i16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_pi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_pi32(va, vb); }

#define simd_add_i64(a,b) simd_add_i32(a,b)
#define simd_add_u16(a,b) simd_add_i16(a,b)
#define simd_add_u32(a,b) simd_add_i32(a,b)
#define simd_add_u64(a,b) simd_add_i32(a,b)

static SIMD_FUNC_INLINE
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return va + vb; }

static SIMD_FUNC_INLINE
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return va + vb; }

/*!
 *  Fused multiply-add for 32/64-bit floating-point elements
 */
static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    return va * vb + vc;
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    return va * vb + vc;
}

/*!
 *  Multiply signed 32-bit integers from each packed 64-bit elements
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mul(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT va_hi = _mm_srli_si64(va, 0x20);
    const int32_t sa_lo = _m_to_int(va);
    const int32_t sa_hi = _m_to_int(va_hi);

    const SIMD_INT vb_hi = _mm_srli_si64(vb, 0x20);
    const int32_t sb_lo = _m_to_int(vb);
    const int32_t sb_hi = _m_to_int(vb_hi);

    const int32_t sc_lo = sa_lo * sb_lo;
    const int32_t sc_hi = sa_hi * sb_hi;

    return _mm_set_pi32(sc_hi, sc_lo);
}
#define simd_mul_u32(a,b) simd_mul(a,b)
#define simd_mul_i32(a,b) simd_mul(a,b)
#define simd_mul_u64(a,b) simd_mul(a,b)
#define simd_mullo_i32(a,b) simd_mul(a,b)

static SIMD_FUNC_INLINE
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return (SIMD_FLT)(va * vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return (SIMD_DBL)(va * vb); }


/********************************
 *  Integral logical intrinsics
 ********************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_or_si64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_xor_si64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_and_si64(va, vb); }



/*****************************
 *  Shift/Shuffle intrinsics
 *****************************/
/*
 *  Shift left (logical) packed 32/64-bit integers
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_sll_32(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_pi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_32(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_pi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_64(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_si64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_64(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_si64(va, shft); }


/*
 *  Merge either low/high parts from pair of registers
 *  into a single register
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_unpacklo_pi32(va, vb); }
#define simd_packmerge_i32(a,b) simd_merge_lo(a,b)

static SIMD_FUNC_INLINE
SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_unpackhi_pi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{
    (void)vb;
    return va;
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
{
    (void)vb;
    return va;
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
{
    (void)va;
    return vb;
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
{
    (void)va;
    return vb;
}


/*******************
 *  Set intrinsics
 *******************/
/*
 *  Set vector to zero.
 */
static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_INT * const va)
{ *va = _mm_setzero_si64(); }

static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_FLT * const va)
{ *va = 0.0f; }

static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_DBL * const va)
{ *va = 0.0; }

/*
 *  Set 32-bit integers to either 32/64 slots.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int32_t sa)
{ return _mm_set1_pi32(sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint32_t sa)
{ return _mm_set1_pi32((int32_t)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const long int sa)
{ return _m_from_int((int32_t)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const long unsigned int sa)
{ return _m_from_int((int32_t)sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_set(const float sa)
{ return (SIMD_FLT)sa; }

static SIMD_FUNC_INLINE
SIMD_DBL simd_set(const double sa)
{ return (SIMD_DBL)sa; }

/*!
 *  Set vector given an array.
 *  Only required for non-contiguous 32-bit elements due to in-between padding,
 *  64-bit elements can use load instructions.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int32_t * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _m_from_int(sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm_set_pi32(sa[1], sa[0]);
    else
        return _mm_setzero_si64();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint32_t * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _m_from_int((int32_t)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm_set_pi32((int32_t)sa[1], (int32_t)sa[0]);
    else
        return _mm_setzero_si64();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const long int * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _m_from_int((int32_t)sa[0]);
    else
        return _mm_setzero_si64();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const long unsigned int * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _m_from_int((int32_t)sa[0]);
    else
        return _mm_setzero_si64();
}


/***********************
 *  Convert intrinsics
 ***********************/
/*!
 *  Convert lower 32-bit integer element
 *  to 32-bit floating-point element.
 */
static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
{ return (SIMD_FLT)_m_to_int(va); }

/*!
 *  Convert lower 32-bit integer element
 *  to 64-bit floating-point element.
 */
static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_i32_f64(const SIMD_INT va)
{ return (SIMD_DBL)_m_to_int(va); }
#define simd_cvt_u32_f32(a) simd_cvt_i32_f32(a)
#define simd_cvt_u32_f64(a) simd_cvt_i32_f64(a)
#define simd_cvt_u64_f32(a) simd_cvt_i32_f32(a)
#define simd_cvt_u64_f64(a) simd_cvt_i32_f64(a)


/********************
 *  Load intrinsics
 ********************/
static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int32_t * const sa)
{ return _mm_set_pi32(sa[1], sa[0]); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const uint32_t * const sa)
{ return _mm_set_pi32((int32_t)sa[1], (int32_t)sa[0]); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const long int * const sa)
{ return _mm_set_pi32((int32_t)sa[1], (int32_t)sa[0]); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const long unsigned int * const sa)
{ return _mm_set_pi32((int32_t)sa[1], (int32_t)sa[0]); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_load(const float * const sa)
{ return (SIMD_FLT)(*sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_load(const double * const sa)
{ return (SIMD_DBL)(*sa); }


/*******************************
 *  Store intrinsics
 *******************************/
static SIMD_FUNC_INLINE
void simd_store(int32_t * const sa, const SIMD_INT va)
{
    const SIMD_INT va_hi = _mm_srli_si64(va, 0x20);
    sa[0] = _m_to_int(va);
    sa[1] = _m_to_int(va_hi);
}

static SIMD_FUNC_INLINE
void simd_store(uint32_t * const sa, const SIMD_INT va)
{
    const SIMD_INT va_hi = _mm_srli_si64(va, 0x20);
    sa[0] = (uint32_t)_m_to_int(va);
    sa[1] = (uint32_t)_m_to_int(va_hi);
}

static SIMD_FUNC_INLINE
void simd_store(long int * const sa, const SIMD_INT va)
{
    const SIMD_INT va_hi = _mm_srli_si64(va, 0x20);
    sa[0] = (long int)_m_to_int(va);
    sa[1] = (long int)_m_to_int(va_hi);
}

static SIMD_FUNC_INLINE
void simd_store(long unsigned int * const sa, const SIMD_INT va)
{
    const SIMD_INT va_hi = _mm_srli_si64(va, 0x20);
    sa[0] = (long unsigned int)_m_to_int(va);
    sa[1] = (long unsigned int)_m_to_int(va_hi);
}

static SIMD_FUNC_INLINE
void simd_store(float * const sa, const SIMD_FLT va)
{ sa[0] = (float)va; }

static SIMD_FUNC_INLINE
void simd_store(double * const sa, const SIMD_DBL va)
{ sa[0] = (double)va; }


#endif  // _MMX_H

