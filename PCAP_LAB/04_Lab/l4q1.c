/*
Question:
Write a MPI program using N processes to find 1! + 2! + ….. + N!.
Use scan. Also, handle different errors using error handling routines.

Name : Devadathan N R
Class: CSE A1
Reg No : 230905010
Roll No : 04
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pid, nprocs, n;
    unsigned long fact_local, fact_scan;
    unsigned long sum_local, sum_global;
    int status;
    char err_msg[MPI_MAX_ERROR_STRING];
    int msg_len;

    status = MPI_Init(&argc, &argv);
    if (status != MPI_SUCCESS)
    {
        MPI_Error_string(status, err_msg, &msg_len);
        printf("%s\n", err_msg);
        MPI_Abort(MPI_COMM_WORLD, status);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (pid == 0)
    {
        if (argc != 2)
        {
            printf("Usage: mpirun -np N ./a.out <N>\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        n = atoi(argv[1]);

        if (n <= 0 || n != nprocs)
        {
            printf("N must be positive and equal to number of processes\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    fact_local = pid + 1;

    MPI_Scan(&fact_local, &fact_scan, 1,
             MPI_UNSIGNED_LONG, MPI_PROD, MPI_COMM_WORLD);

    sum_local = fact_scan;

    MPI_Reduce(&sum_local, &sum_global, 1,
               MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (pid == 0)
        printf("Result = %lu\n", sum_global);

    MPI_Finalize();
    return 0;
}
