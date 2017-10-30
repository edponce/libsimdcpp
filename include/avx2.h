/*!
 *  \defgroup AVX2 AVX2
 *  \brief SIMD interface for AVX2 (256-bit wide vector registers)
 *
 *  Interface Legend:\n
 *  simd_*_iXX = signed XX-bit integers\n
 *  simd_*_uXX = unsigned XX-bit integers\n
 *  simd_*_fXX = floating-point XX-bit elements\n
 *  simd_*_XX  = unsigned/signed XX-bit integers\n
 *  simd_*_XX  = (set functions) specifies width to consider for integer types\n
 *  simd_*     = datatype obtained from function overloading and parameters
 *
 *  \author Eduardo Ponce
 *  \version 1.0
 *  \date 10/30/2017
 *
 *  \todo Reuse vector registers in some cases (will need to remove const from parameter).
 */
#ifndef _AVX2_H
#define _AVX2_H


/*
 *  \defgroup GlobalSIMD_AVX2 Global SIMD identifiers
 *  \ingroup AVX2
 *  \brief Global constants and type definitions to support SIMD interface
 *  \{
 *
 *  \var const int32_t SIMD_WIDTH_BITS
 *  \brief Width of vector registers in bits
 *
 *  \var const int32_t SIMD_WIDTH_BYTES
 *  \brief Width of vector registers in bytes
 *
 *  \var const int32_t SIMD_STREAMS_16
 *  \brief Count of 16-bit numbers supported by width of vector registers
 *
 *  \var const int32_t SIMD_STREAMS_32
 *  \brief Count of 32-bit numbers supported by width of vector registers
 *
 *  \var const int32_t SIMD_STREAMS_64
 *  \brief Count of 64-bit numbers supported by width of vector registers
 *
 *  \typedef __m256i SIMD_INT
 *  \brief Vector type for integral numbers
 *
 *  \typedef __m256 SIMD_FLT
 *  \brief Vector type for single-precision floating-point numbers
 *
 *  \typedef __m256d SIMD_DBL
 *  \brief Vector type for double-precision floating-point numbers
 *
 *  \}
 */


