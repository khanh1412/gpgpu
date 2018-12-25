# opencl

CL on top of OpenCL C++ Binding

![alt text](https://raw.githubusercontent.com/khanh1412/opencl/c/images/20181216_204709.jpg)

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

# Tested Machine (Intel core i7 5500U, Intel HD Graphics 5500, AMD R7 M270)

- Windows 10 with proprietary driver : works

- Fedora 29 with mesa driver : "asynchronous calls" does not work for both GPUs

# TO DO

- add in "Event"

- add in "singleton" for `Buffer`
