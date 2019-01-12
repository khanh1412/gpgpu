#ifndef _KERNEL_H_
#define _KERNEL_H_
#include<CL/cl.h>
#include"Singleton.h"
#include"Container.h"
#include<string>
#include"Device.h"
class Kernel: public Singleton
{
	public:
		cl_program program;
		cl_kernel kernel;
	public:
		Kernel(const cl_context& context, const Container<Device>& devices, const std::string& program_path, const std::string& build_flags);
		~Kernel();
};
#endif
