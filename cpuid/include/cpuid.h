#ifndef _CPUID_H
#define _CPUID_H


/*
 * CPUID
 *
 * Details obtained from Wikipedia and Intel Developer's Guide
 *
 * Examples:
 *   https://trac.wildfiregames.com/browser/ps/trunk/source/lib/sysdep/arch/x86_x64?order=name
 *   https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=vs-2019
 *   http://www.flounder.com/cpuid_explorer2.htm#CPUID(2)
 *
 *   Intel and AMD have CPUID
 *   ARM has CPUID register which requires EL1 or above to access
 *   IBM System Z have STIDP (Store CPU ID)
 *   PowerPC has PVR (Processor Version Register) which requires supervisor access
 *
 * Linux alternatives:
 *   /proc/cpuinfo  
 *   dmidecode
 *   sysconf
 */

#include <string>


#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 150030729
// VC10+ and VC9 SP1 have:
//   void __cpuid(int regs[4], int function)  // (subfunction) ECX = 0
//   void __cpuidex(int regs[4], int function, int subfunction)
#  include <intrin.h>
#  define __cpuid__(r, f)       __cpuid((r), (f))
#  define __cpuidex__(r, f, sf) __cpuidex((r), (f), (sf))
#elif defined(__GNUC__)
#  include <cpuid.h>
#  define __cpuid__(r, f) ((void)__get_cpuid((f), &(r)[0], &(r)[1], &(r)[2], &(r)[3]))
#  define __cpuidex__(r, f, sf) \
     asm volatile ("cpuid"      \
         : "=a" ((r)[0]),       \
           "=b" ((r)[1]),       \
           "=c" ((r)[2]),       \
           "=d" ((r)[3])        \
         : "a" ((f)), "c" ((sf)))
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
    std::string manufacturer_id;
    std::string processor_id;
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


union cpuid_info cpuid(uint32_t function);
union cpuid_info cpuidex(uint32_t function, uint32_t subfunction);
uint32_t highest_function(void);
uint32_t highest_extended_function(void);
std::string manufacturer_id(void);
std::string processor_id(void);
struct features get_features(void);


#endif  // _CPUID_H
