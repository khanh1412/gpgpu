# opencl

CL C++ simple wrapper (master)

![alt text](https://raw.githubusercontent.com/khanh1412/opencl/master/images/20181216_204709.jpg)

Simplify the usage of OpenCL in both Linux and Windows using only 4 classes `Context`, `Buffer`, `Queue` and `Kernel`.

`Context` : the connection between hardware and software. It can be thought as the "DEVICES"

            - Initialize Context (static)
            
            - Allocate buffers
            
            - Create queues
            
            - Compile Kernel

`Buffer` : objects holding the allocated memory in GPU's global memory

`Queue` : similar to CUDA stream, Queue is a list of calls from CPU to GPU

            - Copy data from host to device (writeBuffer), device to host (readBuffer)
            
            - execute Kernels (params:  global dimensions, local dimensions, arguments for kernel)
            
            - synchronize : wait until the queue is empty

`Kernel` : the object holding GPU code (kernel code)

- "DIDNOT SUPPORT OUT-OF-ORDER EXECUTION" - simply because my shitty intel gpu running on fedora doesnot support it

