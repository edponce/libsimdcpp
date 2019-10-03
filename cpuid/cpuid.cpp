/*
 * CPUID
 *
 * Details obtained from Wikipedia and Intel Developer's Guide
 * Examples:
 *   https://trac.wildfiregames.com/browser/ps/trunk/source/lib/sysdep/arch/x86_x64?order=name
 *   https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=vs-2019
 */

#include <iostream>
#include <cstring>
#include <string>


#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 150030729
// VC10+ and VC9 SP1 have:
//   void __cpuid(int regs[4], int function)  // (subfunction) ECX = 0
//   void __cpuidex(int regs[4], int function, int subfunction)
#  include <intrin.h>
#  define __cpuid__ __cpuid 
#elif defined(__GNUC__)
#  include <cpuid.h>
#  define __cpuid__(regs, func) ((void)__get_cpuid((func), &(regs)[0], &(regs)[1], &(regs)[2], &(regs)[3]))
#else
#  error "Old MSC compiler are not supported."
#endif

#define CHECK_BIT(flag, pos) ((flag) & (1 << (pos)))


// Return flags/values from CPUID instruction.
union cpuid_info {
    uint32_t regs[4];
    struct {
        uint32_t eax;
        uint32_t ebx;
        uint32_t ecx;
        uint32_t edx;
    };
};


// Helps make the code more human readable.
// These values are usually hard-coded where used.
enum {
    // EAX=1, EDX
    CLFLUSH = 19,
    MMX = 23,
    SSE = 25,
    SSE2 = 26,
    HTT = 28,
    // EAX=1, ECX
    SSE3 = 0,
    SSSE3 = 9,
    FMA3 = 12,
    SSE4_1 = 19,
    SSE4_2 = 20,
    AVX = 28,
    // EAX=7, ECX=0, EBX
    AVX2 = 5,
    AVX512F = 16,
    AVX512DQ = 17,
    AVX512IFMA = 21,
    CLFLUSHOPT = 23,
    AVX512PF = 26,
    AVX512ER = 27,
    AVX512CD = 28,
    AVX512BW = 30,
    AVX512VL = 31,
    // EAX=7, ECX=0, EDX
    AVX512FMAPS = 3,
    // Extended features begin with an underscore
    // EAX=0x80000000, EDX
    _MMXEXT = 22,
    _MMX = 23,
    _3DNOWEXT = 30,
    _3DNOW = 31,
    // EAX=0x80000000, ECX
    _SSE4A = 6,
    _3DNOWPREFETCH = 8,
    _FMA4 = 16
};


// Main features for x86 systems.
struct features {
    int clsize = 0;  // cache line size
    bool clflush = 0;
    bool clflushopt = 0;
    bool htt = 0;
    bool fma3 = 0;
    bool mmx = 0;
    bool sse = 0;
    bool sse2 = 0;
    bool sse3 = 0;
    bool ssse3 = 0;
    bool sse4_1 = 0;
    bool sse4_2 = 0;
    bool avx = 0;
    bool avx2 = 0;
    bool avx512f = 0;
    bool avx512dq = 0;
    bool avx512pf = 0;
    bool avx512er = 0;
    bool avx512cd = 0;
    bool avx512bw = 0;
    bool avx512vl = 0;
    bool avx512ifma = 0;
    bool avx512fmaps = 0;
    // Extended features begin with an underscore
    bool _fma4 = 0;
    bool _mmx = 0;
    bool _mmxext = 0;
    bool _sse4a = 0;
    bool _3dnow = 0;
    bool _3dnowext = 0;
    bool _3dnowprefetch = 0;
};


