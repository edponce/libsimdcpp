#ifndef _SSE4_2_H
#define _SSE4_2_H


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
//#   include <x86intrin.h>
#   include <nmmintrin.h>
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
#   include <nmmintrin.h>
#elif defined(__GNUC__)
//#   include <x86intrin.h>
#   include <nmmintrin.h>
#else
#   error "Compiler/architecture is not supported."
#endif


/*
 *  SSE4.2 128-bit wide vector units
 *  Define constants required for SIMD module to function properly.
 */
const int32_t SIMD_WIDTH_BITS = 128;
const int32_t SIMD_WIDTH_BYTES = SIMD_WIDTH_BITS / 8;
const int32_t SIMD_STREAMS_16 = SIMD_WIDTH_BYTES / 2;
const int32_t SIMD_STREAMS_32 = SIMD_WIDTH_BYTES / 4;
const int32_t SIMD_STREAMS_64 = SIMD_WIDTH_BYTES / 8;
typedef __m128i SIMD_INT;
typedef __m128  SIMD_FLT;
typedef __m128d SIMD_DBL;


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
{ return _mm_add_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_i64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_epi64(va, vb); }

/*!
 *  Add for unsigned 16-bit integers
 *  Uses saturation arithmetic (no wrap around)
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_add_u16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_adds_epu16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_u32(const SIMD_INT va, const SIMD_INT vb)
{
    uint32_t sa[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint32_t sb[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm_store_si128((SIMD_INT *)sa, va);
    _mm_store_si128((SIMD_INT *)sb, vb);

    for (int i = 0; i < SIMD_STREAMS_32; ++i)
        sa[i] += sb[i];

    return _mm_load_si128((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_add_u64(const SIMD_INT va, const SIMD_INT vb)
{
    uint64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint64_t sb[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm_store_si128((SIMD_INT *)sa, va);
    _mm_store_si128((SIMD_INT *)sb, vb);

    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        sa[i] += sb[i];

    return _mm_load_si128((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_add_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_add_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_i16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_i64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi64(va, vb); }

/*!
 *  Sub for unsigned 16-bit integers
 *  Uses saturation arithmetic (no wrap around)
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_sub_u16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_subs_epu16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_u32(const SIMD_INT va, const SIMD_INT vb)
{
    uint32_t sa[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint32_t sb[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm_store_si128((SIMD_INT *)sa, va);
    _mm_store_si128((SIMD_INT *)sb, vb);

    for (int i = 0; i < SIMD_STREAMS_32; ++i)
        sa[i] -= sb[i];

    return _mm_load_si128((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_u64(const SIMD_INT va, const SIMD_INT vb)
{
    uint64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint64_t sb[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm_store_si128((SIMD_INT *)sa, va);
    _mm_store_si128((SIMD_INT *)sb, vb);

    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        sa[i] -= sb[i];

    return _mm_load_si128((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_sub(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_sub_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_sub(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_sub_pd(va, vb); }

/*!
 *  Fused multiply-add/sub for 32/64-bit floating-point elements
 */
