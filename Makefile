DEBUG = 1
PROFILE = 1



CC = g++
CCFLAGS = -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC
INCLUDE = -I./include
LDFLAGS = -lOpenCL

ifeq (1, $(DEBUG))
CCFLAGS += -g -DDEBUG -DPROFILE -O0
endif
ifeq (1, $(PROFILE))
CCFLAGS += -DPROFILE
endif


test: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/test.cc ./libCL.so $(LDFLAGS)
reduce_sum: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/3_reduce_sum/main.cc ./libCL.so $(LDFLAGS)
scalar_param: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/2_scalar_param/main.cc ./libCL.so $(LDFLAGS)
vecAdd: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/0_vecAdd/main.cc ./libCL.so $(LDFLAGS)
event: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/1_event/main.cc ./libCL.so $(LDFLAGS)
lib: clean
	mkdir objects
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Buffer.o sources/Buffer.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Kernel.o sources/Kernel.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Queue.o sources/Queue.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Context.o sources/Context.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Param.o sources/Param.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Event.o sources/Event.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -fPIC -o objects/Debugger.o sources/Debugger.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -shared -o libCL.so objects/*.o
clean:
	rm -rf objects
	rm -f libCL.so
	rm -f run
