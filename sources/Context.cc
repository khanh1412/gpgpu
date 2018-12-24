#include"Context.h"
#include<vector>
#include<iostream>

Context::Context(const cl::Platform& platform, const cl::Device& device)
	: platform(platform), device(device)
{
	context = cl::Context({device});
}
Context Context::initContext(uint8_t PlatformID, uint8_t DeviceID)
{
	int i;
	//PLATFORMS (OPENCL SOFTWARE)
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	std::cout<<"All platforms:"<<std::endl;
	i=0;
	for (auto& platform : all_platforms)
	{
		std::cout<<"\t["<<i<<"] "<<platform.getInfo<CL_PLATFORM_NAME>()<<std::endl;
		i++;
	}
	cl::Platform platform = all_platforms[PlatformID];
	std::cerr<<"Using platform: ["<<(int)PlatformID<<"] "<<platform.getInfo<CL_PLATFORM_NAME>()<<std::endl<<std::endl;

	//DEVICES (HARDWARE)
	std::vector<cl::Device> all_devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	i=0;
	std::cout<<"Platform's devices:"<<std::endl;
	for (auto& device : all_devices)
	{
		std::cout<<"\t["<<i<<"] "<<device.getInfo<CL_DEVICE_NAME>()<<std::endl;
		i++;
	}
	cl::Device device = all_devices[DeviceID];
	std::cerr<<"Using device: ["<<(int)DeviceID<<"] "<<device.getInfo<CL_DEVICE_NAME>()<<std::endl<<std::endl;




	Context context(platform, device);

	return context;

}
Context::~Context()
{}
Buffer Context::allocateBuffer(cl_mem_flags flag, size_t size)
{
	return Buffer(context, flag, size);
}
Queue Context::createQueue()
{
	return Queue(context, device);
}
Kernel Context::compileKernel(const std::string& kernel_path, const std::string& kernel_name)
{
	return Kernel(context, device, kernel_path, kernel_name);
}
