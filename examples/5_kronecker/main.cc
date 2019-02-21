#include<iostream>
#include<cstdint>
#include"CL/opencl.h"
#include"CL/builtin/gemm.h"
#include"CL/builtin/gkmm.h"
auto device = cl::device::get_all_devices()[0];
auto context = cl::context({device});
auto queue = cl::queue(context, device);
auto A = cl::buffer(context, CL_MEM_READ_ONLY, 4*sizeof(float));
auto B = cl::buffer(context, CL_MEM_READ_ONLY, 4*sizeof(float));
auto C = cl::buffer(context, CL_MEM_READ_WRITE, 16*sizeof(float));
int main(int argc, char **argv)
{
	float a[4] = {1,2,3,4};
	float b[4] = {0,5,6,7};
	float c[16];

	auto w1 = queue.enqueueWriteBuffer(A, a, 4*sizeof(float));
	auto w2 = queue.enqueueWriteBuffer(B, b, 4*sizeof(float));
	queue.enqueueBarrier({w1,w2});
	auto k = cl::builtin::gkmm(queue, 2, 2, 2, 2, 1, 0, A, B, C);
	queue.enqueueBarrier({k});
	queue.enqueueReadBuffer(C, c, 16*sizeof(float));
	queue.join();
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
			std::cout<<c[i*4+j]<<" ";
		std::cout<<"\n";
	}






	return 0;
}
