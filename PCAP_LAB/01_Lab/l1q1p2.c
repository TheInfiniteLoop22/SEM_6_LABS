/*
Program : pow(x,rank)
Name : Devadathan N R
Class : CSE - A
Roll No : 04
Reg No : 230905010
*/

#include<stdio.h>
#include<math.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
    int rank, x=5;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Rank %d output -> pow(%d, %d): %f\n", rank, x, rank, pow(x, rank));

    MPI_Finalize();
    return 0;
}
