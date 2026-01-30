/*
Question:
Write a MPI program to read a 3 X 3 matrix. Enter an element to be searched
in the root process. Find the number of occurrences of this element in the
matrix using three processes.

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
    int mat[3][3];
    int key;
    int part[3];
    int count_local = 0, count_total = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (nprocs != 3)
    {
        if (pid == 0)
            printf("This program requires exactly 3 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (pid == 0)
    {
        printf("Enter 3x3 matrix:\n");
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                scanf("%d", &mat[i][j]);

        printf("Enter element to search: ");
        scanf("%d", &key);
    }

    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(mat, 3, MPI_INT,part, 3, MPI_INT,0, MPI_COMM_WORLD);

    for (int i = 0; i < 3; i++)
        if (part[i] == key)
            count_local++;

    MPI_Reduce(&count_local, &count_total, 1,MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (pid == 0)
        printf("Number of occurrences of %d = %d\n", key, count_total);

    MPI_Finalize();
    return 0;
}


