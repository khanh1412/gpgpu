#include"CL.h"
using namespace CL;
Queue::Queue(const cl_context& context, const cl_device_id& device)
{
	cl_int err;
	cl_command_queue_properties properties[] = {0};
	queue = clCreateCommandQueueWithProperties(context, device, &(properties[0]), &err);
#ifdef DEBUG
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Command Queue failed!");
#endif

}
Queue::~Queue()
{
	clReleaseCommandQueue(queue);
}
Event Queue::writeBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset)
{
	cl_event event;
	clEnqueueWriteBuffer(queue, buffer.buffer, CL_FALSE, offset, size, host_ptr, 0, nullptr, &event);
	return Event(event);
}
Event Queue::readBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset)
{
	cl_event event;
	clEnqueueReadBuffer(queue, buffer.buffer, CL_FALSE, offset, size, host_ptr, 0, nullptr, &event);
	return Event(event);
}
Event Queue::copyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset, size_t src_offset)
{
	cl_event event;
	clEnqueueCopyBuffer(queue, src.buffer, dst.buffer, src_offset, dst_offset, size, 0, nullptr, &event);
	return Event(event);
}
Event Queue::fillBuffer(const Buffer& buffer, void* pattern, size_t pattern_size, size_t size, size_t offset)
{
	cl_event event;
	clEnqueueFillBuffer(queue, buffer.buffer, pattern, pattern_size, offset, size, 0, nullptr, &event);
	return Event(event);
}
Event Queue::executeNDRangeKernel(Kernel& kernel, const std::vector<Argument>& arguments, const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim)
{
	cl_event event;
	for (cl_uint i=0; i < arguments.size(); i++)
		clSetKernelArg(kernel.kernel, i, arguments[i].size, arguments[i].data);
	clEnqueueNDRangeKernel(queue, kernel.kernel, global_dim.size(), nullptr, global_dim.data(), local_dim.data(), 0, nullptr, &event);
	return Event(event);
}
Event Queue::waitForEvents(const std::vector<Argument>& events)
{
	cl_event event;
	std::vector<cl_event> event_list;
	for (auto it = events.begin(); it != events.end(); it++)
		event_list.push_back(*reinterpret_cast<cl_event*>((*it).data));
	clEnqueueMarkerWithWaitList(queue, event_list.size(), event_list.data(), &event);
	return Event(event);
}
Event Queue::waitForEventsWithBarrier(const std::vector<Argument>& events)
{
}
void Queue::flush()
{
	clFlush(queue);
}
void Queue::synchronize()
{
	clFinish(queue);
}
