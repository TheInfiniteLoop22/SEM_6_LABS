/*
Program : Hello World based on rank
Name : Devadathan N R
Class : CSE - A
Roll No : 04
Reg No : 230905010
*/

#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[]){
	int rank;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank%2==0)printf("Hello\n");
	else printf("World\n");
	
	MPI_Finalize();
	return 0;
}
