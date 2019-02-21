#include<cstdint>
#include<string>
#include<iostream>
#include<fstream>
#include"CL/opencl.h"
int64_t fac(int8_t COUNT)
{
	int64_t perms = 1;
	for (int8_t i=2; i<=COUNT; i++) perms *= i;
	return perms;
}
inline std::string read_file(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
	return content;
}
auto device = cl::device::get_all_devices()[0];
auto context = cl::context({device});
auto queue = cl::queue(context, device);
auto kernel = cl::kernel(context, device, {read_file("examples/2_perm/perm.cl.c")}, "-cl-std=CL1.1");
double CL_CALL(int8_t COUNT)
{
	uint64_t num_threads = fac(COUNT);	
	auto k = queue.enqueueNDRangeKernel(kernel, {COUNT, (int64_t)0, cl::localmem(COUNT*sizeof(int8_t)), cl::localmem(COUNT*sizeof(int8_t))}, {num_threads});
	queue.join();
	double t = k.profileEnd() - k.profileStart();
	return t;
}
int main(int argc, char *argv[])
{
	int8_t COUNT = (argc < 2) ? 2 : std::stoi(argv[1]);
	int64_t num_threads = fac(COUNT);

	double cl_time = CL_CALL(COUNT);
	std::cout<<"COUNT  : "<<(int)COUNT<<std::endl;
	std::cout<<"number of permutations: "<<num_threads<<std::endl;
	std::cout<<"avg permutation time: "<<cl_time/num_threads<<" nanosec"<<std::endl;
	
	return 0;
}


