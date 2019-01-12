# opencl

CL C++ simple wrapper

Supports almost every OpenCL features, except

1. ~~Multiple devices (same platform)~~

2. Callback functions (it can be easily solved by a host thread waiting for some specific events)

3. Image objects (it can be replaced by simple buffers)

4. OpenGL interoperability (will be updated)

5. Multiple kernels in the same program. (use multiple programs instead).

6. ~~Profiling Operations (my shitty intel gpu does not support)~~

7. ~~Out-of-order executions (same as 6)~~

8. Pipes (will be updated)

9. Shared Virtual Memory (SVM)


# Tested Machine (Intel core i3 6100, GTX 745)

- GPU : GTX 745

- Host machine : Fedora 29

- Driver : CUDA

- Platform ver: 1.2 (some of 2.0 features)

- Device ver: 1.2

# TO DO

