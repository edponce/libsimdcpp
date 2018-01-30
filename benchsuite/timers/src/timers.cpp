#include <stdlib.h>
#include "timers.h"


#if !defined(USE_MONOTONIC_CLOCK)

#include <sys/time.h>  // gettimeofday, timeval

void tic(long int * const timers)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    timers[0] = tv.tv_sec;
    timers[1] = tv.tv_usec;
}

double toc(long int * const timers)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (tv.tv_usec >= timers[1]) {
        timers[0] = tv.tv_sec - timers[0];
        timers[1] = tv.tv_usec - timers[1];
    }
    else {
        timers[0] = tv.tv_sec - timers[0];
        timers[1] = timers[1] - tv.tv_usec;
    }

    return timers[0] + timers[1] / 1e6;
}

#else

#include <time.h>  // clock_gettime, CLOCK_MONOTONIC_RAW

void tic(long int * const timers)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    timers[0] = ts.tv_sec;
    timers[1] = ts.tv_nsec;
}

double toc(long int * const timers)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    if (ts.tv_nsec >= timers[1]) {
        timers[0] = ts.tv_sec - timers[0];
        timers[1] = ts.tv_nsec - timers[1];
    }
    else {
        timers[0] = ts.tv_sec - timers[0];
        timers[1] = timers[1] - ts.tv_nsec;
    }

    return timers[0] + timers[1] / 1e9;
}

#endif

