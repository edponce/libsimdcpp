#ifndef _SIMD_H
#define _SIMD_H


/*
 *  If SIMD_MODE is enabled, use compiler flags to
 *  check automatically for best SIMD mode supported.
 */
#if defined(SIMD_MODE)
    #undef SIMD_MODE
    #undef SSE4_1_VEC
    #undef AVX2_VEC
    #undef AVX512_VEC

    #if defined(__AVX512BW__)
        #define AVX512_VEC
    #elif defined(__AVX2__)
        #define AVX2_VEC
    #elif defined(__SSE4_1__)
        #define SSE4_1_VEC
    #endif
#endif


/*
 *  If SIMD_MODE is disabled, check for the SIMD mode requested.
 *  SIMD_MODE has to be defined to access available SIMD features.
 *  Include corresponding SIMD interfaces.
 */
#if defined(AVX512_VEC)
    #define SIMD_MODE
    #include "avx512.h"
#elif defined(AVX2_VEC)
    #define SIMD_MODE
    #include "avx2.h"
#elif defined(SSE4_1_VEC)
    #define SIMD_MODE
    #include "sse4_1.h"
#else
    /*
     *  Compiler and architecture specific settings
     */
    #include "compiler.h"

    // Disable SIMD for scalar mode
    #define SIMD_WIDTH_BYTES 8
    #define SIMD_STREAMS_32  1
    #define SIMD_STREAMS_64  1
#endif


/*
 *  General form of macros provided by compiler/architecture settings.
 *  Use SIMD_WIDTH_BYTES provided by SIMD modules.
 */
#define __SIMD_ALIGN__             SIMD_ATTR_ALIGNED(SIMD_WIDTH_BYTES)
#define __SIMD_ASSUME_ALIGNED__(a) SIMD_ASSUME_ALIGNED(a, SIMD_WIDTH_BYTES)
#define __SIMD_ASSUME__(a)         SIMD_ASSUME(a)


#endif  // _SIMD_H