/*!
 *  \defgroup Arith_AVX2 Arithmetic instructions
 *  \ingroup AVX2
 *  \brief Arithmetic instructions supported by SIMD interface
 *  \{
 *
 *    \defgroup AddSub_AVX2 Add and subtract
 *    \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_i16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed 16-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_16; ++j) {
 *      int i = j * 16;
 *      vc[i:i+15] = va[i:i+15] + vb[i:i+15];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_i32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed 32-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] + vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_i64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed 64-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] + vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_u16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add unsigned 16-bit integers
 *  \details Uses saturation arithmetic (no wrap around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_16; ++j) {
 *      int i = j * 16;
 *      vc[i:i+15] = va[i:i+15] + vb[i:i+15];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_u32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add unsigned 32-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] + vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_u64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add unsigned 64-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] + vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Add single-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] + vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Add double-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] + vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_i16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed 16-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_16; ++j) {
 *      int i = j * 16;
 *      vc[i:i+15] = va[i:i+15] - vb[i:i+15];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_i32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed 32-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] - vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_i64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed 64-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] - vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_u16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract unsigned 16-bit integers
 *  \details Uses saturation arithmetic (no wrap around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_16; ++j) {
 *      int i = j * 16;
 *      vc[i:i+15] = va[i:i+15] - vb[i:i+15];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_u32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract unsigned 32-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] - vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_u64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract unsigned 64-bit integers
 *  \details Does not uses saturation arithmetic (wraps around)
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] - vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_sub(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Subtract single-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] - vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_sub(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Subtract double-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] - vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *    \}
 *
 *    \defgroup FMA_AVX2 Fused-multiply add and subtract
 *    \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_fmadd(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
 *  \brief Fused multiply-add single-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vd[i:i+31] = va[i:i+31] * vb[i:i+31] + vc[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \param[in] vc Third operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_fmadd(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
 *  \brief Fused multiply-add double-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vd[i:i+63] = va[i:i+63] * vb[i:i+63] + vc[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \param[in] vc Third operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_fmsub(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
 *  \brief Fused multiply-subtract single-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vd[i:i+31] = va[i:i+31] * vb[i:i+31] - vc[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \param[in] vc Third operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_fmsub(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
 *  \brief Fused multiply-subtract double-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vd[i:i+63] = va[i:i+63] * vb[i:i+63] - vc[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \param[in] vc Third operand
 *  \return vd
 *
 *    \}
 *
 *    \defgroup Mul_AVX2 Multiply
 *    \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mullo_i32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply packed 32-bit integers, produce intermediate 64-bit integers,
 *         and store the low 32-bit results
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      int64_t tmp[0:63] = va[i:i+31] * vb[i:i+31];
 *      vc[i:i+31] = tmp[0:31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_i32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply low signed 32-bit integers from each packed 64-bit elements
 *         and store the signed 64-bit results
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+31] * vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_i64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Perform signed 64-bit integer multiplication using 32-bit integers
 *         since vector extensions do not support 64-bit integer multiplication.
 *  \details x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = (va[i:i+31] * vb[i:i+31]) + (va[i:i+31] * vb[i+32:i+63] + va[i+32:i+63] * vb[i:i+31]) << 32;
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_u32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply low unsigned 32-bit integers from each packed 64-bit elements
 *         and store the unsigned 64-bit results
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+31] * vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_u64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Perform unsigned 64-bit integer multiplication using 32-bit integers
 *         since vector extensions do not support 64-bit integer multiplication.
 *  \details x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = (va[i:i+31] * vb[i:i+31]) + (va[i:i+31] * vb[i+32:i+63] + va[i+32:i+63] * vb[i:i+31]) << 32;
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Multiply single-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      vc[i:i+31] = va[i:i+31] * vb[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Multiply double-precision floating-point numbers
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      vc[i:i+63] = va[i:i+63] * vb[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *    \}
 *
 *  \}
 */


#include "compiler_attributes.h"
#include "compiler_builtins.h"
#include <immintrin.h>
//#include <x86intrin.h>
#include <stdint.h>


const int32_t SIMD_WIDTH_BITS = 256;
const int32_t SIMD_WIDTH_BYTES = SIMD_WIDTH_BITS / 8;
const int32_t SIMD_STREAMS_16 = SIMD_WIDTH_BYTES / 2;
const int32_t SIMD_STREAMS_32 = SIMD_WIDTH_BYTES / 4;
const int32_t SIMD_STREAMS_64 = SIMD_WIDTH_BYTES / 8;
typedef __m256i SIMD_INT;
typedef __m256  SIMD_FLT;
typedef __m256d SIMD_DBL;


