// Lab Exercise 2 - Implement a CUDA program to add two vectors of length N
// keeping number of threads per block as 256 (constant) and varying
// number of blocks to handle N elements.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

const int N = 1000;

__global__ void k(int *a, int *b, int *c)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < N)
        c[id] = a[id] + b[id];
}

int main()
{
    int *d1, *d2, *d3;
    int s = sizeof(int);

    cudaMalloc((void**)&d1, N * s);
    cudaMalloc((void**)&d2, N * s);
    cudaMalloc((void**)&d3, N * s);

    int h1[N], h2[N], h3[N];

    for (int i = 0; i < N; i++)
    {
        h1[i] = i;
        h2[i] = i + 10;
    }

    cudaMemcpy(d1, h1, N * s, cudaMemcpyHostToDevice);
    cudaMemcpy(d2, h2, N * s, cudaMemcpyHostToDevice);

    int t = 256;
    int b = (N + t - 1) / t;

    k<<<b, t>>>(d1, d2, d3);

    cudaMemcpy(h3, d3, N * s, cudaMemcpyDeviceToHost);

    printf("First 20 results:\n");
    for (int i = 0; i < 20; i++)
        printf("%d ", h3[i]);
    printf("\n");

    cudaFree(d1);
    cudaFree(d2);
    cudaFree(d3);

    return 0;
}

