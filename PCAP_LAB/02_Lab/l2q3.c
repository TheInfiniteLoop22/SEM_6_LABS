/*
3] Write an MPI program to read N elements of an array in the root process
(process 0) where N is equal to the total number of processes. The root
process sends one value to each of the slaves. Even ranked processes find
the square of the received element and odd ranked processes find the cube
of the received element. Use buffered send.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, num;
    int arr[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter %d elements:\n", size - 1);
        for (int i = 1; i < size; i++)
            scanf("%d", &arr[i]);

        int buffer_size = (sizeof(int) + MPI_BSEND_OVERHEAD) * (size - 1);
        void *buffer = malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        for (int i = 1; i < size; i++)
        {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    }
    else
    {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        if (rank % 2 == 0)
            printf("Process %d:  Recieved number: %d  Square = %d\n",rank,num,num*num);
        else
            printf("Process %d:  Recieved number: %d  Cube = %d\n",rank,num,num*num*num);
    }

    MPI_Finalize();
    return 0;
}