/*
 *  Arithmetic instructions
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_add_i16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_i64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_u16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_adds_epu16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_u32(const SIMD_INT va, const SIMD_INT vb)
{
    uint32_t sa[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint32_t sb[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm256_store_si256((SIMD_INT *)sa, va);
    _mm256_store_si256((SIMD_INT *)sb, vb);
    for (int i = 0; i < SIMD_STREAMS_32; ++i)
        sa[i] += sb[i];
    return _mm256_load_si256((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_add_u64(const SIMD_INT va, const SIMD_INT vb)
{
    uint64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint64_t sb[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm256_store_si256((SIMD_INT *)sa, va);
    _mm256_store_si256((SIMD_INT *)sb, vb);
    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        sa[i] += sb[i];
    return _mm256_load_si256((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_add_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_add_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_i16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_sub_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_sub_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_i64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_sub_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_u16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_subs_epu16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_u32(const SIMD_INT va, const SIMD_INT vb)
{
    uint32_t sa[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint32_t sb[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm256_store_si256((SIMD_INT *)sa, va);
    _mm256_store_si256((SIMD_INT *)sb, vb);
    for (int i = 0; i < SIMD_STREAMS_32; ++i)
        sa[i] -= sb[i];
    return _mm256_load_si256((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_u64(const SIMD_INT va, const SIMD_INT vb)
{
    uint64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    uint64_t sb[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm256_store_si256((SIMD_INT *)sa, va);
    _mm256_store_si256((SIMD_INT *)sb, vb);
    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        sa[i] -= sb[i];
    return _mm256_load_si256((SIMD_INT *)sa);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_sub(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_sub_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_sub(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_sub_pd(va, vb); }

#if defined(__FMA__)
static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{ return _mm256_fmadd_ps(va, vb, vc); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{ return _mm256_fmadd_pd(va, vb, vc); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmsub(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{ return _mm256_fmsub_ps(va, vb, vc); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmsub(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{ return _mm256_fmsub_pd(va, vb, vc); }

#else
static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    va = _mm256_mul_ps(va, vb);
    return _mm256_add_ps(va, vc);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    va = _mm256_mul_pd(va, vb);
    return _mm256_add_pd(va, vc);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmsub(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    va = _mm256_mul_ps(va, vb);
    return _mm256_sub_ps(va, vc);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmsub(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    va = _mm256_mul_pd(va, vb);
    return _mm256_sub_pd(va, vc);
}
#endif

static SIMD_FUNC_INLINE
SIMD_INT simd_mullo_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mullo_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mul_epi32(va, vb); }

// x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i64(const SIMD_INT va, const SIMD_INT vb)
{
/*
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vtmp, vhi, vlo;
    vtmp = _mm256_shuffle_epi32(vb, 0xB1); // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vtmp);    // xl * yh, xh * yl
    vtmp = _mm256_slli_epi64(vhi, 0x20);   // shift << 32
    vhi = _mm256_add_epi64(vhi, vtmp);     // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl
    return _mm256_add_epi64(vlo, vhi);     // l + h
*/
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vlo, vhi;
    vlo = _mm256_shuffle_epi32(vb, 0xB1);  // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vlo);     // xl * yh, xh * yl
    vlo = _mm256_slli_epi64(vhi, 0x20);    // shift << 32
    vhi = _mm256_add_epi64(vhi, vlo);      // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl
    return _mm256_add_epi64(vlo, vhi);     // l + h
}

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mul_epu32(va, vb); }

// x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u64(const SIMD_INT va, const SIMD_INT vb)
{
/*
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vtmp, vhi, vlo;
    vtmp = _mm256_shuffle_epi32(vb, 0xB1); // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vtmp);    // xl * yh, xh * yl
    vtmp = _mm256_slli_epi64(vhi, 0x20);   // shift << 32
    vhi = _mm256_add_epi64(vhi, vtmp);     // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl
    return _mm256_add_epi64(vlo, vhi);     // l + h
*/
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vlo, vhi;
    vlo = _mm256_shuffle_epi32(vb, 0xB1);  // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vlo);     // xl * yh, xh * yl
    vlo = _mm256_slli_epi64(vhi, 0x20);    // shift << 32
    vhi = _mm256_add_epi64(vhi, vlo);      // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl
    return _mm256_add_epi64(vlo, vhi);     // l + h
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_mul_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_mul_pd(va, vb); }


/*
 *  Logical instructions
 */
/*!
 *  \defgroup Logic_AVX2 Logical instructions
 *  \ingroup AVX2
 *  \brief Logical instructions supported by SIMD interface
 *  \{
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_or_si256(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_xor_si256(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_and_si256(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm256_castps_si256(va);
    va_int = _mm256_and_si256(va_int, vb);
    return _mm256_castsi256_ps(va_int);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm256_castpd_si256(va);
    va_int = _mm256_and_si256(va_int, vb);
    return _mm256_castsi256_pd(va_int);
}

/*!
 *  \}
 */


/*
 *  Shift and shuffle instructions
 */
/*!
 *  \defgroup ShiftShuffle_AVX2 Shift and shuffle instructions
 *  \ingroup AVX2
 *  \brief Shift and shuffle instructions supported by SIMD interface
 *  \{
 */

