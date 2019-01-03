#include<iostream>
#include"CL.h"

const uint64_t COUNT = 10;

void ADD(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = CL::Context::initContext(1,0);

	auto ds = context.createBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.createBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.createBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add = context.createKernel("./examples/0_vecAdd/add.cl.c", "add");

	auto write1 = queue.enqueueWriteBuffer(da, a, COUNT*sizeof(float));
	auto write2 = queue.enqueueWriteBuffer(db, b, COUNT*sizeof(float));
	auto barrier1 = queue.enqueueBarrier({write1, write2});
	auto kernel = queue.enqueueNDRangeKernel(add, {ds, da, db}, {COUNT, 1, 1}, {512,1,1});
	auto barrier2 = queue.enqueueBarrier({kernel});
	auto read = queue.enqueueReadBuffer(ds, s, COUNT*sizeof(float));
	auto barrier3 = queue.enqueueBarrier({read});
	barrier3.wait();

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
