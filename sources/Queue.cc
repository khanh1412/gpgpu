#include"CL.h"
using namespace CL;
Queue::Queue(const cl_context& context, const cl_device_id& device)
{
	queue = clCreateCommandQueue(context, device, 0, nullptr);
}
Queue::~Queue()
{
	clReleaseCommandQueue(queue);
}
void Queue::writeBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset)
{
	clEnqueueWriteBuffer(queue, buffer.buffer, CL_FALSE, offset, size, host_ptr, 0, nullptr, nullptr);
}
void Queue::readBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset)
{
	clEnqueueReadBuffer(queue, buffer.buffer, CL_FALSE, offset, size, host_ptr, 0, nullptr, nullptr);
}
void Queue::copyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset, size_t src_offset)
{
	clEnqueueCopyBuffer(queue, src.buffer, dst.buffer, src_offset, dst_offset, size, 0, nullptr, nullptr);
}
void Queue::fillBuffer(const Buffer& buffer, void* pattern, size_t pattern_size, size_t size, size_t offset)
{
	clEnqueueFillBuffer(queue, buffer.buffer, pattern, pattern_size, offset, size, 0, nullptr, nullptr);
}
void Queue::executeNDRangeKernel(Kernel& kernel, const std::vector<Argument>& arguments, const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim)
{
	for (cl_uint i=0; i < arguments.size(); i++)
		clSetKernelArg(kernel.kernel, i, sizeof(cl_mem), arguments[i].data);
	clEnqueueNDRangeKernel(queue, kernel.kernel, global_dim.size(), 0, global_dim.data(), local_dim.data(), 0, nullptr, nullptr);
}
void Queue::synchronize()
{
	clFinish(queue);
}
