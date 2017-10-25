#ifndef _SIMD_H
#define _SIMD_H


/*
 *  If SIMD_MODE is enabled, use compiler flags to
 *  check automatically for best SIMD mode supported.
 */
#if defined(SIMD_MODE)
    #undef SIMD_MODE
    #undef SIMD_MMX
    #undef SIMD_SSE4_1
    #undef SIMD_AVX2
    #undef SIMD_AVX512

    #if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512DQ__)
    //#if defined(__AVX512BW__) && defined(__AVX512F__) && defined(__AVX512PF__) && defined(__AVX512DQ__) && defined(__AVX512CD__) && defined(__AVX512ER__) && defined(__AVX512VL__)
        #define SIMD_AVX512
    #elif defined(__AVX2__)
        #define SIMD_AVX2
    #elif defined(__SSE4_1__)
        #define SIMD_SSE4_1
    #elif defined(__MMX__)
        #define SIMD_MMX
    #endif
#endif


/*
 *  If SIMD_MODE is disabled, check for the SIMD mode requested.
 *  SIMD_MODE has to be defined to access available SIMD features.
 *  Include corresponding SIMD interfaces.
 */
#if defined(SIMD_AVX512)
    #define SIMD_MODE
    #include "avx512.h"
#elif defined(SIMD_AVX2)
    #define SIMD_MODE
    #include "avx2.h"
#elif defined(SIMD_SSE4_1)
    #define SIMD_MODE
    #include "sse4_1.h"
#elif defined(SIMD_MMX)
    #define SIMD_MODE
    #include "mmx.h"
#else
    #include "scalar.h"
#endif


/*
 *  General form of macros provided by compiler/architecture settings.
 *  Use SIMD_WIDTH_BYTES provided by SIMD modules.
 */
#define __SIMD_ALIGN__ SIMD_ALIGNED(SIMD_WIDTH_BYTES)
#define __SIMD_ASSUME_ALIGNED__(a) SIMD_ASSUME_ALIGNED(a, SIMD_WIDTH_BYTES)
#define __SIMD_FUNC_ASSUME_ALIGNED__ SIMD_FUNC_ASSUME_ALIGNED(SIMD_WIDTH_BYTES)
#define __SIMD_ASSUME__(a) SIMD_ASSUME(a)
#define __SIMD_FUNC_INLINE__ SIMD_FUNC_INLINE
#define __SIMD_PREFETCH__(a,x) SIMD_PREFETCH(a,x)


#endif  // _SIMD_H

