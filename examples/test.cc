#include<iostream>
#include"Context.h"

const uint64_t COUNT = 200;

void canvas_add(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = Context::initContext(0,0);

	auto ds = context.allocateBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add_kernel = context.compileKernel("kernels/add.cl.c", "add");


	queue.writeBuffer(da, CL_FALSE, COUNT*sizeof(float), a);
	queue.writeBuffer(db, CL_FALSE, COUNT*sizeof(float), b);
	queue.executeKernel(add_kernel, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.readBuffer(ds, CL_FALSE, COUNT*sizeof(float), s);
	queue.synchronize();
}

int main()
{
	auto a = new float[COUNT];
	auto b = new float[COUNT];
	auto s = new float[COUNT];

	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = i;
		b[i] = COUNT - i;
	}


	canvas_add(s, a, b, COUNT);

	std::cout<<"a = "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;

	std::cout<<"b = "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<b[i]<<" ";
	std::cout<<std::endl;


	std::cout<<"s = a + b "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<s[i]<<" ";
	std::cout<<std::endl;




}
