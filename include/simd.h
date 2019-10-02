#ifndef _SIMD_H
#define _SIMD_H

/*
 *  If SIMD_MODE is enabled, use compiler flags to auto-select best SIMD mode supported
 *  Auto-select SIMD support has priority over specific SIMD support
 */
#if defined(SIMD_MODE)
#   undef SIMD_AVX512
#   undef SIMD_AVX2
#   undef SIMD_AVX
#   undef SIMD_SSE4_2
#   undef SIMD_SSE2
#   undef SIMD_MMX

#   if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512DQ__)
    //#if defined(__AVX512BW__) && defined(__AVX512F__) && defined(__AVX512PF__) && defined(__AVX512DQ__) && defined(__AVX512CD__) && defined(__AVX512ER__) && defined(__AVX512VL__)
#       define SIMD_AVX512
#   elif defined(__AVX2__)
#       define SIMD_AVX2
//#   elif defined(__AVX__)
//#       define SIMD_AVX
#   elif defined(__SSE4_2__)
#       define SIMD_SSE4_2
#   elif defined(__SSE2__)
#       define SIMD_SSE2
#   elif defined(__MMX__)
#       define SIMD_MMX
#   endif
#else
#   define SIMD_MODE
#endif


/*
 *  Identify the SIMD mode requested and include SIMD interface
 *  SIMD_MODE has to be defined to access available SIMD features
 */
#if defined(SIMD_AVX512)
#   include "avx512.h"
#elif defined(SIMD_AVX2)
#   include "avx2.h"
#elif defined(SIMD_AVX)
#   include "avx.h"
#elif defined(SIMD_SSE4_2)
#   include "sse4_2.h"
#elif defined(SIMD_SSE2)
#   include "sse2.h"
#elif defined(SIMD_MMX)
#   include "mmx.h"
#else
#   undef SIMD_MODE
#   include "scalar.h"
#endif


/*
 *  General form of macros provided by compiler/architecture settings
 *  Use SIMD_WIDTH_BYTES provided by SIMD modules
 *  NOTE: This macros will not be correct if multiple SIMD interfaces are loaded
 */
#define __SIMD_ALIGN__ SIMD_ALIGNED(SIMD_WIDTH_BYTES)
#define __SIMD_ASSUME_ALIGNED__(a) SIMD_ASSUME_ALIGNED(a, SIMD_WIDTH_BYTES)
#define __SIMD_FUNC_ASSUME_ALIGNED__ SIMD_FUNC_ASSUME_ALIGNED(SIMD_WIDTH_BYTES)
#define __SIMD_ASSUME__(a) SIMD_ASSUME(a)
#define __SIMD_FUNC_INLINE__ SIMD_FUNC_INLINE
#define __SIMD_PREFETCH__(a,x) SIMD_PREFETCH(a,x)


#endif  // _SIMD_H

