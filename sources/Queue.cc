#include"CL.h"
using namespace CL;
Queue::Queue(const cl::Context& context, const cl::Device& device)
	: context(context), device(device)
{
	queue = cl::CommandQueue(context, device);
}
Queue::~Queue()
{}
void Queue::executeKernel(Kernel& kernel, const std::vector<Buffer>& arguments, const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim)
{
	cl_uint i = 0;
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
void Queue::writeBuffer(const Buffer& buffer, size_t size, void* host_ptr)
{
	queue.enqueueWriteBuffer(buffer.buffer, CL_FALSE, 0, size, host_ptr);
}
void Queue::readBuffer(const Buffer& buffer, size_t size, void* host_ptr)
{
	queue.enqueueReadBuffer(buffer.buffer, CL_FALSE, 0, size, host_ptr);
}
void Queue::synchronize()
{
	queue.finish();
}
