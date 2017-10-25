/***************************************************************
   File:     c_timer.c

   Function: get_cur_time()

   Return:   current time in seconds as a double value.
             The precision can be as accurate as microseconds
             (10^-6 second).

****************************************************************/

#include <sys/time.h>

double get_cur_time() {
  struct timeval   tv;
  struct timezone  tz;
  double cur_time;
  
  gettimeofday(&tv, &tz);
  cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;
  
  return cur_time;
} 


