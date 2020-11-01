#include <stdio.h>
#include <math.h>

int main(){
    int n, N;
    double x, y, Delta, S,f;
    
    N = 10;
    Delta = (1.0 - 0.0)/N;
    S = 0.0;

    for(n = 1; n <= N; n++){
        x = n * Delta;
        y = -x * x/2.0;
        f = exp(y);
        S = S + Delta * f;
    }
    printf("S = %f \n", S);
    return 0;
}