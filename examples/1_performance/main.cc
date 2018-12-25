#include<iostream>
#include"CL.h"

#include<ctime>
#include<thread>


const uint64_t size = 256;
const uint64_t COUNT = size*size*size;

void clCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = CL::Context::initContext(0,0);

	auto ds = context.allocateBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add = context.loadKernel("examples/kernels/add.cl.c", "add");

	auto t1 = std::clock();
	queue.writeBuffer(da, a, COUNT*sizeof(float));
	queue.writeBuffer(db, b, COUNT*sizeof(float));
	queue.synchronize();
	auto t2 = std::clock();
	queue.executeNDRangeKernel(add, {&ds, &da, &db}, {COUNT, 1, 1}, {size,1,1});
	queue.synchronize();
	auto t3 = std::clock();

	queue.readBuffer(ds, s, COUNT*sizeof(float));
	queue.synchronize();
	auto t4 = std::clock();
	std::cout<<"CL time: "<<static_cast<float>(t4-t1)/CLOCKS_PER_SEC<<std::endl;
	std::cout<<"\tWrite  time: "<<static_cast<float>(t2-t1)/CLOCKS_PER_SEC<<" | "<<2*COUNT*sizeof(float)<<"bytes"<<std::endl;
	std::cout<<"\tKernel time: "<<static_cast<float>(t3-t2)/CLOCKS_PER_SEC<<std::endl;
	std::cout<<"\tRead   time: "<<static_cast<float>(t4-t3)/CLOCKS_PER_SEC<<" | "<<COUNT*sizeof(float)<<"bytes"<<std::endl;
}

void add(float *s, float *a, float *b, uint64_t COUNT)
{
	for (uint64_t i = 0; i<COUNT; i++)
		s[i] = a[i] + b[i];
}
void add_m(float *s, float *a, float *b, uint64_t COUNT)
{
	uint8_t threads = 4;
	std::thread t[threads];
	for (int i=0; i<threads; i++)
	{
		uint64_t offset = i*COUNT/4;
		if (i != threads-1)
		{
			t[i] = std::thread(add, s+offset, a+offset, b+offset, COUNT/4);
		}
		else
		{
			uint64_t lastlength = COUNT - offset;
			t[i] = std::thread(add, s+offset, a+offset, b+offset, lastlength);
		}
	}
	for (int i=0; i<threads; i++)
		t[i].join();
}


void nativeCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto t1 = std::clock();
	add(s, a, b, COUNT);
	auto t2 = std::clock();
	std::cout<<"native time: "<<static_cast<float>(t2-t1)/CLOCKS_PER_SEC<<std::endl;
}

void mpCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto t1 = std::clock();
	add_m(s, a, b, COUNT);
	auto t2 = std::clock();
	std::cout<<"mp time: "<<static_cast<float>(t2-t1)/CLOCKS_PER_SEC<<std::endl;
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
	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(i);
		b[i] = static_cast<float>(COUNT - i);
		s[i] = 0;
	}
	mpCAL(s, a, b, COUNT);
	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(i);
		b[i] = static_cast<float>(COUNT - i);
		s[i] = 0;
	}
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
