// Lab Exercise 2
// Write a program in CUDA to multiply two matrices for the following specifictaions:
// a. Each row of resultant matrix to be computed by one thread
// b. Each column of resultant matrix to be computed by one thread
// c. Each element of resultant matrix to be computed by one thread

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void rowMulKernel(int *a,int *b,int *c,int wa,int wb){
    int row=threadIdx.x;
    for(int col=0;col<wb;col++){
        c[row*wb+col]=0;
        for(int k=0;k<wa;k++){
            c[row*wb+col]+=a[row*wa+k]*b[k*wb+col];
        }
    }
}

__global__ void colMulKernel(int *a,int *b,int *c,int ha,int wa){
    int col=threadIdx.x;
    for(int row=0;row<ha;row++){
        c[row*wa+col]=0;
        for(int k=0;k<wa;k++){
            c[row*wa+col]+=a[row*wa+k]*b[k*wa+col];
        }
    }
}

__global__ void elementMulKernel(int *a,int *b,int *c,int ha,int wb,int wa){
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    
    if(row<ha && col<wb){
        c[row*wb+col]=0;
        for(int k=0;k<wa;k++){
            c[row*wb+col]+=a[row*wa+k]*b[k*wb+col];
        }
    }
}

void displayMat(int *m,int row,int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d ",m[i*col+j]);
        }
        printf("\n");
    }
}

int main(){
    int *h_a,*h_b,*h_c,*d_a,*d_b,*d_c;
    int ha,wa,hb,wb;
    
    printf("Enter dimensions of matrix A: ");
    scanf("%d %d",&ha,&wa);
    printf("Enter dimensions of matrix B: ");
    scanf("%d %d",&hb,&wb);

    if(wa!=hb){
        printf("Invalid dimensions for multiplication.\n");
        return -1;
    }

    int sizeA=ha*wa;
    int sizeB=hb*wb;
    int sizeC=ha*wb;

    h_a=(int*)malloc(sizeA*sizeof(int));
    h_b=(int*)malloc(sizeB*sizeof(int));
    h_c=(int*)malloc(sizeC*sizeof(int));

    printf("Enter elements for matrix A:\n");
    for(int i=0;i<sizeA;i++) scanf("%d",&h_a[i]);

    printf("Enter elements for matrix B:\n");
    for(int i=0;i<sizeB;i++) scanf("%d",&h_b[i]);

    cudaMalloc((void**)&d_a,sizeA*sizeof(int));
    cudaMalloc((void**)&d_b,sizeB*sizeof(int));
    cudaMalloc((void**)&d_c,sizeC*sizeof(int));

    cudaMemcpy(d_a,h_a,sizeA*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,h_b,sizeB*sizeof(int),cudaMemcpyHostToDevice);

    // Row-wise multiplication
    rowMulKernel<<<1,ha>>>(d_a,d_b,d_c,wa,wb);
    cudaMemcpy(h_c,d_c,sizeC*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nRow-wise result:\n");
    displayMat(h_c,ha,wb);

    // Column-wise multiplication
    colMulKernel<<<1,wb>>>(d_a,d_b,d_c,ha,wa);
    cudaMemcpy(h_c,d_c,sizeC*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nColumn-wise result:\n");
    displayMat(h_c,ha,wb);

    // Element-wise multiplication
    dim3 threadsPerBlock(16,16);
    dim3 blocksPerGrid(
        ceil((float)wb/threadsPerBlock.x),
        ceil((float)ha/threadsPerBlock.y)
    );

    elementMulKernel<<<blocksPerGrid,threadsPerBlock>>>(d_a,d_b,d_c,ha,wb,wa);
    cudaMemcpy(h_c,d_c,sizeC*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nElement-wise result:\n");
    displayMat(h_c,ha,wb);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}
