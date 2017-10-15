#include <stdio.h>


#if defined(__GNUC__)
    #define GNUC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
    #if GNUC_VERSION > 40800
        #define CPU_INIT_SUPPORT() __builtin_cpu_init()
        #define CPU_SUPPORTS(a)    ((__builtin_cpu_supports(a)) ? (1) : (0))
    #else
        // NOTE: assume SIMD support is not available if no way of checking
        #define CPU_INIT_SUPPORT()
        #define CPU_SUPPORTS(a)    0
    #endif

static void print_feature_support(const char *feature, int supported) {
    fprintf(stdout, "%s: %s\n", feature, (supported) ? ("YES") : ("NO"));
}


int detectProcSIMD(void)
{
    int support_features = 1;  // aggregate features check
    int support_feature = 0;   // single feature check

    CPU_INIT_SUPPORT();

    #if defined(__FMA4__)
        // TODO: need to add FMA detection
    #endif
    #if defined(__MMX__)
    support_feature = CPU_SUPPORTS("mmx");
    print_feature_support("MMX", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__SSE__)
    support_feature = CPU_SUPPORTS("sse");
    print_feature_support("SSE", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__SSE2__)
    support_feature = CPU_SUPPORTS("sse2");
    print_feature_support("SSE2", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__SSE3__)
    support_feature = CPU_SUPPORTS("sse3");
    print_feature_support("SSE3", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__SSSE3__)
    support_feature = CPU_SUPPORTS("ssse3");
    print_feature_support("SSSE3", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__SSE4_1__)
    support_feature = CPU_SUPPORTS("sse4.1");
    print_feature_support("SSE4.1", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__SSE4_2__)
    support_feature = CPU_SUPPORTS("sse4.2");
    print_feature_support("SSE4.2", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__AVX__)
    support_feature = CPU_SUPPORTS("avx");
    print_feature_support("AVX", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__AVX2__)
    support_feature = CPU_SUPPORTS("avx2");
    print_feature_support("AVX2", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif
    #if defined(__AVX512BW__)
    support_feature = CPU_SUPPORTS("avx512BW");
    print_feature_support("AVX512BW", support_feature);
    if (!support_feature)
        support_features = 0;
    #endif

    return support_features;
}

#elif defined(__INTEL_COMPILER)

    #define CPU_SUPPORTS(a) _may_i_use_cpu_feature(a)

static void print_feature_support(const char *feature, int supported) {
    fprintf(stdout, "%s: %s\n", feature, (supported) ? ("YES") : ("NO"));
}


// TODO: add macro checks for each feature
int detectProcSIMD(void)
{
    int support_features = 1;  // aggregate features check
    int support_feature = 0;   // single feature check

    support_feature = CPU_SUPPORTS(_FEATURE_FMA);
    print_feature_support("FMA", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_MMX);
    print_feature_support("MMX", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_SSE);
    print_feature_support("SSE", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_SSE2);
    print_feature_support("SSE2", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_SSE3);
    print_feature_support("SSE3", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_SSSE3);
    print_feature_support("SSSE3", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_SSE4_1);
    print_feature_support("SSE4.1", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_SSE4_2);
    print_feature_support("SSE4.2", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_AVX);
    print_feature_support("AVX", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_AVX2);
    print_feature_support("AVX2", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_AVX512F | _FEATURE_AVX512PF | _FEATURE_AVX512CD | _FEATURE_AVX512ER);
    print_feature_support("AVX512", support_feature);
    if (!support_feature)
        support_features = 0;

    support_feature = CPU_SUPPORTS(_FEATURE_KNCNI);
    print_feature_support("KNCNI", support_feature);
    if (!support_feature)
        support_features = 0;

    return support_features;
}

#else

int detectProcSIMD(void)
{
    int support_features = 1;

    support_features = 0;

    return support_features;
}

#endif

