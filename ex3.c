#include <stdio.h>
#include <math.h>
#include <mpi.h>

void main()
{
    int size, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //begin calculations
    int n1, n2, n, N = 1000;
    double Delta, x, f1, f2, x1, x2, S1, S2, S;

    Delta = (M_PI / 2.0 - 0.0) / N;

    if (rank == 0)
    {
        S1 = 0.0;
        for (n = 0; n <= N; n = n + 1)
        {
            x1 = n * Delta;
            f1 = sin(x1);
            S1 = S1 + Delta * f1;
        }
        printf("S(rank=%d) = %f\n", rank, S1);
    }
    else
    {
        S2 = 0.0;
        for (n = 0; n <= N; n = n + 1)
        {
            x2 = n * Delta;
            f2 = cos(x2);
            S2 = S2 + Delta * f2;
        }

        printf("S(rank=%d) = %f\n", rank, S2);
    }

    MPI_Finalize();
}