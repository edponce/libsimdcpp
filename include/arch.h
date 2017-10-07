#ifndef __ARCH_H
#define __ARCH_H


/*
 *  Compiler specific macro to set array alignment.
 */
#if defined(__GNUC__)
    #define ARCH_ATTR_ALIGNED(a)     __attribute__((__aligned__(a)))
    #define ARCH_ASSUME_ALIGNED(a,x)
    #define ARCH_ASSUME(a)           __builtin_assume(a)
    #define ARCH_ATTR_INLINE         __attribute__((__gnu_inline__, __always_inline__, __artificial__)) inline
#elif defined(__INTEL_COMPILER)
    #define ARCH_ATTR_ALIGNED(a)     __attribute__((__aligned__(a)))
    #define ARCH_ASSUME_ALIGNED(a,x) __assume_aligned(a, x)
    #define ARCH_ASSUME(a)           __assume(a)
    #define ARCH_ATTR_INLINE         inline
#else
    #define ARCH_ATTR_ALIGNED(a)
    #define ARCH_ASSUME_ALIGNED(a,x)
    #define ARCH_ASSUME(a)
    #define ARCH_ATTR_INLINE         inline
#endif


#endif  // __ARCH_H

