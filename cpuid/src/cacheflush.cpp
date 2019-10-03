#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <immintrin.h>
#include "cpuid.h"


void cacheflush_file(const int mode)
{
    const char *file = "/proc/sys/vm/drop_caches";
    FILE *fd = fopen(file, "w");
    fprintf(fd, "%d", mode);
    fclose(fd);
}


void cacheflush(const void *buf, const size_t size)
{
    if (!buf || !size) {
        return;
    }

    struct features fs = get_features();
    if (fs.clflushopt) {
        // clflushopt is available via immintrin.h
        //for (const char *p = (const char *)buf; p < (p + size); p += fs.clsize) {
        //    _mm_clflushopt(p);
        //}
    } else if (fs.clflush) {
        // clflush is also available in SSE2 via emmintrin.h
        for (const char *p = (const char *)buf; p < (p + size); p += fs.clsize) {
            _mm_clflush(p);
        }

        //for (const char *p = (const char *)buf; p < (p + size); p += fs.clsize) {
        //    asm volatile ("clflush (%0)" : : "r"(p));
        //}
        //asm volatile ("sfence" : : : "memory");
    } else {
        cacheflush_file(3);
    } 
}


int main()
{
    cacheflush_file(3);
}
