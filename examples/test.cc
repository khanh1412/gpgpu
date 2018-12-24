#include<iostream>
#include"Context.h"

#include<ctime>
#include<thread>
const uint64_t COUNT = 1936*1096;

void clCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = Context::initContext(1,0);

	auto ds = context.allocateBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add = context.compileKernel("kernels/add.cl.c", "add");

	auto t1 = std::clock();
	queue.writeBuffer(da, COUNT*sizeof(float), a);
	queue.writeBuffer(db, COUNT*sizeof(float), b);
	queue.executeKernel(add, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(add, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(add, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(add, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(add, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.readBuffer(ds, COUNT*sizeof(float), s);
	queue.synchronize();
	auto t2 = std::clock();
	std::cout<<"CL time: "<<t2-t1<<" ticks"<<std::endl;
}

void add_kernel(float *s, float *a, float *b, uint64_t COUNT)
{
	for (uint64_t i = 0; i<COUNT; i++)
		s[i] = a[i] + b[i];
}
inline void add_s(float *s, float *a, float *b, uint64_t COUNT)
{
	add_kernel(s, a, b, COUNT);
}
void add(float *s, float *a, float *b, uint64_t COUNT)
{
	uint8_t threads = 4;
	std::thread t[threads];
	for (int i=0; i<threads; i++)
	{
		uint64_t offset = i*COUNT/4;
		if (i != threads-1)
		{
			t[i] = std::thread(add_kernel, s+offset, a+offset, b+offset, COUNT/4);
		}
		else
		{
			uint64_t lastlength = COUNT - offset;
			t[i] = std::thread(add_kernel, s+offset, a+offset, b+offset, lastlength);
		}
	}
	for (int i=0; i<threads; i++)
		t[i].join();
}


void nativeCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto t1 = std::clock();
	add(s, a, b, COUNT);
	add(s, a, b, COUNT);
	add(s, a, b, COUNT);
	add(s, a, b, COUNT);
	add(s, a, b, COUNT);
	auto t2 = std::clock();
	std::cout<<"native time: "<<t2-t1<<" ticks"<<std::endl;
}


int main()
{
	auto a = new float[COUNT];
	auto b = new float[COUNT];
	auto s = new float[COUNT];

	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(i);
		b[i] = static_cast<float>(COUNT - i);
		s[i] = 0;
	}

	clCAL(s, a, b, COUNT);

	nativeCAL(s, a, b, COUNT);
	/*
	std::cout<<"a = ";
	for (uint64_t i=0; i<COUNT; i++)
	{
		std::cout<<a[i]<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"b = ";
	for (uint64_t i=0; i<COUNT; i++)
	{
		std::cout<<b[i]<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"s = ";
	for (uint64_t i=0; i<COUNT; i++)
	{
		std::cout<<s[i]<<" ";
	}
	std::cout<<std::endl;
	*/

	return 0;


}
