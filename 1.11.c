#include <stdio.h>
#include <math.h>
#include <mpi.h>

//&data: dia chi cua bien (dia chi dau tien)
//count: so luong bien trong mot chuoi
//MPI_DOUBLE:kieu cua bien (so thuc, so nguyen, hay ky tu)
//MPI_INT: so thuc
//dest: noi nhan
//tag:

void master_code()
{
    int i, count, dest, tag, n;
    double a[2] = {0, 1};
    count = 2;
    dest = 1; //rank
    tag = 1;
    for (i = 0; i < 15; i = i + 1)
    {
        MPI_Send(a, count, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);

        MPI_Recv(a, count, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("master i%d data = %f \n", i, a[1]);
    }
}

void slave_code()
{
    int i, count, dest, tag, n;
    double a[2], b;

    count = 2;
    dest = 0; //rank
    tag = 1;
    for (i = 0; i < 15; i = i + 1)
    {
        MPI_Recv(a, count, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("slave i%d data = %f \n", i, a[1]);

        b = a[1] + a[0];
        a[0] = a[1];
        a[1] = b;

        MPI_Send(a, count, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
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
//data = 0;
