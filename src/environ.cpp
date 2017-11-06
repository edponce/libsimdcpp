#include <stdio.h>
#include "environ.h"
#include "compiler_builtins.h"


static void print_feature_support(const char *feature, const int supported) {
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
    #if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512DQ__)
    //#if defined(__AVX512BW__) && defined(__AVX512F__) && defined(__AVX512PF__) && defined(__AVX512DQ__) && defined(__AVX512CD__) && defined(__AVX512ER__) && defined(__AVX512VL__)
    support_feature = SIMD_FEATURE_AVX512;
    if (support_feature)
        print_feature_support("AVX512", support_feature);
    #endif
    #if defined(__MIC__)
    support_feature = SIMD_FEATURE_KNCNI;
    if (support_feature)
        print_feature_support("KNCNI", support_feature);
    #endif

    return 0;
}

