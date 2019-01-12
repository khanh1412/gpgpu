#include"Context.h"
#include<stdexcept>
Context::Context(const Array<cl_device_id>& device_ids)
{
	cl_int err;
	context = clCreateContext(nullptr, device_ids.size(), device_ids.data(), nullptr, nullptr, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Context creation failed!");
	for (size_t i=0; i<device_ids.size(); ++i)
		devices.push_back(new Device(device_ids[i]));
}
