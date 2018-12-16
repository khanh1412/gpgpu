#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include"CL/cl.hpp"
#include<string>
#include"Buffer.h"
#include"Kernel.h"
#include"Queue.h"
class Context
{
	private:
		cl::Platform platform;
		cl::Device device;
		cl::Context context;
		Context(const cl::Platform& platform, const cl::Device& device);
	public:
		static Context initContext(uint8_t PlatformID, uint8_t DeviceID);
		Buffer allocateBuffer(cl_mem_flags flag, size_t size);
		Queue createQueue();
		Kernel compileKernel(const std::string& kernelpath, const std::string& kernelname);
		~Context();
};


#endif
