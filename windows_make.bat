mkdir objects
g++ -std=c++17 -I.\include -c -fPIC -o objects\Buffer.o sources\Buffer.cc -w
g++ -std=c++17 -I.\include -c -fPIC -o objects\Kernel.o sources\Kernel.cc -w
g++ -std=c++17 -I.\include -c -fPIC -o objects\Queue.o sources\Queue.cc   -w 
g++ -std=c++17 -I.\include -c -fPIC -o objects\Context.o sources\Context.cc -w

g++ -std=c++17 -I.\include -o CLWrapper.dll objects\*.o .\OpenCL.dll -w

del objects\*.o
rmdir objects

