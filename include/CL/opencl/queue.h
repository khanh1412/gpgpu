#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/device.h"
#include"CL/opencl/context.h"
#include"CL/opencl/event.h"
#include"CL/opencl/buffer.h"
namespace cl {
class queue: public singleton
{
	private:
		cl_command_queue handler;
		device *target_device;
		context *target_context;
	public:
		queue(device& target_device, context& target_context);
		~queue();
};
queue::queue(device& target_device, context& target_context)
	: target_device(&target_device), target_context(&target_context)
{
	bool isdevicequeue = false;
	cl_command_queue_properties properties[] = {CL_QUEUE_PROPERTIES, 0, 0};
	if (isdevicequeue)
		properties[1] = CL_QUEUE_ON_DEVICE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;
	else
		properties[1] = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;
	cl_int err; handler = clCreateCommandQueueWithProperties(target_context.handler, target_device.handler, &(properties[0]), &err); cl_assert(err);
}
queue::~queue()
{
	clReleaseCommandQueue(handler);
}

enum paramtype {EVENT, BUFFER, NUMBER};
class localmem
{
	private:
		size_t size;
	public:
		localmem(size_t size): size(size) {}
		~localmem(){}
};
class param
{
	private:
		friend class queue;
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
}
#endif
