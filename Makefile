DEBUG = 1

CC = g++
CCFLAGS = -std=c++17 -fPIC -Wall -Wfatal-errors
INFLAGS = -I./include -I./examples
LDFLAGS = -lOpenCL

ifeq (1, $(DEBUG))
CCFLAGS += -g -O0
else
CCFLAGS += -DNDEBUG -O3
endif

test: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/test.cc
axpy: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/0_axpy/main.cc
event: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/1_event/main.cc
perm: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/2_perm/main.cc
rsa: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/3_rsa/main.cc -I./examples/3_rsa -fopenmp -lgmp -lgmpxx
gemm: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/4_gemm/main.cc -fopenmp -lclblast
kronecker: 
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) -o run ./examples/5_kronecker/main.cc
clean:
	rm -f run
