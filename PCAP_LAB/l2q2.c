/*
write mpi program where the master process (process 0) snd a number to each of the slaves and 
the slave processes recieve the number and prints it. Use standard send
*/

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
printf("Process %d: Enter the number to send: \n", r);
scanf("%d", &n);
for(int i=1;i<s;i++)
{
MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
}
}
else
{
MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &w);
printf("Process %d: Recieved the number: %d\n", r,n);
}
MPI_Finalize();
return 0;
}