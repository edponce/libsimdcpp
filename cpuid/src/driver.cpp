#include <iostream>
#include "cpuid.h"


int main()
{
    std::cout << "CPUID level: " << highest_function() << std::endl;
    std::cout << "CPUID extended level: " << highest_extended_function() << std::endl;

    struct features fs = get_features();
    std::cout << "Manufacturer ID: " << fs.manufacturer_id << std::endl;
    std::cout << "Processor ID: " << fs.processor_id << std::endl;
    std::cout << "Cache line size (B): " << fs.clsize << std::endl;
    std::cout << "CLFLUSH: " << fs.clflush << std::endl;
    std::cout << "CLFLUSHOPT: " << fs.clflushopt << std::endl;
    std::cout << "HTT: " << fs.htt << std::endl;
    std::cout << "FMA3: " << fs.fma3 << std::endl;
    std::cout << "MMX: " << fs.mmx << std::endl;
    std::cout << "SSE: " << fs.sse << std::endl;
    std::cout << "SSE2: " << fs.sse2 << std::endl;
    std::cout << "SSE3: " << fs.sse3 << std::endl;
    std::cout << "SSSE3: " << fs.ssse3 << std::endl;
    std::cout << "SSE4.1: " << fs.sse4_1 << std::endl;
    std::cout << "SSE4.2: " << fs.sse4_2 << std::endl;
    std::cout << "AVX: " << fs.avx << std::endl;
    std::cout << "AVX2: " << fs.avx2 << std::endl;
    std::cout << "AVX512_f: " << fs.avx512f << std::endl;
    std::cout << "AVX512_dq: " << fs.avx512dq << std::endl;
    std::cout << "AVX512_pf: " << fs.avx512pf << std::endl;
    std::cout << "AVX512_er: " << fs.avx512er << std::endl;
    std::cout << "AVX512_cd: " << fs.avx512cd << std::endl;
    std::cout << "AVX512_bw: " << fs.avx512bw << std::endl;
    std::cout << "AVX512_vl: " << fs.avx512vl << std::endl;
    std::cout << "AVX512_ifma: " << fs.avx512ifma << std::endl;
    std::cout << "AVX512_4fmaps: " << fs.avx512fmaps << std::endl;

    std::cout << "Extended features" << std::endl;
    std::cout << "FMA4: " << fs._fma4 << std::endl;
    std::cout << "MMX: " << fs._mmx << std::endl;
    std::cout << "SSE4a: " << fs._sse4a << std::endl;
    std::cout << "3DNow!: " << fs._3dnow << std::endl;
    std::cout << "Extended 3DNow!: " << fs._3dnowext << std::endl;
    std::cout << "3DNow! Prefetch: " << fs._3dnowprefetch << std::endl;
}
