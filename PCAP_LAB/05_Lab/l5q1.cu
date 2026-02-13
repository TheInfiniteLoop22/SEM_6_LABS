//// Lab Exercise 1 - Write a CUDA program to add two vectors of length N using:
// a) N blocks
// b) N threads

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

const int N = 10;

__global__ void k1(int *a, int *b, int *c)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < N)
        c[id] = a[id] + b[id];
}

__global__ void k2(int *a, int *b, int *c)
{
    int id = threadIdx.x;
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

    int h1[N] = {5, -3, 12, 7, 0, 14, -6, 8, 21, 4};
    int h2[N] = {2, 9, -2, 3, 5, -4, 10, 1, -1, 6};
    int h3[N];

    cudaMemcpy(d1, h1, N * s, cudaMemcpyHostToDevice);
    cudaMemcpy(d2, h2, N * s, cudaMemcpyHostToDevice);

    k1<<<N,1>>>(d1, d2, d3);
    cudaMemcpy(h3, d3, N * s, cudaMemcpyDeviceToHost);

    printf("Blocks:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", h3[i]);
    printf("\n");

    k2<<<1,N>>>(d1, d2, d3);
    cudaMemcpy(h3, d3, N * s, cudaMemcpyDeviceToHost);

    printf("Threads:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", h3[i]);
    printf("\n");

    cudaFree(d1);
    cudaFree(d2);
    cudaFree(d3);

    return 0;
}

