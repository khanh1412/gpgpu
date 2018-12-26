#include<cstdio>
#include"CL.h"
int main()
{
	float a[] = {1,2,3};
	print_data("a", &a, sizeof(a));

	std::printf("before : %f %f %f\n", a[0], a[1], a[2]);

	auto context = CL::Context::initContext(1,0);

	{
		auto d_a = context.allocateBuffer(CL_MEM_READ_WRITE, 3*sizeof(float));
		print_data("d_a", &d_a, sizeof(d_a));


		auto queue = context.createQueue();

		auto fill = context.loadKernel("./examples/kernels/fill.cl.c", "fill");

		queue.writeBuffer(d_a, a, 3*sizeof(float));

		queue.executeNDRangeKernel(fill, {d_a, 2.5f}, {3, 1, 1}, {3, 1, 1});

		queue.readBuffer(d_a, a, 3*sizeof(float));

		queue.synchronize();



	}

	std::printf("after  : %f %f %f\n", a[0], a[1], a[2]);
	return 0;
}
