#include"Context.h"
#include<iostream>

void ADD(float *hc, float *ha, float *hb, size_t COUNT)
{
	Container<Context> all_contexts = Context::initContexts();

	auto& context = all_contexts[0];
	auto& kernel = context.createKernel("./examples/add.cl", ""); 
	auto& queue = context.devices[0].createQueue(false);


	auto& dc = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));	
	auto& da = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));	
	auto& db = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));	

	
	auto& w1 = queue.enqueueWriteBuffer(da, ha, COUNT*sizeof(float));
	auto& w2 = queue.enqueueWriteBuffer(db, hb, COUNT*sizeof(float));

	auto& b1 = queue.enqueueBarrier({w1, w2});

	auto& k = queue.enqueueNDRangeKernel(kernel, {dc, da, db}, {COUNT, 1, 1}, {1, 1, 1});

	auto& b2 = queue.enqueueBarrier({k});

	auto& r1 = queue.enqueueReadBuffer(dc, hc, COUNT*sizeof(float));

	r1.join();
	queue.synchronize();
}

void print(float *a)
{
	std::cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<std::endl;
}

int main()
{
	float a[3] = {1,1,1};
	float b[3] = {1,1,1};
	float c[3] = {1,1,1};

	ADD(c, a, b, 3);
	print(c);

	return 0;
}
