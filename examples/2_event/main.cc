#include"CL.h"
#include<iostream>
#include<chrono>
#include<thread>
const uint64_t COUNT = 100;
void SWAP(float *a0, float *a1, uint64_t COUNT)
{
	auto context = CL::Context::initContext(1,0);
	auto d = context.allocateBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));

	auto q1 = context.createQueue();


	auto control = context.createUserEvent();

	q1.waitForEvents({control});
	auto read = q1.readBuffer(d, a1, COUNT*sizeof(float));
	q1.flush();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	auto q0 = context.createQueue();
	auto write = q0.writeBuffer(d, a0, COUNT*sizeof(float));

	write.wait();
	control.setCompleted();

	q0.synchronize();
	q1.synchronize();
}
void print_array(float *a, uint64_t COUNT)
{
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}
int main()
{
	
	float *a0 = new float[COUNT];
	float *a1 = new float[COUNT];
	for (uint64_t i=0; i<COUNT; i++)
	{
		a0[i] = 13;
		a1[i] = 26;
	}
	print_array(a0, COUNT);
	print_array(a1, COUNT);
	SWAP(a0, a1, COUNT);
	print_array(a0, COUNT);
	print_array(a1, COUNT);
}
