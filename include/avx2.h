#ifndef _AVX2_H
#define _AVX2_H


/*
 *  Compiler and architecture specific settings
 */
#include "arch.h"


/*
 *  Include supporting header files based on compiler and architecture
 *  NOTE: currently only support x86_64, GCC and Intel compilers
 */
#include <x86intrin.h>
//#include <immintrin.h>

/*
 *  AVX2 256-bit wide vector units
 *  Define constants required for SIMD module to function properly.
 */
#define SIMD_INT __m256i
#define SIMD_FLT __m256
#define SIMD_DBL __m256d
#define SIMD_WIDTH_BYTES 32
#define SIMD_STREAMS_32  8
#define SIMD_STREAMS_64  4


#define __SIMD_FUN_ATTR__   ARCH_ATTR_INLINE // force inline when no optimizations
#define __SIMD_FUN_PREFIX__ inline static


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
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_add_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi32(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_add_i64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi64(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_add_ps(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_add_pd(va, vb); }

/*!
 *  Fused multiply-add for 32/64-bit floating-point elements
 */
#if defined(__FMA__)
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{ return _mm256_fmadd_ps(va, vb, vc); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{ return _mm256_fmadd_pd(va, vb, vc); }

#else
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    const SIMD_FLT vab = _mm256_mul_ps(va, vb);
    return _mm256_add_ps(vab, vc);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    const SIMD_DBL vab = _mm256_mul_pd(va, vb);
    return _mm256_add_pd(vab, vc);
}
#endif

/*!
 *  Multiply low unsigned 32-bit integers from each packed 64-bit elements
 *  and store the unsigned 64-bit results
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mul_u32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mul_epu32(va, vb); }

/*!
 *  Multiply low signed 32-bit integers from each packed 64-bit elements
 *  and store the signed 64-bit results
 *  NOTE: requires at least AVX2 for _mm256_mul_epi32()
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mul_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mul_epi32(va, vb); }

/*!
 *  Perform 64-bit integer multiplication using 32-bit integers
 *  since vector extensions do not support 64-bit integer multiplication.
 *  x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
 *  NOTE: requires at least AVX2 for _mm256_mullo_epi32()
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mul_u64(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vtmp, vhi, vlo;

    vtmp = _mm256_shuffle_epi32(vb, 0xB1); // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vtmp);    // xl * yh, xh * yl
    vtmp = _mm256_slli_epi64(vhi, 0x20);   // shift << 32
    vhi = _mm256_add_epi64(vhi, vtmp);     // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl

    return _mm256_add_epi64(vlo, vhi);     // l + h
}

/*!
 *  Multiply packed 32-bit integers, produce intermediate 64-bit integers,
 *  and store the low 32-bit results
 *  NOTE: requires at least AVX2 for _mm256_mullo_epi32()
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mullo_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mullo_epi32(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_mul_ps(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_mul_pd(va, vb); }


/********************************
 *  Integral logical intrinsics
 ********************************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_or_si256(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_xor_si256(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_and_si256(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm256_castps_si256(va);
    va_int = _mm256_and_si256(va_int, vb);
    return _mm256_castsi256_ps(va_int);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm256_castpd_si256(va);
    va_int = _mm256_and_si256(va_int, vb);
    return _mm256_castsi256_pd(va_int);
}


/*****************************
 *  Shift/Shuffle intrinsics
 *****************************/
/*
 *  Shift left (logical) packed 32/64-bit integers
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
//SIMD_INT simd_sll_32(const SIMD_INT va, const int shft)
SIMD_INT simd_sll_32(const SIMD_INT va, const int shft)
{ return _mm256_slli_epi32(va, shft); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_srl_32(const SIMD_INT va, const int shft)
{ return _mm256_srli_epi32(va, shft); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_sll_64(const SIMD_INT va, const int shft)
{ return _mm256_slli_epi64(va, shft); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_srl_64(const SIMD_INT va, const int shft)
{ return _mm256_srli_epi64(va, shft); }

/*
 *  Shuffle 32-bit elements using control value
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_shuffle_i32(const SIMD_INT va, const int ctrl)
{ return _mm256_shuffle_epi32(va, ctrl); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_shuffle_f32(const SIMD_FLT va, const SIMD_FLT vb, const int ctrl)
{ return _mm256_shuffle_ps(va, vb, (unsigned int)ctrl); }

/*
 *  Merge either low/high parts from pair of registers
 *  into a single register
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i vb_lo = _mm256_castsi256_si128(vb);
    return _mm256_inserti128_si256(va, vb_lo, 0x1);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m128 vb_lo = _mm256_castps256_ps128(vb);
    return _mm256_insertf128_ps(va, vb_lo, 0x1);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m128d vb_lo = _mm256_castpd256_pd128(vb);
    return _mm256_insertf128_pd(va, vb_lo, 0x1);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i va_hi = _mm256_extracti128_si256(va, 0x1);
    return _mm256_inserti128_si256(vb, va_hi, 0x0);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m128 va_hi = _mm256_extractf128_ps(va, 0x1);
    return _mm256_insertf128_ps(vb, va_hi, 0x0);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m128d va_hi = _mm256_extractf128_pd(va, 0x1);
    return _mm256_insertf128_pd(vb, va_hi, 0x0);
}

/*!
 *  Pack and merge a pair of registers
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_packmerge_i32(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i va_lo = _mm256_castsi256_si128(va);
    const __m128i va_hi = _mm256_extracti128_si256(va, 0x1);
    const __m128i vb_lo = _mm256_castsi256_si128(vb);
    const __m128i vb_hi = _mm256_extracti128_si256(vb, 0x1);

    // Pack va
    __m128i vtmp1 = _mm_shuffle_epi32(va_lo, 0x58);
    __m128i vtmp2 = _mm_shuffle_epi32(va_hi, 0x85);
    vtmp2 = _mm_or_si128(vtmp1, vtmp2);
    const SIMD_INT va_pk = _mm256_castsi128_si256(vtmp2);


    // Pack vb
    vtmp1 = _mm_shuffle_epi32(vb_lo, 0x58);
    vtmp2 = _mm_shuffle_epi32(vb_hi, 0x85);
    vtmp2 = _mm_or_si128(vtmp1, vtmp2);

    // Merge
    return _mm256_inserti128_si256(va_pk, vtmp2, 0x1);
}


/*******************
 *  Set intrinsics
 *******************/
/*
 *  Set vector to zero.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_set_zero(SIMD_INT * const va)
{ *va = _mm256_setzero_si256(); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_set_zero(SIMD_FLT * const va)
{ *va = _mm256_setzero_ps(); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_set_zero(SIMD_DBL * const va)
{ *va = _mm256_setzero_pd(); }

/*
 *  Set 32-bit integers to either 32/64 slots.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const int sa)
{ return _mm256_set1_epi32(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set_64(const int sa)
{ return _mm256_set1_epi64x((long int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned int sa)
{ return _mm256_set1_epi32((int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set_64(const unsigned int sa)
{ return _mm256_set1_epi64x((long int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const long int sa)
{ return _mm256_set1_epi64x(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned long int sa)
{ return _mm256_set1_epi64x((long int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_set(const float sa)
{ return _mm256_set1_ps(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_set(const double sa)
{ return _mm256_set1_pd(sa); }

/*!
 *  Set vector given an array.
 *  Only required for non-contiguous 32-bit elements due to in-between padding,
 *  64-bit elements can use load instructions.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x((long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm256_load_si256((SIMD_INT *)sa);
    else
        return _mm256_setzero_si256();
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x((long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm256_load_si256((SIMD_INT *)sa);
    else
        return _mm256_setzero_si256();
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const long int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x(sa[3], sa[2], sa[1], sa[0]);
    else
        return _mm256_setzero_si256();
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned long int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x((long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else
        return _mm256_setzero_si256();
}


/***********************
 *  Convert intrinsics
 ***********************/
/*!
 *  Convert packed 32-bit integer elements
 *  to packed single-precision floating-point elements.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
{ return _mm256_cvtepi32_ps(va); }

/*!
 *  Convert packed 32-bit integer elements
 *  to packed double-precision floating-point elements.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_cvt_i32_f64(const SIMD_INT va)
{
    const SIMD_FLT va_flt = _mm256_cvtepi32_ps(va);
    const __m128 va_flt_lo = _mm256_castps256_ps128(va_flt);
    return _mm256_cvtps_pd(va_flt_lo);
}

/*!
 *  Convert packed unsigned 64-bit integer elements
 *  to packed 32-bit floating-point elements, the high half of the register is set to 0.0.
 *  NOTE: type conversion performed with scalar FPU since vector extensions do not support 64-bit integer conversions.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_cvt_u64_f32(const SIMD_INT va)
{
    unsigned long int sa_ul[SIMD_STREAMS_64] ARCH_ATTR_ALIGNED(SIMD_WIDTH_BYTES);
    unsigned long int *sa_ul_ptr = sa_ul;
    float sa_flt[SIMD_STREAMS_32] ARCH_ATTR_ALIGNED(SIMD_WIDTH_BYTES);
    float *sa_flt_ptr = sa_flt;

    _mm256_store_si256((SIMD_INT *)sa_ul, va);

    #pragma vector aligned
    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        *(sa_flt_ptr++) = (float)*(sa_ul_ptr++);

    #pragma vector aligned
    for (int i = SIMD_STREAMS_64; i < SIMD_STREAMS_32; ++i)
        *(sa_flt_ptr++) = 0.0;

    return _mm256_load_ps(sa_flt);
}

/*!
 *  Convert unsigned 64-bit integers to 64-bit floating-point elements.
 *  NOTE: type conversion performed with scalar FPU since vector extensions do not support 64-bit integer conversions.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_cvt_u64_f64(const SIMD_INT va)
{
    unsigned long int sa_ul[SIMD_STREAMS_64] ARCH_ATTR_ALIGNED(SIMD_WIDTH_BYTES);
    unsigned long int *sa_ul_ptr = sa_ul;
    double sa_dbl[SIMD_STREAMS_64] ARCH_ATTR_ALIGNED(SIMD_WIDTH_BYTES);
    double *sa_dbl_ptr = sa_dbl;

    _mm256_store_si256((SIMD_INT *)sa_ul, va);

    #pragma vector aligned
    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        *(sa_dbl_ptr++) = (double)*(sa_ul_ptr++);

    return _mm256_load_pd(sa_dbl);
}


/********************
 *  Load intrinsics
 ********************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const int * const sa)
{ return _mm256_loadu_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const unsigned int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const unsigned int * const sa)
{ return _mm256_loadu_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const long int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const long int * const sa)
{ return _mm256_loadu_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const unsigned long int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const unsigned long int * const sa)
{ return _mm256_loadu_si256((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_load(const float * const sa)
{ return _mm256_load_ps(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_loadu(const float * const sa)
{ return _mm256_loadu_ps(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_load(const double * const sa)
{ return _mm256_load_pd(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_loadu(const double * const sa)
{ return _mm256_loadu_pd(sa); }


/*******************************
 *  Store intrinsics
 *******************************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(unsigned int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(unsigned int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(long int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(long int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(unsigned long int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(unsigned long int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(float * const sa, const SIMD_FLT va)
{ _mm256_store_ps(sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(float * const sa, const SIMD_FLT va)
{ _mm256_storeu_ps(sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(double * const sa, const SIMD_DBL va)
{ _mm256_store_pd(sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(double * const sa, const SIMD_DBL va)
{ _mm256_storeu_pd(sa, va); }


#endif  // _AVX2_H

