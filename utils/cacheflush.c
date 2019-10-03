#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <immintrin.h>


void cacheflush_file(const int mode)
{
    const char *file = "/proc/sys/vm/drop_caches";
    FILE *fd = fopen(file, "w");
    fprintf(fd, "%d", mode);
    fclose(fd);
}


void cacheflush(const void *p, const size_t size, int mode)
{
    // NOTE: Get cache line from CPUID
    const size_t cache_line = 64;
    const char *cp = (const char *)p;

    if (!p || !size) {
        return;
    }

    // NOTE: CPUID can be used to check clflush instruction.
    switch (mode) {
        case 0:
            for (size_t i = 0; i < size; i+= cache_line) {
                 asm volatile (
                      "clflush (%0)" :
                                     : "r"(&cp[i])
                 );
            }
            
            asm volatile (
                 "sfence" :
                          :
                          : "memory"
            );
            break;
        case 1:
            // clflush is also available in SSE2 via emmintrin.h
            for (size_t i = 0; i < size; i+= cache_line) {
                _mm_clflush(&cp[i]);
            }
            break;
        case 2:
            // clflushopt is available via immintrin.h
            for (size_t i = 0; i < size; i+= cache_line) {
                _mm_clflushopt(&cp[i]);
            }
            break;
    }
}


int main()
{
    cacheflush_file(3);
}
