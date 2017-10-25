#include <stdio.h>
#include "c_timer.h"

int main(int argc, char** argv) {
  double btime, etime;
  int i;
  double tmp = 0;
  
  btime = get_cur_time();
  /* Beginning of the desired block to be measured */
  for (i = 0; i < 1000; i++) tmp += 0.09;
  /* End of the desired block to be measured */
  etime = get_cur_time();
  
  printf("Elapsed time: %f seconds\n", etime-btime);

  return 0;
}
