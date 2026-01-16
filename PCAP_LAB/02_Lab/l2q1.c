/*
Program : Synchronous Send and Receive with MPI
Name    : Devadathan N R
Class   : CSE - A
Roll No : 04
Reg No  : 230905010

MPI program using synchronous send. Sender process sends a word to receiver.
The second process receives the word, toggles each letter of the word and
sends it back to the first process. Both processes use synchronous send.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    char str[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Process 0: Enter a word: ");
        scanf("%s", str);

        MPI_Ssend(str, strlen(str) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(str, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);

        printf("Process 0: Toggled word received: %s\n", str);
    }
    else if (rank == 1)
    {
        MPI_Recv(str, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (islower(str[i]))
                str[i] = toupper(str[i]);
            else if (isupper(str[i]))
                str[i] = tolower(str[i]);
        }

        MPI_Ssend(str, strlen(str) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

