#include <stdio.h>
#include <stdlib.h> // getenv
#include <unistd.h> // sysconf
#include "utils.h"


#if defined(_OPENMP)
#include <omp.h>
#endif


/*
 *  If parameter is less than 1, the environment variable OMP_NUM_THREADS is considered.
 */
int setOmpEnv(const int num_threads)
{
    int nt;

#if defined(_OPENMP)
    if (getenv("OMP_NUM_THREADS"))
        nt = (num_threads > 0) ? (num_threads) : OMP_NUM_THREADS;
    else
        nt = (num_threads > 0) ? (num_threads) : 1;
    omp_set_num_threads(nt);

# if defined(__INTEL_COMPILER)
    setenv("KMP_AFFINITY", "granularity=fine,scatter", 1);
# endif
#else
    nt = (num_threads > 0) ? (num_threads) : 1;
#endif

    return nt;
}


#define GNUC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
int detectProcSIMD()
{
#if GNUC_VERSION > 40800
#define CPU_INIT_SUPPORT() __builtin_cpu_init()
#define CPU_SUPPORTS(a)   (__builtin_cpu_supports(a) ? 1 : 0)
#else
#define CPU_INIT_SUPPORT()
#define CPU_SUPPORTS(a) 0 // NOTE: assume SIMD support is not available if no way of checking
#endif

    int support = 1;

    CPU_INIT_SUPPORT();

#if defined(__FMA4__)
    // NOTE: need to add FMA detection
#endif
#if defined(__MMX__)
    if (!CPU_SUPPORTS("mmx"))
        support = 0;
#endif
#if defined(__SSE__)
    if (!CPU_SUPPORTS("sse"))
        support = 0;
#endif
#if defined(__SSE2__)
    if (!CPU_SUPPORTS("sse2"))
        support = 0;
#endif
#if defined(__SSE3__)
    if (!CPU_SUPPORTS("sse3"))
        support = 0;
#endif
#if defined(__SSSE3__)
    if (!CPU_SUPPORTS("ssse3"))
        support = 0;
#endif
#if defined(__SSE4_1__)
    if (!CPU_SUPPORTS("sse4.1"))
        support = 0;
#endif
#if defined(__SSE4_2__)
    if (!CPU_SUPPORTS("sse4.2"))
        support = 0;
#endif
#if defined(__AVX__)
    if (!CPU_SUPPORTS("avx"))
        support = 0;
#endif
#if defined(__AVX2__)
    if (!CPU_SUPPORTS("avx2"))
        support = 0;
#endif
#if defined(__AVX512BW__)
    if (!CPU_SUPPORTS("avx512BW"))
        support = 0;
#endif

    return support;

#undef CPU_SUPPORTS
#undef CPU_INIT_SUPPORT
}


int detectIntelProcSIMD()
{
    int avail = 0;

#if defined(__INTEL_COMPILER)
    unsigned long int features;

    features = _FEATURE_SSE | _FEATURE_SSE2 | _FEATURE_SSE3 | _FEATURE_SSSE3 | _FEATURE_SSE4_1 | _FEATURE_SSE4_2;
    avail = _may_i_use_cpu_feature(features);
    printf("SSE - SSE4.2 = %s\n", (avail) ? "YES" : "NO");

    features = _FEATURE_AVX | _FEATURE_AVX2;
    avail = _may_i_use_cpu_feature(features);
    printf("AVX - AVX2 = %s\n", (avail) ? "YES" : "NO");

    features = _FEATURE_FMA;
    avail = _may_i_use_cpu_feature(features);
    printf("FMA = %s\n", (avail) ? "YES" : "NO");

    features = _FEATURE_AVX512F | _FEATURE_AVX512PF | _FEATURE_AVX512CD | _FEATURE_AVX512ER;
    avail = _may_i_use_cpu_feature(features);
    printf("AVX512 - AVX512xx = %s\n", (avail) ? "YES" : "NO");

    features = _FEATURE_KNCNI;
    avail = _may_i_use_cpu_feature(features);
    printf("KNCNI = %s\n", (avail) ? "YES" : "NO");
#endif

    return avail;
}


void printSysconf()
{
    printf("Number of processors online = %ld\n", getNumProcOnline());
    printf("Page size = %ld\n", getPageSz());

    printf("L1 data cache size = %ld\n", getL1Sz());
    printf("L1 data cache associativity = %ld\n", getL1LineSz());
    printf("L1 data cache line size = %ld\n", getL1Assoc());

    printf("L2 cache size = %ld\n", getL2Sz());
    printf("L2 cache associativity = %ld\n", getL2LineSz());
    printf("L2 cache line size = %ld\n", getL2Assoc());

    printf("L3 cache size = %ld\n", getL3Sz());
    printf("L3 cache associativity = %ld\n", getL3LineSz());
    printf("L3 cache line size = %ld\n", getL3Assoc());

#if defined(_OPENMP)
    printf("OMP threads = %d of %d\n", omp_get_num_threads(), omp_get_max_threads());
#endif
}


long int getNumProcOnline()
{ return sysconf(_SC_NPROCESSORS_ONLN); }
//{ return sysconf(_SC_NPROCESSORS_CONF); }

long int getPageSz()
{ return sysconf(_SC_PAGESIZE); }
//{ return sysconf(_SC_PAGE_SIZE); }

long int getL1Sz()
{ return sysconf(_SC_LEVEL1_DCACHE_SIZE); }

long int getL1LineSz()
{ return sysconf(_SC_LEVEL1_DCACHE_LINESIZE); }

long int getL1Assoc()
{ return sysconf(_SC_LEVEL1_DCACHE_ASSOC); }

long int getL2Sz()
{ return sysconf(_SC_LEVEL2_CACHE_SIZE); }

long int getL2LineSz()
{ return sysconf(_SC_LEVEL2_CACHE_LINESIZE); }

long int getL2Assoc()
{ return sysconf(_SC_LEVEL2_CACHE_ASSOC); }

long int getL3Sz()
{ return sysconf(_SC_LEVEL3_CACHE_SIZE); }

long int getL3LineSz()
{ return sysconf(_SC_LEVEL3_CACHE_LINESIZE); }

long int getL3Assoc()
{ return sysconf(_SC_LEVEL3_CACHE_ASSOC); }

