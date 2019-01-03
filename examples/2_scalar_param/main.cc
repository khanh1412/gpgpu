#include"CL.h"
#include<iostream>
#include<chrono>
#include<thread>
const uint64_t COUNT = 10;
auto context = CL::Context::initContext(1,0);
auto d_a = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));

auto q = context.createQueue();
auto k = context.createKernel("./examples/2_scalar_param/fill.cl.c", "fill");

void FILL(float *a, uint64_t COUNT, float value)
{
	auto write = q.enqueueWriteBuffer(d_a, a, COUNT*sizeof(float));
	auto kernel = q.enqueueNDRangeKernel(k, {d_a, value}, {COUNT, 1, 1}, {1, 1, 1});
	auto read = q.enqueueReadBuffer(d_a, a, COUNT*sizeof(float));

	q.synchronize();
}
void print_array(float *a, uint64_t COUNT)
{
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}
int main()
{	
	float *a = new float[COUNT];
	FILL(a, COUNT, 3.5);
	print_array(a, COUNT);
	FILL(a, COUNT, 7.6);
	print_array(a, COUNT);
	FILL(a, COUNT, -2.1);
	print_array(a, COUNT);
}
