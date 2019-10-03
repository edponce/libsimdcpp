//#include <cstring>
#include "cpuid.h"


union cpuid_info cpuidex(uint32_t function, uint32_t subfunction)
{
    union cpuid_info info;
    __cpuidex__(info.regs, function, subfunction);
    return info;
}


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
//    const uint32_t subfunction = 0;  // ECX
//    union cpuid_info info;
//    asm volatile (
//        "cpuid" : "=a" (info.eax),
//                  "=b" (info.ebx),
//                  "=c" (info.ecx),
//                  "=d" (info.edx)
//                : "a" (function), "c" (subfunction)
//    );
//    __cpuid__(info.regs, function);
//    return info;
    return cpuidex(function, 0);
}


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


struct features get_features()
{
    struct features vf;
    union cpuid_info info;

    vf.manufacturer_id = manufacturer_id();
    vf.processor_id = processor_id(); 

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

    uint32_t hxf = highest_extended_function();
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
