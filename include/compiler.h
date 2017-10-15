#ifndef _COMPILER_H
#define _COMPILER_H


/*
 *  Compiler specific macro to set array alignment.
 */
#if defined(__GNUC__)
    #define SIMD_ATTR_ALIGNED(a)     __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x)
    #define SIMD_ASSUME(a)           __builtin_assume(a)
    #define SIMD_ATTR_INLINE         __attribute__((__gnu_inline__, __always_inline__, __artificial__)) inline
#elif defined(__INTEL_COMPILER)
    #define SIMD_ATTR_ALIGNED(a)     __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __assume_aligned(a, x)
    #define SIMD_ASSUME(a)           __assume(a)
    #define SIMD_ATTR_INLINE         inline
#else
    #define SIMD_ATTR_ALIGNED(a)
    #define SIMD_ASSUME_ALIGNED(a,x)
    #define SIMD_ASSUME(a)
    #define SIMD_ATTR_INLINE         inline
#endif


#endif  // _COMPILER_H

