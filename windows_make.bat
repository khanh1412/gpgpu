mkdir objects
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Buffer.o sources\Buffer.cc
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Kernel.o sources\Kernel.cc
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Queue.o sources\Queue.cc
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Context.o sources\Context.cc
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Param.o sources\Param.cc
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Event.o sources\Event.cc
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -c -fPIC -o objects\Debugger.o sources\Debugger.cc

g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -shared -o CL.dll objects\*.o .\OpenCL.dll

del objects\*.o
rmdir objects

g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -o vecAdd.exe examples\0_vecAdd\main.cc .\Cl.dll .\OpenCL.dll
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -o event.exe examples\1_event\main.cc .\Cl.dll .\OpenCL.dll
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -o scalar_param.exe examples\2_scalar_param\main.cc .\Cl.dll .\OpenCL.dll
g++ -std=c++17 -O0 -DDEBUG -DPROFILE -g -I.\include -o reduce_sum.exe examples\3_reduce_sum\main.cc .\Cl.dll .\OpenCL.dll