///////////////////////////////////////////////////////////////////////////////
// CPUID instruction
///////////////////////////////////////////////////////////////////////////////
union cpuid_info cpuid(uint32_t function)
{
    // EAX=0: Highest function parameter and manufacturer ID
    // EAX=1: Processor info and feature bits
    // EAX=2: Cache and TLB descriptor info
    // EAX=3: Processor serial number
    // EAX=[4,B]: Intel thread/core and cache topology
    // EAX=7, ECX=0: Extended features
    // EAX=80000000: Highest extended function implemented
    // EAX=80000001: Extended processor info and feature bits
    // EAX=8000000[2-4]: Processor brand string
    // EAX=80000005: L1 cache and TLB identifiers
    // EAX=80000006: Extended L2 cache features
    // EAX=80000007: Advanced power management info
    // EAX=80000008: Virtual and physical address sizes
    const uint32_t subfunction = 0;  // ECX
    union cpuid_info info;
//    asm volatile (
//        "cpuid" : "=a" (info.eax),
//                  "=b" (info.ebx),
//                  "=c" (info.ecx),
//                  "=d" (info.edx)
//                : "a" (function), "c" (subfunction)
//    );
    __cpuid__(info.regs, function);
    return info;
}


///////////////////////////////////////////////////////////////////////////////
// Helper functions for detecting CPU features of interest.
///////////////////////////////////////////////////////////////////////////////
uint32_t highest_function()
{
    union cpuid_info info = cpuid(0);
    return info.eax;
}


uint32_t highest_extended_function()
{
    union cpuid_info info = cpuid(0x80000000);
    return info.eax & 0x7FFFFFFF;  // mask 0x80000000
}


std::string manufacturer_id()
{
    std::string id;
    union cpuid_info info = cpuid(0);
    id += std::string((const char *)&info.ebx, sizeof(info.ebx));
    id += std::string((const char *)&info.edx, sizeof(info.edx));
    id += std::string((const char *)&info.ecx, sizeof(info.ecx));
    return id;
}


std::string processor_id()
{
    std::string id;
    uint32_t hxf = highest_function();
    if (hxf >= 4) {
        union cpuid_info info;
        for (int f = 0x80000002; f <= 0x80000004; f++) {
            info = cpuid(f);
            id += std::string((const char *)&info.eax, sizeof(info.eax));
            id += std::string((const char *)&info.ebx, sizeof(info.ebx));
            id += std::string((const char *)&info.ecx, sizeof(info.ecx));
            id += std::string((const char *)&info.edx, sizeof(info.edx));
        }
    }
    return id;
}


struct features features_supported()
{
    struct features vf;
    union cpuid_info info;

    uint32_t hf = highest_function();
    if (hf >= 1) {
        info = cpuid(1);
        vf.clsize = (0x0000FF00 & info.ebx) >> 5;  // 8 * (x >> 8) = x >> 5
        vf.clflush = CHECK_BIT(info.edx, CLFLUSH);
        vf.htt = CHECK_BIT(info.edx, HTT);
        vf.fma3 = CHECK_BIT(info.ecx, FMA3);
        vf.mmx = CHECK_BIT(info.edx, MMX);
        vf.sse = CHECK_BIT(info.edx, SSE);
        vf.sse2 = CHECK_BIT(info.edx, SSE2);
        vf.sse3 = CHECK_BIT(info.ecx, SSE3);
        vf.ssse3 = CHECK_BIT(info.ecx, SSSE3);
        vf.sse4_1 = CHECK_BIT(info.ecx, SSE4_1);
        vf.sse4_2 = CHECK_BIT(info.ecx, SSE4_2);
        vf.avx = CHECK_BIT(info.ecx, AVX);
    }

    if (hf >= 7) {
        info = cpuid(7);
        vf.clflushopt = CHECK_BIT(info.ebx, CLFLUSHOPT);
        vf.avx2 = CHECK_BIT(info.ebx, AVX2);
        vf.avx512f = CHECK_BIT(info.ebx, AVX512F);
        vf.avx512dq = CHECK_BIT(info.ebx, AVX512DQ);
        vf.avx512pf = CHECK_BIT(info.ebx, AVX512PF);
        vf.avx512er = CHECK_BIT(info.ebx, AVX512ER);
        vf.avx512cd = CHECK_BIT(info.ebx, AVX512CD);
        vf.avx512bw = CHECK_BIT(info.ebx, AVX512BW);
        vf.avx512vl = CHECK_BIT(info.ebx, AVX512VL);
        vf.avx512ifma = CHECK_BIT(info.ebx, AVX512IFMA);
        vf.avx512fmaps = CHECK_BIT(info.edx, AVX512FMAPS);
    }

