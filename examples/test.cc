#include<iostream>
#include"CL/opencl.h"
#include"CL/exts/gemm.h"
int main(int argc, char **argv)
{
	float a[4] = {1, 2, 3, 4};
	float b[4] = {5, 6, 7, 8};
	float c[4];
	{
		auto device = cl::device::get_all_devices()[1];
		auto context = cl::context({device});
		auto queue = cl::queue(context, device);
		auto A = cl::buffer(context, CL_MEM_READ_ONLY, 4*sizeof(float));
		auto B = cl::buffer(context, CL_MEM_READ_ONLY, 4*sizeof(float));
		auto C = cl::buffer(context, CL_MEM_READ_WRITE, 4*sizeof(float));

		auto w1 = queue.enqueueWriteBuffer(A, a, 4*sizeof(float));
		auto w2 = queue.enqueueWriteBuffer(B, b, 4*sizeof(float));
		queue.enqueueBarrier({w1, w2});
		auto k = cl::clblast::gemm(queue, 2, 2, 2, 1.0f, 0.0f, A, B, C);
		queue.enqueueBarrier({k});
		queue.enqueueReadBuffer(C, c, 4*sizeof(float));
		queue.join();
	}
	std::cout<<c[0]<<" "<<c[1]<<std::endl;
	std::cout<<c[2]<<" "<<c[3]<<std::endl;
	return 0;
}
