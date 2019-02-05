DEBUG = 1
OPENCL = 1

CC = g++
CCFLAGS = -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -DCL -fopenmp
INFLAGS = -I./include
LDFLAGS = -lOpenCL

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
else
CCFLAGS += -DNDEBUG -O3
endif

test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/test.cc 
clean:
	rm -f run
