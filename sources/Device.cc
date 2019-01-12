#include"Device.h"
Device::Device(const cl_device_id& device_id, const cl_context& context)
	: device_id(device_id), context(context)
{}
Device::~Device()
{
	queues.flush();
}
Queue& Device::createQueue(bool isdevicequeue)
{
	queues.push_back(new Queue(context, device_id, isdevicequeue));
	return queues[queues.size() - 1];
}
