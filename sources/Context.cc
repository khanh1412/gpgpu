#include"cl.hpp"
#include<stdexcept>
using namespace cl;
Context::Context(const std::vector<cl_device_id>& device_ids)
{
	cl_int err;
	context = clCreateContext(nullptr, device_ids.size(), device_ids.data(), nullptr, nullptr, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Context creation failed!");
	for (auto& device_id : device_ids)
	{
		all_devices.push_back(Device(device_id));
	}
	
}
#include<iostream>
Context::~Context()
{
	if (release)
	{
		std::cout<<"Release "<<this<<std::endl;
		clReleaseContext(context);
	}
}
std::vector<Context> Context::all_contexts;
void Context::initContexts()
{
	if (not all_contexts.empty()) all_contexts.clear();

	cl_uint num_platforms;
	clGetPlatformIDs(0, nullptr, &num_platforms);
	std::vector<cl_platform_id> all_platforms(num_platforms);
	clGetPlatformIDs(num_platforms, all_platforms.data(), nullptr);

	for (auto& platform_id : all_platforms)
	{
		cl_uint num_devices;
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices);
		std::vector<cl_device_id> all_devices(num_devices);
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, all_devices.data(), nullptr);

		all_contexts.push_back(Context(all_devices));
	}
}
