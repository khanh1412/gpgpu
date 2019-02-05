#ifndef _CALL_H_
#define _CALL_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/event.h"
#include"CL/opencl/buffer.h"
#include"CL/opencl/kernel.h"
namespace cl {
enum paramtype {EVENT, BUFFER, NUMBER};
class localmem
{
	private:
		size_t size;
	public:
		localmem(size_t size): size(size) {}
		~localmem(){}
};
class call;
class param
{
	private:
		friend class queue;
		friend class call;
	private:
		paramtype type;
		size_t size;
		void *data;
	public:
		param(const event& obj): type(EVENT), size(sizeof(cl_event)), data((void*)&obj.handler) {}
		param(const buffer& obj): type(BUFFER), size(sizeof(cl_mem)), data((void*)&obj.handler) {}
		param(const localmem& obj): type(BUFFER), size(sizeof(cl_mem)), data(nullptr) {}
		template<class numtype>
		param(const numtype& obj): type(NUMBER), size(sizeof(numtype)), data((void*)&obj){}
};
class call
{
	public:
static const event enqueueWriteBuffer(const queue& q, const buffer& b, void *host_ptr, size_t size, size_t offset=0);
static const event enqueueReadBuffer (const queue& q, const buffer& b, void *host_ptr, size_t size, size_t offset=0);
static const event enqueueCopyBuffer (const queue& q, const buffer& dst, const buffer& src, size_t size, size_t dst_offset=0, size_t src_offset=0);
static const event enqueueFillBuffer (const queue& q, const buffer& b, const void *pattern, size_t pattern_size, size_t size, size_t offset=0);
static const event enqueueMarker (const queue& q, const std::initializer_list<param>& events);
static const event enqueueBarrier(const queue& q, const std::initializer_list<param>& events);
static const event enqueueNDRangeKernel(const queue& q, const kernel& k, const std::initializer_list<param>& p, array<size_t> global_dim, array<size_t> local_dim = array<size_t>());
static void flush(const queue& q);
static void join(const queue& q);
};
const event call::enqueueWriteBuffer(const queue& q, const buffer& b, void *host_ptr, size_t size, size_t offset)
{
	cl_event event_id;
	cl_assert(clEnqueueWriteBuffer(q.handler, b.handler, CL_FALSE, offset, size, host_ptr, 0, nullptr, &event_id));
	return event(event_id);
}
const event call::enqueueReadBuffer (const queue& q, const buffer& b, void *host_ptr, size_t size, size_t offset)
{
	cl_event event_id;
	cl_assert(clEnqueueReadBuffer(q.handler, b.handler, CL_FALSE, offset, size, host_ptr, 0, nullptr, &event_id));
	return event(event_id);
}
const event call::enqueueCopyBuffer (const queue& q, const buffer& dst, const buffer& src, size_t size, size_t dst_offset, size_t src_offset)
{
	cl_event event_id;
	cl_assert(clEnqueueCopyBuffer(q.handler, src.handler, dst.handler, src_offset, dst_offset, size, 0, nullptr, &event_id));
	return event(event_id);
}
const event call::enqueueFillBuffer (const queue& q, const buffer& b, const void *pattern, size_t pattern_size, size_t size, size_t offset)
{
	cl_event event_id;
	cl_assert(clEnqueueFillBuffer(q.handler, b.handler, pattern, pattern_size, offset, size, 0, nullptr, &event_id));
	return event(event_id);
}
const event call::enqueueMarker (const queue& q, const std::initializer_list<param>& events)
{
	cl_event event_id;
	array<cl_event> event_ids(events.size());
	size_t i=0; for (auto it = events.begin(); it != events.end(); ++it, ++i)
		if (it->type == EVENT)
			event_ids[i] = *(cl_event*)it->data;
	cl_assert(clEnqueueMarkerWithWaitList(q.handler, event_ids.size(), event_ids.data(), &event_id));
	return event(event_id);
}
const event call::enqueueBarrier(const queue& q, const std::initializer_list<param>& events)
{
	cl_event event_id;
	array<cl_event> event_ids(events.size());
	size_t i=0; for (auto it = events.begin(); it != events.end(); ++it, ++i)
		if (it->type == EVENT)
			event_ids[i] = *(cl_event*)it->data;
	cl_assert(clEnqueueBarrierWithWaitList(q.handler, event_ids.size(), event_ids.data(), &event_id));
	return event(event_id);
}
const event call::enqueueNDRangeKernel(const queue& q, const kernel& k, const std::initializer_list<param>& p, array<size_t> global_dim, array<size_t> local_dim)
{
	while (local_dim.size() < global_dim.size()) local_dim.push_back(1);
	cl_event event_id;
	cl_uint i=0; for (auto it = p.begin(); it != p.end(); ++it, ++i)
		if (it->type == BUFFER or it->type == NUMBER)
			cl_assert(clSetKernelArg(k.handler, i, it->size, it->data));
	cl_assert(clEnqueueNDRangeKernel(q.handler, k.handler, global_dim.size(), nullptr, global_dim.data(), local_dim.data(), 0, nullptr, &event_id));
	return event(event_id);
}
void call::flush(const queue& q)
{
	cl_assert(clFlush(q.handler));
}
void call::join(const queue& q)
{
	cl_assert(clFinish(q.handler));
}
}
#endif
