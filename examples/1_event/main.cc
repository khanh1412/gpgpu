#include"CL/opencl.h"
#include<iostream>
const uint64_t COUNT = 100;
auto all_platforms = cl::platform::get_all_platforms();
auto all_devices = cl::device::get_all_devices(all_platforms[0]);
auto context = cl::context({all_devices[0]});
void COPY(float *a0, float *a1, uint64_t COUNT)
{
	auto b = cl::buffer(context, CL_MEM_READ_WRITE, COUNT*sizeof(float));

	auto q0 = cl::queue(context, all_devices[0]);
	auto q1 = cl::queue(context, all_devices[0]);
	{
		auto controller = cl::event(context);
		q1.enqueueBarrier({controller});
		auto read = q1.enqueueReadBuffer(b, a1, COUNT*sizeof(float));
		auto write = q0.enqueueWriteBuffer(b, a0, COUNT*sizeof(float));
		write.join();
		controller.setComplete();
		q0.join();
		q1.join();
	}
}
void COPYwithoutEvents(float *a0, float *a1, uint64_t COUNT)
{
	auto b = cl::buffer(context, CL_MEM_READ_WRITE, COUNT*sizeof(float));

	auto q0 = cl::queue(context, all_devices[0]);
	auto q1 = cl::queue(context, all_devices[0]);
	{
		auto read = q1.enqueueReadBuffer(b, a1, COUNT*sizeof(float));
		auto write = q0.enqueueWriteBuffer(b, a0, COUNT*sizeof(float));
		write.join();
		q0.join();
		q1.join();
	}
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
