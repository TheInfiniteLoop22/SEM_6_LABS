/*
/*
Write an MPI program to read integer M and N×M elements.
Root sends M elements to each process.
Each process finds average of its M elements.
Root finds total average using collective communication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int r, s, m;
    int *a = NULL;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    MPI_Comm_size(MPI_COMM_WORLD,&s);

    if(r==0)
    {
        printf("Enter M: ");
        scanf("%d",&m);
    }

    MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

    int *local = (int*)malloc(m*sizeof(int));
    float local_avg;

    if(r==0)
    {
        a = (int*)malloc(s*m*sizeof(int));
        printf("Enter %d elements:\n", s*m);
        for(int i=0;i<s*m;i++)
            scanf("%d",&a[i]);
    }

    MPI_Scatter(a,m,MPI_INT,local,m,MPI_INT,0,MPI_COMM_WORLD);

    int sum=0;
    for(int i=0;i<m;i++)
        sum+=local[i];

    local_avg = (float)sum/m;

    float total_avg;
    MPI_Reduce(&local_avg,&total_avg,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

    if(r==0)
        printf("Total average: %.2f\n", total_avg/s);

    MPI_Finalize();
    return 0;
}

/*
Enter M: 3
Enter 9 elements:
1 2 3 4 5 6 7 8 9
Total average: 5.00
*/