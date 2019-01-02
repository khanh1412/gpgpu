#include"CL.h"
#include<cstdio>
using namespace CL;
Context::Context(const cl_device_id& device)
	: device(device)
{
	cl_int err;
	context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
#ifdef DEBUG
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Context failed!");
#endif
}
Context::~Context()
{
	clReleaseContext(context);
}
Context Context::initContext(uint32_t PlatformID, uint32_t DeviceID)
{
	cl_uint num_platforms;
	cl_platform_id all_platforms[256];
	clGetPlatformIDs(0, nullptr, &num_platforms);
	clGetPlatformIDs(num_platforms, &(all_platforms[0]), nullptr);

	cl_uint num_devices;
	cl_device_id all_devices[256];
	clGetDeviceIDs(all_platforms[PlatformID], CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices);
	clGetDeviceIDs(all_platforms[PlatformID], CL_DEVICE_TYPE_ALL, num_devices, &(all_devices[0]), nullptr);

	char name[256];
	for (int i=0; i<256; i++) name[i] = '\0';
	clGetPlatformInfo(all_platforms[PlatformID], CL_PLATFORM_NAME, 256*sizeof(char), &(name[0]), nullptr);
	std::printf("Platform: %s\n", name);
	for (int i=0; i<256; i++) name[i] = '\0';
	clGetDeviceInfo(all_devices[DeviceID], CL_DEVICE_NAME, 256*sizeof(char), &(name[0]), nullptr);
	std::printf("Device: %s\n", name);



	return Context(all_devices[DeviceID]);
}
Buffer Context::allocateBuffer(cl_mem_flags flags, size_t size)
{
	return Buffer(context, flags, size);
}
Queue Context::createQueue()
{
	return Queue(context, device);
}
Kernel Context::loadKernel(const std::string& program_path, const std::string& kernel_name)
{
	return Kernel(context, device, program_path, kernel_name);
}
Event Context::createUserEvent()
{
	return Event(context);
}
