#include"Device.h"
Device::Device(const cl_device_id& device_id, const cl_context& context)
	: device_id(device_id), context(context)
{}
Device::~Device()
{}
