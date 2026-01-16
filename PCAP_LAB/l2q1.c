/*
MPi program using synchronous send. Sender process send a word to reciever. The secind 
process recieves the woed, toggles each letter of word and sends back to first rpocess. Both 
processes are synchronous send operations
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char* argv[])
{
int r, s;
char st[100];
MPI_Init(&argc, &argv);
MPI_Status w;
MPI_Comm_rank(MPI_COMM_WORLD, &r);
if(r==0)
{
printf("Process %d: Enter the string: \n", r);
scanf("%s", st);
MPI_Send(st, strlen(st)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
fflush(stdout);
MPI_Recv(st, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &w);
printf("Process %d: Recieved the string: %s\n", r,st);
fflush(stdout);
}
else
{
MPI_Recv(st, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &w);
printf("Process %d: Recieved the string: %s\n", r,st);
for(int i=0;i<strlen(st);i++)
{
if(islower(st[i]))
{
st[i]=toupper(st[i]);
}
else
{
}
st[i]=tolower(st[i]);
}
MPI_Send(st, strlen(st)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
fflush(stdout);
}
MPI_Finalize();
return 0;
}