/*
Program : Hello World
Name : Devadathan N R
Class : CSE - A
Roll No : 04
Reg No : 230905010
*/

#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[]){
	int rank,size;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	printf("Processor %d of %d: Hello World!\n",rank,size);
	
	MPI_Finalize();
	return 0;
}
