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