/*
 *  Shift left (logical) packed 32/64-bit integers
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_sll_32(const SIMD_INT va, const int shft)
{ return _mm256_slli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_32(const SIMD_INT va, const int shft)
{ return _mm256_srli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_64(const SIMD_INT va, const int shft)
{ return _mm256_slli_epi64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_64(const SIMD_INT va, const int shft)
{ return _mm256_srli_epi64(va, shft); }

#if !defined(__clang__)
/*
 *  Shuffle 32-bit elements using control value
 */
// TODO: Clang throws error with shuffle intrinsics due to non-constants with macro expansion
static SIMD_FUNC_INLINE
SIMD_INT simd_shuffle_i32(const SIMD_INT va, const int ctrl)
{ return _mm256_shuffle_epi32(va, ctrl); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_shuffle_f32(const SIMD_FLT va, const SIMD_FLT vb, const int ctrl)
{ return _mm256_shuffle_ps(va, vb, ctrl); }
#endif

/*
 *  Merge either low/high parts from pair of registers
 *  into a single register
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i vb_lo = _mm256_castsi256_si128(vb);
    return _mm256_inserti128_si256(va, vb_lo, 0x1);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m128 vb_lo = _mm256_castps256_ps128(vb);
    return _mm256_insertf128_ps(va, vb_lo, 0x1);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m128d vb_lo = _mm256_castpd256_pd128(vb);
    return _mm256_insertf128_pd(va, vb_lo, 0x1);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i va_hi = _mm256_extracti128_si256(va, 0x1);
    return _mm256_inserti128_si256(vb, va_hi, 0x0);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m128 va_hi = _mm256_extractf128_ps(va, 0x1);
    return _mm256_insertf128_ps(vb, va_hi, 0x0);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m128d va_hi = _mm256_extractf128_pd(va, 0x1);
    return _mm256_insertf128_pd(vb, va_hi, 0x0);
}

/*!
 *  Pack and merge a pair of registers
 */
static SIMD_FUNC_INLINE
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

/*!
 *  \}
 */


/*
 *  Set instructions
 */
/*!
 *  \defgroup Set_AVX2 Set instructions
 *  \ingroup AVX2
 *  \brief Set instructions supported by SIMD interface
 *  \{
 */

/*
 *  Set vector to zero.
 */
static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_INT * const va)
{ *va = _mm256_setzero_si256(); }

static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_FLT * const va)
{ *va = _mm256_setzero_ps(); }

static SIMD_FUNC_INLINE
void simd_set_zero(SIMD_DBL * const va)
{ *va = _mm256_setzero_pd(); }

/*
 *  Set 32-bit integers to either 32/64 slots.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int sa)
{ return _mm256_set1_epi32(sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set_64(const int sa)
{ return _mm256_set1_epi64x((long int)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const unsigned int sa)
{ return _mm256_set1_epi32((int)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set_64(const unsigned int sa)
{ return _mm256_set1_epi64x((long int)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const long int sa)
{ return _mm256_set1_epi64x(sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const unsigned long int sa)
{ return _mm256_set1_epi64x((long int)sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_set(const float sa)
{ return _mm256_set1_ps(sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_set(const double sa)
{ return _mm256_set1_pd(sa); }

/*!
 *  Set vector given an array.
 *  Only required for non-contiguous 32-bit elements due to in-between padding,
 *  64-bit elements can use load instructions.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x((long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm256_load_si256((SIMD_INT *)sa);
    else
        return _mm256_setzero_si256();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const unsigned int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x((long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm256_load_si256((SIMD_INT *)sa);
    else
        return _mm256_setzero_si256();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const long int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x(sa[3], sa[2], sa[1], sa[0]);
    else
        return _mm256_setzero_si256();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const unsigned long int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm256_set_epi64x((long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else
        return _mm256_setzero_si256();
}

/*!
 *  \}
 */


/*
 *  Convert instructions
 */
/*!
 *  \defgroup Convert_AVX2 Convert instructions
 *  \ingroup AVX2
 *  \brief Convert instructions supported by SIMD interface
 *  \{
 */

/*!
 *  Convert packed 32-bit integer elements
 *  to packed single-precision floating-point elements.
 */
static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
{ return _mm256_cvtepi32_ps(va); }

