#include <stdio.h>
#include <mpi.h>

int N = 5;

void master_code()
{
    int n = 0, i;
    double a;

    for (i = 0; i < N; i++)
    {
        a = (n + 1) / i;

        MPI_Send(&n, 0, MPI_INT, 1, 1, MPI_COMM_WORLD);

        MPI_Recv(&n, 0, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("master i=%d n=%d a=%f\n", i, n, a);
        n++;
    }
}

void slave_code()
{
    int n, i;
    double a;

    for (i = 0; i < N; i++)        
    {
        a = (n + 1) / i;

        MPI_Recv(&n, 0, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("slave i=%d n=%d a=%f\n", i, n, a);
        n++;

        MPI_Send(&n, 0, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
}