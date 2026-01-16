/*
Program : Standard Send and Receive with MPI
Name    : Devadathan N R
Class   : CSE - A
Roll No : 04
Reg No  : 230905010

Write an MPI program where the master process (process 0) sends a number
to each of the slave processes and the slave processes receive the number
and print it. Use standard send.
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, num;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Master: Enter a number: ");
        scanf("%d", &num);

        /* Send number to all slave processes */
        for (int i = 1; i < size; i++)
        {
            MPI_Send(&num, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master: Sent %d to process %d\n", num, i);
        }
    }
    else
    {
        /* Slave receives number */
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Slave process %d received %d\n", rank, num);
    }

    MPI_Finalize();
    return 0;
}
