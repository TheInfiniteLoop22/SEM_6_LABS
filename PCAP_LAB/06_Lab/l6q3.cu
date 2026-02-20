// CUDA program to perform Odd-Even Transposition Sort in parallel

#include <stdio.h>
#include <math.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void oddEvenSort(int *d_arr, int n, int phase)
{
    int tid = threadIdx.x + blockDim.x * blockIdx.x;

    int idx = (phase % 2 == 0) ? (2 * tid) : (2 * tid + 1);

    if (idx + 1 < n)
    {
        if (d_arr[idx] > d_arr[idx + 1])
        {
            int temp = d_arr[idx];
            d_arr[idx] = d_arr[idx + 1];
            d_arr[idx + 1] = temp;
        }
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int h_arr[n];
    int *d_arr;

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_arr[i]);

    cudaMalloc((void **)&d_arr, n * sizeof(int));
    cudaMemcpy(d_arr, h_arr, n * sizeof(int), cudaMemcpyHostToDevice);

    for (int p = 0; p < n; p++)
    {
        oddEvenSort<<<ceil((float)n / 512), 512>>>(d_arr, n, p);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(h_arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", h_arr[i]);

    printf("\n");
    cudaFree(d_arr);

    return 0;
}

/*
Enter number of elements: 8
Enter the elements: 9 4 7 2 6 1 8 3
Sorted array: 1 2 3 4 6 7 8 9
*/