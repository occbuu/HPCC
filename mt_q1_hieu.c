#include <stdio.h>
#include <math.h>
#include "mpi.h"

void main()
{
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n, N;
    double Delta, f, S, x;

    N = 1000;
    Delta = M_PI / 2.0 / N;
    S = 0.0;

    int a = rank;
    for (n = 0; n < N; n++)
    {
        x = n * Delta;
        f = 1.0 / (1.0 + a + sin(x));
        S = S + Delta * f;
    }
    printf("Rank %d: S = %f \n", rank, S);
    MPI_Finalize();
}