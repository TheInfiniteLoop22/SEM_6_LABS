/*
/*
Write an MPI program to read two strings S1 and S2 of same length.
Using N processes, interleave characters and produce resultant string.
Display result in root.
*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int r,s,l;

    char s1[100], s2[100];
    char b1[100], b2[100];
    char local[200], result[400];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    MPI_Comm_size(MPI_COMM_WORLD,&s);

    if(r==0)
    {
        printf("Enter string 1: ");
        scanf("%s",s1);

        printf("Enter string 2: ");
        scanf("%s",s2);

        l = strlen(s1);
    }

    MPI_Bcast(&l,1,MPI_INT,0,MPI_COMM_WORLD);

    int chunk = l/s;

    MPI_Scatter(s1,chunk,MPI_CHAR,b1,chunk,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(s2,chunk,MPI_CHAR,b2,chunk,MPI_CHAR,0,MPI_COMM_WORLD);

    int k=0;
    for(int i=0;i<chunk;i++)
    {
        local[k++] = b1[i];
        local[k++] = b2[i];
    }

    MPI_Gather(local,2*chunk,MPI_CHAR,result,2*chunk,MPI_CHAR,0,MPI_COMM_WORLD);

    if(r==0)
    {
        result[2*l]='\0';
        printf("Resultant string: %s\n",result);
    }

    MPI_Finalize();
    return 0;
}

/*
Enter string 1: string
Enter string 2: length
Resultant string: slternigntgh
*/