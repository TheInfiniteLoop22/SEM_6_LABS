/*
Program : Even Factorial Odd Fibonacci
Name : Devadathan N R
Class : CSE - A
Roll No : 04
Reg No : 230905010
*/

#include <mpi.h>
#include <stdio.h>

long factorial(int n){
    long f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}


long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank % 2 == 0) {
        printf("factorial(%d) = %ld\n",rank, factorial(rank));
    } else {
        printf("fibonacci(%d) = %ld\n",rank, fibonacci(rank));
    }

    MPI_Finalize();
    return 0;
}

