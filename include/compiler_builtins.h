#ifndef _COMPILER_BUILTINS_H
#define _COMPILER_BUILTINS_H


#include "compiler_versions.h"


/*
 *  Compiler specific builtin functions
 *
 *  TODO: Verify builtins for Intel and Clang compilers.
 *  TODO: Verify FMA/4 and AVX512 feature macros
 *  TODO: Refer to 'stdlib.h' and '_mm_malloc.h' for aligned allocation variants and support.
 *
 *        C11:     void * aligned_alloc(size_t alignment, size_t size)
 *        POSIX:   int posix_memalign(void **memptr, size_t alignment, size_t size)
 *        Intel:   void * _mm_malloc(int size, int align)
 *                 void _mm_free(void *p)
 *        Windows: void * _aligned_malloc(size_t size, size_t alignment)
 *
 *  simd_prefetch(a,x):
 *      standalone function to specify the movement of data (pointed by 'a') into cache
 *      before it is accessed. Read accesses use 'x' = 0 and write accesses use 'x' = 1.
 *      A third argument corresponds to the degree of temporal locality [0-3], where
 *      3 is highest and default.
 *      Ex:
 *          for (int i = 0; i < n; ++i) {
 *              a[i] += b[i];
 *              simd_prefetch(&a[i+j],1);
 *              simd_prefetch(&b[i+j],0);
 *          }
 */
#if defined(__clang__)
    // Used to verify SIMD features supported
#   define CPU_INIT_SUPPORT() ((void)0)
#   define CPU_IS(a)          0
#   define CPU_SUPPORTS(a)    (__builtin_cpu_supports(a))

#   define SIMD_FEATURE_FMA    CPU_SUPPORTS("fma")
#   define SIMD_FEATURE_FMA4   CPU_SUPPORTS("fma4")
#   define SIMD_FEATURE_MMX    CPU_SUPPORTS("mmx")
#   define SIMD_FEATURE_SSE    CPU_SUPPORTS("sse")
#   define SIMD_FEATURE_SSE2   CPU_SUPPORTS("sse2")
#   define SIMD_FEATURE_SSE3   CPU_SUPPORTS("sse3")
#   define SIMD_FEATURE_SSSE3  CPU_SUPPORTS("ssse3")
#   define SIMD_FEATURE_SSE4_1 CPU_SUPPORTS("sse4.1")
#   define SIMD_FEATURE_SSE4_2 CPU_SUPPORTS("sse4.2")
#   define SIMD_FEATURE_AVX    CPU_SUPPORTS("avx")
#   define SIMD_FEATURE_AVX2   CPU_SUPPORTS("avx2")
#   define SIMD_FEATURE_AVX512 (CPU_SUPPORTS("avx512f") && CPU_SUPPORTS("avx512bw") && CPU_SUPPORTS("avx512dq"))
#   define SIMD_FEATURE_KNCNI  0

    // Prefetching builtins
#   define simd_prefetch(a,x) __builtin_prefetch(a,x)
#   define simd_prefetch_r(a) simd_prefetch(a,0)
#   define simd_prefetch_w(a) simd_prefetch(a,1)

#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
    // Used to verify SIMD features supported
#   define CPU_INIT_SUPPORT() ((void)0)
#   define CPU_IS(a)          0
#   define CPU_SUPPORTS(a)    _may_i_use_cpu_feature(a)

#   define SIMD_FEATURE_FMA    CPU_SUPPORTS(_FEATURE_FMA)
#   define SIMD_FEATURE_FMA4   CPU_SUPPORTS(_FEATURE_FMA4)
#   define SIMD_FEATURE_MMX    CPU_SUPPORTS(_FEATURE_MMX)
#   define SIMD_FEATURE_SSE    CPU_SUPPORTS(_FEATURE_SSE)
#   define SIMD_FEATURE_SSE2   CPU_SUPPORTS(_FEATURE_SSE2)
#   define SIMD_FEATURE_SSE3   CPU_SUPPORTS(_FEATURE_SSE3)
#   define SIMD_FEATURE_SSSE3  CPU_SUPPORTS(_FEATURE_SSSE3)
#   define SIMD_FEATURE_SSE4_1 CPU_SUPPORTS(_FEATURE_SSE4_1)
#   define SIMD_FEATURE_SSE4_2 CPU_SUPPORTS(_FEATURE_SSE4_2)
#   define SIMD_FEATURE_AVX    CPU_SUPPORTS(_FEATURE_AVX)
#   define SIMD_FEATURE_AVX2   CPU_SUPPORTS(_FEATURE_AVX2)
#   define SIMD_FEATURE_AVX512 CPU_SUPPORTS(_FEATURE_AVX512F | _FEATURE_AVX512BW | _FEATURE_AVX512DQ)
    //#define SIMD_FEATURE_AVX512 CPU_SUPPORTS(_FEATURE_AVX512BW | _FEATURE_AVX512F | _FEATURE_AVX512PF | _FEATURE_AVX512DQ | _FEATURE_AVX512CD | _FEATURE_AVX512ER | _FEATURE_AVX512VL)
