3] write mpi program to read N elements of the array in the root process(process 0) where N is 
equal to the total number of process. The root process sends one value to each of the slaves. Let 
even ranked process finds square of the recieved element and odd ranked process finds cube of 
recieved element. use Buffered send
Code:
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char* argv[])
{
int r, s, n;
MPI_Init(&argc, &argv);
MPI_Status w;
MPI_Comm_rank(MPI_COMM_WORLD, &r);
MPI_Comm_size(MPI_COMM_WORLD, &s);
if(r==0)
{
printf("Process %d: Enter %d elements: \n", r, s-1);
int a[s];
a[0]=0;
for(int i=1;i<s;i++)
{
scanf("%d", &a[i]);
}
int bs=(sizeof(int)+MPI_BSEND_OVERHEAD)*s;
void* b=malloc(bs);
MPI_Buffer_attach(b, bs);
for(int i=1;i<s;i++)
{
MPI_Bsend(&a[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
}
MPI_Buffer_detach(&b, &bs);
free(b);
}
else
{
MPI_Recv(&n, 1, MPI_INT, 0, r, MPI_COMM_WORLD, &w);
if(r%2==0)
{
}
else
{
}
printf("Process %d: Recieved the number: %d  Square: %d\n", r,n, (n*n));
printf("Process %d: Recieved the number: %d  Cube: %d\n", r,n, (n*n*n));
}
MPI_Finalize();
return 0;
}