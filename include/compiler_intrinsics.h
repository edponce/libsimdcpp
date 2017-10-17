#ifndef _COMPILER_INTRINSICS_H
#define _COMPILER_INTRINSICS_H


/*
 *  Compiler specific intrinsics
 *
 *  TODO: Verify intrinsics for Intel and Clang compilers.
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
    #define simd_prefetch(a,x) __builtin_prefetch(a,x)
    #define simd_prefetch_r(a) simd_prefetch(a,0)
    #define simd_prefetch_w(a) simd_prefetch(a,1)
#elif defined(__GNUC__)
    #define simd_prefetch(a,x) __builtin_prefetch(a,x)
    #define simd_prefetch_r(a) simd_prefetch(a,0)
    #define simd_prefetch_w(a) simd_prefetch(a,1)
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
    #define simd_prefetch(a,x) _mm_prefetch(a,x)
    #define simd_prefetch_r(a) simd_prefetch(a,_MM_HINT_T0)
    #define simd_prefetch_w(a) simd_prefetch(a,_MM_HINT_T0)
#else
    #define simd_prefetch(a,x) ((void)0)
    #define simd_prefetch_r(a) ((void)0)
    #define simd_prefetch_w(a) ((void)0)
#endif


#endif  // _COMPILER_INTRINSICS_H

