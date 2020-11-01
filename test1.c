#include <stdio.h>
#include "mpi.h"

void main()
{
	int size, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);	
    int n, N=100;
    double Delta, x, f,S;
    Delta = (1.0-0.0)/N;
    S = 0.0;
    for(n=rank+1; n<=N;n=n+2)
    {
        x= n*Delta;
        f = 4.0/(1.0+x*x);
        S= S + Delta*f;
    }
    printf("S(rank= %d)= %f \n" ,rank, S);
    MPI_Finalize();
}
