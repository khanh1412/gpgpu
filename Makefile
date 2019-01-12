DEBUG = 1
PROFILE = 1



CC = g++
CCFLAGS = -std=c++17 -Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC
INCLUDE = -I./include
LDFLAGS = -lOpenCL

ifeq (1, $(DEBUG))
CCFLAGS += -g -DDEBUG -O0
else
CCFLAGS += -O3
endif

ifeq (1, $(PROFILE))
CCFLAGS += -DPROFILE
endif


test: lib
	$(CC) $(CCFLAGS) $(INCLUDE) -o run examples/test.cc ./libCL.so $(LDFLAGS)
lib: clean
	mkdir objects
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o objects/Device.o sources/Device.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o objects/Context.o sources/Context.cc
	$(CC) $(CCFLAGS) $(INCLUDE) -shared -o libCL.so objects/*.o
clean:
	rm -rf objects
	rm -f libCL.so
	rm -f run
