#ifndef _KERNEL_H_
#define _KERNEL_H_
#include<CL/cl.hpp>
#include<string>
class Kernel
{
	private:
		cl::Context context;
		cl::Device device;
		friend class Context;
		
		Kernel(const cl::Context& context, const cl::Device& device, const std::string& kernel_path, const std::string& kernel_name);
	public:
		cl::Kernel kernel;
		
		~Kernel();
};
#endif
