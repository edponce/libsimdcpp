#include <stdio.h>


#if defined(__clang__)
    // TODO: check what are the Clang builtins, these are placeholders.
    #define CPU_INIT_SUPPORT() __builtin_cpu_init()
    #define CPU_IS(a)          (__builtin_cpu_is(a))
    #define CPU_SUPPORTS(a)    (__builtin_cpu_supports(a))

    #define SIMD_FEATURE_FMA    CPU_SUPPORTS("fma")
    #define SIMD_FEATURE_FMA4   CPU_SUPPORTS("fma4")
    #define SIMD_FEATURE_MMX    CPU_SUPPORTS("mmx")
    #define SIMD_FEATURE_SSE    CPU_SUPPORTS("sse")
    #define SIMD_FEATURE_SSE2   CPU_SUPPORTS("sse2")
    #define SIMD_FEATURE_SSE3   CPU_SUPPORTS("sse3")
    #define SIMD_FEATURE_SSSE3  CPU_SUPPORTS("ssse3")
    #define SIMD_FEATURE_SSE4_1 CPU_SUPPORTS("sse4.1")
    #define SIMD_FEATURE_SSE4_2 CPU_SUPPORTS("sse4.2")
    #define SIMD_FEATURE_AVX    CPU_SUPPORTS("avx")
    #define SIMD_FEATURE_AVX2   CPU_SUPPORTS("avx2")
    #define SIMD_FEATURE_AVX512 CPU_SUPPORTS("avx512BW")
    #define SIMD_FEATURE_KNCNI  0

#elif defined(__GNUC__)
    #define GNUC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
    #if GNUC_VERSION > 40800
        #define CPU_INIT_SUPPORT() __builtin_cpu_init()
        #define CPU_IS(a)          (__builtin_cpu_is(a))
        #define CPU_SUPPORTS(a)    (__builtin_cpu_supports(a))
    #else
        #define CPU_INIT_SUPPORT()
        #define CPU_IS(a)          0
        #define CPU_SUPPORTS(a)    0
    #endif

    #define SIMD_FEATURE_FMA    CPU_SUPPORTS("fma")
    #define SIMD_FEATURE_FMA4   CPU_SUPPORTS("fma4")
    #define SIMD_FEATURE_MMX    CPU_SUPPORTS("mmx")
    #define SIMD_FEATURE_SSE    CPU_SUPPORTS("sse")
    #define SIMD_FEATURE_SSE2   CPU_SUPPORTS("sse2")
    #define SIMD_FEATURE_SSE3   CPU_SUPPORTS("sse3")
    #define SIMD_FEATURE_SSSE3  CPU_SUPPORTS("ssse3")
    #define SIMD_FEATURE_SSE4_1 CPU_SUPPORTS("sse4.1")
    #define SIMD_FEATURE_SSE4_2 CPU_SUPPORTS("sse4.2")
    #define SIMD_FEATURE_AVX    CPU_SUPPORTS("avx")
    #define SIMD_FEATURE_AVX2   CPU_SUPPORTS("avx2")
    #define SIMD_FEATURE_AVX512 CPU_SUPPORTS("avx512bw")
    #define SIMD_FEATURE_KNCNI  0


#elif defined(__INTEL_COMPILER)
    #define CPU_INIT_SUPPORT()
    #define CPU_IS(a)          0
    #define CPU_SUPPORTS(a)    _may_i_use_cpu_feature(a)

    // TODO: verify FMA/4 _FEATURE macros
    #define SIMD_FEATURE_FMA    CPU_SUPPORTS(_FEATURE_FMA)
    #define SIMD_FEATURE_FMA4   CPU_SUPPORTS(_FEATURE_FMA4)
    #define SIMD_FEATURE_MMX    CPU_SUPPORTS(_FEATURE_MMX)
    #define SIMD_FEATURE_SSE    CPU_SUPPORTS(_FEATURE_SSE)
    #define SIMD_FEATURE_SSE2   CPU_SUPPORTS(_FEATURE_SSE2)
    #define SIMD_FEATURE_SSE3   CPU_SUPPORTS(_FEATURE_SSE3)
    #define SIMD_FEATURE_SSSE3  CPU_SUPPORTS(_FEATURE_SSSE3)
    #define SIMD_FEATURE_SSE4_1 CPU_SUPPORTS(_FEATURE_SSE4_1)
    #define SIMD_FEATURE_SSE4_2 CPU_SUPPORTS(_FEATURE_SSE4_2)
    #define SIMD_FEATURE_AVX    CPU_SUPPORTS(_FEATURE_AVX)
    #define SIMD_FEATURE_AVX2   CPU_SUPPORTS(_FEATURE_AVX2)
    #define SIMD_FEATURE_AVX512 CPU_SUPPORTS(_FEATURE_AVX512F | _FEATURE_AVX512PF | _FEATURE_AVX512CD | _FEATURE_AVX512ER)
    #define SIMD_FEATURE_KNCNI  CPU_SUPPORTS(_FEATURE_KNCNI)

