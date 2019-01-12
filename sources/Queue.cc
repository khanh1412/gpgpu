#include"Queue.h"
#include<stdexcept>
Queue::Queue(const cl_context& context, const cl_device_id& device_id, bool isdevicequeue)
{
	cl_command_queue_properties properties[] = {CL_QUEUE_PROPERTIES, 0, 0};
	if (isdevicequeue)
		properties[1] = CL_QUEUE_ON_DEVICE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;
	else
		properties[1] = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;

	cl_int err;
	queue = clCreateCommandQueueWithProperties(context, device_id, &(properties[0]), &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Command Queue failed!");	
}
Queue::~Queue()
{
	clReleaseCommandQueue(queue);
}
Event Queue::enqueueCopyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset, size_t src_offset)
{
	cl_event event;
	clEnqueueCopyBuffer(queue, src.buffer, dst.buffer, src_offset, dst_offset, size, 0, nullptr, &event);
	return Event(event);
}
Event Queue::enqueueFillBuffer(const Buffer& buffer, void* pattern, size_t pattern_size, size_t size, size_t offset)
{
	cl_event event;
	clEnqueueFillBuffer(queue, buffer.buffer, pattern, pattern_size, offset, size, 0, nullptr, &event);
	return Event(event);
}

