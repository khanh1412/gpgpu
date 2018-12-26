CC = g++
CC_FLAGS = -std=c++17 -g
INCLUDE = -I./include
LIBRARY = -lOpenCL -lpthread

lib:
	rm -rf objects
	mkdir objects
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Buffer.o sources/Buffer.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Kernel.o sources/Kernel.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Queue.o sources/Queue.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Context.o sources/Context.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -c -fPIC -o objects/Debugger.o sources/Debugger.cc
	$(CC) $(CC_FLAGS) $(INCLUDE) -shared -o libCL.so objects/*.o
	rm -rf objects

test: lib
	$(CC) $(CC_FLAGS) $(INCLUDE) -o run examples/test.cc ./libCL.so $(LIBRARY)
vecAdd: lib
	$(CC) $(CC_FLAGS) $(INCLUDE) -o run examples/0_vecAdd/main.cc ./libCL.so $(LIBRARY)
performance: lib
	$(CC) $(CC_FLAGS) $(INCLUDE) -o run examples/1_performance/main.cc ./libCL.so $(LIBRARY)
fill: lib
	$(CC) $(CC_FLAGS) $(INCLUDE) -o run examples/2_fill/main.cc ./libCL.so $(LIBRARY)
	
