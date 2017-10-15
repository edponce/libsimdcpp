#ifndef _COMPILER_H
#define _COMPILER_H


/*
 *  Compiler specific macro to set array alignment.
 *
 *  TODO: Verify builtins for Intel and Clang compilers.
 *
 *  NOTE: C/C++ arrays that are dynamically allocated, it is not enough to just
 *        align the data during creation using 'mm_malloc/posix_memalign', but it
 *        also requires a clause of SIMD_ASSUME_ALIGNED before the loop of interest.
 *
 *  SIMD_ALIGNED(a):
 *      use on a variable declaration to specify at least 'a' bytes aligned.
 *
 *  SIMD_ASSUME_ALIGNED(a,x):
 *      use on a variable declaration/assignment, returns 'a' and allows the compiler
 *      to assume that the returned pointer is at least 'x' bytes aligned.
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
 *
 *  SIMD_PREFETCH(a,x):
 *      standalone function to specify the movement of data (pointed by 'a') into cache
 *      before it is accessed. Read accesses use 'x' = 0 and write accesses use 'x' = 1.
 *      A third argument corresponds to the degree of temporal locality [0-3], where
 *      3 is highest and default.
 *      Ex:
 *          for (int i = 0; i < n; ++i) {
 *              a[i] += b[i];
 *              SIMD_PREFETCH(&a[i+j],1);
 *              SIMD_PREFETCH(&b[i+j],0);
 *          }
 */
#if defined(__clang__)
    #define SIMD_ALIGNED(a) __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __builtin_assume_aligned(a, x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a)
    #define SIMD_ASSUME(a) __builtin_assume(a)
    #define SIMD_FUNC_INLINE __inline __attribute__((__always_inline__))
    #define SIMD_PREFETCH(a,x) __builtin_prefetch(a,x)
#elif defined(__GNUC__)
    #define SIMD_ALIGNED(a) __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __builtin_assume_aligned(a, x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a) __attribute__((assume_aligned(a)))
    #define SIMD_ASSUME(a) __builtin_assume(a)
    #define SIMD_FUNC_INLINE __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
    #define SIMD_PREFETCH(a,x) __builtin_prefetch(a,x)
#elif defined(__INTEL_COMPILER)
    #define SIMD_ALIGNED(a) __attribute__((__aligned__(a)))
    #define SIMD_ASSUME_ALIGNED(a,x) __assume_aligned(a, x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a)
    #define SIMD_ASSUME(a) __assume(a)
    #define SIMD_FUNC_INLINE inline
    #define SIMD_PREFETCH(a,x) _mm_prefetch(a,_MM_HINT_T0)
#else
    #define SIMD_ALIGNED(a)
    #define SIMD_ASSUME_ALIGNED(a,x)
    #define SIMD_FUNC_ASSUME_ALIGNED(a)
    #define SIMD_ASSUME(a)
    #define SIMD_FUNC_INLINE
    #define SIMD_PREFETCH(a,x)
#endif


#endif  // _COMPILER_H

