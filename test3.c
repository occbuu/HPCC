#include <stdio.h>
#define NBIN 10000000

void main()
{
    int i;
    double step, x, sum = 0.0, pi;
    step = 1.0/NBIN;
    for (i=0; i<NBIN; i++)
    {
        x= (i+0.5)*step;
        sum += 4.0 / (1.0 +x*x);
    }
    pi = sum*step;
    printf("PU = %f\n", pi);
}