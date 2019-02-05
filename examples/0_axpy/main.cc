#include"CL/opencl.h"
#include<iostream>
#include<fstream>
inline std::string read_file(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
	return content;
}
double cl_call(float *z, float a, float *x, float *y, size_t COUNT)
{
	auto all_platforms = cl::platform::get_all_platforms();
	auto all_devices = cl::device::get_all_devices(all_platforms[0]);
	auto context = cl::context({all_devices[0]});
	double kernel_time;
	{
	auto queue = cl::queue(all_devices[0], context);
	auto kernel = cl::kernel(context, {read_file("examples/0_axpy/axpy.cl.c")}, "-cl-std=CL2.0", all_devices[0]);

	cl::array<size_t> global_dim({COUNT});
	cl::array<size_t> local_dim({1});

	auto b_x = cl::buffer(context, CL_MEM_READ_ONLY, COUNT*sizeof(float));
	auto b_y = cl::buffer(context, CL_MEM_READ_ONLY, COUNT*sizeof(float));
	auto b_z = cl::buffer(context, CL_MEM_WRITE_ONLY, COUNT*sizeof(float));

	auto e1 = queue.enqueueWriteBuffer(b_x, x, COUNT*sizeof(float));
	auto e2 = queue.enqueueWriteBuffer(b_y, y, COUNT*sizeof(float));

	queue.enqueueBarrier({e1, e2});
	auto ek = queue.enqueueNDRangeKernel(kernel, {b_z, a, b_x, b_y}, global_dim, local_dim);
	queue.enqueueBarrier({ek});
	auto e3 = queue.enqueueReadBuffer(b_z, z, COUNT*sizeof(float));
	queue.join();
	kernel_time = ek.profileEnd() - ek.profileStart();
	}
	return kernel_time;
}
const float tol = 0.001;
int main(int argc, char **argv)
{
	const size_t COUNT = (argc < 2) ? 2 : std::stoi(argv[1]);
	cl::array<float> x(COUNT);
	cl::array<float> y(COUNT);
	cl::array<float> z(COUNT);

	for (size_t i=0; i<COUNT; ++i)
	{
		x[i] = i;
		y[i] = COUNT-i;
		z[i] = 0;
	}
	std::cout<<"time: "<<cl_call(z.data(), 1, x.data(), y.data(), COUNT)<<std::endl;
	size_t fail = 0;
	for (size_t i=0; i<COUNT; ++i)
	{
		float diff = z[i] - (x[i] + y[i]);
		if (diff*diff > tol*tol)
			fail++;
	}
	std::cout<<"fail: "<<fail<<"/"<<COUNT<<std::endl;



	return 0;
}
