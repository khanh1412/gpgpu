#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/device.h"
#include"CL/opencl/context.h"
namespace cl {
class queue: public singleton
{
	private:
		cl_command_queue handler;
		const device target_device;
		const context* target_context;
	public:
		queue(const device& target_device, const context& target_context);
		~queue();
};
queue::queue(const device& target_device, const context& target_context)
	: target_device(target_device), target_context(&target_context)
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
}
#endif