#else
    #define CPU_INIT_SUPPORT()
    #define CPU_IS(a)          0
    #define CPU_SUPPORTS(a)    0

    #define SIMD_FEATURE_FMA     0
    #define SIMD_FEATURE_FMA4    0
    #define SIMD_FEATURE_MMX     0
    #define SIMD_FEATURE_SSE     0
    #define SIMD_FEATURE_SSE2    0
    #define SIMD_FEATURE_SSE3    0
    #define SIMD_FEATURE_SSSE3   0
    #define SIMD_FEATURE_SSE4_1  0
    #define SIMD_FEATURE_SSE4_2  0
    #define SIMD_FEATURE_AVX     0
    #define SIMD_FEATURE_AVX2    0
    #define SIMD_FEATURE_AVX512  0
    #define SIMD_FEATURE_KNCNI   0
#endif


static void print_feature_support(const char *feature, int supported) {
    fprintf(stdout, "%s: %s\n", feature, (supported) ? ("YES") : ("NO"));
}


int detectCPU(void)
{
    int support_feature = 0;

    CPU_INIT_SUPPORT();

    support_feature = CPU_IS("amd");
    if (support_feature)
        print_feature_support("AMD CPU", support_feature);

    support_feature = CPU_IS("intel");
    if (support_feature)
        print_feature_support("Intel CPU", support_feature);

    support_feature = CPU_IS("core2");
    if (support_feature)
        print_feature_support("Intel Core 2 CPU", support_feature);

    support_feature = CPU_IS("corei7");
    if (support_feature)
        print_feature_support("Intel Core i7 CPU", support_feature);

    support_feature = CPU_IS("nehalem");
    if (support_feature)
        print_feature_support("Intel Core i7 Nehalem CPU", support_feature);

    support_feature = CPU_IS("westmere");
    if (support_feature)
        print_feature_support("Intel Core i7 Westmere CPU", support_feature);

    support_feature = CPU_IS("sandybridge");
    if (support_feature)
        print_feature_support("Intel Core i7 Sandy Bridge CPU", support_feature);

    support_feature = CPU_IS("ivybridge");
    if (support_feature)
        print_feature_support("Intel Ivy Bridge CPU", support_feature);

    support_feature = CPU_IS("haswell");
    if (support_feature)
        print_feature_support("Intel Haswell CPU", support_feature);

    support_feature = CPU_IS("knl");
    if (support_feature)
        print_feature_support("KNL CPU", support_feature);

    return 0;
}


int detectSIMD(void)
{
    int support_feature = 0;

    CPU_INIT_SUPPORT();

    // NOTE: Macro defined if FMA/FMA3 is supported
    #if defined(__FMA__)
    // NOTE: Intel and AMD processors support FMA/FMA3 if AVX2 is present.
    support_feature = SIMD_FEATURE_FMA;
    if (support_feature)
        print_feature_support("FMA/FMA3", support_feature);
    #endif
    #if defined(__FMA4__)
    // NOTE: AMD processors FMA4
    support_feature = SIMD_FEATURE_FMA4;
    if (support_feature)
        print_feature_support("FMA4", support_feature);
    #endif
    #if defined(__MMX__)
    support_feature = SIMD_FEATURE_MMX;
    if (support_feature)
        print_feature_support("MMX", support_feature);
    #endif
    #if defined(__SSE__)
    support_feature = SIMD_FEATURE_SSE;
    if (support_feature)
        print_feature_support("SSE", support_feature);
    #endif
    #if defined(__SSE2__)
    support_feature = SIMD_FEATURE_SSE2;
    if (support_feature)
        print_feature_support("SSE2", support_feature);
    #endif
    #if defined(__SSE3__)
    support_feature = SIMD_FEATURE_SSE3;
    if (support_feature)
        print_feature_support("SSE3", support_feature);
    #endif
    #if defined(__SSSE3__)
    support_feature = SIMD_FEATURE_SSSE3;
    if (support_feature)
        print_feature_support("SSSE3", support_feature);
    #endif
    #if defined(__SSE4_1__)
    support_feature = SIMD_FEATURE_SSE4_1;
    if (support_feature)
        print_feature_support("SSE4.1", support_feature);
    #endif
    #if defined(__SSE4_2__)
    support_feature = SIMD_FEATURE_SSE4_2;
    if (support_feature)
        print_feature_support("SSE4.2", support_feature);
    #endif
    #if defined(__AVX__)
    support_feature = SIMD_FEATURE_AVX;
    if (support_feature)
        print_feature_support("AVX", support_feature);
    #endif
    #if defined(__AVX2__)
    support_feature = SIMD_FEATURE_AVX2;
    if (support_feature) {
        print_feature_support("AVX2", support_feature);
    }
    #endif
    #if defined(__AVX512BW__) || defined(__AVX512F__) || defined(__AVX512PF__) || defined(__AVX512CD__) || defined(__AVX512ER__)
    support_feature = SIMD_FEATURE_AVX512;
    if (support_feature)
        print_feature_support("AVX512", support_feature);
    #endif

    support_feature = SIMD_FEATURE_KNCNI;
    if (support_feature)
        print_feature_support("KNCNI", support_feature);

    return 0;
}

