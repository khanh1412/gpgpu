#include<iostream>
#include"CL.h"

#include<ctime>
#include<thread>

const uint64_t COUNT = 20;

void clCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = CL::Context::initContext(1,0);

	auto ds = context.allocateBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add = context.loadKernel("examples/kernels/add.cl.c", "add");

	auto t1 = std::clock();
	queue.writeBuffer(da, a, COUNT*sizeof(float));
	queue.writeBuffer(db, b, COUNT*sizeof(float));
	queue.executeNDRangeKernel(add, {ds, da, db}, {COUNT, 1, 1}, {1,1,1});
	queue.readBuffer(ds, s, COUNT*sizeof(float));
	queue.synchronize();
	auto t4 = std::clock();
	std::cout<<"CL time: "<<static_cast<float>(t4-t1)/CLOCKS_PER_SEC<<std::endl;
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
