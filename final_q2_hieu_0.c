#include <stdio.h>
#include <mpi.h>

//&data: dia chi cua bien (dia chi dau tien)
//count: so luong bien trong mot chuoi
//MPI_DOUBLE:kieu cua bien (so thuc, so nguyen, hay ky tu)
//MPI_INT: so thuc
//dest: noi nhan
//tag:


int fibo(int n)
{
    int a = 0, b = 1, c, i;
    if (n == 0)
        return a;
    for (i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void master_code(int N)
{
    int S, S0, S1, data;
    int i;

    S0 = fibo(N - 1);

    int count, dest, tag;
    count = 1;
    dest = 1; //rank
    tag = 1;

    MPI_Recv(&data, count, MPI_INT, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Master has calculated The Fibonacci of (n-1)=%d :\n", (N - 1));
    printf("\tF(%d) = %d\n", (N - 1), S0);
    printf("Master received data F(%d)= %d from slave.\n", (N - 2), data);
    S1 = data;
    S = S0 + S1;
    printf("The F(%d) = F(%d) + F(%d) :\n", N, (N - 1), (N - 2));
    printf("\t= %d \n", S);
}

void slave_code(int N)
{
    int S1, data;
    int count, dest, tag;
    S1 = fibo(N - 2);

    data = S1;
    count = 1;
    dest = 0; //rank
    tag = 1;
    MPI_Send(&data, count, MPI_INT, dest, tag, MPI_COMM_WORLD);

    printf("Slave has calculated F(%d) = %d :\n", (N - 2), S1);
    printf("Slave sent data to master\n");
}

void main()
{
    int N=10 ;
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    

    if (rank == 0)
        master_code(N);
    else
        slave_code(N);
    MPI_Finalize();
}