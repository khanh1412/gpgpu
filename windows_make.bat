mkdir objects
g++ -std=c++17 -I.\include -c -fPIC -o objects\Buffer.o sources\Buffer.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Kernel.o sources\Kernel.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Queue.o sources\Queue.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Context.o sources\Context.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Debugger.o sources\Debugger.cc

g++ -std=c++17 -I.\include -shared -o CL.dll objects\*.o .\OpenCL.dll

del objects\*.o
rmdir objects

g++ -std=c++17 -I.\include -o run.exe examples\test.cc .\Cl.dll .\OpenCL.dll -lpthread


