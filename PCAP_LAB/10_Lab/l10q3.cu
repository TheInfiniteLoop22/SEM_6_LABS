/*
Q3. Write a program in CUDA to perform inclusive scan algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Kernel for Inclusive Scan (Hillis-Steele)
__global__ void inclusiveScanKernel(int *input, int *output, int n)
{
    extern __shared__ int temp[];

    int tid = threadIdx.x;

    // Load input into shared memory
    if (tid < n)
        temp[tid] = input[tid];
    __syncthreads();

    // Inclusive Scan
    for (int offset = 1; offset < n; offset *= 2)
    {
        int val = 0;

        if (tid >= offset)
            val = temp[tid - offset];

        __syncthreads();

        if (tid < n)
            temp[tid] += val;

        __syncthreads();
    }

    // Write result
    if (tid < n)
        output[tid] = temp[tid];
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *h_input = (int *)malloc(n * sizeof(int));
    int *h_output = (int *)malloc(n * sizeof(int));

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_input[i]);

    int *d_input, *d_output;

    cudaMalloc((void **)&d_input, n * sizeof(int));
    cudaMalloc((void **)&d_output, n * sizeof(int));

    cudaMemcpy(d_input, h_input, n * sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel (single block version)
    inclusiveScanKernel<<<1, n, n * sizeof(int)>>>(d_input, d_output, n);

    cudaMemcpy(h_output, d_output, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nInclusive Scan Output:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", h_output[i]);

    printf("\n");

    cudaFree(d_input);
    cudaFree(d_output);

    free(h_input);
    free(h_output);

    return 0;
}