/*!
 *  Convert packed 32-bit integer elements
 *  to packed double-precision floating-point elements.
 */
static SIMD_FUNC_INLINE
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
static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_u64_f32(const SIMD_INT va)
{
    unsigned long int sa_ul[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    float sa_flt[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm256_store_si256((SIMD_INT *)sa_ul, va);

    #pragma vector aligned
    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        sa_flt[i] = (float)sa_ul[i];

    #pragma vector aligned
    for (int i = SIMD_STREAMS_64; i < SIMD_STREAMS_32; ++i)
        sa_flt[i] = 0.0f;

    return _mm256_load_ps(sa_flt);
}

/*!
 *  Convert unsigned 64-bit integers to 64-bit floating-point elements.
 *  NOTE: type conversion performed with scalar FPU since vector extensions do not support 64-bit integer conversions.
 */
static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_u64_f64(const SIMD_INT va)
{
    unsigned long int sa_ul[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    double sa_dbl[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);

    _mm256_store_si256((SIMD_INT *)sa_ul, va);

    #pragma vector aligned
    for (int i = 0; i < SIMD_STREAMS_64; ++i)
        sa_dbl[i] = (double)sa_ul[i];

    return _mm256_load_pd(sa_dbl);
}


/*!
 *  \}
 */


/*
 *  Load instructions
 */
/*!
 *  \defgroup Load_AVX2 Load instructions
 *  \ingroup AVX2
 *  \brief Load instructions supported by SIMD interface
 *  \{
 */

/*!
 *  Aligned and unaligned load variants have same latency and throughput,
 *  so can always use the unaligned variant.
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_load(const short int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const short int * const sa)
//{ return _mm256_loadu_si256((SIMD_INT *)sa); }
{ return _mm256_lddqu_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int * const sa)
//{ return _mm256_loadu_si256((SIMD_INT *)sa); }
{ return _mm256_lddqu_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const unsigned short int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const unsigned short int * const sa)
//{ return _mm256_loadu_si256((SIMD_INT *)sa); }
{ return _mm256_lddqu_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const unsigned int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const unsigned int * const sa)
//{ return _mm256_loadu_si256((SIMD_INT *)sa); }
{ return _mm256_lddqu_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const long int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const long int * const sa)
//{ return _mm256_loadu_si256((SIMD_INT *)sa); }
{ return _mm256_lddqu_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const unsigned long int * const sa)
{ return _mm256_load_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const unsigned long int * const sa)
//{ return _mm256_loadu_si256((SIMD_INT *)sa); }
{ return _mm256_lddqu_si256((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_load(const float * const sa)
{ return _mm256_load_ps(sa); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_loadu(const float * const sa)
{ return _mm256_loadu_ps(sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_load(const double * const sa)
{ return _mm256_load_pd(sa); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_loadu(const double * const sa)
{ return _mm256_loadu_pd(sa); }

/*!
 *  \}
 */


/*
 *  Store instructions
 */
/*!
 *  \defgroup Store_AVX2 Store instructions
 *  \ingroup AVX2
 *  \brief Store instructions supported by SIMD interface
 *  \{
 */

/*!
 *  Aligned and unaligned store variants have same latency and throughput,
 *  so can always use the unaligned variant.
 */
static SIMD_FUNC_INLINE
void simd_store(short int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(short int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(unsigned short int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(unsigned short int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(unsigned int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(unsigned int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(long int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(long int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(unsigned long int * const sa, const SIMD_INT va)
{ _mm256_store_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(unsigned long int * const sa, const SIMD_INT va)
{ _mm256_storeu_si256((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(float * const sa, const SIMD_FLT va)
{ _mm256_store_ps(sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(float * const sa, const SIMD_FLT va)
{ _mm256_storeu_ps(sa, va); }

static SIMD_FUNC_INLINE
void simd_store(double * const sa, const SIMD_DBL va)
{ _mm256_store_pd(sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(double * const sa, const SIMD_DBL va)
{ _mm256_storeu_pd(sa, va); }

/*!
 *  \}
 */


#endif  // _AVX2_H

