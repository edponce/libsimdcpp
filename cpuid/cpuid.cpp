#include <iostream>
#include <cstring>
#include <string>


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
    MMX = 23,
    SSE = 25,
    SSE2 = 26,
    // EAX=1, ECX
    SSE3 = 0,
    SSSE3 = 9,
    SSE4_1 = 19,
    SSE4_2 = 20,
    AVX = 28,
    // EAX=7, EBX
    AVX2 = 5,
    AVX512f = 16,
    AVX512dq = 17,
    AVX512pf = 26,
    AVX512er = 27,
    AVX512cd = 28,
    AVX512bw = 30,
    AVX512vl = 31,
};


// Main vector features for x86 systems.
union vector_features {
    bool flags[16];
    struct {
        bool mmx;
        bool sse;
        bool sse2;
        bool sse3;
        bool ssse3;
        bool sse4_1;
        bool sse4_2;
        bool avx;
        bool avx2;
        bool avx512f;
        bool avx512dq;
        bool avx512pf;
        bool avx512er;
        bool avx512cd;
        bool avx512bw;
        bool avx512vl;
    };
};


///////////////////////////////////////////////////////////////////////////////
// CPUID instruction
///////////////////////////////////////////////////////////////////////////////
union cpuid_info cpuid(uint32_t leaf)
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
    union cpuid_info info;
    asm volatile (
        "cpuid" : "=a" (info.eax),
                  "=b" (info.ebx),
                  "=c" (info.ecx),
                  "=d" (info.edx)
                : "a" (leaf), "c" (0)
    );

    return info;
}


///////////////////////////////////////////////////////////////////////////////
// Helper functions for detecting CPU features of interest.
///////////////////////////////////////////////////////////////////////////////
uint32_t highest_leaf_value()
{
    union cpuid_info info = cpuid(0);
    return info.eax;
}


std::string manufacturer()
{
    union cpuid_info info = cpuid(0);
    std::string vendor;
    vendor += std::string((const char *)&info.ebx, sizeof(info.ebx));
    vendor += std::string((const char *)&info.edx, sizeof(info.edx));
    vendor += std::string((const char *)&info.ecx, sizeof(info.ecx));
    return vendor;
}


union vector_features vector_features_supported()
{
    union cpuid_info info = cpuid(1);
    union vector_features vf;
    vf.mmx = CHECK_BIT(info.edx, MMX);
    vf.sse = CHECK_BIT(info.edx, SSE);
    vf.sse2 = CHECK_BIT(info.edx, SSE2);
    vf.sse3 = CHECK_BIT(info.ecx, SSE3);
    vf.ssse3 = CHECK_BIT(info.ecx, SSSE3);
    vf.sse4_1 = CHECK_BIT(info.ecx, SSE4_1);
    vf.sse4_2 = CHECK_BIT(info.ecx, SSE4_2);
    vf.avx = CHECK_BIT(info.ecx, AVX);

    info = cpuid(7);
    vf.avx2 = CHECK_BIT(info.ebx, AVX2);
    vf.avx512f = CHECK_BIT(info.ebx, AVX512f);
    vf.avx512dq = CHECK_BIT(info.ebx, AVX512dq);
    vf.avx512pf = CHECK_BIT(info.ebx, AVX512pf);
    vf.avx512er = CHECK_BIT(info.ebx, AVX512er);
    vf.avx512cd = CHECK_BIT(info.ebx, AVX512cd);
    vf.avx512bw = CHECK_BIT(info.ebx, AVX512bw);
    vf.avx512vl = CHECK_BIT(info.ebx, AVX512vl);

    return vf;
}


///////////////////////////////////////////////////////////////////////////////
// Program
///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "Highest CPUID leaf value: " << highest_leaf_value() << std::endl;
    std::cout << "CPU manufacturer: " << manufacturer() << std::endl;

    union vector_features vf = vector_features_supported();
    std::cout << "MMX: " << vf.mmx << std::endl;
    std::cout << "SSE: " << vf.sse << std::endl;
    std::cout << "SSE2: " << vf.sse2 << std::endl;
    std::cout << "SSE3: " << vf.sse3 << std::endl;
    std::cout << "SSSE3: " << vf.ssse3 << std::endl;
    std::cout << "SSE4.1: " << vf.sse4_1 << std::endl;
    std::cout << "SSE4.2: " << vf.sse4_2 << std::endl;
    std::cout << "AVX: " << vf.avx << std::endl;
    std::cout << "AVX2: " << vf.avx2 << std::endl;
    std::cout << "AVX512f: " << vf.avx512f << std::endl;
    std::cout << "AVX512dq: " << vf.avx512dq << std::endl;
    std::cout << "AVX512pf: " << vf.avx512pf << std::endl;
    std::cout << "AVX512er: " << vf.avx512er << std::endl;
    std::cout << "AVX512cd: " << vf.avx512cd << std::endl;
    std::cout << "AVX512bw: " << vf.avx512bw << std::endl;
    std::cout << "AVX512vl: " << vf.avx512vl << std::endl;
}
