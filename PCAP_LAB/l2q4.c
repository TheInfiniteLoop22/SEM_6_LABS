/*
Write an MPI program to read an integer value in the root process.
The root process sends this value to process 1, process 1 sends it
to process 2 and so on. The last process sends the value back to the
root process. When sending the value, each process increments the
received value by one. Use point-to-point communication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int r, s, n;
    MPI_Status w;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    if (r == 0)
    {
        printf("Process %d: Enter the number to send:\n", r);
        scanf("%d", &n);

        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_INT, s - 1, 0, MPI_COMM_WORLD, &w);

        printf("Process %d: Received the number: %d\n", r, n);
    }
    else
    {
        MPI_Recv(&n, 1, MPI_INT, r - 1, 0, MPI_COMM_WORLD, &w);
        printf("Process %d: Received the number: %d\n", r, n);

        n++;

        if (r != s - 1)
        {
            MPI_Send(&n, 1, MPI_INT, r + 1, 0, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Send(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
