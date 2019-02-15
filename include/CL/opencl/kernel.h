#ifndef _KERNEL_H_
#define _KERNEL_H_
#include<CL/cl.h>
#include<iostream>
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/utils/alarm.h"
#include"CL/opencl/error.h"
#include"CL/opencl/context.h"
#include"CL/opencl/device.h"
namespace cl {
class kernel: public singleton
{
	public:
		cl_kernel handler;
	public:
		kernel(const cl_kernel& kernel_id);
		kernel(const context& target_context, const device& target_device, const container<std::string>& source, const std::string& options);
		~kernel();
		static container<kernel> build(const context& target_context, const container<device>& target_devices, const container<std::string>& source, const std::string& options);
};
class program
{
	public:
		cl_program handler;
	public:
		program(const context& target_context, const container<device>& target_devices, const container<std::string>& source, const std::string& options);
		~program();
};
kernel::kernel(const cl_kernel& kernel_id)
	: handler(kernel_id)
{}
kernel::kernel(const context& target_context, const device& target_device, const container<std::string>& source, const std::string& options)
{
	program prog(target_context, {target_device}, source, options);
	cl_assert(clCreateKernelsInProgram(prog.handler, 1, &handler, nullptr));
}
kernel::~kernel()
{
	clReleaseKernel(handler);
}
container<kernel> kernel::build(const context& target_context, const container<device>& target_devices, const container<std::string>& source, const std::string& options)
{
	program prog(target_context, target_devices, source, options);
	cl_uint num_kernels;
	cl_assert(clCreateKernelsInProgram(prog.handler, 0, nullptr, &num_kernels));
	array<cl_kernel> kernels(num_kernels);
	cl_assert(clCreateKernelsInProgram(prog.handler, num_kernels, kernels.data(), nullptr));
	container<kernel> all_kernels;
	for (size_t i=0; i<num_kernels; ++i)
		all_kernels.push_back(new kernel(kernels[i]));
	return all_kernels;

}
program::program(const context& target_context, const container<device>& target_devices, const container<std::string>& source, const std::string& options)
{
	cl_uint count = source.size();
	array<const char*> charsource(count);
	for (size_t i=0; i<count; ++i)
		charsource[i] = source[i].c_str();
	array<size_t> lengthsource(count);
	for (size_t i=0; i<count; ++i)
		lengthsource[i] = source[i].length();
	cl_int err;
	handler = clCreateProgramWithSource(target_context.handler, count, charsource.data(), lengthsource.data(), &err); cl_assert(err);
	array<cl_device_id> device_ids(target_devices.size());
	for (size_t i=0; i<device_ids.size(); ++i)
		device_ids[i] = target_devices[i].handler;
	try
	{
		cl_assert(clBuildProgram(handler, device_ids.size(), device_ids.data(), options.c_str(), nullptr, nullptr));
	}
	catch (const cl::error& err)
	{
		for (size_t i=0; i<target_devices.size(); ++i)
		{
			std::cout<<"\nBuild log: ("<<target_devices[i].name()<<")"<<std::endl;
			cl_build_status sts;
			cl_assert(clGetProgramBuildInfo(handler, target_devices[i].handler, CL_PROGRAM_BUILD_STATUS, sizeof(sts), &sts, nullptr));
			if (CL_BUILD_SUCCESS != sts)
			{
				size_t logsize;
				cl_assert(clGetProgramBuildInfo(handler, target_devices[i].handler, CL_PROGRAM_BUILD_LOG, 0, nullptr, &logsize));
				array<char> log(logsize+1); log[logsize] = '\0';
				cl_assert(clGetProgramBuildInfo(handler, target_devices[i].handler, CL_PROGRAM_BUILD_LOG, logsize, log.data(), nullptr));
				std::cout<<log.data()<<std::endl;
			}
		}
		throw err;
	}
}
program::~program()
{
	clReleaseProgram(handler);
}
}
#endif

