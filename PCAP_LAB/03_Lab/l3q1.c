/*
Write an MPI program to read N values in root. 
Root sends one value to each process. 
Each process returns factorial of the number to root. 
Root prints sum of factorials of all processes.
*/

#include <stdio.h>
#include <mpi.h>

int fact(int n)
{
    int k = 1;
    for(int i = 1; i <= n; i++)
        k *= i;
    return k;
}

int main(int argc, char *argv[])
{
    int r, s, c, sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    int a[s], b[s];

    if(r == 0)
    {
        printf("Enter %d elements:\n", s);
        for(int i=0;i<s;i++)
            scanf("%d",&a[i]);
    }

    MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);

    c = fact(c);

    MPI_Gather(&c,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);

    if(r==0)
    {
        for(int i=0;i<s;i++)
            sum += b[i];

        printf("Total sum: %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}
/*
Enter 4 elements:
1 2 3 4
Total sum: 33
*/

