#include<iostream>
#include"CL/opencl_lazy.h"
int main()
{
	const size_t COUNT = 3;
	const size_t size = COUNT*sizeof(float);

	float x[3] = {1,2,3};
	float y[3] = {3,2,1};
	float z[3];

	chooseDevice(0);
	auto kernel = createKernel("./examples/kernel.cl");
	auto bx = createBuffer(size);
	auto by = createBuffer(size);
	auto bz = createBuffer(size);

	std::cout<<"write x: "<<enqueueWriteBuffer(bx, x, size)<<std::endl;
	std::cout<<"write y: "<<enqueueWriteBuffer(by, y, size)<<std::endl;
	std::cout<<"kernel : "<<enqueueExecuteKernel(kernel, {bz, bx, by}, {3})<<std::endl;
	std::cout<<"read z : "<<enqueueReadBuffer(bz, z, size)<<std::endl;

	std::cout<<z[0]<<z[1]<<z[2]<<std::endl;



	

	return 0;
}
