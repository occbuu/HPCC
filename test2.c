#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int process_Rank, size_Of_Cluster;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    printf("Xin chao, day la thong diep tu tien trinh so %d trong tong so %d tien trinh \n",process_Rank,size_Of_Cluster);
    MPI_Finalize();
    return 0;
}