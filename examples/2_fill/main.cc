#include<cstdio>
#include"CL.h"
int main()
{

	float a[] = {1,2,3};
	std::printf("%f %f %f\n", a[0], a[1], a[2]);
	auto context = CL::Context::initContext(1,0);

	{
		auto d_a = context.allocateBuffer(CL_MEM_READ_WRITE, 3*sizeof(float));


		auto queue = context.createQueue();

		auto fill = context.loadKernel("./examples/kernels/fill.cl.c", "fill");



		queue.writeBuffer(d_a, a, 3*sizeof(float));


		queue.executeNDRangeKernel(fill, {d_a, 20}, {3, 1, 1}, {3, 1, 1});



		queue.readBuffer(d_a, a, 3*sizeof(float));

		queue.synchronize();



	}

	std::printf("%f %f %f\n", a[0], a[1], a[2]);


	return 0;
}
