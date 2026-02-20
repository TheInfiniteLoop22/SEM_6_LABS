// CUDA program to perform parallel selection sort

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void selSort(int *d_in, int *d_out, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    int rank = 0;

    for (int i = 0; i < n; i++)
    {
        if ((d_in[i] < d_in[tid]) ||
            (d_in[i] == d_in[tid] && i > tid))
        {
            rank++;
        }
    }

    d_out[rank] = d_in[tid];
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int h_in[n];
    int h_out[n];

    int *d_in, *d_out;

    cudaMalloc((void **)&d_in, n * sizeof(int));
    cudaMalloc((void **)&d_out, n * sizeof(int));

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_in[i]);

    cudaMemcpy(d_in, h_in, n * sizeof(int), cudaMemcpyHostToDevice);

    selSort<<<1, n>>>(d_in, d_out, n);

    cudaMemcpy(h_out, d_out, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", h_out[i]);

    printf("\n");
    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}

/*
Enter number of elements: 6
Enter the elements: 8 4 6 2 9 1
Sorted array: 1 2 4 6 8 9
*/