    uint32_t hxf = highest_function();
    if (hxf >= 1) {
        info = cpuid(0x80000001);
        vf._fma4 = CHECK_BIT(info.ecx, _FMA4);
        vf._mmx = CHECK_BIT(info.edx, _MMX);
        vf._mmxext = CHECK_BIT(info.edx, _MMXEXT);
        vf._sse4a = CHECK_BIT(info.ecx, _SSE4A);
        vf._3dnow = CHECK_BIT(info.edx, _3DNOW);
        vf._3dnowext = CHECK_BIT(info.edx, _3DNOWEXT);
        vf._3dnowprefetch = CHECK_BIT(info.ecx, _3DNOWPREFETCH);
    } 

    // Extended L2 cache features
    if (hxf >= 6) {
        info = cpuid(0x80000006);
        // Use this cache line size value
        vf.clsize = info.ecx & 0xFF;
    }

    return vf;
}


///////////////////////////////////////////////////////////////////////////////
// Program
///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "CPUID level: " << highest_function() << std::endl;
    std::cout << "CPUID extended level: " << highest_extended_function() << std::endl;
    std::cout << "Manufacturer ID: " << manufacturer_id() << std::endl;
    std::cout << "Processor ID: " << processor_id() << std::endl;

    struct features vf = features_supported();
    std::cout << "Cache line size (B): " << vf.clsize << std::endl;
    std::cout << "CLFLUSH: " << vf.clflush << std::endl;
    std::cout << "CLFLUSHOPT: " << vf.clflushopt << std::endl;
    std::cout << "HTT: " << vf.htt << std::endl;
    std::cout << "FMA3: " << vf.fma3 << std::endl;
    std::cout << "MMX: " << vf.mmx << std::endl;
    std::cout << "SSE: " << vf.sse << std::endl;
    std::cout << "SSE2: " << vf.sse2 << std::endl;
    std::cout << "SSE3: " << vf.sse3 << std::endl;
    std::cout << "SSSE3: " << vf.ssse3 << std::endl;
    std::cout << "SSE4.1: " << vf.sse4_1 << std::endl;
    std::cout << "SSE4.2: " << vf.sse4_2 << std::endl;
    std::cout << "AVX: " << vf.avx << std::endl;
    std::cout << "AVX2: " << vf.avx2 << std::endl;
    std::cout << "AVX512_f: " << vf.avx512f << std::endl;
    std::cout << "AVX512_dq: " << vf.avx512dq << std::endl;
    std::cout << "AVX512_pf: " << vf.avx512pf << std::endl;
    std::cout << "AVX512_er: " << vf.avx512er << std::endl;
    std::cout << "AVX512_cd: " << vf.avx512cd << std::endl;
    std::cout << "AVX512_bw: " << vf.avx512bw << std::endl;
    std::cout << "AVX512_vl: " << vf.avx512vl << std::endl;
    std::cout << "AVX512_ifma: " << vf.avx512ifma << std::endl;
    std::cout << "AVX512_4fmaps: " << vf.avx512fmaps << std::endl;

    std::cout << "Extended features" << std::endl;
    std::cout << "FMA4: " << vf._fma4 << std::endl;
    std::cout << "MMX: " << vf._mmx << std::endl;
    std::cout << "SSE4a: " << vf._sse4a << std::endl;
    std::cout << "3DNow!: " << vf._3dnow << std::endl;
    std::cout << "Extended 3DNow!: " << vf._3dnowext << std::endl;
    std::cout << "3DNow! Prefetch: " << vf._3dnowprefetch << std::endl;
}
