// Lab Exercise 1
// Write a program in CUDA to add two Matrices for the following specifications
// a. Each row of the resultant matrix to be computed by one thread
// b. Each column of resultant matrix to be computed by one thread
// c. Ecah element of resultant matrix to be computed by one thread

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void rowAddKernel(int *a,int *b,int *c,int m,int n){
    int row=threadIdx.x;
    if(row<m){
        for(int col=0;col<n;col++){
            c[row*n+col]=a[row*n+col]+b[row*n+col];
        }
    }
}

__global__ void colAddKernel(int *a,int *b,int *c,int m,int n){
    int col=threadIdx.x;
    if(col<n){
        for(int row=0;row<m;row++){
            c[row*n+col]=a[row*n+col]+b[row*n+col];
        }
    }
}

__global__ void elementAddKernel(int *a,int *b,int *c,int m,int n){
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    
    if(row<m && col<n){
        c[row*n+col]=a[row*n+col]+b[row*n+col];
    }
}

void displayMat(int *m,int m_rows,int n_cols){
    for(int i=0;i<m_rows;i++){
        for(int j=0;j<n_cols;j++){
            printf("%d ",m[i*n_cols+j]);
        }
        printf("\n");
    }
}

int main(){
    int *h_a,*h_b,*h_c,m,n,*d_a,*d_b,*d_c;
    printf("Enter the number of rows (m): ");
    scanf("%d",&m);
    printf("Enter the number of columns (n): ");
    scanf("%d",&n);
    
    int size=m*n;
    
    h_a=(int*)malloc(size*sizeof(int));
    h_b=(int*)malloc(size*sizeof(int));
    h_c=(int*)malloc(size*sizeof(int));
    
    printf("Enter elements for matrix A:\n");
    for(int i=0;i<size;i++) scanf("%d",&h_a[i]);
    
    printf("Enter elements for matrix B:\n");
    for(int i=0;i<size;i++) scanf("%d",&h_b[i]);

    cudaMalloc((void**)&d_a,size*sizeof(int));
    cudaMalloc((void**)&d_b,size*sizeof(int));
    cudaMalloc((void**)&d_c,size*sizeof(int));

    cudaMemcpy(d_a,h_a,size*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,h_b,size*sizeof(int),cudaMemcpyHostToDevice);

    // Row-wise addition
    rowAddKernel<<<1,m>>>(d_a,d_b,d_c,m,n);
    cudaMemcpy(h_c,d_c,size*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nRow-wise result:\n");
    displayMat(h_c,m,n);

    // Column-wise addition
    colAddKernel<<<1,n>>>(d_a,d_b,d_c,m,n);
    cudaMemcpy(h_c,d_c,size*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nColumn-wise result:\n");
    displayMat(h_c,m,n);

    // Element-wise addition
    dim3 threadsPerBlock(16,16); 
    dim3 blocksPerGrid(
        ceil((float)n/threadsPerBlock.x),
        ceil((float)m/threadsPerBlock.y)
    );                  
    elementAddKernel<<<blocksPerGrid,threadsPerBlock>>>(d_a,d_b,d_c,m,n);
    cudaMemcpy(h_c,d_c,size*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nElement-wise result:\n");
    displayMat(h_c,m,n);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}
