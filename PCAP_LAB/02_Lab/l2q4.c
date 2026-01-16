/*
Program : Ring Communication with MPI
Name    : Devadathan N R
Class   : CSE - A
Roll No : 04
Reg No  : 230905010

Write an MPI program to read an integer value in the root process.
The root process sends this value to process 1, process 1 sends it
to process 2 and so on. The last process sends the value back to the
root process. When sending the value, each process increments the
received value by one. Use point-to-point communication.
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, value;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter an integer: ");
        scanf("%d", &value);

        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);

        printf("Final value received in root = %d\n", value);
    }
    else if (rank == size - 1)
    {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        value = value + 1;
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        value = value + 1;
        MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