#if defined(__FMA__)
static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{ return _mm_fmadd_ps(va, vb, vc); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{ return _mm_fmadd_pd(va, vb, vc); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmsub(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{ return _mm_fmsub_ps(va, vb, vc); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmsub(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{ return _mm_fmsub_pd(va, vb, vc); }

#else
static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    const SIMD_FLT vab = _mm_mul_ps(va, vb);
    return _mm_add_ps(vab, vc);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    const SIMD_DBL vab = _mm_mul_pd(va, vb);
    return _mm_add_pd(vab, vc);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmsub(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    const SIMD_FLT vab = _mm_mul_ps(va, vb);
    return _mm_sub_ps(vab, vc);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmsub(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    const SIMD_DBL vab = _mm_mul_pd(va, vb);
    return _mm_sub_pd(vab, vc);
}
#endif

/*!
 *  Multiply low unsigned 32-bit integers from each packed 64-bit elements
 *  and store the unsigned 64-bit results
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mul_epu32(va, vb); }

/*!
 *  Multiply low signed 32-bit integers from each packed 64-bit elements
 *  and store the signed 64-bit results
 *  NOTE: requires at least SSE 4.1 for _mm_mul_epi32()
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mul_epi32(va, vb); }

/*!
 *  Perform 64-bit integer multiplication using 32-bit integers
 *  since vector extensions do not support 64-bit integer multiplication.
 *  x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
 *  NOTE: requires at least SSE 4.1 for _mm_mullo_epi32()
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u64(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT vmsk = _mm_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vtmp, vhi, vlo;

    vtmp = _mm_shuffle_epi32(vb, 0xB1); // shuffle multiplier
    vhi = _mm_mullo_epi32(va, vtmp);    // xl * yh, xh * yl
    vtmp = _mm_slli_epi64(vhi, 0x20);   // shift << 32
    vhi = _mm_add_epi64(vhi, vtmp);     // h = h1 + h2
    vhi = _mm_and_si128(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm_mul_epu32(va, vb);        // l = xl * yl

    return _mm_add_epi64(vlo, vhi);     // l + h
}

/*!
 *  Multiply packed 32-bit integers, produce intermediate 64-bit integers,
 *  and store the low 32-bit results
 *  NOTE: requires at least SSE 4.1 for _mm_mullo_epi32()
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mullo_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mullo_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_mul_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_mul_pd(va, vb); }


/********************************
 *  Integral logical intrinsics
 ********************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_or_si128(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_xor_si128(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_and_si128(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm_castps_si128(va);
    va_int = _mm_and_si128(va_int, vb);
    return _mm_castsi128_ps(va_int);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm_castpd_si128(va);
    va_int = _mm_and_si128(va_int, vb);
    return _mm_castsi128_pd(va_int);
}


/*****************************
 *  Shift/Shuffle intrinsics
 *****************************/
/*
 *  Shift left (logical) packed 32/64-bit integers
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_sll_32(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_32(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_64(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_epi64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_64(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_epi64(va, shft); }

#if !defined(__clang__)
/*
 *  Shuffle 32-bit elements using control value
 */
// TODO: Clang throws error with shuffle intrinsics due to non-constants with macro expansion
static SIMD_FUNC_INLINE
SIMD_INT simd_shuffle_i32(const SIMD_INT va, const int8_t ctrl)
{ return _mm_shuffle_epi32(va, ctrl); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_shuffle_f32(const SIMD_FLT va, const SIMD_FLT vb, const int8_t ctrl)
{ return _mm_shuffle_ps(va, vb, ctrl); }
#endif

/*
 *  Merge either low/high parts from pair of registers
 *  into a single register
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_unpacklo_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_movelh_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_unpacklo_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_unpackhi_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_movehl_ps(vb, va); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_unpackhi_pd(va, vb); }

/*!
 *  Pack and merge the low 32-bits of 64-bit integers
 *  from a pair of registers.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_packmerge_i32(const SIMD_INT va, const SIMD_INT vb)
{
    // Mask unused elements
    const SIMD_INT vmsk = _mm_set_epi32(0x0, 0xFFFFFFFF, 0x0, 0xFFFFFFFF);
    SIMD_INT va_pk = _mm_and_si128(va, vmsk);
    SIMD_INT vb_pk = _mm_and_si128(vb, vmsk);

    // Pack registers
    va_pk = _mm_shuffle_epi32(va_pk, 0x58);
    vb_pk = _mm_shuffle_epi32(vb_pk, 0x85);

    // Merge
    return _mm_or_si128(va_pk, vb_pk);

/*
    // This implementation requires that the input vectors
    // already have to be of the form [#, 0, #, 0 ...]

    // Pack registers
    const SIMD_INT va_pk = _mm_shuffle_epi32(va, 0x58);
    const SIMD_INT vb_pk = _mm_shuffle_epi32(vb, 0x85);

    // Merge
    return _mm_or_si128(va_pk, vb_pk);
*/
}


/*******************
 *  Set intrinsics
 *******************/
/*
 *  Set vector to zero.
 */
static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_INT * const va)
{ *va = _mm_setzero_si128(); }

static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_FLT * const va)
{ *va = _mm_setzero_ps(); }

static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_DBL * const va)
{ *va = _mm_setzero_pd(); }

/*
 *  Set 32-bit integers to either 32/64 slots.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int32_t sa)
{ return _mm_set1_epi32(sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set_64(const int32_t sa)
{ return _mm_set1_epi64x((int64_t)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint32_t sa)
{ return _mm_set1_epi32((int32_t)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set_64(const uint32_t sa)
{ return _mm_set1_epi64x((int64_t)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int64_t sa)
{ return _mm_set1_epi64x(sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint64_t sa)
{ return _mm_set1_epi64x((int64_t)sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_set(const float sa)
{ return _mm_set1_ps(sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_set(const double sa)
{ return _mm_set1_pd(sa); }

/*!
 *  Set vector given an array.
 *  Only required for non-contiguous 32-bit elements due to in-between padding,
 *  64-bit elements can use load instructions.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int32_t * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x((int64_t)sa[1], (int64_t)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm_load_si128((SIMD_INT *)sa);
    else
        return _mm_setzero_si128();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint32_t * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x((int64_t)sa[1], (int64_t)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm_load_si128((SIMD_INT *)sa);
    else
        return _mm_setzero_si128();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int64_t * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x(sa[1], sa[0]);
    else
        return _mm_setzero_si128();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint64_t * const sa, const int32_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x((int64_t)sa[1], (int64_t)sa[0]);
    else
        return _mm_setzero_si128();
}


/***********************
 *  Convert intrinsics
 ***********************/
/*!
 *  Convert packed 32-bit integer elements
 *  to packed 32-bit floating-point elements.
 */
static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
{ return _mm_cvtepi32_ps(va); }

/*!
 *  Convert packed 32-bit integer elements
 *  to packed 64-bit floating-point elements.
 */
static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_i32_f64(const SIMD_INT va)
{ return _mm_cvtepi32_pd(va); }

/*!
 *  Convert packed unsigned 64-bit integer elements
 *  to packed 32-bit floating-point elements, the high half of the register is set to 0.0.
 *  NOTE: type conversion performed with scalar FPU since vector extensions do not support 64-bit integer conversions.
 */
static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_u64_f32(const SIMD_INT va)
{
    uint64_t sa_ul[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    float sa_flt[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm_store_si128((SIMD_INT *)sa_ul, va);

    #pragma vector aligned
    for (int32_t i = 0; i < SIMD_STREAMS_64; ++i)
        sa_flt[i] = (float)sa_ul[i];

    #pragma vector aligned
    for (int32_t i = SIMD_STREAMS_64; i < SIMD_STREAMS_32; ++i)
        sa_flt[i] = 0.0f;

    return _mm_load_ps(sa_flt);
}

/*!
 *  Convert unsigned 64-bit integers to 64-bit floating-point elements.
 *  NOTE: type conversion performed with scalar FPU since vector extensions do not support 64-bit integer conversions.
 */
static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_u64_f64(const SIMD_INT va)
{
    uint64_t sa_ul[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    double sa_dbl[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm_store_si128((SIMD_INT *)sa_ul, va);

    #pragma vector aligned
    for (int32_t i = 0; i < SIMD_STREAMS_64; ++i)
        sa_dbl[i] = (double)sa_ul[i];

    return _mm_load_pd(sa_dbl);
}


/********************
 *  Load intrinsics
 ********************/
static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int16_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int16_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int32_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int32_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const uint16_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const uint16_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const uint32_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const uint32_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int64_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int64_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const uint64_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const uint64_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_load(const float * const sa)
{ return _mm_load_ps(sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_loadu(const float * const sa)
{ return _mm_loadu_ps(sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_load(const double * const sa)
{ return _mm_load_pd(sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_loadu(const double * const sa)
{ return _mm_loadu_pd(sa); }


/*******************************
 *  Store intrinsics
 *******************************/
static SIMD_FUNC_INLINE
void simd_store(int16_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int16_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(int32_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int32_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(uint16_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(uint16_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(uint32_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(uint32_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(int64_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int64_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(uint64_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(uint64_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(float * const sa, const SIMD_FLT va)
{ _mm_store_ps(sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(float * const sa, const SIMD_FLT va)
{ _mm_storeu_ps(sa, va); }

static SIMD_FUNC_INLINE
void simd_store(double * const sa, const SIMD_DBL va)
{ _mm_store_pd(sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(double * const sa, const SIMD_DBL va)
{ _mm_storeu_pd(sa, va); }


#endif  // _SSE4_2_H

