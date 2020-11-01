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
    double S0, S1, S, data, Delta, x, f;
    int n, N = 10000;
    Delta = (M_PI / 2.0 - 0.0) / N;
    // S0 de tinh sin(x)
    S0 = 0.0;
    for (n = 0; n <= N; n++)
    {
        x = n * Delta;
        f = sin(x);
        S0 = S0 + Delta * f;
    }
    int count, dest, tag;
    count = 1;
    dest = 1; //rank
    tag = 1;

    MPI_Recv(&data, count, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    printf("Master has calculated The integral from 0 to PI/2 of sin(x) :\n");
    printf("\tS0 = %f\n", S0);
    printf("Master received data S1 from slave.\n");
    S1 = data;
    S = S0 + S1;
    printf("The integral from 0 to PI/2 of [sin(x) + cos(x)] :\n");
    printf("\tS = %f \n", S);
}

void slave_code()
{
    double S1 , data, Delta, f, x;
    int count, dest, tag;
    S1 = 0.0;
    int n, N = 10000;
    Delta = (M_PI / 2.0- 0.0) / N;
    for (n = 0; n <= N; n++)
    {
        x = n * Delta;
        f = cos(x);
        S1 = S1 + Delta * f;
    }
    data = S1;
    count = 1;
    dest = 0; //rank
    tag = 1;
    MPI_Send(&data, count, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    
    printf("Slave has calculated The integral from 0 to PI/2 of cos(x) :\n");
    printf("\tS1 = %f\n", S1);
    printf("Slave sent data to master\n");
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