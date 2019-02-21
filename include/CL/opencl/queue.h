#ifndef _QUEUE_H_
#define _QUEUE_H_
#include<CL/cl.h>
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/device.h"
#include"CL/opencl/context.h"
#include"CL/opencl/event.h"
#include"CL/opencl/buffer.h"
#include"CL/opencl/kernel.h"
namespace cl {
class param;
class queue: public singleton
{
	public:
		cl_command_queue handler;
	public:
		queue(const context& target_context, const device& target_device, bool out_of_order = false);
		~queue();
	public:
		const event enqueueWriteBuffer(const buffer& b, void *host_ptr, size_t size, size_t offset=0);
		const event enqueueReadBuffer (const buffer& b, void *host_ptr, size_t size, size_t offset=0);
		const event enqueueCopyBuffer (const buffer& dst, const buffer& src, size_t size, size_t dst_offset=0, size_t src_offset=0);
		const event enqueueFillBuffer (const buffer& b, const void *pattern, size_t pattern_size, size_t size, size_t offset=0);
		const event enqueueMarker (const std::initializer_list<param>& events);
		const event enqueueBarrier(const std::initializer_list<param>& events);
		const event enqueueNDRangeKernel(const kernel& k, const std::initializer_list<param>& p, 
				array<size_t> global_dim, array<size_t> local_dim = array<size_t>());
		void flush();
		void join();
};
enum paramtype {EVENT, BUFFER, NUMBER};
class localmem
{
	public:
		size_t size;
		localmem(size_t size): size(size) {}
		~localmem(){}
};
class param
{
	public:
		paramtype type;
		size_t size;
		void *data;
	public:
		param(const event& obj): type(EVENT), size(sizeof(cl_event)), data((void*)&obj.handler) {}
		param(const buffer& obj): type(BUFFER), size(sizeof(cl_mem)), data((void*)&obj.handler) {}
		param(const localmem& obj): type(BUFFER), size(obj.size), data(nullptr) {}
		template<class numtype>
		param(const numtype& obj): type(NUMBER), size(sizeof(numtype)), data((void*)&obj){}
};
queue::queue(const context& target_context, const device& target_device, bool devicequeue)
{
	if (target_device.version().find("OpenCL 2.") == 0)
	{
	cl_command_queue_properties properties[] = {CL_QUEUE_PROPERTIES, 0, 0};
	if (devicequeue)
		properties[1] = CL_QUEUE_ON_DEVICE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;
	else
		properties[1] = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;
	cl_int err; handler = clCreateCommandQueueWithProperties(target_context.handler, target_device.handler, &(properties[0]), &err); cl_assert(err);
	}
	else if (target_device.version().find("OpenCL 1.") == 0)
	{
	cl_command_queue_properties properties = CL_QUEUE_PROFILING_ENABLE;
	cl_int err; handler = clCreateCommandQueue(target_context.handler, target_device.handler, properties, &err); cl_assert(err);	
	}
	else
	cl_assert(CL_INVALID_DEVICE);
}
queue::~queue()
{
	clReleaseCommandQueue(handler);
}
const event queue::enqueueWriteBuffer(const buffer& b, void *host_ptr, size_t size, size_t offset)
{
	cl_event event_id;
	cl_assert(clEnqueueWriteBuffer(handler, b.handler, CL_FALSE, offset, size, host_ptr, 0, nullptr, &event_id));
	return event(event_id);
}
const event queue::enqueueReadBuffer (const buffer& b, void *host_ptr, size_t size, size_t offset)
{
	cl_event event_id;
	cl_assert(clEnqueueReadBuffer(handler, b.handler, CL_FALSE, offset, size, host_ptr, 0, nullptr, &event_id));
	return event(event_id);
}
const event queue::enqueueCopyBuffer (const buffer& dst, const buffer& src, size_t size, size_t dst_offset, size_t src_offset)
{
	cl_event event_id;
	cl_assert(clEnqueueCopyBuffer(handler, src.handler, dst.handler, src_offset, dst_offset, size, 0, nullptr, &event_id));
	return event(event_id);
}
const event queue::enqueueFillBuffer (const buffer& b, const void *pattern, size_t pattern_size, size_t size, size_t offset)
{
	cl_event event_id;
	cl_assert(clEnqueueFillBuffer(handler, b.handler, pattern, pattern_size, offset, size, 0, nullptr, &event_id));
	return event(event_id);
}
const event queue::enqueueMarker (const std::initializer_list<param>& events)
{
	cl_event event_id;
	array<cl_event> event_ids(events.size());
	size_t i=0; for (auto it = events.begin(); it != events.end(); ++it, ++i)
		if (it->type == EVENT)
			event_ids[i] = *(cl_event*)it->data;
	cl_assert(clEnqueueMarkerWithWaitList(handler, event_ids.size(), event_ids.data(), &event_id));
	return event(event_id);
}
const event queue::enqueueBarrier(const std::initializer_list<param>& events)
{
	cl_event event_id;
	array<cl_event> event_ids(events.size());
	size_t i=0; for (auto it = events.begin(); it != events.end(); ++it, ++i)
		if (it->type == EVENT)
			event_ids[i] = *(cl_event*)it->data;
	cl_assert(clEnqueueBarrierWithWaitList(handler, event_ids.size(), event_ids.data(), &event_id));
	return event(event_id);
}
const event queue::enqueueNDRangeKernel(const kernel& k, const std::initializer_list<param>& p, array<size_t> global_dim, array<size_t> local_dim)
{
	while (local_dim.size() < global_dim.size()) local_dim.push_back(1);
	cl_event event_id;
	cl_uint i=0; for (auto it = p.begin(); it != p.end(); ++it, ++i)
		if (it->type == BUFFER or it->type == NUMBER)
			cl_assert(clSetKernelArg(k.handler, i, it->size, it->data));
	cl_assert(clEnqueueNDRangeKernel(handler, k.handler, global_dim.size(), nullptr, global_dim.data(), local_dim.data(), 0, nullptr, &event_id));
	return event(event_id);
}
void queue::flush()
{
	cl_assert(clFlush(handler));
}
void queue::join()
{
	cl_assert(clFinish(handler));
}



}
#endif
