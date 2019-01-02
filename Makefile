DEBUG = 0

CC = g++
CCFLAGS = -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC

ifeq (1, $(DEBUG))
CCFLAGS += -g -DDEBUG -O0
else
CCFLAGS += -O3
endif

INCLUDE = -I./include
LDFLAGS = -lOpenCL

.PHONY: vecAdd
vecAdd: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/0_vecAdd/main.cc ./libCL.so $(LDFLAGS)
.PHONY: performance
performance: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/1_performance/main.cc ./libCL.so $(LDFLAGS) -lpthread

.PHONY: lib
lib:
	rm -rf objects
	mkdir objects
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Buffer.o sources/Buffer.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Kernel.o sources/Kernel.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Queue.o sources/Queue.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Context.o sources/Context.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Debugger.o sources/Debugger.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -shared -o libCL.so objects/*.o
	rm -rf objects
.PHONY: clinfo
clinfo:
	./clinfo/clinfo
