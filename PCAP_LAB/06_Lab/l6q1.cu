/*
Write a CUDA program to perform 1D convolution on an input array
using a mask array and produce the output array.
*/

#include <stdio.h>
#include <cuda.h>

#define N 7
#define M 5

__global__ void conv1D(float *in, float *mask, float *out, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    float sum = 0;
    int start = tid - (M / 2);

    for (int i = 0; i < M; i++)
    {
        if (start + i >= 0 && start + i < n)
        {
            sum += in[start + i] * mask[i];
        }
    }

    out[tid] = sum;
}

int main()
{
    float h_in[N]  = {2, 4, 6, 8, 10, 12, 14};
    float h_mask[M] = {1, 0, -1, 0, 1};
    float h_out[N];

    float *d_in, *d_mask, *d_out;

    cudaMalloc(&d_in,  N * sizeof(float));
    cudaMalloc(&d_mask, M * sizeof(float));
    cudaMalloc(&d_out, N * sizeof(float));

    cudaMemcpy(d_in, h_in, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, h_mask, M * sizeof(float), cudaMemcpyHostToDevice);

    conv1D<<<1, N>>>(d_in, d_mask, d_out, N);

    cudaMemcpy(h_out, d_out, N * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Output Array:\n");
    for (int i = 0; i < N; i++)
        printf("%f ", h_out[i]);

    printf("\n");
    cudaFree(d_in);
    cudaFree(d_mask);
    cudaFree(d_out);

    return 0;
}

/*
Output Array:
2.000000 4.000000 8.000000 12.000000 16.000000 -4.000000 4.000000
*/