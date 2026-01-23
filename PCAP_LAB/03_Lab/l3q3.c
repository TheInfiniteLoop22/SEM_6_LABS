/*
Write an MPI program to read a string.
Using N processes, find number of non-vowels.
Root prints count from each process and total count.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int r,s,len;
    char str[100], local[100];
    int count=0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    MPI_Comm_size(MPI_COMM_WORLD,&s);

    if(r==0)
    {
        printf("Enter string: ");
        scanf("%s",str);
        len = strlen(str);
    }

    MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);

    int chunk = len/s;

    MPI_Scatter(str,chunk,MPI_CHAR,local,chunk,MPI_CHAR,0,MPI_COMM_WORLD);

    for(int i=0;i<chunk;i++)
    {
        char c = tolower(local[i]);
        if(!(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'))
            count++;
    }

    int res[s];

    MPI_Gather(&count,1,MPI_INT,res,1,MPI_INT,0,MPI_COMM_WORLD);

    if(r==0)
    {
        int total=0;
        for(int i=0;i<s;i++)
        {
            printf("Process %d -> %d\n",i,res[i]);
            total+=res[i];
        }
        printf("Total non vowels: %d\n",total);
    }

    MPI_Finalize();
    return 0;
}

/*
Enter string: function
Process 0 -> 1
Process 1 -> 2
Process 2 -> 1
Process 3 -> 1
Total non vowels: 5

*/