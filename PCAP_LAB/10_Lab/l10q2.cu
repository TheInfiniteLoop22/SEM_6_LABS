/*
Q2. Write a program in CUDA to improve the performance of 1D parallel convolution using constant memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define MAX_MASK_WIDTH 64

// Constant memory for mask
__constant__ int d_M[MAX_MASK_WIDTH];

// Kernel
__global__ void conv1D(int *N, int *P, int width, int mask_width)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int radius = mask_width / 2;

    if (i < width)
    {
        int sum = 0;

        for (int j = 0; j < mask_width; j++)
        {
            int idx = i - radius + j;

            if (idx >= 0 && idx < width)
            {
                sum += N[idx] * d_M[j];
            }
        }

        P[i] = sum;
    }
}

int main()
{
    int width, mask_width;

    printf("Enter size of input array: ");
    scanf("%d", &width);

    printf("Enter mask width (<= %d): ", MAX_MASK_WIDTH);
    scanf("%d", &mask_width);

    int *h_N = (int *)malloc(width * sizeof(int));
    int *h_P = (int *)malloc(width * sizeof(int));
    int *h_M = (int *)malloc(mask_width * sizeof(int));

    printf("Enter input array:\n");
    for (int i = 0; i < width; i++)
        scanf("%d", &h_N[i]);

    printf("Enter mask array:\n");
    for (int i = 0; i < mask_width; i++)
        scanf("%d", &h_M[i]);

    int *d_N, *d_P;

    cudaMalloc((void **)&d_N, width * sizeof(int));
    cudaMalloc((void **)&d_P, width * sizeof(int));

    cudaMemcpy(d_N, h_N, width * sizeof(int), cudaMemcpyHostToDevice);

    // Copy mask to constant memory
    cudaMemcpyToSymbol(d_M, h_M, mask_width * sizeof(int));

    int blockSize = 256;
    int gridSize = (width + blockSize - 1) / blockSize;

    conv1D<<<gridSize, blockSize>>>(d_N, d_P, width, mask_width);

    cudaMemcpy(h_P, d_P, width * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nOutput array:\n");
    for (int i = 0; i < width; i++)
        printf("%d ", h_P[i]);

    printf("\n");

    cudaFree(d_N);
    cudaFree(d_P);

    free(h_N);
    free(h_P);
    free(h_M);

    return 0;
}