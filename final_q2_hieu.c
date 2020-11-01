#include <stdio.h>
#include <math.h>
#include <mpi.h>

//&data: dia chi cua bien (dia chi dau tien)
//count: so luong bien trong mot chuoi
//MPI_DOUBLE:kieu cua bien (so thuc, so nguyen, hay ky tu)
//MPI_INT: so thuc
//dest: noi nhan
//tag:

int isPrime(int n)
{
    int j, flag = 1;
    for (j = 2; j <= n / 2; ++j) {
        if (n % j == 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}

void master_code(int N)
{
    int i, count, dest, tag;
    int a[2] = {0, 1};
    count = 2;
    dest = 1; //rank
    tag = 1;
    for (i = 0; i <= N; i = i + 1)
    {
        MPI_Send(a, count, MPI_INT, dest, tag, MPI_COMM_WORLD);

        MPI_Recv(a, count, MPI_INT, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //printf("master Fibo(%d)  = %d \n", i, a[1]);
        if(isPrime(a[1])==1)
            printf("master Fibo(%d) = %d , this is Prime number \n", i, a[1]);
        else
            printf("master Fibo(%d) = %d \n", i, a[1]);       
        
    }
}

void slave_code(int N)
{
    int i, count, dest, tag;
    int a[2], b;

    count = 2;
    dest = 0; //rank
    tag = 1;
    for (i = 0; i <= N; i = i + 1)
    {
        MPI_Recv(a, count, MPI_INT, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Slave Fibo(%d) = %d \n", i, a[1]);

        b = a[1] + a[0];
        a[0] = a[1];
        a[1] = b;

        MPI_Send(a, count, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
}

void main()
{
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N =30;
    if (rank == 0)
        master_code(N);
    else
        slave_code(N);

    MPI_Finalize();
}
