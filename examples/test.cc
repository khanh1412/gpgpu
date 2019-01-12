#include"Context.h"
#include<iostream>

void ADD(float *c, float *a, float *b, size_t COUNT)
{
	Container<Context> all_contexts = Context::initContexts();

	auto& context = all_contexts[0];
	auto& kernel = context.createKernel("./examples/add.cl", ""); 
	auto& queue = context.devices[0].createQueue(false);


	auto& hc = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float), c);
	auto& ha = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float), a);	
	auto& hb = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float), b);	
	auto& dc = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));	
	auto& da = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));	
	auto& db = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));	

	
	auto w1 = queue.enqueueCopyBuffer(da, ha, COUNT*sizeof(float));
	auto w2 = queue.enqueueCopyBuffer(db, hb, COUNT*sizeof(float));

	auto b1 = queue.enqueueBarrier({w1, w2});

	auto k = queue.enqueueNDRangeKernel(kernel, {dc, da, db}, {COUNT, 1, 1}, {1, 1, 1});

	auto b2 = queue.enqueueBarrier({k});

	auto r1 = queue.enqueueCopyBuffer(hc, dc, COUNT*sizeof(float));

	r1.join();
	queue.synchronize();
}

int main()
{
	float a[3] = {1,1,1};
	float b[3] = {1,1,1};
	float c[3] = {1,1,1};

	ADD(c, a, b, 3);

	return 0;
}
