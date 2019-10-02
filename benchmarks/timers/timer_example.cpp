#include <stdio.h>
#include "timers.h"


int main(int argc, char** argv)
{
    long int timer[2];
    double elapsed = 0.0;

    printf("Press any non-whitespace key to stop timer...");

    tic(timer);
    char a = getchar();
    elapsed = toc(timer);

    printf("Elapsed time: %f seconds\n", elapsed);

    return 0;
}
