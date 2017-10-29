#include <stdio.h>
#include "timers.h"

int main(int argc, char** argv)
{
    long int timer[2];
    double elapsed = 0.0;

    tic(timer);
    char a = getchar();
    elapsed = toc(timer);

    printf("Elapsed time: %f seconds\n", elapsed);

    return 0;
}
