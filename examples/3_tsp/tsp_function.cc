#include"opencl.h"
#include<cstdint>
#include<ctime>
#include<iostream>
uint64_t hm_permutations(uint8_t size);
uint64_t cl_call(float *result, const float *arr, const uint8_t size, const uint8_t *perm)
{
	std::clock_t t1, t2;
	/*SET UP*/
	const uint64_t num_threads = hm_permutations(size);
	auto& context = Context::initContext("CUDA");
	{
	auto& device = context.all_devices[0];
	auto& queue = device.createQueue();
	auto& kernel = context.createKernelFromFile("./examples/3_tsp/tsp_kernel.cl.c", "-cl-std=CL2.0");
	size_t MaxWorkGroupSize = 0;
	Array<size_t> global_dim({num_threads});
	/*BUFFER*/
	auto& d_arr = context.createBuffer(CL_MEM_READ_ONLY, size*size*sizeof(float));
	auto& d_perm= context.createBuffer(CL_MEM_READ_ONLY, num_threads*size*sizeof(uint8_t));
	auto& d_result = context.createBuffer(CL_MEM_WRITE_ONLY, num_threads*sizeof(float));
	/*KERNEL*/
	t1 = std::clock();
	auto& write1 =	queue.enqueueWriteBuffer(d_perm, (void*)perm, num_threads*size*sizeof(uint8_t));
	auto& write2 = 	queue.enqueueWriteBuffer(d_arr, (void*)arr, size*size*sizeof(float));
			queue.enqueueBarrier({write1, write2});
	auto& kern   =	queue.enqueueNDRangeKernel(kernel, {d_result, d_arr, size, d_perm, num_threads}, global_dim);
			queue.enqueueBarrier({kern});
	auto& read1  =	queue.enqueueReadBuffer(d_result, result, num_threads*sizeof(float));
			queue.enqueueBarrier({read1});
	queue.join();
	t2 = std::clock();
	std::cout<<"copy datasheet time: "<<(write1.profileEnd() - write1.profileStart())/1000000<<" millisec"<<std::endl;
	std::cout<<"kernel         time: "<<(kern.profileEnd() - kern.profileStart())/1000000<<" millisec"<<std::endl;
	/*CLEAN UP*/
	Context::flushAllContexts();
	}
	return (1000000*(t2-t1))/CLOCKS_PER_SEC;
}
