#ifndef _COMPILER_ATTRIBUTES_H
#define _COMPILER_ATTRIBUTES_H


/*
 *  Compiler specific attributes
 *
 *  TODO: Verify builtins for Intel and Clang compilers.
 *
 *  SIMD_ALIGNED(a):
 *      use on a variable declaration to specify at least 'a' bytes aligned.
 *
 *  SIMD_ASSUME_ALIGNED(a,x):
 *      use on a variable declaration/assignment, returns 'a' and allows the compiler
 *      to assume that the returned pointer is at least 'x' bytes aligned.
 *
 *      NOTE: C/C++ arrays that are dynamically allocated, it is not enough to just
 *            align the data during creation, but also requires a clause of
 *            SIMD_ASSUME_ALIGNED before the loop of interest.
 *
 *      NOTE: Add '#pragma vector aligned' before a loop to assert that all array
 *            accesses inside the loop are aligned (the programmer is responsible for
 *            ensuring the alignment holds otherwise segmentation faults will occur).
 *            Note that this pragma needs to be added just before each applicable
 *            vector loop. In this way you do not have to specify each variable as
 *            shown in SIMD_ASSUME example.
 *
 *  SIMD_FUNC_ASSUME_ALIGNED(a):
 *      use on a function declaration to specify that the return value of
 *      the function (must be a pointer type) is 'a' bytes aligned.
 *      Ex:
 *          float * foo(int a) SIMD_FUNC_ASSUME_ALIGNED { ... }
 *
 *  SIMD_ASSUME(a):
 *      hint compiler that the boolean property 'a' holds at a particular point in the
 *      program. Useful to specify that a [lower-bound-of-i-loop + offset] is a
 *      multiple of a constant.
 *      Ex:
 *          float X[1000] SIMD_ALIGNED(64);
 *          void foo(float * a, int n, int n1) {
 *              SIMD_ASSUME_ALIGNED(a, 64);
 *              SIMD_ASSUME((n1 % 16) == 0);
 *              for (int i = 0; i < n; ++i)
 *                  X[i] += a[i] + a[i + n1];
 *          }
 *
 *  SIMD_FUNC_INLINE:
 *      use on a function declaration to direct compiler to make function call faster
 *      by integrating the function's code into the code for its callers.
 */
#if defined(__clang__)
    #define SIMD_ALIGNED(a) __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __builtin_assume_aligned(a, x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a)
    #define SIMD_ASSUME(a) __builtin_assume(a)
    #define SIMD_FUNC_INLINE __inline __attribute__((__always_inline__))
#elif defined(__GNUC__)
    #define SIMD_ALIGNED(a) __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __builtin_assume_aligned(a, x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a) __attribute__((assume_aligned(a)))
    #define SIMD_ASSUME(a) __builtin_assume(a)
    #define SIMD_FUNC_INLINE __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
    #define SIMD_ALIGNED(a) __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __assume_aligned(a, x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a)
    #define SIMD_ASSUME(a) __assume(a)
    #define SIMD_FUNC_INLINE inline
#else
    #define SIMD_ALIGNED(a)
    #define SIMD_ASSUME_ALIGNED(a,x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a)
    #define SIMD_ASSUME(a)
    #define SIMD_FUNC_INLINE
#endif


#endif  // _COMPILER_ATTRIBUTES_H

