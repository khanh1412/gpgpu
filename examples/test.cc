#include<iostream>
#include<fstream>
#include<cstdint>
#include<clblast.h>
#include"CL/opencl.h"
#include"CL/builtin/gemm.h"
inline std::string readfile(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
	return content;
}
auto device = cl::device::get_all_devices()[1];
auto context = cl::context({device});
auto queue = cl::queue(context, device);
auto kernel = cl::kernel(context, device, {readfile("./examples/kernel.cl.c")}, "");
auto A = cl::buffer(context, CL_MEM_READ_ONLY, 4*sizeof(float));
auto B = cl::buffer(context, CL_MEM_READ_ONLY, 4*sizeof(float));
auto C = cl::buffer(context, CL_MEM_READ_WRITE, 16*sizeof(float));
int main(int argc, char **argv)
{
	float a[4] = {1,2,3,4};
	float b[4] = {0,5,6,7};
	float c[16];

	{
		queue.enqueueWriteBuffer(A, a, 4*sizeof(float));
		queue.enqueueWriteBuffer(B, b, 4*sizeof(float));
	}
	{
		queue.enqueueNDRangeKernel(kernel, {(size_t)2, (size_t)2, (size_t)2, (size_t)2, A, B, C, cl::localmem(sizeof(float))}, {4, 4}, {2, 2});
	}
	{
		queue.enqueueReadBuffer(C, c, 16*sizeof(float));
	}

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
			std::cout<<c[i*4+j]<<" ";
		std::cout<<"\n";
	}






	return 0;
}
