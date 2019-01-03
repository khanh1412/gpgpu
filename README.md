# opencl

CL C++ simple wrapper (OpenCL 2.0)

Supports almost every OpenCL features, except

1. Multiple devices (same platform)

2. Callback functions (it can be easily solved by a host thread waiting for some specific events)

3. Image objects (it can be replaced by simple buffers)

4. OpenGL interoperability (will be updated)

5. Multiple kernels in the same program. (use multiple programs instead).

6. Profiling Operations (my shitty intel gpu does not support)

7. Out-of-order executions (same as 6)

8. Pipes (will be updated)

9. Shared Virtual Memory (SVM)


# Tested Machine (Intel core i7 5500U, Intel HD Graphics 5500)

- GPU : Intel HD Graphics 5500

- Host machine : Fedora 29

- Driver : Intel Gen OCL Driver (OpenCL 2.0 beignet 1.3)

# TO DO

- rename functions

- add in "Context of multiple devices"
