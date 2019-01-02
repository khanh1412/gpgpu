mkdir objects
g++ -std=c++17 -I.\include -c -fPIC -o objects\Buffer.o sources\Buffer.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Kernel.o sources\Kernel.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Queue.o sources\Queue.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Context.o sources\Context.cc
g++ -std=c++17 -I.\include -c -fPIC -o objects\Debugger.o sources\Debugger.cc

g++ -std=c++17 -I.\include -shared -o CL.dll objects\*.o .\OpenCL.dll

del objects\*.o
rmdir objects

g++ -std=c++17 -I.\include -o vecAdd.exe examples\0_vecAdd\main.cc .\Cl.dll .\OpenCL.dll
g++ -std=c++17 -I.\include -o performance.exe examples\1_performance\main.cc .\Cl.dll .\OpenCL.dll -lpthread
g++ -std=c++17 -I.\include -o event.exe examples\2_event\main.cc .\Cl.dll .\OpenCL.dll


