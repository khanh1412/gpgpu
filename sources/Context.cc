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
Context::~Context()
{
	clReleaseContext(context);
}
Container<Context> Context::all_contexts;
void initContexts()
{
	if (not all_contexts.empty()) all_contexts.clear();

	cl_uint num_platforms;
	clGetPlatformIDs(0, nullptr, &num_platforms);
	Array<cl_platform_id> all_platforms(num_platforms);
	clGetPlatformIDs(num_platforms, all_platforms.data(), nullptr);

	for (size_t i=0; i<num_platforms; ++i)
	{
		auto& platform_id = all_platforms[i];

		cl_uint num_devices;
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices);
		Array<cl_device_id> all_devices(num_devices);
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, all_devices.data(), nullptr);

		all_contexts.push_back(new Context(all_devices));
	}
}
