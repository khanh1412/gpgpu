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
	//PLATFORMS (OPENCL SOFTWARE)
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	std::cout<<std::endl<<"All platforms:\tAll devices:"<<std::endl;
	int i=0; int j=0;
	for (auto& platform : all_platforms)
	{
		std::cout<<"["<<i<<"] "<<platform.getInfo<CL_PLATFORM_NAME>()<<std::endl;
		//DEVICES (HARDWARE)
		j=0;
		std::vector<cl::Device> all_devices;
		platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
		for (auto& device : all_devices)
		{
			if (j != DeviceID or i != PlatformID)
				std::cout<<"\t\t["<<j<<"] "<<device.getInfo<CL_DEVICE_NAME>()<<std::endl;
			else
				std::cout<<"\tusing\t["<<j<<"] "<<device.getInfo<CL_DEVICE_NAME>()<<std::endl;
			j++;
		}
		i++;
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	cl::Platform platform = all_platforms[PlatformID];
	std::vector<cl::Device> all_devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	cl::Device device = all_devices[DeviceID];




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
