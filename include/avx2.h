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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed/unsigned 16-bit integers
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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed/unsigned 32-bit integers
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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_add_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Add signed/unsigned 64-bit integers
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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_16(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed/unsigned 16-bit integers
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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_32(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed/unsigned 32-bit integers
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
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sub_64(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Subtract signed/unsigned 64-bit integers
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


/*!
 *  \defgroup Logic_AVX2 Logical instructions
 *  \ingroup AVX2
 *  \brief Logical instructions supported by SIMD interface
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Bitwise OR of integral numbers
 *  \code{.c}
 *      vc[0:SIMD_WIDTH_BITS-1] = va[0:SIMD_WIDTH_BITS-1] | vb[0:SIMD_WIDTH_BITS-1];
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Bitwise XOR of integral numbers
 *  \code{.c}
 *      vc[0:SIMD_WIDTH_BITS-1] = va[0:SIMD_WIDTH_BITS-1] ^ vb[0:SIMD_WIDTH_BITS-1];
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Bitwise AND of integral numbers
 *  \code{.c}
 *      vc[0:SIMD_WIDTH_BITS-1] = va[0:SIMD_WIDTH_BITS-1] & vb[0:SIMD_WIDTH_BITS-1];
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
 *  \brief Bitwise AND of single-precision floating-point number and integral number
 *  \code{.c}
 *      vc[0:SIMD_WIDTH_BITS-1] = (SIMD_FLT)((SIMD_INT)va[0:SIMD_WIDTH_BITS-1] & vb[0:SIMD_WIDTH_BITS-1]);
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
 *  \brief Bitwise AND of double-precision floating-point number and integral number
 *  \code{.c}
 *      vc[0:SIMD_WIDTH_BITS-1] = (SIMD_DBL)((SIMD_INT)va[0:SIMD_WIDTH_BITS-1] & vb[0:SIMD_WIDTH_BITS-1]);
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *  \}
 */


/*!
 *  \defgroup ShiftShuffle_AVX2 Shift and shuffle instructions
 *  \ingroup AVX2
 *  \brief Shift and shuffle instructions supported by SIMD interface
 *  \{
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_16(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 16-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_16; ++j) {
 *      int i = j * 16;
 *      if (shft > 15)
 *          vc[i:i+15] = 0;
 *      else
 *          vc[i:i+15] = ZeroExtend(va[i:i+15] << shft);
 *  }
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_32(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 32-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      if (shft > 31)
 *          vc[i:i+31] = 0;
 *      else
 *          vc[i:i+31] = ZeroExtend(va[i:i+31] << shft);
 *  }
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_64(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 64-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      if (shft > 63)
 *          vc[i:i+63] = 0;
 *      else
 *          vc[i:i+63] = ZeroExtend(va[i:i+63] << shft);
 *  }
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_sll_128(const SIMD_INT va, const int8_t shft)
 *  \brief Shift left logical packed 128-bit integers (at byte level) while shifting in zeros
 *  \code{.c}
 *  if (shft > 15)
 *      shft = 16;
 *  vc[0:127] = va[0:127] << (shft * 8);
 *  vc[128:255] = va[128:255] << (shft * 8);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_16(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 16-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_16; ++j) {
 *      int i = j * 16;
 *      if (shft > 15)
 *          vc[i:i+15] = 0;
 *      else
 *          vc[i:i+15] = ZeroExtend(va[i:i+15] >> shft);
 *  }
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_32(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 32-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_32; ++j) {
 *      int i = j * 32;
 *      if (shft > 31)
 *          vc[i:i+31] = 0;
 *      else
 *          vc[i:i+31] = ZeroExtend(va[i:i+31] >> shft);
 *  }
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_64(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 64-bit integers while shifting in zeros
 *  \code{.c}
 *  for (int j = 0; j < SIMD_STREAMS_64; ++j) {
 *      int i = j * 64;
 *      if (shft > 63)
 *          vc[i:i+63] = 0;
 *      else
 *          vc[i:i+63] = ZeroExtend(va[i:i+63] >> shft);
 *  }
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_srl_128(const SIMD_INT va, const int8_t shft)
 *  \brief Shift right logical packed 128-bit integers (at byte level) while shifting in zeros
 *  \code{.c}
 *  if (shft > 15)
 *      shft = 16;
 *  vc[0:127] = va[0:127] >> (shft * 8);
 *  vc[128:255] = va[128:255] >> (shft * 8);
 *  \endcode
 *  \param[in] va Vector register to shift
 *  \param[in] shft Shift amount
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Merge low parts from pair of 16/32/64-bit integer registers
 *  \code{.c}
 *  vc[0:127] = va[0:127]
 *  vc[128:255] = vb[0:127]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Merge low parts from pair of single-precision floating point registers
 *  \code{.c}
 *  vc[0:31] = va[0:31]
 *  vc[32:63] = va[32:63]
 *  vc[64:95] = va[64:95]
 *  vc[96:127] = va[96:127]
 *  vc[128:159] = vb[0:31]
 *  vc[160:191] = vb[32:63]
 *  vc[192:223] = vb[64:95]
 *  vc[224:255] = vb[96:127]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Merge low parts from pair of double-precision floating point registers
 *  \code{.c}
 *  vc[0:63] = va[0:63]
 *  vc[64:127] = va[64:127]
 *  vc[128:191] = vb[0:63]
 *  vc[192:255] = vb[64:127]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
 *  \brief Merge high parts from pair of 16/32/64-bit integer registers
 *  \code{.c}
 *  vc[0:127] = va[128:255]
 *  vc[128:255] = vb[128:255]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Merge high parts from pair of single-precision floating point registers
 *  \code{.c}
 *  vc[0:31] = va[128:159]
 *  vc[32:63] = va[160:191]
 *  vc[64:95] = va[192:223]
 *  vc[96:127] = va[224:255]
 *  vc[128:159] = vb[128:159]
 *  vc[160:191] = vb[160:191]
 *  vc[192:223] = vb[192:223]
 *  vc[224:255] = vb[224:255]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
 *  \brief Merge high parts from pair of double-precision floating point registers
 *  \code{.c}
 *  vc[0:63] = va[128:191]
 *  vc[64:127] = va[192:255]
 *  vc[128:191] = vb[128:191]
 *  vc[192:255] = vb[192:255]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_INT simd_packmerge_lo(SIMD_INT va, SIMD_INT vb)
 *  \brief Pack and merge the low 32-bit integers from 64-bit elements
 *  \code{.c}
 *  vc[0:31] = va[0:31]
 *  vc[32:63] = va[64:95]
 *  vc[64:95] = va[128:159]
 *  vc[96:127] = va[192:223]
 *  vc[128:159] = vb[0:31]
 *  vc[160:191] = vb[64:95]
 *  vc[192:223] = vb[128:159]
 *  vc[224:255] = vb[192:223]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
 *
 *
 *  \fn static SIMD_FUNC_INLINE SIMD_FLT simd_packmerge_lo(const SIMD_FLT va, const SIMD_FLT vb)
 *  \brief Pack and merge the low single-precision floating-point number from 64-bit elements
 *  \code{.c}
 *  vc[0:31] = va[0:31]
 *  vc[32:63] = va[64:95]
 *  vc[64:95] = va[128:159]
 *  vc[96:127] = va[192:223]
 *  vc[128:159] = vb[0:31]
 *  vc[160:191] = vb[64:95]
 *  vc[192:223] = vb[128:159]
 *  vc[224:255] = vb[192:223]
 *  \endcode
 *  \param[in] va First operand
 *  \param[in] vb Second operand
 *  \return vc
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
const int32_t SIMD_STREAMS_8 = SIMD_WIDTH_BYTES;
const int32_t SIMD_STREAMS_16 = SIMD_WIDTH_BYTES / 2;
const int32_t SIMD_STREAMS_32 = SIMD_WIDTH_BYTES / 4;
const int32_t SIMD_STREAMS_64 = SIMD_WIDTH_BYTES / 8;
typedef __m256i SIMD_INT;
typedef __m256  SIMD_FLT;
typedef __m256d SIMD_DBL;


/*****************************
 *  Arithmetic instructions  *
 *****************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_add_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_add_64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_add_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_add_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_add_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_hadd_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_hadd_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_hadd_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_hadd_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_hadd(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_hadd_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_hadd(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_hadd_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_sub_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_sub_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sub_64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_sub_epi64(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_sub(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_sub_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_sub(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_sub_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_hsub_16(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_hsub_epi16(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_hsub_32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_hsub_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_hsub(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_hsub_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_hsub(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_hsub_pd(va, vb); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmadd(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
#if defined(__FMA__)
    return _mm256_fmadd_ps(va, vb, vc);
#else
    va = _mm256_mul_ps(va, vb);
    return _mm256_add_ps(va, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmadd(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
#if defined(__FMA__)
    return _mm256_fmadd_pd(va, vb, vc);
#else
    va = _mm256_mul_pd(va, vb);
    return _mm256_add_pd(va, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_fmsub(SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
#if defined(__FMA__)
    return _mm256_fmsub_ps(va, vb, vc);
#else
    va = _mm256_mul_ps(va, vb);
    return _mm256_sub_ps(va, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_fmsub(SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
#if defined(__FMA__)
    return _mm256_fmsub_pd(va, vb, vc);
#else
    va = _mm256_mul_pd(va, vb);
    return _mm256_sub_pd(va, vc);
#endif
}

static SIMD_FUNC_INLINE
SIMD_INT simd_mullo_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mullo_epi32(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mul_epi32(va, vb); }

/*!
 *  x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_i64(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vlo, vhi;
    vlo = _mm256_shuffle_epi32(vb, 0xB1);  // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vlo);     // xl * yh, xh * yl
    vlo = _mm256_slli_epi64(vhi, 0x20);    // shift << 32
    vhi = _mm256_add_epi64(vhi, vlo);      // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl
    return _mm256_add_epi64(vlo, vhi);     // l + h
/*
    // This implementation uses a temp register
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
}

static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_mul_epu32(va, vb); }

/*!
 *  x64 * y64 = (xl * yl) + (xl * yh + xh * yl) * 2^32
 */
static SIMD_FUNC_INLINE
SIMD_INT simd_mul_u64(const SIMD_INT va, const SIMD_INT vb)
{
    const SIMD_INT vmsk = _mm256_set1_epi64x(0xFFFFFFFF00000000UL);
    SIMD_INT vlo, vhi;
    vlo = _mm256_shuffle_epi32(vb, 0xB1);  // shuffle multiplier
    vhi = _mm256_mullo_epi32(va, vlo);     // xl * yh, xh * yl
    vlo = _mm256_slli_epi64(vhi, 0x20);    // shift << 32
    vhi = _mm256_add_epi64(vhi, vlo);      // h = h1 + h2
    vhi = _mm256_and_si256(vhi, vmsk);     // h & 0xFFFFFFFF00000000
    vlo = _mm256_mul_epu32(va, vb);        // l = xl * yl
    return _mm256_add_epi64(vlo, vhi);     // l + h
/*
    // This implementation uses a temp register
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
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm256_mul_ps(va, vb); }

static SIMD_FUNC_INLINE
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm256_mul_pd(va, vb); }


/**************************
 *  Logical instructions  *
 **************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_or_si256(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_xor_si256(va, vb); }

static SIMD_FUNC_INLINE
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm256_and_si256(va, vb); }

/*!
 *  Used to mask vector elements
 */
static SIMD_FUNC_INLINE
SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm256_castps_si256(va);
    va_int = _mm256_and_si256(va_int, vb);
    return _mm256_castsi256_ps(va_int);
}

/*!
 *  Used to mask vector elements
 */
static SIMD_FUNC_INLINE
SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
{
    SIMD_INT va_int = _mm256_castpd_si256(va);
    va_int = _mm256_and_si256(va_int, vb);
    return _mm256_castsi256_pd(va_int);
}


/************************************
 *  Shift and shuffle instructions  *
 ************************************/
static SIMD_FUNC_INLINE
SIMD_INT simd_sll_16(const SIMD_INT va, const int8_t shft)
{ return _mm256_slli_epi16(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_32(const SIMD_INT va, const int8_t shft)
{ return _mm256_slli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_64(const SIMD_INT va, const int8_t shft)
{ return _mm256_slli_epi64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_sll_256(const SIMD_INT va, const int8_t shft)
{ return _mm256_slli_si256(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_16(const SIMD_INT va, const int8_t shft)
{ return _mm256_srli_epi16(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_32(const SIMD_INT va, const int8_t shft)
{ return _mm256_srli_epi32(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_64(const SIMD_INT va, const int8_t shft)
{ return _mm256_srli_epi64(va, shft); }

static SIMD_FUNC_INLINE
SIMD_INT simd_srl_256(const SIMD_INT va, const int8_t shft)
{ return _mm256_srli_si256(va, shft); }

#if !defined(__clang__)
/*
 *  Shuffle 32-bit elements using control value
 */
// TODO: Clang throws error with shuffle intrinsics due to non-constants with macro expansion
static SIMD_FUNC_INLINE
SIMD_INT simd_shuffle_i32(const SIMD_INT va, const int8_t ctrl)
{ return _mm256_shuffle_epi32(va, ctrl); }

static SIMD_FUNC_INLINE
SIMD_FLT simd_shuffle_f32(const SIMD_FLT va, const SIMD_FLT vb, const int8_t ctrl)
{ return _mm256_shuffle_ps(va, vb, ctrl); }
#endif

static SIMD_FUNC_INLINE
SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i vb_lo = _mm256_castsi256_si128(vb);
    return _mm256_inserti128_si256(va, vb_lo, 0x01);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m128 vb_lo = _mm256_castps256_ps128(vb);
    return _mm256_insertf128_ps(va, vb_lo, 0x01);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m128d vb_lo = _mm256_castpd256_pd128(vb);
    return _mm256_insertf128_pd(va, vb_lo, 0x01);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
{
    const __m128i va_hi = _mm256_extracti128_si256(va, 0x01);
    return _mm256_inserti128_si256(vb, va_hi, 0x00);
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m128 va_hi = _mm256_extractf128_ps(va, 0x01);
    return _mm256_insertf128_ps(vb, va_hi, 0x00);
}

static SIMD_FUNC_INLINE
SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m128d va_hi = _mm256_extractf128_pd(va, 0x01);
    return _mm256_insertf128_pd(vb, va_hi, 0x00);
}

static SIMD_FUNC_INLINE
SIMD_INT simd_packmerge_lo(SIMD_INT va, SIMD_INT vb)
{
    __m128i v_lo = _mm256_castsi256_si128(va);          // extract low part
    __m128i v_hi = _mm256_extracti128_si256(va, 0x01);  // extract high part
    v_lo = _mm_shuffle_epi32(v_lo, 0xD8);       // pack into low part of register
    v_hi = _mm_shuffle_epi32(v_hi, 0xD8);       // pack into low part of register
    v_lo = _mm_unpacklo_epi64(v_lo, v_hi);      // merge packed 128-bit registers
    va = _mm256_castsi128_si256(v_lo);
    v_lo = _mm256_castsi256_si128(vb);          // extract low part
    v_hi = _mm256_extracti128_si256(vb, 0x01);  // extract high part
    v_lo = _mm_shuffle_epi32(v_lo, 0xD8);       // pack into low part of register
    v_hi = _mm_shuffle_epi32(v_hi, 0xD8);       // pack into low part of register
    v_lo = _mm_unpacklo_epi64(v_lo, v_hi);      // merge packed 128-bit registers
    return _mm256_inserti128_si256(va, v_lo, 0x01);  // merge into 256-bit register
}

static SIMD_FUNC_INLINE
SIMD_FLT simd_packmerge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{
    SIMD_INT va_int = _mm256_castps_si256(va);
    SIMD_INT vb_int = _mm256_castps_si256(vb);
    __m128i v_lo = _mm256_castsi256_si128(va_int);          // extract low part
    __m128i v_hi = _mm256_extracti128_si256(va_int, 0x01);  // extract high part
    v_lo = _mm_shuffle_epi32(v_lo, 0xD8);       // pack into low part of register
    v_hi = _mm_shuffle_epi32(v_hi, 0xD8);       // pack into low part of register
    v_lo = _mm_unpacklo_epi64(v_lo, v_hi);      // merge packed 128-bit registers
    va_int = _mm256_castsi128_si256(v_lo);
    v_lo = _mm256_castsi256_si128(vb_int);          // extract low part
    v_hi = _mm256_extracti128_si256(vb_int, 0x01);  // extract high part
    v_lo = _mm_shuffle_epi32(v_lo, 0xD8);       // pack into low part of register
    v_hi = _mm_shuffle_epi32(v_hi, 0xD8);       // pack into low part of register
    v_lo = _mm_unpacklo_epi64(v_lo, v_hi);      // merge packed 128-bit registers
    va_int = _mm256_inserti128_si256(va_int, v_lo, 0x01);  // merge into 256-bit register
    return _mm256_castsi256_ps(va_int);
}


/**********************
 *  Set instructions  *
 **********************/
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


/**************************
 *  Convert instructions  *
 **************************/
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


/***********************
 *  Load instructions  *
 ***********************/
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


/************************
 *  Store instructions  *
 ************************/
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

