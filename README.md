# Simple Compute Framework based on OpenCL

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e836909b61e242a2a52aa9d00c198dbd)](https://app.codacy.com/app/khanhhhh/SimpleComputeFramework?utm_source=github.com&utm_medium=referral&utm_content=khanhhhh/SimpleComputeFramework&utm_campaign=Badge_Grade_Dashboard)

OpenCL C++ Template-based library

## Resources

[OpenCL 2.0 doc](https://www.khronos.org/registry/OpenCL/sdk/2.0/docs/man/xhtml/)

[OpenCL 1.2 doc](https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/)

[Porting CUDA to OpenCL](https://www.sharcnet.ca/help/index.php/Porting_CUDA_to_OpenCL)

[CUDA Runtime API](https://docs.nvidia.com/cuda/cuda-runtime-api/index.html)

[CUDA Driver API](https://docs.nvidia.com/cuda/cuda-driver-api/index.html)

![alt text](https://raw.githubusercontent.com/khanhhhh/SimpleComputeLibrary/master/images/20181216_204709.jpg)

Simplify the usage of OpenCL in both Linux and Windows using only 4 classes `Context`, `Buffer`, `Queue` and `Kernel`.

`Context` : the connection between hardware and software. It can be thought as the "DEVICES"

            - Initialize Context (static)
            
            - Allocate buffers
            
            - Create queues
            
            - Compile Kernel and Load into Devices

`Buffer` : objects holding the shared memory across devices

`Queue` : similar to CUDA stream, Queue is a list of calls from CPU to GPU

            - Copy data from host to device (writeBuffer), device to host (readBuffer)
            
            - execute Kernels (params:  global dimensions, local dimensions, arguments for kernel)
            
            - synchronize : wait until the queue is empty

`Kernel` : the object holding GPU code (kernel code)
