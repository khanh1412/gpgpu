#ifndef _QUEUE_H_
#define _QUEUE_H_
#include<CL/cl.h>
#include"Singleton.h"
class Queue: public Singleton
{
	public:
		cl_command_queue queue;
	public:
		Queue(const cl_context& context, const cl_device_id& device_id, bool isdevicequeue = false);
		~Queue();
};
#endif
