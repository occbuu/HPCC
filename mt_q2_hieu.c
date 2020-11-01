#include <stdio.h>
#include <math.h>

void main()
{
    //begin calculations
    int n1, n2, n, N = 10000;
    double Delta, x, f1, f2, x1, x2, S1, S2, S;

    Delta = (M_PI / 2.0 - 0.0) / N;

    S1 = 0.0;
    for (n = 0; n <= N; n++)
    {
        x1 = n * Delta;
        f1 = sin(x1);
        S1 = S1 + Delta * f1;
    }
    printf("The integral from 0 to PI/2 of sin(x) :\n");
    printf("\tS(1) = %f\n", S1);

    S2 = 0.0;
    for (n = 0; n <= N; n++)
    {
        x2 = n * Delta;
        f2 = cos(x2);
        S2 = S2 + Delta * f2;
    }
    printf("The integral from 0 to PI/2 of cos(x) :\n");
    printf("\tS(2) = %f\n", S2);

    S = S1 + S2;
    printf("The integral from 0 to PI/2 of [sin(x) + cos(x)] :\n");
    printf("\tS    = S(1) + S(2) = %f\n", S);
}