DEBUG = 1

CC = g++
CCFLAGS = -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC
INCLUDE = -I./include
LDFLAGS = -lOpenCL

ifeq (1, $(DEBUG))
CCFLAGS += -g -DDEBUG -O0
else
CCFLAGS += -O3
endif


.PHONY: test
test: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/test.cc ./libCL.so $(LDFLAGS)
.PHONY: vecAdd
vecAdd: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/0_vecAdd/main.cc ./libCL.so $(LDFLAGS)
.PHONY: performance
performance: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/1_performance/main.cc ./libCL.so $(LDFLAGS) -lpthread
.PHONY: lib
lib: clean
	mkdir objects
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Buffer.o sources/Buffer.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Kernel.o sources/Kernel.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Queue.o sources/Queue.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Context.o sources/Context.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Argument.o sources/Argument.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Debugger.o sources/Debugger.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -shared -o libCL.so objects/*.o
.PHONY: clean
clean:
	rm -rf objects
	rm -f libCL.so
	rm -f run
.PHONY: clinfo
clinfo:
	./clinfo/clinfo
