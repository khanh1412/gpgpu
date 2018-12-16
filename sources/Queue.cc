#include"Queue.h"
Queue::Queue(const cl::Context& context, const cl::Device& device)
	: context(context), device(device)
{
	queue = cl::CommandQueue(context, device);
}
Queue::~Queue()
{}
void Queue::executeKernel(Kernel& kernel, const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim, const std::vector<Buffer>& arguments)
{
	int i = 0;
	for (auto it = arguments.begin(); it != arguments.end(); it++)
	{
		kernel.kernel.setArg(i, (*it).buffer);
		i++;
	}
	queue.enqueueNDRangeKernel(
			kernel.kernel, 
			cl::NullRange, 
			cl::NDRange(global_dim[0], global_dim[1], global_dim[2]), 
			cl::NDRange(local_dim[0], local_dim[1], local_dim[2]), 
			nullptr, nullptr);
			
}
