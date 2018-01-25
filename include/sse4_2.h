/*!
 *  \defgroup SSE4_2 SSE4.2
 *  \brief SIMD interface for SSE4.2 (128-bit wide vector registers)
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
 *  \todo Verify sign extension in functions that unpack/convert elements to a larger width
 *  \todo Remove SIMD_ from functions
 *  \todo Change data types to int8_v, int16_v, int32_v, int64_v, flt32_v, flt64_v (and unsigned integer versions)
 *  \todo For OO interface, define macros to eliminate user from scoping class, e.g. #define vadd(a,b) int32_v::add(a,b)
 *  \todo For OO interface, add automatic prefetching when it makes sense
 *  \todo Load/store with aligned/unaligned and streaming
 *  \todo Add const * const where applicable, use uint32_t for array sizes
 *  \todo size_t for indexing and sizes
 *  \todo How to handle prefetching when memory unaligned (strip mining approach)
 *  \todo Change SIMD_STREAMS_32 to SIMD_STREAMS_I32, that is, more meaningful names
 */
#ifndef _SSE4_2_H
#define _SSE4_2_H


#include <stdio.h>
#include <stdlib.h>   // NULL, free, posix_memalign, getenv, atoi
#include <iostream>
using std::cout;
using std::endl;


#ifndef _SHUFFLE_CTRL_
#define _SHUFFLE_CTRL_
/*!
 *  Control values for shuffle operations
 *  \todo Move this enum to a global area, all SIMD modes will use it
 */
enum SHUFFLE_CTRL { XCHG = 0, // Exchange lower/upper halfs of register
                    XCHG8,    // Exchange pairs of 8-bit elements
                    XCHG16,   // Exchange pairs of 16-bit elements
                    XCHG32,   // Exchange pairs of 32-bit elements
                    XCHG64,   // Exchange pairs of 64-bit elements
                    DUPL,     // Duplicate lower half into upper half of register
                    DUPH };   // Duplicate upper half into lower half of register
#endif


