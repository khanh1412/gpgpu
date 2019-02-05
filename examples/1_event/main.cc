#include"opencl.h"
#include<iostream>
const uint64_t COUNT = 100;
auto& context = Context::initContext("NVIDIA CUDA");
void COPY(float *a0, float *a1, uint64_t COUNT)
{

	auto& d = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));

	auto& q1 = context.all_devices[0].createQueue();
	auto& q0 = context.all_devices[0].createQueue();

	{
		auto& control = context.createUserEvent();
		q1.enqueueBarrier({control});
		auto& read = q1.enqueueReadBuffer(d, a1, COUNT*sizeof(float));
		auto& write = q0.enqueueWriteBuffer(d, a0, COUNT*sizeof(float));
		write.join();
		control.setCompleted();

		q1.join();
		q0.join();
	}
}
void COPYwithoutEvents(float *a0, float *a1, uint64_t COUNT)
{
	auto& d = context.createBuffer(CL_MEM_READ_WRITE, COUNT*sizeof(float));

	auto& q1 = context.all_devices[0].createQueue();
	auto& q0 = context.all_devices[0].createQueue();

	auto& read = q1.enqueueReadBuffer(d, a1, COUNT*sizeof(float));
	auto& write = q0.enqueueWriteBuffer(d, a0, COUNT*sizeof(float));
	

	q1.join();
	q0.join();
}
void print_array(float *a)
{
	for (uint64_t i=0; i<10; i++)
		std::cout<<a[i]<<" ";
	std::cout<<" ..."<<std::endl;
}
int main()
{
	
	float *a0 = new float[COUNT];
	float *a1 = new float[COUNT];
	//COPY WITH EVENTS
	for (uint64_t i=0; i<COUNT; i++)
	{
		a0[i] = 1;
		a1[i] = 2;
	}
	std::cout<<"copy with events"<<std::endl;
	COPY(a0, a1, COUNT);
	print_array(a0);
	print_array(a1);
	//COPY WITHOUT EVENTS
	std::cout<<"copy without events"<<std::endl;
	std::cout<<std::endl;
	for (uint64_t i=0; i<COUNT; i++)
	{
		a0[i] = 1;
		a1[i] = 2;
	}
	COPYwithoutEvents(a0, a1, COUNT);
	print_array(a0);
	print_array(a1);
}
