#include<iostream>
#include"CL.h"

#include<ctime>
#include<thread>

const uint64_t COUNT = 10;

void ADD(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = CL::Context::initContext(1,0);

	auto ds = context.createBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.createBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.createBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add = context.loadKernel("./examples/0_vecAdd/add.cl.c", "add");

	auto w1 = queue.enqueueWriteBuffer(da, a, COUNT*sizeof(float));
	auto w2 = queue.enqueueWriteBuffer(db, b, COUNT*sizeof(float));
	auto b1 = queue.enqueueBarrier({w1, w2});
	auto c = queue.enqueueNDRangeKernel(add, {ds, da, db}, {COUNT, 1, 1}, {512,1,1});
	auto r = queue.enqueueReadBuffer(ds, s, COUNT*sizeof(float));
	auto b2 = queue.enqueueBarrier({r});
	b2.wait();

	queue.synchronize();
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
	ADD(s, a, b, COUNT);
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
	return 0;


}
