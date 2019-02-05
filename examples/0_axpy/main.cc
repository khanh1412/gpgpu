#include<iostream>
#include<omp.h>
#include<vector>
#include"opencl.h"

double OMP_CALL(float *res, float a, float *x, float *y, uint64_t COUNT)
{
	double t1 = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for nowait
		for (uint64_t i=0; i<COUNT; ++i)
			res[i] = a*x[i] + y[i];
	}
	double t2 = omp_get_wtime();
	return 1e9*(t2-t1);
}

double CL_CALL(float *res, float a, float *x, float *y, uint64_t COUNT)
{
	auto& context = Context::initContext("CUDA");
//	auto& context = Context::initContext("Intel");
	
	auto& device = context.all_devices[0];
	auto& kernel = context.createKernelFromFile("./examples/0_axpy/axpy.cl.c", "");
	auto& queue = device.createQueue();

	Array<size_t> local_dim({1});
	Array<size_t> global_dim({COUNT});


	auto& d_res = context.createBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto& d_x = context.createBuffer(CL_MEM_READ_ONLY, COUNT*sizeof(float));
	auto& d_y = context.createBuffer(CL_MEM_READ_ONLY, COUNT*sizeof(float));

	auto& w_x = queue.enqueueWriteBuffer(d_x, x, COUNT*sizeof(float));
	auto& w_y = queue.enqueueWriteBuffer(d_y, y, COUNT*sizeof(float));
	queue.enqueueBarrier({w_x, w_y});
	auto& k = queue.enqueueNDRangeKernel(kernel, {d_res, a, d_x, d_y, COUNT}, global_dim, local_dim);
	queue.enqueueBarrier({k});
	auto& r1 = queue.enqueueReadBuffer(d_res, res, COUNT*sizeof(float));
	r1.join();
	queue.join();
	double t = k.profileEnd() - k.profileStart();
	Context::flushContext("CUDA");
	return t;
}

void print_array(float *a)
{
	for (uint64_t i=0; i<10; i++)
		std::cout<<a[i]<<" ";
	std::cout<<" ..."<<std::endl;
}

int main(int argc, char **argv)
{
	const uint64_t COUNT = (argc < 2) ? 2 : std::stoi(argv[1]);

	std::vector<float> x(COUNT);
	std::vector<float> y(COUNT);
	std::vector<float> res(COUNT);
	float a = 1.21;

	double cl_time = CL_CALL(res.data(), a, x.data(), y.data(), COUNT);
	std::cout<<"time: "<<cl_time/1e6<<" millisec"<<std::endl;
	std::cout<<"performance: "<<(2*COUNT)/cl_time<<" GFLOPS"<<std::endl;

	double omp_time = OMP_CALL(res.data(), a, x.data(), y.data(), COUNT);
	std::cout<<"time: "<<omp_time/1e6<<" millisec"<<std::endl;
	std::cout<<"performance: "<<(2*COUNT)/omp_time<<" GFLOPS"<<std::endl;



	return 0;
}

