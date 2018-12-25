#include<cstdio>
#include"CL.h"
int main()
{
	float a[] = {1,2,3};
	float b[] = {3,2,1};
	float c[] = {0,0,0};




	auto context = CL::Context::initContext(0,0);

	{
		auto d_a = context.allocateBuffer(CL_MEM_READ_WRITE, 3*sizeof(float));
		auto d_b = context.allocateBuffer(CL_MEM_READ_WRITE, 3*sizeof(float));
		auto d_c = context.allocateBuffer(CL_MEM_READ_WRITE, 3*sizeof(float));

		auto queue = context.createQueue();

		auto add = context.loadKernel("./examples/kernels/add.cl.c", "add");



		queue.writeBuffer(d_a, a, 3*sizeof(float));
		queue.writeBuffer(d_b, b, 3*sizeof(float));


		queue.executeNDRangeKernel(add, {&d_c, &d_a, &d_b}, {3, 1, 1}, {1, 1, 1});





		queue.readBuffer(d_c, c, 3*sizeof(float));

		queue.synchronize();



	}

	std::printf("%f %f %f\n", a[0], a[1], a[2]);
	std::printf("%f %f %f\n", b[0], b[1], b[2]);
	std::printf("%f %f %f\n", c[0], c[1], c[2]);


	return 0;
}
