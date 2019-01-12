#include<iostream>
#include"Context.h"

	auto& all_contexts = Context::initContexts();
	auto& context = all_contexts[0];
	auto& kernel = context.createKernel("./examples/0_vecadd/add.cl", "");
	auto& queue = context.devices[0].createQueue();
const uint64_t COUNT = 100;
void ADD(float *c, float *a, float *b)
{
	auto& dc = context.createBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto& da = context.createBuffer(CL_MEM_READ_ONLY, COUNT*sizeof(float));
	auto& db = context.createBuffer(CL_MEM_READ_ONLY, COUNT*sizeof(float));

	auto& w1 = queue.enqueueWriteBuffer(da, a, COUNT*sizeof(float));
	auto& w2 = queue.enqueueWriteBuffer(db, b, COUNT*sizeof(float));
	queue.enqueueBarrier({w1, w2});
	auto& k = queue.enqueueNDRangeKernel(kernel, {dc, da, db}, {COUNT, 1, 1}, {1, 1, 1});
	queue.enqueueBarrier({k});
	auto& r1 = queue.enqueueReadBuffer(dc, c, COUNT*sizeof(float));
	r1.join();
	queue.synchronize();
}

void print_array(float *a)
{
	for (uint64_t i=0; i<10; i++)
		std::cout<<a[i]<<" ";
	std::cout<<" ..."<<std::endl;
}

int main()
{
	float a[COUNT];
	float b[COUNT];
	float c[COUNT];

	for (size_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(i)/COUNT;
		b[i] = 1 - static_cast<float>(i)/COUNT;
	}
	
	print_array(a);
	print_array(b);
	ADD(c, a, b);
	print_array(c);
	

}

