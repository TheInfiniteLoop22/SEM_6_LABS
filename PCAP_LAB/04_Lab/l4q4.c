/*
Question:
Write a MPI program to read a word of length N. Using N processes including
the root get output word with the pattern as shown.

Name : Devadathan N R
Class: CSE A1
Reg No : 230905010
Roll No : 04
*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int pid, nprocs, length;
    char str[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (pid == 0)
    {
        printf("Enter the word: ");
        scanf("%s", str);
        length = strlen(str);
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (nprocs != length)
    {
        if (pid == 0)
            printf("Number of processes must be equal to word length\n");
        MPI_Finalize();
        return 0;
    }

    char letter;
    MPI_Scatter(str, 1, MPI_CHAR,&letter, 1, MPI_CHAR,0, MPI_COMM_WORLD);

    char local_buf[100];
    int repeat = pid + 1;

    for (int i = 0; i < repeat; i++)
        local_buf[i] = letter;
    local_buf[repeat] = '\0';

    int recv_cnt[100], disp[100];
    int total_len = 0;

    if (pid == 0)
    {
        for (int i = 0; i < nprocs; i++)
        {
            recv_cnt[i] = i + 1;
            disp[i] = total_len;
            total_len += recv_cnt[i];
        }
    }

    char final_str[500];

    MPI_Gatherv(local_buf, repeat, MPI_CHAR,final_str, recv_cnt, disp,MPI_CHAR, 0, MPI_COMM_WORLD);

    if (pid == 0)
    {
        final_str[total_len] = '\0';
        printf("Output: %s\n", final_str);
    }

    MPI_Finalize();
    return 0;
}