#   define SIMD_FEATURE_KNCNI  CPU_SUPPORTS(_FEATURE_KNCNI)

    // Prefetching builtins
#   define simd_prefetch(a,x) _mm_prefetch(a,x)
#   define simd_prefetch_r(a) simd_prefetch(a,_MM_HINT_T0)
#   define simd_prefetch_w(a) simd_prefetch(a,_MM_HINT_T0)

#elif defined(__GNUC__)
    // Used to verify SIMD features supported
    // NOTE: Requires 4.8 or greater for __builtin_cpu_supports
#   if GNUC_VERSION > 40800
#       define CPU_INIT_SUPPORT() __builtin_cpu_init()
#       define CPU_IS(a)          (__builtin_cpu_is(a))
#       define CPU_SUPPORTS(a)    (__builtin_cpu_supports(a))
#   else
#       define CPU_INIT_SUPPORT() ((void)0)
#       define CPU_IS(a)          0
#       define CPU_SUPPORTS(a)    0
#   endif

#   define SIMD_FEATURE_FMA    CPU_SUPPORTS("fma")
#   define SIMD_FEATURE_FMA4   CPU_SUPPORTS("fma4")
#   define SIMD_FEATURE_MMX    CPU_SUPPORTS("mmx")
#   define SIMD_FEATURE_SSE    CPU_SUPPORTS("sse")
#   define SIMD_FEATURE_SSE2   CPU_SUPPORTS("sse2")
#   define SIMD_FEATURE_SSE3   CPU_SUPPORTS("sse3")
#   define SIMD_FEATURE_SSSE3  CPU_SUPPORTS("ssse3")
#   define SIMD_FEATURE_SSE4_1 CPU_SUPPORTS("sse4.1")
#   define SIMD_FEATURE_SSE4_2 CPU_SUPPORTS("sse4.2")
#   define SIMD_FEATURE_AVX    CPU_SUPPORTS("avx")
#   define SIMD_FEATURE_AVX2   CPU_SUPPORTS("avx2")
#   define SIMD_FEATURE_AVX512 CPU_SUPPORTS("avx512f")
    //#define SIMD_FEATURE_AVX512 (CPU_SUPPORTS("avx512f") && CPU_SUPPORTS("avx512bw") && CPU_SUPPORTS("avx512dq"))
#   define SIMD_FEATURE_KNCNI  0

    // Prefetching builtins
#   define simd_prefetch(a,x) __builtin_prefetch(a,x)
#   define simd_prefetch_r(a) simd_prefetch(a,0)
#   define simd_prefetch_w(a) simd_prefetch(a,1)

#else
    // Used to verify SIMD features supported
#   define CPU_INIT_SUPPORT() ((void)0)
#   define CPU_IS(a)          0
#   define CPU_SUPPORTS(a)    0

#   define SIMD_FEATURE_FMA     0
#   define SIMD_FEATURE_FMA4    0
#   define SIMD_FEATURE_MMX     0
#   define SIMD_FEATURE_SSE     0
#   define SIMD_FEATURE_SSE2    0
#   define SIMD_FEATURE_SSE3    0
#   define SIMD_FEATURE_SSSE3   0
#   define SIMD_FEATURE_SSE4_1  0
#   define SIMD_FEATURE_SSE4_2  0
#   define SIMD_FEATURE_AVX     0
#   define SIMD_FEATURE_AVX2    0
#   define SIMD_FEATURE_AVX512  0
#   define SIMD_FEATURE_KNCNI   0

    // Prefetching builtins
#   define simd_prefetch(a,x) ((void)0)
#   define simd_prefetch_r(a) ((void)0)
#   define simd_prefetch_w(a) ((void)0)
#endif


#endif  // _COMPILER_BUILTINS_H

