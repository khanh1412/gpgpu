#ifndef _QUEUE_H_
#define _QUEUE_H_
#include<CL/cl.h>
#include"Singleton.h"
#include"Buffer.h"
#include"Container.h"
#include"Event.h"
class Queue: public Singleton
{
	public:
		cl_command_queue queue;
	public:
		Queue(const cl_context& context, const cl_device_id& device_id, bool isdevicequeue = false);
		~Queue();
	public:
		Event enqueueCopyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset = 0, size_t src_offset = 0);
		Event enqueueFillBuffer(const Buffer& buffer, void* pattern, size_t pattern_size, size_t size, size_t offset = 0);

		Event enqueueMarker(const Container<Event>& events);
		Event enqueueBarrier(const Container<Event>& events);
		void flush();
		void synchronize();
};
#endif