//! \note Include comments inside namespace for correct module listing in documentation
namespace SSE4_2 {


/*
 *  \defgroup GlobalSIMD_SSE4_2 Global SIMD identifiers
 *  \ingroup SSE4_2
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
 *  \typedef __m128i SIMD_INT
 *  \brief Vector type for integral numbers
 *
 *  \typedef __m128 SIMD_FLT
 *  \brief Vector type for single-precision floating-point numbers
 *
 *  \typedef __m128d SIMD_DBL
 *  \brief Vector type for double-precision floating-point numbers
 *
 *  \}
 */


/*!
 *  \defgroup Arith_SSE4_2 Arithmetic instructions
 *  \ingroup SSE4_2
 *  \brief Arithmetic instructions supported by SIMD interface
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed/unsigned 16-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=16)
 *      vc[i:i+15] = va[i:i+15] + vb[i:i+15];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed/unsigned 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] + vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed/unsigned 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] + vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Add single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] + vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Add double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] + vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed/unsigned 16-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=16)
 *      vc[i:i+15] = va[i:i+15] - vb[i:i+15];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed/unsigned 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] - vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed/unsigned 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] - vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_sub(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Subtract single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] - vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_sub(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Subtract double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] - vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
 *  \brief Fused multiply-add single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vd[i:i+31] = va[i:i+31] * vb[i:i+31] + vc[i:i+31];
 *  \endcode
 *  \param[in] va Left multiply operand
 *  \param[in] vb Right multiply operand
 *  \param[in] vc Right add operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
 *  \brief Fused multiply-add double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vd[i:i+63] = va[i:i+63] * vb[i:i+63] + vc[i:i+63];
 *  \endcode
 *  \param[in] va Left multiply operand
 *  \param[in] vb Right multiply operand
 *  \param[in] vc Right add operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_fmsub(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
 *  \brief Fused multiply-subtract single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vd[i:i+31] = va[i:i+31] * vb[i:i+31] - vc[i:i+31];
 *  \endcode
 *  \param[in] va Left multiply operand
 *  \param[in] vb Right multiply operand
 *  \param[in] vc Right subtract operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_fmsub(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
 *  \brief Fused multiply-subtract double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vd[i:i+63] = va[i:i+63] * vb[i:i+63] - vc[i:i+63];
 *  \endcode
 *  \param[in] va Left multiply operand
 *  \param[in] vb Right multiply operand
 *  \param[in] vc Right subtract operand
 *  \return vd
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply signed/unsigned 16-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=16)
 *      vc[i:i+15] = va[i:i+15] * vb[i:i+15];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply signed/unsigned 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] * vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply signed/unsigned 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] * vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Multiply single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] * vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Multiply double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] * vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_i16_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply signed 16-bit integers and store result as 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+15] * vb[i:i+15];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_i32_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply signed 32-bit integers and store result as 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+31] * vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_u16_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply unsigned 16-bit integers and store result as 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+15] * vb[i:i+15];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_mul_u32_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Multiply unsigned 32-bit integers and store result as 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+31] * vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_div(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Divide single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = va[i:i+31] / vb[i:i+31];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_div(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Divide double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = va[i:i+63] / vb[i:i+63];
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_sqrt(const SIMD_FLT va)
 *  \brief Calculate square root of single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = SQRT(va[i:i+31]);
 *  \endcode
 *  \param[in] va Operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_sqrt(const SIMD_DBL va)
 *  \brief Calculate square root of double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = SQRT(va[i:i+63]);
 *  \endcode
 *  \param[in] va Operand
 *  \return vc
 *
 *  \}
 */


/*!
 *  \defgroup Logic_SSE4_2 Logical instructions
 *  \ingroup SSE4_2
 *  \brief Logical instructions supported by SIMD interface
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Bitwise AND of 128-bit integer registers
 *  \code{.c}
 *  vc = va & vb;
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
 *  \brief Bitwise AND of single-precision floating-point number and 128-bit integer register
 *  \code{.c}
 *  vc = (SIMD_FLT)((SIMD_INT)va & vb);
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
 *  \brief Bitwise AND of double-precision floating-point number and 128-bit integer register
 *  \code{.c}
 *  vc = (SIMD_DBL)((SIMD_INT)va & vb);
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Bitwise OR of 128-bit integer registers
 *  \code{.c}
 *  vc = va | vb;
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Bitwise XOR of 128-bit integer registers
 *  \code{.c}
 *  vc = va ^ vb;
 *  \endcode
 *  \param[in] va Left operand
 *  \param[in] vb Right operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_16(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 16-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=16)
 *      vc[i:i+15] = (shft > 15) ? 0 : ZeroExtend(va[i:i+15] << shft);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_32(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 32-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = (shft > 31) ? 0 : ZeroExtend(va[i:i+31] << shft);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_64(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 64-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = (shft > 63) ? 0 : ZeroExtend(va[i:i+63] << shft);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_128(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 128-bit integers (at byte level) while shifting in zeros
 *  \code{.c}
 *  vc = (shft > 15) 0 : (va << (shft * 8));
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_16(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 16-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=16)
 *      vc[i:i+15] = (shft > 15) ? 0 : ZeroExtend(va[i:i+15] >> shft);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_32(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 32-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = (shft > 31) ? 0 : ZeroExtend(va[i:i+31] >> shft);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_64(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 64-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = (shft > 63) ? 0 : ZeroExtend(va[i:i+63] >> shft);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_128(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 128-bit integers (at byte level) while shifting in zeros
 *  \code{.c}
 *  vc = (shft > 15) 0 : (va >> (shft * 8));
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *  \}
 */


/*!
 *  \defgroup Merge_SSE4_2 Merge instructions
 *  \ingroup SSE4_2
 *  \brief Merge instructions supported by SIMD interface
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Merge lower half from pair of integer registers
 *  \code{.c}
 *  vc[0:63] = va[0:63]
 *  vc[64:127] = vb[0:63]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Merge lower half from pair of single-precision floating-point registers
 *  \code{.c}
 *  vc[0:63] = va[0:63]
 *  vc[64:127] = vb[0:63]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Merge lower half from pair of double-precision floating-point registers
 *  \code{.c}
 *  vc[0:63] = va[0:63]
 *  vc[64:127] = vb[0:63]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Merge upper half from pair of integer registers
 *  \code{.c}
 *  vc[0:63] = va[64:127]
 *  vc[64:127] = vb[64:127]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Merge upper half from pair of single-precision floating-point registers
 *  \code{.c}
 *  vc[0:63] = va[64:127]
 *  vc[64:127] = vb[64:127]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Merge upper half from pair of double-precision floating-point registers
 *  \code{.c}
 *  vc[0:63] = va[64:127]
 *  vc[64:127] = vb[64:127]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *  \}
 */


/*!
 *  \defgroup Shuffle_SSE4_2 Shuffle instructions
 *  \ingroup SSE4_2
 *  \brief Shuffle instructions supported by SIMD interface
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_pack_8(const SIMD_INT va)
 *  \brief Pack into first half of register the lower 8-bit integers from 16-bit elements
 *         and pack into second half of register the upper 8-bit integers from 16-bit elements
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=8) {
 *      int k = i * 2;
 *      vc[i:i+7] = va[k:k+7];
 *      vc[i+64:(i+64)+7] = va[k+8:(k+8)+7];
 *  }
 *  \endcode
 *  \param[in] va Vector register to pack
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_pack_16(const SIMD_INT va)
 *  \brief Pack into first half of register the lower 16-bit integers from 32-bit elements
 *         and pack into second half of register the upper 16-bit integers from 32-bit elements
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=16) {
 *      int k = i * 2;
 *      vc[i:i+15] = va[k:k+15];
 *      vc[i+64:(i+64)+15] = va[k+16:(k+16)+15];
 *  }
 *  \endcode
 *  \param[in] va Vector register to pack
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_pack_32(const SIMD_INT va)
 *  \brief Pack into first half of register the lower 32-bit integers from 64-bit elements
 *         and pack into second half of register the upper 32-bit integers from 64-bit elements
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[i:i+31] = va[k:k+31];
 *      vc[i+64:(i+64)+31] = va[k+32:(k+32)+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to pack
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_pack(const SIMD_FLT va)
 *  \brief Pack into first half of register the lower single-precision floating-point numbers from 64-bit elements
 *         and pack into second half of register the upper single-precision floating-point numbers from 64-bit elements
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[i:i+31] = va[k:k+31];
 *      vc[i+64:(i+64)+31] = va[k+32:(k+32)+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to pack
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_shuffle(const SIMD_INT va, const SHUFFLE_CTRL ctrl)
 *  \brief Shuffle integer vector register
 *  \code{.c}
 *  switch (ctrl) {
 *      case XCHG:    // Exchange lower/upper halfs of register
 *      case XCHG8:   // Exchange pairs of 8-bit elements
 *      case XCHG16:  // Exchange pairs of 16-bit elements
 *      case XCHG32:  // Exchange pairs of 32-bit elements
 *      case XCHG64:  // Exchange pairs of 64-bit elements
 *      case DUPL:    // Duplicate lower half into upper half of register
 *      case DUPH:    // Duplicate upper half into lower half of register
 *      default: return va;
 *  }
 *  \endcode
 *  \param[in] va Vector register to shuffle
 *  \param[in] ctrl Shuffle control
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_shuffle(const SIMD_FLT va, const SHUFFLE_CTRL ctrl)
 *  \brief Shuffle single-precision floating-point vector register
 *  \code{.c}
 *  switch (ctrl) {
 *      case XCHG:    // Exchange lower/upper halfs of register
 *      case XCHG32:  // Exchange pairs of 32-bit elements
 *      case XCHG64:  // Exchange pairs of 64-bit elements
 *      case DUPL:    // Duplicate lower half into upper half of register
 *      case DUPH:    // Duplicate upper half into lower half of register
 *      default: return va;
 *  }
 *  \endcode
 *  \param[in] va Vector register to shuffle
 *  \param[in] ctrl Shuffle control
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_shuffle(const SIMD_DBL va, const SHUFFLE_CTRL ctrl)
 *  \brief Shuffle second-precision floating-point vector register
 *  \code{.c}
 *  switch (ctrl) {
 *      case XCHG:    // Exchange lower/upper halfs of register
 *      case XCHG64:  // Exchange pairs of 64-bit elements
 *      case DUPL:    // Duplicate lower half into upper half of register
 *      case DUPH:    // Duplicate upper half into lower half of register
 *      default: return va;
 *  }
 *  \endcode
 *  \param[in] va Vector register to shuffle
 *  \param[in] ctrl Shuffle control
 *  \return vc
 *
 *  \}
 */


/*!
 *  \defgroup Convert_SSE4_2 Convert instructions
 *  \ingroup SSE4_2
 *  \brief Convert instructions supported by SIMD interface
 *  \todo Check if upper half of register is zeroed when converting bigger-to-smallest elements
 *  \todo Complete convert functions 64-to-64
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_cvt_i16_i32(const SIMD_INT va)
 *  \brief Sign extend packed 16-bit integers to packed 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=16) {
 *      int k = i * 2;
 *      vc[k:k+31] = (int32_t)va[i:i+15];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_cvt_i32_i64(const SIMD_INT va)
 *  \brief Sign extend packed 32-bit integers to packed 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[k:k+63] = (int64_t)va[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
 *  \brief Convert packed 32-bit integers to packed single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = (float)va[i:i+31];
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_cvt_i32_f64(const SIMD_INT va)
 *  \brief Convert packed 32-bit integers to packed double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[k:k+63] = (double)va[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_cvt_i64_f32(const SIMD_INT va)
 *  \brief Convert packed 64-bit integers to packed single-precision floating-point numbers and zero upper half of vector register
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=64) {
 *      int k = i / 2;
 *      vc[k:k+31] = (float)va[i:i+63];
 *  }
 *  vc[64:128] = 0.0;
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_cvt_i64_f64(const SIMD_INT va)
 *  \brief Convert packed 64-bit integers to packed double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = (double)va[i:i+63];
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_cvt_u16_i32(const SIMD_INT va)
 *  \brief Zero extend packed unsigned 16-bit integers to packed 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=16) {
 *      int k = i * 2;
 *      vc[k:k+31] = (uint32_t)va[i:i+15];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_cvt_u32_i64(const SIMD_INT va)
 *  \brief Zero extend unsigned packed 32-bit integers to packed 64-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[k:k+63] = (uint64_t)va[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_cvt_u32_f32(const SIMD_INT va)
 *  \brief Convert packed unsigned 32-bit integers to packed single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = (float)va[i:i+31];
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_cvt_u32_f64(const SIMD_INT va)
 *  \brief Convert packed unsigned 32-bit integers to packed double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[k:k+63] = (double)va[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_cvt_u64_f32(const SIMD_INT va)
 *  \brief Convert packed unsigned 64-bit integers to packed single-precision floating-point numbers and zero upper half of vector register
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=64) {
 *      int k = i / 2;
 *      vc[k:k+31] = (float)va[i:i+63];
 *  }
 *  vc[64:128] = 0.0;
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_cvt_u64_f64(const SIMD_INT va)
 *  \brief Convert packed unsigned 64-bit integers to packed double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=64)
 *      vc[i:i+63] = (double)va[i:i+63];
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_cvt_f32_i32(const SIMD_FLT va)
 *  \brief Convert packed single-precision floating-point numbers to packed 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 128; i+=32)
 *      vc[i:i+31] = (int32_t)va[i:i+31];
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_cvt_f32_f64(const SIMD_FLT va)
 *  \brief Convert packed single-precision floating-point numbers to packed double-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=32) {
 *      int k = i * 2;
 *      vc[k:k+63] = (double)va[i:i+31];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_cvt_f64_i32(const SIMD_DBL va)
 *  \brief Convert packed double-precision floating-point numbers to packed 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=64) {
 *      int k = i / 2;
 *      vc[k:k+31] = (int32_t)va[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_cvt_f64_f32(const SIMD_DBL va)
 *  \brief Convert packed double-precision floating-point numbers to packed single-precision floating-point numbers
 *  \code{.c}
 *  for (int i = 0; i < 64; i+=64) {
 *      int k = i / 2;
 *      vc[k:k+31] = (float)va[i:i+63];
 *  }
 *  \endcode
 *  \param[in] va Vector register to convert
 *  \return vc
 *
 *  \}
 */


/*!
 *  \defgroup Set_SSE4_2 Set instructions
 *  \ingroup SSE4_2
 *  \brief Set instructions supported by SIMD interface
 *  \{
 *
 *
 *  /}
 */


/*!
 *  \defgroup Load_SSE4_2 Load instructions
 *  \ingroup SSE4_2
 *  \brief Load instructions supported by SIMD interface
 *  \{
 *
 *
 *  /}
 */


/*!
 *  \defgroup Store_SSE4_2 Store instructions
 *  \ingroup SSE4_2
 *  \brief Store instructions supported by SIMD interface
 *  \{
 *
 *
 *  /}
 */


#include "compiler_attributes.h"
#include "compiler_builtins.h"
#include <nmmintrin.h>
//#include <x86intrin.h>
#include <stdint.h>


const size_t SIMD_WIDTH_BITS = 128;
const size_t SIMD_WIDTH_BYTES = SIMD_WIDTH_BITS / 8;
const size_t SIMD_STREAMS_8 = SIMD_WIDTH_BYTES;
const size_t SIMD_STREAMS_16 = SIMD_WIDTH_BYTES / sizeof(int16_t);
const size_t SIMD_STREAMS_32 = SIMD_WIDTH_BYTES / sizeof(int32_t);
const size_t SIMD_STREAMS_64 = SIMD_WIDTH_BYTES / sizeof(int64_t);
typedef __m128i SIMD_INT;
typedef __m128  SIMD_FLT;
typedef __m128d SIMD_DBL;


/***********************
 *  Misc instructions  *
 ***********************/
static SIMD_FUNC_INLINE
void simd_prefetch(const void *sa, const int32_t hint = 0)
{
    switch (hint) {
        case 1: __prefetchw((char *)sa); break;
        default: __prefetchr((char *)sa); break;
    }
}


/*****************************
 *  Arithmetic instructions  *
 *****************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_add_8(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_epi8(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_add_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_add_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_add_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_8(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi8(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_sub_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_sub(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_sub_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_sub(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_sub_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
#if defined(__FMA__)
    return _mm_fmadd_ps(va, vb, vc);
#else
    const SIMD_FLT vab = _mm_mul_ps(va, vb);
    return _mm_add_ps(vab, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
#if defined(__FMA__)
    return _mm_fmadd_pd(va, vb, vc);
#else
    const SIMD_DBL vab = _mm_mul_pd(va, vb);
    return _mm_add_pd(vab, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmsub(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
#if defined(__FMA__)
    return _mm_fmsub_ps(va, vb, vc);
#else
    const SIMD_FLT vab = _mm_mul_ps(va, vb);
    return _mm_sub_ps(vab, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmsub(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
#if defined(__FMA__)
    return _mm_fmsub_pd(va, vb, vc);
#else
    const SIMD_DBL vab = _mm_mul_pd(va, vb);
    return _mm_sub_pd(vab, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mullo_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mullo_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_64(const SIMD_INT va, const SIMD_INT vb)
{
    //! \note x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
    const SIMD_INT vmsk = _mm_set1_epi64x(0xFFFFFFFF00000000);
    SIMD_INT vlo, vhi;
    vlo = _mm_shuffle_epi32(vb, 0xB1);  // shuffle multiplier
    vhi = _mm_mullo_epi32(va, vlo);     // xl * yh, xh * yl
    vlo = _mm_slli_epi64(vhi, 0x20);    // shift << 32
    vhi = _mm_add_epi64(vhi, vlo);      // h = h1 + h2
    vhi = _mm_and_si128(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm_mul_epu32(va, vb);        // l = xl * yl
    return _mm_add_epi64(vlo, vhi);     // l + h
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_mul_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_mul_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i16_32(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT vlo = _mm_mullo_epi16(va, vb);  // low 16-bits
    SIMD_INT vhi = _mm_mulhi_epi16(va, vb);        // high 16-bits
    vhi = _mm_slli_si128(vhi, 0x02);               // shift 16-bits
    return _mm_blend_epi16(vlo, vhi, 0xAA);        // merge low and high parts
}

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i32_64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mul_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u16_32(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT vlo = _mm_mullo_epi16(va, vb);  // low 16-bits
    SIMD_INT vhi = _mm_mulhi_epu16(va, vb);        // high 16-bits
    vhi = _mm_slli_si128(vhi, 0x02);               // shift 16-bits
    return _mm_blend_epi16(vlo, vhi, 0xAA);        // merge low and high parts
}

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u32_64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_mul_epu32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_div(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm_div_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_div(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm_div_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_sqrt(const SIMD_FLT va)
{ return _mm_sqrt_ps(va); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_sqrt(const SIMD_DBL va)
{ return _mm_sqrt_pd(va); }


/**************************
 *  Logical instructions  *
 **************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_and_si128(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
{
    //! \note Used to mask vector elements
    SIMD_INT va_int = _mm_castps_si128(va);
    va_int = _mm_and_si128(va_int, vb);
    return _mm_castsi128_ps(va_int);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
{
    //! \note Used to mask vector elements
    SIMD_INT va_int = _mm_castpd_si128(va);
    va_int = _mm_and_si128(va_int, vb);
    return _mm_castsi128_pd(va_int);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_or_si128(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm_xor_si128(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_16(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_epi16(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_32(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_64(const SIMD_INT va, const int8_t shft)
{ return _mm_slli_epi64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_128(const SIMD_INT va, const int8_t shft)
{
    /*!
     *  \note Explicit cases are included because \c shft
     *        has to be an 8-bit immediate literal\n
     *        The alternative is to use: \c _mm_slli_si128(va, shft)
     */
    switch (shft) {
        case 0: return va; break;
        case 1: return _mm_slli_si128(va, 0x01); break;
        case 2: return _mm_slli_si128(va, 0x02); break;
        case 3: return _mm_slli_si128(va, 0x03); break;
        case 4: return _mm_slli_si128(va, 0x04); break;
        case 5: return _mm_slli_si128(va, 0x05); break;
        case 6: return _mm_slli_si128(va, 0x06); break;
        case 7: return _mm_slli_si128(va, 0x07); break;
        case 8: return _mm_slli_si128(va, 0x08); break;
        case 9: return _mm_slli_si128(va, 0x09); break;
        case 10: return _mm_slli_si128(va, 0x0A); break;
        case 11: return _mm_slli_si128(va, 0x0B); break;
        case 12: return _mm_slli_si128(va, 0x0C); break;
        case 13: return _mm_slli_si128(va, 0x0D); break;
        case 14: return _mm_slli_si128(va, 0x0E); break;
        case 15: return _mm_slli_si128(va, 0x0F); break;
        default: return _mm_setzero_si128(); break;
    }
}

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_16(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_epi16(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_32(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_64(const SIMD_INT va, const int8_t shft)
{ return _mm_srli_epi64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_128(const SIMD_INT va, const int8_t shft)
{
    /*!
     *  \note Explicit cases are included because \c shft
     *        has to be an 8-bit immediate literal\n
     *        The alternative is to use: \c _mm_srli_si128(va, shft)
     */
    switch (shft) {
        case 0: return va; break;
        case 1: return _mm_srli_si128(va, 0x01); break;
        case 2: return _mm_srli_si128(va, 0x02); break;
        case 3: return _mm_srli_si128(va, 0x03); break;
        case 4: return _mm_srli_si128(va, 0x04); break;
        case 5: return _mm_srli_si128(va, 0x05); break;
        case 6: return _mm_srli_si128(va, 0x06); break;
        case 7: return _mm_srli_si128(va, 0x07); break;
        case 8: return _mm_srli_si128(va, 0x08); break;
        case 9: return _mm_srli_si128(va, 0x09); break;
        case 10: return _mm_srli_si128(va, 0x0A); break;
        case 11: return _mm_srli_si128(va, 0x0B); break;
        case 12: return _mm_srli_si128(va, 0x0C); break;
        case 13: return _mm_srli_si128(va, 0x0D); break;
        case 14: return _mm_srli_si128(va, 0x0E); break;
        case 15: return _mm_srli_si128(va, 0x0F); break;
        default: return _mm_setzero_si128(); break;
    }
}


/*********************************
 *  Merge and pack instructions  *
 *********************************/
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


/**************************
 *  Shuffle instructions  *
 **************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_pack_8(const SIMD_INT va)
{
    const SIMD_INT vmsk = _mm_set_epi64x(0x0F0D0B0907050301, 0x0E0C0A0806040200);
    return _mm_shuffle_epi8(va, vmsk);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_pack_16(const SIMD_INT va)
{
    const SIMD_INT vmsk = _mm_set_epi64x(0x0F0E0B0A07060302, 0x0D0C090805040100);
    return _mm_shuffle_epi8(va, vmsk);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_pack_32(const SIMD_INT va)
{ return _mm_shuffle_epi32(va, 0xD8); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_pack(const SIMD_FLT va)
{ return _mm_shuffle_ps(va, va, 0xD8); }

//! \note Shuffle assumes that vector register width is a multiple of 32
static SIMD_FUNC_INLINE
SIMD_INT simd_shuffle(const SIMD_INT va, const SHUFFLE_CTRL ctrl)
{
    switch (ctrl) {
        case XCHG: return _mm_shuffle_epi32(va, 0x4E); break;
        case XCHG8:
        {
            const SIMD_INT vmsk = _mm_set_epi64x(0x0E0F0C0D0A0B0809, 0x0607040502030001);
            return _mm_shuffle_epi8(va, vmsk);
        }
        break;
        case XCHG16:
        {
            const SIMD_INT vmsk = _mm_set_epi64x(0x0D0C0F0E09080B0A, 0x0504070601000302);
            return _mm_shuffle_epi8(va, vmsk);
        }
        break;
        case XCHG32: return _mm_shuffle_epi32(va, 0xB1); break;
        case XCHG64: return _mm_shuffle_epi32(va, 0x4E); break;
        case DUPL: return _mm_shuffle_epi32(va, 0x44); break;
        case DUPH: return _mm_shuffle_epi32(va, 0xEE); break;
        default: return va; break;
    }
}

//! \note Shuffle assumes that vector register width is a multiple of 32
static SIMD_FUNC_INLINE
SIMD_FLT simd_shuffle(const SIMD_FLT va, const SHUFFLE_CTRL ctrl)
{
    SIMD_INT va_int = _mm_castps_si128(va);
    switch (ctrl) {
        case XCHG: va_int = _mm_shuffle_epi32(va_int, 0x4E); break;
        case XCHG32: va_int = _mm_shuffle_epi32(va_int, 0xB1); break;
        case XCHG64: va_int = _mm_shuffle_epi32(va_int, 0x4E); break;
        case DUPL: va_int = _mm_shuffle_epi32(va_int, 0x44); break;
        case DUPH: va_int = _mm_shuffle_epi32(va_int, 0xEE); break;
        default: break;
    }
    return _mm_castsi128_ps(va_int);
}

//! \note Shuffle assumes that vector register width is a multiple of 32
static SIMD_FUNC_INLINE
SIMD_DBL simd_shuffle(const SIMD_DBL va, const SHUFFLE_CTRL ctrl)
{
    SIMD_INT va_int = _mm_castpd_si128(va);
    switch (ctrl) {
        case XCHG: va_int = _mm_shuffle_epi32(va_int, 0x4E); break;
        case XCHG64: va_int = _mm_shuffle_epi32(va_int, 0x4E); break;
        case DUPL: va_int = _mm_shuffle_epi32(va_int, 0x44); break;
        case DUPH: va_int = _mm_shuffle_epi32(va_int, 0xEE); break;
        default: break;
    }
    return _mm_castsi128_pd(va_int);
}


/**************************
 *  Convert instructions  *
 **************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_cvt_i16_i32(const SIMD_INT va)
{ return _mm_cvtepi16_epi32(va); }

static SIMD_FUNC_INLINE
SIMD_INT simd_cvt_i32_i64(const SIMD_INT va)
{ return _mm_cvtepi32_epi64(va); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
{ return _mm_cvtepi32_ps(va); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_i32_f64(const SIMD_INT va)
{ return _mm_cvtepi32_pd(va); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_i64_f32(const SIMD_INT va)
{
    /*!
     *  \note Type conversion performed with scalar unit since
     *        vector extensions do not support direct conversion
     */
    int64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    float sa_flt[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm_store_si128((SIMD_INT *)sa, va);
    #pragma unroll
    for (size_t i = 0; i < SIMD_STREAMS_64; ++i) {
        sa_flt[i] = (float)sa[i];
        sa_flt[i + SIMD_STREAMS_64] = 0.0f;
    }
    return _mm_load_ps(sa_flt);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_i64_f64(const SIMD_INT va)
{
    /*!
     *  \note Type conversion performed with scalar unit since
     *        vector extensions do not support direct conversion
     */
    int64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    double sa_dbl[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm_store_si128((SIMD_INT *)sa, va);
    #pragma unroll
    for (size_t i = 0; i < SIMD_STREAMS_64; ++i)
        sa_dbl[i] = (double)sa[i];
    return _mm_load_pd(sa_dbl);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_cvt_u16_i32(const SIMD_INT va)
{ return _mm_cvtepu16_epi32(va); }

static SIMD_FUNC_INLINE
SIMD_INT simd_cvt_u32_i64(const SIMD_INT va)
{ return _mm_cvtepu32_epi64(va); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_u32_f32(const SIMD_INT va)
{ return _mm_cvtepi32_ps(va); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_u32_f64(const SIMD_INT va)
{ return _mm_cvtepi32_pd(va); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_u64_f32(const SIMD_INT va)
{
    /*!
     *  \note Type conversion performed with scalar unit since
     *        vector extensions do not support direct conversion
     */
    uint64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    float sa_flt[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm_store_si128((SIMD_INT *)sa, va);
    #pragma unroll
    for (size_t i = 0; i < SIMD_STREAMS_64; ++i) {
        sa_flt[i] = (float)sa[i];
        sa_flt[i + SIMD_STREAMS_64] = 0.0f;
    }
    return _mm_load_ps(sa_flt);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_u64_f64(const SIMD_INT va)
{
    /*!
     *  \note Type conversion performed with scalar unit since
     *        vector extensions do not support direct conversion
     */
    uint64_t sa[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    double sa_dbl[SIMD_STREAMS_64] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
    _mm_store_si128((SIMD_INT *)sa, va);
    #pragma unroll
    for (size_t i = 0; i < SIMD_STREAMS_64; ++i)
        sa_dbl[i] = (double)sa[i];
    return _mm_load_pd(sa_dbl);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_cvt_f32_i32(const SIMD_FLT va)
{ return _mm_cvtps_epi32(va); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_cvt_f32_f64(const SIMD_FLT va)
{ return _mm_cvtps_pd(va); }

static SIMD_FUNC_INLINE
SIMD_INT simd_cvt_f64_i32(const SIMD_DBL va)
{ return _mm_cvtpd_epi32(va); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_cvt_f64_f32(const SIMD_DBL va)
{ return _mm_cvtpd_ps(va); }


/**********************
 *  Set instructions  *
 **********************/
/*!
 *  Set vector to zero. Use pointer for function overloading.
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

/*!
 *  Set vector with 32/64 elements.
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
SIMD_INT simd_set(const int32_t * const sa, const size_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x((int64_t)sa[1], (int64_t)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm_load_si128((SIMD_INT *)sa);
    else
        return _mm_setzero_si128();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint32_t * const sa, const size_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x((int64_t)sa[1], (int64_t)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm_load_si128((SIMD_INT *)sa);
    else
        return _mm_setzero_si128();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const int64_t * const sa, const size_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x(sa[1], sa[0]);
    else
        return _mm_setzero_si128();
}

static SIMD_FUNC_INLINE
SIMD_INT simd_set(const uint64_t * const sa, const size_t n)
{
    if (n == SIMD_STREAMS_64)
        return _mm_set_epi64x((int64_t)sa[1], (int64_t)sa[0]);
    else
        return _mm_setzero_si128();
}


/***********************
 *  Load instructions  *
 ***********************/
static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int8_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int8_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int16_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int16_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const int32_t * const sa, const size_t n = SIMD_STREAMS_32, const bool strmHint = false)
{
    SIMD_INT va;
    switch (n) {
        case 1: va = _mm_set_epi32(0, 0, 0, sa[0]); break;
        //case 2: va = _mm_set_epi32(0, 0, sa[1], sa[0]); break;
        case 2: va = _mm_loadl_epi64((SIMD_INT *)sa); break;
        case 3: va = _mm_set_epi32(0, sa[2], sa[1], sa[0]); break;
        case 4: va = (strmHint) ? (_mm_stream_load_si128((SIMD_INT *)sa)) : (_mm_load_si128((SIMD_INT *)sa)); break;
        default: va = _mm_setzero_si128(); break;
    }
    return va;
}

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int32_t * const sa, const size_t n = SIMD_STREAMS_32)
{
    //return _mm_loadu_si128((SIMD_INT *)sa);
    SIMD_INT va;
    switch (n) {
        case 1: va = _mm_set_epi32(0, 0, 0, sa[0]); break;
        //case 2: va = _mm_set_epi32(0, 0, sa[1], sa[0]); break;
        case 2: va = _mm_loadl_epi64((SIMD_INT *)sa); break;
        case 3: va = _mm_set_epi32(0, sa[2], sa[1], sa[0]); break;
        case 4: va = _mm_lddqu_si128((SIMD_INT *)sa); break;
        default: va = _mm_setzero_si128(); break;
    }
    return va;
}

static SIMD_FUNC_INLINE
SIMD_INT simd_load(const uint8_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const uint8_t * const sa)
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
SIMD_FLT simd_load(const float * const sa, const size_t n = SIMD_STREAMS_32, const bool strmHint = false)
{
    SIMD_FLT va;
    switch (n) {
        case 1: va = _mm_load_ss(sa); break;
        case 2: va = _mm_set_ps(0.0f, 0.0f, sa[1], sa[0]); break;
        case 3: va = _mm_set_ps(0.0f, sa[2], sa[1], sa[0]); break;
        case 4: va = (strmHint) ? (_mm_castsi128_ps(_mm_stream_load_si128((SIMD_INT *)sa))) : (_mm_load_ps(sa)); break;
        default: va = _mm_setzero_ps(); break;
    }
    return va;
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_loadu(const float * const sa, const size_t n = SIMD_STREAMS_32)
{
    SIMD_FLT va;
    switch (n) {
        case 1: va = _mm_load_ss(sa); break;
        case 2: va = _mm_set_ps(0.0f, 0.0f, sa[1], sa[0]); break;
        case 3: va = _mm_set_ps(0.0f, sa[2], sa[1], sa[0]); break;
        case 4: va = _mm_loadu_ps(sa); break;
        default: va = _mm_setzero_ps(); break;
    }
    return va;
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_load(const double * const sa, const size_t n = SIMD_STREAMS_64, const bool strmHint = false)
{
    SIMD_DBL va;
    switch (n) {
        case 1: va = _mm_load_sd(sa); break;
        case 2: va = (strmHint) ? (_mm_castsi128_pd(_mm_stream_load_si128((SIMD_INT *)sa))) : (_mm_load_pd(sa)); break;
        default: va = _mm_setzero_pd(); break;
    }
    return va;
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_loadu(const double * const sa, const size_t n = SIMD_STREAMS_64)
{
    SIMD_DBL va;
    switch (n) {
        case 1: va = _mm_load_sd(sa); break;
        case 2: va = _mm_loadu_pd(sa); break;
        default: va = _mm_setzero_pd(); break;
    }
    return va;
}


/************************
 *  Store instructions  *
 ************************/
static SIMD_FUNC_INLINE
void simd_store(int8_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int8_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(int16_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int16_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_store(int32_t * const sa, const SIMD_INT va, const size_t n = SIMD_STREAMS_32, const bool strmHint = false)
{
    switch (n) {
        case 1:
        case 2:
        case 3:
            {
                int32_t tmp[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
                _mm_store_si128((SIMD_INT *)tmp, va);
                for (size_t i = 0; i < n; ++i)
                    sa[i] = tmp[i];
            }
            break;
        case 4: (strmHint) ? (_mm_stream_si128((SIMD_INT *)sa, va)) : (_mm_store_si128((SIMD_INT *)sa, va)); break;
        default: break;
    }
}

static SIMD_FUNC_INLINE
void simd_storeu(int32_t * const sa, const SIMD_INT va, const size_t n = SIMD_STREAMS_32)
{
    switch (n) {
        case 1:
        case 2:
        case 3:
            {
                int32_t tmp[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
                _mm_store_si128((SIMD_INT *)tmp, va);
                for (size_t i = 0; i < n; ++i)
                    sa[i] = tmp[i];
            }
            break;
        case 4: _mm_storeu_si128((SIMD_INT *)sa, va); break;
        default: break;
    }
}

static SIMD_FUNC_INLINE
void simd_store(uint8_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(uint8_t * const sa, const SIMD_INT va)
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
void simd_store(float * const sa, const SIMD_FLT va, const size_t n = SIMD_STREAMS_32, const bool strmHint = false)
{
    switch (n) {
        case 1: _mm_store_ss(sa, va); break;
        case 2:
        case 3:
            {
                float tmp[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
                _mm_store_ps(tmp, va);
                for (size_t i = 0; i < n; ++i)
                    sa[i] = tmp[i];
            }
            break;
        case 4: (strmHint) ? (_mm_stream_ps(sa, va)) : (_mm_store_ps(sa, va)); break;
        default: break;
    }
}

static SIMD_FUNC_INLINE
void simd_storeu(float * const sa, const SIMD_FLT va, const size_t n = SIMD_STREAMS_32)
{
    switch (n) {
        case 1: _mm_store_ss(sa, va); break;
        case 2:
        case 3:
            {
                float tmp[SIMD_STREAMS_32] SIMD_ALIGNED(SIMD_WIDTH_BYTES);
                _mm_store_ps(tmp, va);
                for (size_t i = 0; i < n; ++i)
                    sa[i] = tmp[i];
            }
            break;
        case 4: _mm_store_ps(sa, va); break;
        default: break;
    }
}

static SIMD_FUNC_INLINE
void simd_store(double * const sa, const SIMD_DBL va, const size_t n = SIMD_STREAMS_64, const bool strmHint = false)
{
    switch (n) {
        case 1: _mm_store_sd(sa, va); break;
        case 2: (strmHint) ? (_mm_stream_pd(sa, va)) : (_mm_store_pd(sa, va)); break;
        default: break;
    }
}

static SIMD_FUNC_INLINE
void simd_storeu(double * const sa, const SIMD_DBL va, const size_t n = SIMD_STREAMS_64)
{
    switch (n) {
        case 1: _mm_store_sd(sa, va); break;
        case 2: _mm_storeu_pd(sa, va); break;
        default: break;
    }
}



///////////////////////////////////////////////////////////////////////////////

/*
 *  Identify OpenMP support
 */
#if defined(_OPENMP)
#   include <omp.h>
#endif

#include <unistd.h>  // sysconf

/*!
 *  \brief Class to represent system configuration
 */
class SYSCONF
{
    protected:
        static bool omp_enabled;
        static int32_t omp_threads;
        static size_t L1l_elems_i32;
        static size_t L1c_elems_i32;
        static size_t L2l_elems_i32;
        static size_t L2c_elems_i32;
        static size_t page_sz;

    public:
        /************
         *  OpenMP  *
         ************/
        /*!
         *  If \c nthreads < 1, the environment variable OMP_NUM_THREADS is used
         *  OpenMP only gets activated if set_omp() is invoked
         *  \todo Fix logic of OpenMP setting
         */
        static void set_omp(const int32_t nthreads)
        {
        #if defined(_OPENMP)
            if (nthreads == 0 || nthreads == 1) {
                omp_threads = 1;
                omp_enabled = false;
            } else {
                int32_t nt = atoi(getenv("OMP_NUM_THREADS"));
                if (nt > 0)
                    nt = (nthreads > 0) ? (nthreads) : (nt);
                else
                    nt = (nthreads > 0) ? (nthreads) : (1);
                //omp_set_num_threads(nt);
                omp_threads = nt;
                omp_enabled = true;
            }
            //setenv("OMP_PROC_BIND","TRUE",1);
            //setenv("GOMP_CPU_AFFINITY","0,2,4,6,1,3,5,7",1);
            //setenv("GOMP_CPU_AFFINITY","0,1,2,3",1);
            //setenv("OMP_PLACES","sockets{2}",1);
            //setenv("OMP_PLACES","cores",1);
            //setenv("OMP_PLACES","threads",1);
        #else
            (void)nthreads;
            omp_threads = 1;
            omp_enabled = false;
        #endif
        }

        static bool get_omp()
        { return omp_enabled; }

        static int32_t get_threads()
        { return omp_threads; }

        static void omp_settings()
        {
        #if defined(_OPENMP)
            if (get_omp()) {
                cout << "OpenMP is enabled" << endl;
                cout << "OpenMP max threads = " << get_threads() << endl;
            }
            else {
                cout << "OpenMP is disabled" << endl;
            }
        #else
            omp_enabled = false;
            cout << "OpenMP is disabled" << endl;
        #endif
        }

        /*!
         *  Initialize system configurations
         */
        static int32_t initSysconf()
        {
            omp_enabled = false;
            omp_threads = 1;
            L1l_elems_i32 = (size_t)getL1LineSz() / sizeof(int32_t);
            L1c_elems_i32 = (size_t)getL1Sz() / sizeof(int32_t);
            L2l_elems_i32 = (size_t)getL2LineSz() / sizeof(int32_t);
            L2c_elems_i32 = (size_t)getL2Sz() / sizeof(int32_t);
            page_sz = (size_t)getPageSz();

            return 0;
        }

        /*!
         *  Print some system configurations
         */
        static void printSysconf()
        {
            cout << "Number of processors online = " << getNumProcOnline() << endl;
            cout << "Page size = " << getPageSz() << " B" << endl;

            cout << "L1 data cache size = " << getL1Sz() << " B" << endl;
            cout << "L1 data cache line size = " << getL1LineSz() << " B" << endl;
            cout << "L1 data cache associativity = " << getL1Assoc() << endl;

            cout << "L2 cache size = " << getL2Sz() << " B" << endl;
            cout << "L2 cache line size = " << getL2LineSz() << " B" << endl;
            cout << "L2 cache associativity = " << getL2Assoc() << endl;

            cout << "L3 cache size = " << getL3Sz() << " B" << endl;
            cout << "L3 cache line size = " << getL3LineSz() << " B" << endl;
            cout << "L3 cache associativity = " << getL3Assoc() << endl;
        }

        /*!
         *  Get the number of processors currently online (available)
         */
        static long int getNumProcOnline()
        { return sysconf(_SC_NPROCESSORS_ONLN); }
        //{ return sysconf(_SC_NPROCESSORS_CONF); }

        /*!
         *  Get the size of page in bytes
         */
        static long int getPageSz()
        { return sysconf(_SC_PAGESIZE); }
        //{ return sysconf(_SC_PAGE_SIZE); }

        /*!
         *  Get the size in bytes of L1 data cache
         */
        static long int getL1Sz()
        { return sysconf(_SC_LEVEL1_DCACHE_SIZE); }

        /*!
         *  Get the line size in bytes of L1 data cache
         */
        static long int getL1LineSz()
        { return sysconf(_SC_LEVEL1_DCACHE_LINESIZE); }

        /*!
         *  Get the associativity of L1 data cache
         */
        static long int getL1Assoc()
        { return sysconf(_SC_LEVEL1_DCACHE_ASSOC); }

        /*!
         *  Get the size in bytes of L2 cache
         */
        static long int getL2Sz()
        { return sysconf(_SC_LEVEL2_CACHE_SIZE); }

        /*!
         *  Get the line size in bytes of L2 cache
         */
        static long int getL2LineSz()
        { return sysconf(_SC_LEVEL2_CACHE_LINESIZE); }

        /*!
         *  Get the associativity of L2 cache
         */
        static long int getL2Assoc()
        { return sysconf(_SC_LEVEL2_CACHE_ASSOC); }

        /*!
         *  Get the size in bytes of L3 cache
         */
        static long int getL3Sz()
        { return sysconf(_SC_LEVEL3_CACHE_SIZE); }

        /*!
         *  Get the line size in bytes of L3 cache
         */
        static long int getL3LineSz()
        { return sysconf(_SC_LEVEL3_CACHE_LINESIZE); }

        /*!
         *  Get the associativity of L3 cache
         */
        static long int getL3Assoc()
        { return sysconf(_SC_LEVEL3_CACHE_ASSOC); }
};


/*!
 *  \class base_v
 *  \brief Abstract class to represent a vector object
 */
class base_v
{
    public:
        virtual ~base_v() {};  //!< virtual destructor allows polymorphism to invoke derived destructors
        static size_t get_nstreams() { return 0; };
        static size_t get_nbytes() { return 0; };
};


#define VCLASS int32_v
#define VTYPE SIMD_INT
#define STYPE int32_t
/*!
 *  \class int32_v
 *  \brief Class to represent a 32-bit integer vector
 */
class VCLASS: public base_v
{
    private:
        VTYPE v;
        static const size_t nstreams = SIMD_STREAMS_32;
        static const size_t nbytes = SIMD_WIDTH_BYTES;

    public:

        /******************
         *  Constructors  *
         ******************/
        //! Constructor with no parameters
        VCLASS()
        { simd_set_zero(&v); }

        //! (Low-level) Copy constructor
        VCLASS(const VTYPE va): v(va)
        { }

        //! Copy constructor
        VCLASS(const VCLASS &va): v(va.v)
        { }

        /*!
         *  Constructor with scalar pointer parameter
         *  Does not assumes \c sa alignment is conformant
         */
        VCLASS(const STYPE * const sa, const size_t n = nstreams)
        { loadu(sa, n); }

        ~VCLASS()
        { }

        /*************
         *  Get/set  *
         *************/
        static SIMD_FUNC_INLINE size_t get_nstreams()
        { return nstreams; }

        static SIMD_FUNC_INLINE size_t get_nbytes()
        { return nbytes; }

        SIMD_FUNC_INLINE void set_vector(const VTYPE va)
        { v = va; }

        SIMD_FUNC_INLINE VTYPE get_vector() const
        { return v; }

        /****************
         *  Operations  *
         ****************/
        SIMD_FUNC_INLINE VCLASS operator+(const VCLASS& vb) const
        {
            VCLASS vc(simd_add_32(v, vb.v));
            return vc;
        }

        /****************
         *  Load/Store  *
         ****************/
        SIMD_FUNC_INLINE void load(const STYPE * const sa, const size_t n = nstreams, const bool strmHint = false)
        { v = simd_load((const STYPE *)sa, n, strmHint); }

        SIMD_FUNC_INLINE void store(STYPE * const sa, const size_t n = nstreams, const bool strmHint = false) const
        { simd_store(sa, v, n, strmHint); }

        SIMD_FUNC_INLINE void loadu(const STYPE * const sa, const size_t n = nstreams)
        { v = simd_loadu((const STYPE *)sa, n); }

        SIMD_FUNC_INLINE void storeu(STYPE * const sa, const size_t n = nstreams) const
        { simd_storeu(sa, v, n); }
};

//! Kernel is memory-bound, use 2 threads to prevent bus contention
static SIMD_FUNC_INLINE STYPE * add(const STYPE * const sa, const STYPE * const sb, const size_t n = SIMD_STREAMS_32, const bool run_par = true)
{
    STYPE *sc = NULL;
    if (!posix_memalign((void **)&sc, SIMD_WIDTH_BYTES, n * sizeof(STYPE))) {
        const size_t rem = n & (SIMD_STREAMS_32 - 1);
        const size_t nn = n - rem;
        const size_t salign = (((size_t)sa & (SIMD_WIDTH_BYTES - 1)) | ((size_t)sb & (SIMD_WIDTH_BYTES - 1)));
        #pragma omp parallel for default(shared) schedule(static) num_threads(2) if ((SYSCONF::get_omp() & run_par) == true)
        for (size_t i = 0; i < nn; i+=SIMD_STREAMS_32) {
            VTYPE va, vb;
            if (salign == 0) {
                va = simd_load(sa + i, SIMD_STREAMS_32, true);
                vb = simd_load(sb + i, SIMD_STREAMS_32, true);
            } else {
                va = simd_loadu(sa + i);
                vb = simd_loadu(sb + i);
            }
            vb = simd_add_32(va, vb);
            simd_store(sc + i, vb, SIMD_STREAMS_32, true);
        }
        for (size_t i = nn; i < n; ++i) {
            sc[i] = sa[i] + sb[i];
        }
    }
    (void)run_par;  // used in OpenMP pragma but compiler identifies it as not used
    return sc;
}
#undef STYPE
#undef VTYPE
#undef VCLASS


#define VCLASS flt32_v
#define VTYPE SIMD_FLT
#define STYPE float
/*!
 *  \class flt32_v
 *  \brief Class to represent a single-precision floating-point vector
 */
class VCLASS: public base_v
{
    private:
        VTYPE v;
        static const size_t nstreams = SIMD_STREAMS_32;
        static const size_t nbytes = SIMD_WIDTH_BYTES;

    public:
        /******************
         *  Constructors  *
         ******************/
        VCLASS()
        { simd_set_zero(&v); }

        VCLASS(const VTYPE va): v(va)
        { }

        VCLASS(const VCLASS &va): v(va.v)
        { }

        VCLASS(const STYPE * const sa, const size_t n = nstreams)
        { loadu(sa, n); }

        ~VCLASS()
        { }

        /*************
         *  Get/set  *
         *************/
        static SIMD_FUNC_INLINE size_t get_nstreams()
        { return nstreams; }

        static SIMD_FUNC_INLINE size_t get_nbytes()
        { return nbytes; }

        SIMD_FUNC_INLINE void set_vector(const VTYPE va)
        { v = va; }

        SIMD_FUNC_INLINE VTYPE get_vector() const
        { return v; }

        /****************
         *  Operations  *
         ****************/
        SIMD_FUNC_INLINE VCLASS operator+(const VCLASS& vb) const
        {
            VCLASS vc(simd_add(v, vb.v));
            return vc;
        }

        /****************
         *  Load/Store  *
         ****************/
        SIMD_FUNC_INLINE void load(const STYPE * const sa, const size_t n = nstreams, const bool strmHint = false)
        { v = simd_load((const STYPE *)sa, n, strmHint); }

        SIMD_FUNC_INLINE void store(STYPE * const sa, const size_t n = nstreams, const bool strmHint = false) const
        { simd_store(sa, v, n, strmHint); }

        SIMD_FUNC_INLINE void loadu(const STYPE * const sa, const size_t n = nstreams)
        { v = simd_loadu((const STYPE *)sa, n); }

        SIMD_FUNC_INLINE void storeu(STYPE * const sa, const size_t n = nstreams) const
        { simd_storeu(sa, v, n); }
};

static SIMD_FUNC_INLINE STYPE * add(const STYPE * const sa, const STYPE * const sb, const size_t n = SIMD_STREAMS_32, const bool run_par = true)
{
    STYPE *sc = NULL;
    if (!posix_memalign((void **)&sc, SIMD_WIDTH_BYTES, n * sizeof(STYPE))) {
        const size_t rem = n & (SIMD_STREAMS_32 - 1);
        const size_t nn = n - rem;
        const size_t salign = (((size_t)sa & (SIMD_WIDTH_BYTES - 1)) | ((size_t)sb & (SIMD_WIDTH_BYTES - 1)));
        #pragma omp parallel for default(shared) schedule(static) num_threads(SYSCONF::get_threads()) if ((SYSCONF::get_omp() & run_par) == true)
        for (size_t i = 0; i < nn; i+=SIMD_STREAMS_32) {
            VTYPE va, vb;
            if (salign == 0) {
                //va = simd_load(sa + i, SIMD_STREAMS_32, true);
                //vb = simd_load(sb + i, SIMD_STREAMS_32, true);
                va = simd_load(sa + i);
                vb = simd_load(sb + i);
            } else {
                va = simd_loadu(sa + i);
                vb = simd_loadu(sb + i);
            }
            vb = simd_add(va, vb);
            simd_store(sc + i, vb, SIMD_STREAMS_32, true);
        }
        for (size_t i = nn; i < n; ++i) {
            sc[i] = sa[i] + sb[i];
        }
    }
    (void)run_par;  // used in OpenMP pragma but compiler identifies it as not used
    return sc;
}
#undef STYPE
#undef VTYPE
#undef VCLASS


#define VCLASS flt64_v
#define VTYPE SIMD_DBL
#define STYPE double
/*!
 *  \class flt64_v
 *  \brief Class to represent a double-precision floating-point vector
 */
class VCLASS: public base_v
{
    private:
        VTYPE v;
        static const size_t nstreams = SIMD_STREAMS_64;
        static const size_t nbytes = SIMD_WIDTH_BYTES;

    public:
        /******************
         *  Constructors  *
         ******************/
        VCLASS()
        { simd_set_zero(&v); }

        VCLASS(const VTYPE va): v(va)
        { }

        VCLASS(const VCLASS &va): v(va.v)
        { }

        VCLASS(const STYPE * const sa, const size_t n = nstreams)
        { loadu(sa, n); }

        ~VCLASS()
        { }

        /*************
         *  Get/set  *
         *************/
        static SIMD_FUNC_INLINE size_t get_nstreams()
        { return nstreams; }

        static SIMD_FUNC_INLINE size_t get_nbytes()
        { return nbytes; }

        SIMD_FUNC_INLINE void set_vector(const VTYPE va)
        { v = va; }

        SIMD_FUNC_INLINE VTYPE get_vector() const
        { return v; }

        /****************
         *  Operations  *
         ****************/
        SIMD_FUNC_INLINE VCLASS operator+(const VCLASS& vb) const
        {
            VCLASS vc(simd_add(v, vb.v));
            return vc;
        }

        /****************
         *  Load/Store  *
         ****************/
        SIMD_FUNC_INLINE void load(const STYPE * const sa, const size_t n = nstreams, const bool strmHint = false)
        { v = simd_load((const STYPE *)sa, n, strmHint); }

        SIMD_FUNC_INLINE void store(STYPE * const sa, const size_t n = nstreams, const bool strmHint = false) const
        { simd_store(sa, v, n, strmHint); }

        SIMD_FUNC_INLINE void loadu(const STYPE * const sa, const size_t n = nstreams)
        { v = simd_loadu((const STYPE *)sa, n); }

        SIMD_FUNC_INLINE void storeu(STYPE * const sa, const size_t n = nstreams) const
        { simd_storeu(sa, v, n); }
};

static SIMD_FUNC_INLINE STYPE * add(const STYPE * const sa, const STYPE * const sb, const size_t n = SIMD_STREAMS_64, const bool run_par = true)
{
    STYPE *sc = NULL;
    if (!posix_memalign((void **)&sc, SIMD_WIDTH_BYTES, n * sizeof(STYPE))) {
        const size_t rem = n & (SIMD_STREAMS_64 - 1);
        const size_t nn = n - rem;
        const size_t salign = (((size_t)sa & (SIMD_WIDTH_BYTES - 1)) | ((size_t)sb & (SIMD_WIDTH_BYTES - 1)));
        #pragma omp parallel for default(shared) schedule(static) num_threads(SYSCONF::get_threads()) if ((SYSCONF::get_omp() & run_par) == true)
        for (size_t i = 0; i < nn; i+=SIMD_STREAMS_64) {
            VTYPE va, vb;
            if (salign == 0) {
                //va = simd_load(sa + i, SIMD_STREAMS_64, true);
                //vb = simd_load(sb + i, SIMD_STREAMS_64, true);
                va = simd_load(sa + i);
                vb = simd_load(sb + i);
            } else {
                va = simd_loadu(sa + i);
                vb = simd_loadu(sb + i);
            }
            vb = simd_add(va, vb);
            simd_store(sc + i, vb, SIMD_STREAMS_64, true);
        }
        for (size_t i = nn; i < n; ++i) {
            sc[i] = sa[i] + sb[i];
        }
    }
    (void)run_par;  // used in OpenMP pragma but compiler identifies it as not used
    return sc;
}
#undef STYPE
#undef VTYPE
#undef VCLASS
///////////////////////////////////////////////////////////////////////////////


}  // SSE4_2 namespace


using namespace SSE4_2;


#endif  // _SSE4_2_H

