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
    for (j = 2; j <= n / 2; ++j)
    {
        if (n % j == 0)
        {
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
    int S = 0;
    for (i = 0; i <= N; i++)
    {
        MPI_Recv(a, count, MPI_INT, dest, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (isPrime(i) == 1)
        {
            printf("Master found Prime at %d \n", i);
            S = S + i;
        }
        if(a[0] == 1)
        {
            printf("\tSlave found Prime at %d , sent to Master \n", a[1]);
            S = S + a[1];
        }
    }

    printf("Total of found Primes = %d \n", S);
}

void slave_code(int N)
{
    int i, count, dest, tag;
    int a[2], b;

    count = 2;
    dest = 0; //rank
    tag = 1;
    for (i = N+1; i <= N*2+1; i++)
    {
        if(isPrime(i)==1)
        {
            a[0]=1;
            a[1]= i;
        }
        else
        {
            a[0]=0;
            a[1]=0;
        }
        MPI_Send(a, count, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
}

void main()
{
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N = 50;
    if (rank == 0)
        master_code(N);
    else
        slave_code(N);

    MPI_Finalize();
}
