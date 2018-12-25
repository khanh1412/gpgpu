CC = g++
CC_FLAGS = -std=c++17 -g -w
INCLUDE = -I./include
LIBRARY = -lOpenCL -lpthread

lib:
	rm -rf objects
	mkdir objects
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Buffer.o sources/Buffer.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Kernel.o sources/Kernel.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Queue.o sources/Queue.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Context.o sources/Context.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -shared -o libCL.so objects/*.o
	rm -rf objects

test: lib
	$(CC) $(CC_FLAGS) $(INCLUDE) -o run examples/test.cc ./libCL.so $(LIBRARY)
