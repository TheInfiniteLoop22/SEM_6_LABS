/*
Program : Rank based string charecter toggle
Name : Devadathan N R
Class : CSE - A
Roll No : 04
Reg No : 230905010
*/

#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char str[] = "HELLO";
    int len;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    len = strlen(str);

    if (rank < len) {
        if (str[rank] >= 'A' && str[rank] <= 'Z')
            str[rank] = str[rank] + 32;
        else if (str[rank] >= 'a' && str[rank] <= 'z')
            str[rank] = str[rank] - 32;

        printf("Process %d toggled string: %s\n", rank, str);
    }

    MPI_Finalize();
    return 0;
}

