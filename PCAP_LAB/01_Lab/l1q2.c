/*
Program : Simple Calculator Simulation
Name : Devadathan N R
Class : CSE - A
Roll No : 04
Reg No : 230905010
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, a, b;
    a=10;
    b=5;
    

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        printf("Addition: %d + %d = %d\n", a, b, a + b);
    }
    else if (rank == 1) {
        printf("Subtraction: %d - %d = %d\n", a, b, a - b);
    }
    else if (rank == 2) {
        printf("Multiplication: %d * %d = %d\n", a, b, a * b);
    }
    else if (rank == 3) {
        printf("Division: %d / %d = %d\n", a, b, a / b);
    }

    MPI_Finalize();
    return 0;
}

