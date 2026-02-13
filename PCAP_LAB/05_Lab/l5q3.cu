// // Lab Exercise 3 - Write a CUDA program to process a 1D array containing
// angles in radians and generate sine values in the output array.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

const int N = 6;

__global__ void sine_calc(double *x, double *y){
    int i = threadIdx.x;
    if(i < N){
        y[i] = sinf(x[i]);
    }
}

int main(){
    double *d_x, *d_y;
    int sz = sizeof(double);

    cudaMalloc((void**)&d_x, N * sz);
    cudaMalloc((void**)&d_y, N * sz);

    double h_x[N] = {PI/8, PI/5, PI/2, 3*PI/4, PI, 2*PI};
    double h_y[N];

    cudaMemcpy(d_x, h_x, N * sz, cudaMemcpyHostToDevice);

    sine_calc<<<1,N>>>(d_x, d_y);

    cudaMemcpy(h_y, d_y, N * sz, cudaMemcpyDeviceToHost);

    printf("Sine Results:\n");
    for(int i = 0; i < N; i++){
        printf("sin(%.4lf) = %.4lf\n", h_x[i], h_y[i]);
    }

    cudaFree(d_x);
    cudaFree(d_y);

    return 0;
}

