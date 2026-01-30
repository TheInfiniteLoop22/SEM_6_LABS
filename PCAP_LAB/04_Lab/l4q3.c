/*
Question:
Write a MPI program to read 4 X 4 matrix and display the following output
using four processes.

Name : Devadathan N R
Class: CSE A1
Reg No : 230905010
Roll No : 04
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int pid, nprocs;
    int mat[4][4], out[4][4];
    int block[4], prefix[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (nprocs != 4)
    {
        if (pid == 0)
            printf("This program requires exactly 4 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (pid == 0)
    {
        printf("Enter 4x4 matrix:\n");
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            	scanf("%d", &mat[i][j]);
    }

    MPI_Scatter(mat, 4, MPI_INT,block, 4, MPI_INT,0, MPI_COMM_WORLD);

    MPI_Scan(block, prefix, 4, MPI_INT,MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(prefix, 4, MPI_INT,out, 4, MPI_INT,0, MPI_COMM_WORLD);

    if (pid == 0)
    {
        printf("Output Matrix:\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%d ", out[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}


