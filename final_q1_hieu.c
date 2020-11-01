#include <stdio.h>
#include <mpi.h>

int N = 5;

void master_code()
{
    int n = 0, i;
    double a;

    for (i = 1; i < N; i++)
    {
        a = (n + 1.0) / i;
        MPI_Send(&n, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

        MPI_Recv(&n, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("master i=%d n=%d a=%f\n", i, n, a);
        n++;
    }
}

void slave_code()
{
    int n=0, i;
    double a;

    for (i = 1; i < N; i++)
    {
        a = (n + 1.0) / i;

        MPI_Recv(&n, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("slave i=%d n=%d a=%f\n", i, n, a);
        n++;

        MPI_Send(&n, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
}

void main()
{
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        master_code();
    else
        slave_code();

    MPI_Finalize();
}