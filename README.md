# opencl

CL/CU C++ simple wrapper (master)

# sources

https://www.khronos.org/registry/OpenCL/sdk/2.0/docs/man/xhtml/

https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/

https://www.sharcnet.ca/help/index.php/Porting_CUDA_to_OpenCL

https://docs.nvidia.com/cuda/cuda-runtime-api/index.html

https://docs.nvidia.com/cuda/cuda-driver-api/index.html

![alt text](https://raw.githubusercontent.com/khanh1412/opencl/master/images/20181216_204709.jpg)

Simplify the usage of OpenCL in both Linux and Windows using only 4 classes `Context`, `Buffer`, `Queue` and `Kernel`.

`Context` : the connection between hardware and software. It can be thought as the "DEVICES"

            - Initialize Context (static)
            
            - Allocate buffers
            
            - Create queues
            
            - Compile Kernel and Load into Devices

`Buffer` : objects holding the allocated memory in GPU's global memory

`Queue` : similar to CUDA stream, Queue is a list of calls from CPU to GPU

            - Copy data from host to device (writeBuffer), device to host (readBuffer)
            
            - execute Kernels (params:  global dimensions, local dimensions, arguments for kernel)
            
            - synchronize : wait until the queue is empty

`Kernel` : the object holding GPU code (kernel code)
