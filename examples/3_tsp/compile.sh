#!/usr/bin/env sh
nvcc -ccbin cuda-g++ -c -o tsp_kernel.o tsp_kernel.cu
nvcc -ccbin cuda-g++ -c -o tsp_function.o tsp_function.cu
nvcc -ccbin cuda-g++ -c -o main.o main.cc
nvcc -ccbin cuda-g++    -o cuda.out *.o
rm -f *.o
g++ -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -DCL -O3 -c -o tsp_function.o tsp_function.cc -I../../include/CL
g++ -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -DCL -O3 -c -o main.o main.cc -I../../include/CL
g++ -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -DCL -O3 -o ocl.out *.o -I../../include/CL -lOpenCL
rm -f *.o
