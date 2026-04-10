/* 
Q1. Write a program in CUDA to perform matrix multiplication using 2D Grid and 2D Block.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Kernel function
__global__ void matrixMulKernel(int *A, int *B, int *C, int rowsA, int colsA, int colsB)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rowsA && col < colsB)
    {
        int sum = 0;
        for (int i = 0; i < colsA; i++)
        {
            sum += A[row * colsA + i] * B[i * colsB + col];
        }
        C[row * colsB + col] = sum;
    }
}

int main()
{
    int rowsA, colsA, rowsB, colsB;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &rowsB, &colsB);

    if (colsA != rowsB)
    {
        printf("Matrix multiplication not possible!\n");
        return 0;
    }

    int *h_A = (int *)malloc(rowsA * colsA * sizeof(int));
    int *h_B = (int *)malloc(rowsB * colsB * sizeof(int));
    int *h_C = (int *)malloc(rowsA * colsB * sizeof(int));

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < rowsA * colsA; i++)
        scanf("%d", &h_A[i]);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < rowsB * colsB; i++)
        scanf("%d", &h_B[i]);

    int *d_A, *d_B, *d_C;

    cudaMalloc((void **)&d_A, rowsA * colsA * sizeof(int));
    cudaMalloc((void **)&d_B, rowsB * colsB * sizeof(int));
    cudaMalloc((void **)&d_C, rowsA * colsB * sizeof(int));

    cudaMemcpy(d_A, h_A, rowsA * colsA * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, rowsB * colsB * sizeof(int), cudaMemcpyHostToDevice);

    // 2D Block and Grid
    dim3 block(16, 16);
    dim3 grid((colsB + 15) / 16, (rowsA + 15) / 16);

    matrixMulKernel<<<grid, block>>>(d_A, d_B, d_C, rowsA, colsA, colsB);

    cudaMemcpy(h_C, d_C, rowsA * colsB * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nResult Matrix:\n");
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
            printf("%d ", h_C[i * colsB + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}