#include "mymodule_kernels.hpp"

#include <stdio.h>

/**
 * \brief A basic CUDA kernel.
 */
__global__ void mymodule_kernel() {
    printf("Hello world from CUDA kernel from thread %d\n", threadIdx.x);
}

void mymodule_kernel_wrapper() {
    printf("Will call kernel\n");
    mymodule_kernel<<<1,1>>>();
    cudaDeviceSynchronize();
    printf("Done calling kernel\n");
}
