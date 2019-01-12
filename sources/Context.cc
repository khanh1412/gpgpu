#include"Context.h"
#include<stdexcept>
#include<iostream>
#include"Array.h"
Context::Context(const Array<cl_device_id>& device_ids)
{
	cl_int err;
	context = clCreateContext(nullptr, device_ids.size(), device_ids.data(), nullptr, nullptr, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Context creation failed!");
	for (size_t i=0; i<device_ids.size(); ++i)
		devices.push_back(new Device(device_ids[i], context));
}
Context::~Context()
{
	devices.flush();
	buffers.flush();
	kernels.flush();
	clReleaseContext(context);
}
Container<Context> Context::initContexts()
{
	cl_uint num_platforms;
	clGetPlatformIDs(0, nullptr, &num_platforms);
	Array<cl_platform_id> all_platforms(num_platforms);
	clGetPlatformIDs(num_platforms, all_platforms.data(), nullptr);

	Container<Context> all_contexts;

	for (size_t i=0; i<num_platforms; ++i)
	{
		auto& platform_id = all_platforms[i];
		
		cl_uint num_devices;
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices);
		Array<cl_device_id> all_devices(num_devices);
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, all_devices.data(), nullptr);

		Array<char> name(256);
		clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 256, name.data(), nullptr);
		std::cout<<"platform "<<name.data()<<std::endl;

		if (std::string(name.data()).find("Clover") == 0)
			continue;
		if (std::string(name.data()).find("Intel Gen OCL Driver") == 0)
			continue;

		all_contexts.push_back(new Context(all_devices));
	}
	return all_contexts;
}
Buffer& Context::createBuffer(cl_mem_flags flags, size_t size, void *host_ptr)
{
	buffers.push_back(new Buffer(context, flags, size, host_ptr));
	return buffers[buffers.size() - 1];
}
Kernel& Context::createKernel(const std::string& program_path, const std::string& build_flags)
{
	Array<cl_device_id> device_ptr(devices.size());
	for (size_t i=0; i<devices.size(); ++i)
		device_ptr[i] = devices[i].device_id;



	kernels.push_back(new Kernel(context, device_ptr, program_path, build_flags));
	return kernels[kernels.size() - 1];
}
Event& Context::createUserEvent()
{
	user_events.push_back(new Event(context));
	return user_events[user_events.size() - 1];
}
