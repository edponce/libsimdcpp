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
 */
#ifndef _SSE4_2_H
#define _SSE4_2_H


// NOTE: Include comments inside namespace for correct module listing in documentation
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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_shuffle_32(const SIMD_INT va, const int8_t ctrl)
 *  \brief Shuffle 32-bit integers
 *  \code{.c}
 *  for (int i = 0; i < 4; ++i) {
 *      int j = i * 32;
 *      int k = i * 2;
 *      switch (ctrl[k:k+1]) {
 *          case 0: vc[j:j+31] = va[0:31]; break;
 *          case 1: vc[j:j+31] = va[32:63]; break;
 *          case 2: vc[j:j+31] = va[64:95]; break;
 *          case 3: vc[j:j+31] = va[96:127]; break;
 *      }
 *  }
 *  \endcode
 *  \param[in] va Vector register to shuffle
 *  \return vc
 *
 *  \}
 */


#include "compiler_attributes.h"
#include "compiler_builtins.h"
#include <nmmintrin.h>
//#include <x86intrin.h>
#include <stdint.h>


const int32_t SIMD_WIDTH_BITS = 128;
const int32_t SIMD_WIDTH_BYTES = SIMD_WIDTH_BITS / 8;
const int32_t SIMD_STREAMS_8 = SIMD_WIDTH_BYTES;
const int32_t SIMD_STREAMS_16 = SIMD_WIDTH_BYTES / 2;
const int32_t SIMD_STREAMS_32 = SIMD_WIDTH_BYTES / 4;
const int32_t SIMD_STREAMS_64 = SIMD_WIDTH_BYTES / 8;
typedef __m128i SIMD_INT;
typedef __m128  SIMD_FLT;
typedef __m128d SIMD_DBL;


/*****************************
 *  Arithmetic instructions  *
 *****************************/
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


//! \todo Move this to somewhere else
enum SHUFFLE_CTRL { XCHG = 0, // Exchange lower/upper halfs of register
                    XCHG8,    // Exchange pairs of 8-bit elements
                    XCHG16,   // Exchange pairs of 16-bit elements
                    XCHG32,   // Exchange pairs of 32-bit elements
                    XCHG64,   // Exchange pairs of 64-bit elements
                    DUPL,     // Duplicate lower half into upper half of register
                    DUPH      // Duplicate upper half into lower half of register
                  };



static SIMD_FUNC_INLINE
SIMD_INT simd_shuffle(const SIMD_INT va, const SHUFFLE_CTRL ctrl)
{
    //! \note Options assume that vector register width is a multiple of 32
    //! \todo Missing XCHG8 and XCHG16
    switch (ctrl) {
        case XCHG: return _mm_shuffle_epi32(va, 0x4E); break;
        case XCHG32: return _mm_shuffle_epi32(va, 0xB1); break;
        case XCHG64: return _mm_shuffle_epi32(va, 0x4E); break;
        case DUPL: return _mm_shuffle_epi32(va, 0x44); break;
        case DUPH: return _mm_shuffle_epi32(va, 0xEE); break;
        default: return va; break;
    }
}


#if !defined(__clang__)
static SIMD_FUNC_INLINE
SIMD_FLT simd_shuffle(const SIMD_FLT va, const SIMD_FLT vb, const int8_t ctrl)
{ return _mm_shuffle_ps(va, vb, ctrl); }
#endif


/**********************
 *  Set instructions  *
 **********************/
/*!
 *  \defgroup Set_SSE4_2 Set instructions
 *  \ingroup SSE4_2
 *  \brief Set instructions supported by SIMD interface
 *  \{
 */

/*
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

/*!
 *  \}
 */


/**************************
 *  Convert instructions  *
 **************************/
/*!
 *  \defgroup Convert_SSE4_2 Convert instructions
 *  \ingroup SSE4_2
 *  \brief Convert instructions supported by SIMD interface
 *  \{
 */

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

/*!
 *  \}
 */


/***********************
 *  Load instructions  *
 ***********************/
/*!
 *  \defgroup Load_SSE4_2 Load instructions
 *  \ingroup SSE4_2
 *  \brief Load instructions supported by SIMD interface
 *  \{
 */

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
SIMD_INT simd_load(const int32_t * const sa)
{ return _mm_load_si128((SIMD_INT *)sa); }

static SIMD_FUNC_INLINE
SIMD_INT simd_loadu(const int32_t * const sa)
//{ return _mm_loadu_si128((SIMD_INT *)sa); }
{ return _mm_lddqu_si128((SIMD_INT *)sa); }

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

/*!
 *  \}
 */


/************************
 *  Store instructions  *
 ************************/
/*!
 *  \defgroup Store_SSE4_2 Store instructions
 *  \ingroup SSE4_2
 *  \brief Store instructions supported by SIMD interface
 *  \{
 */

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
void simd_store(int32_t * const sa, const SIMD_INT va)
{ _mm_store_si128((SIMD_INT *)sa, va); }

static SIMD_FUNC_INLINE
void simd_storeu(int32_t * const sa, const SIMD_INT va)
{ _mm_storeu_si128((SIMD_INT *)sa, va); }

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

/*!
 *  \}
 */


}  // SSE4_2 namespace


using namespace SSE4_2;


#endif  // _SSE4_2_H

