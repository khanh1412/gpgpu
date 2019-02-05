#ifndef _KERNEL_H_
#define _KERNEL_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/context.h"
#include"CL/opencl/device.h"
#include<mutex>
#include<condition_variable>
#include<string>
class Event: public cl::singleton
{
	private:
		std::mutex signal_m;
		std::condition_variable signal_v;
	public:
		Event(){}
		~Event(){}
		inline void signal()
		{signal_v.notify_all();}
		inline void wait_for_signal()
		{std::unique_lock<std::mutex> signal_lock(signal_m);signal_v.wait(signal_lock);}
};
Event e;
extern "C" void CL_CALLBACK build_callback(cl_program program, void *user_data)
{
	Event& e = *reinterpret_cast<Event*>(user_data);
	e.signal();
}
namespace cl {
class compiler;
class kernel: public singleton
{
	private:
		friend class compiler;
	private:
		cl_kernel handler;
		kernel(const cl_kernel& kernel_id);
	public:
		~kernel();
};
kernel::kernel(const cl_kernel& kernel_id)
	: handler(kernel_id)
{}
kernel::~kernel()
{
	clReleaseKernel(handler);
}
class compiler
{
	public:
		static container<kernel> build(const context& target, const container<std::string>& source, const container<device>& devices, const std::string& options);
};
container<kernel> compiler::build(const context& target, const container<std::string>& source, const container<device>& devices, const std::string& options)
{
	cl_uint count = source.size();
	array<const char*> charsource(count);
	for (size_t i=0; i<count; ++i)
		charsource[i] = source[i].c_str();
	array<size_t> lengthsource(count);
	for (size_t i=0; i<count; ++i)
		lengthsource[i] = source[i].length();
	cl_int err;
	cl_program program = clCreateProgramWithSource(target.handler, count, charsource.data(), lengthsource.data(), &err); cl_assert(err);
	array<cl_device_id> device_ids(devices.size());
	for (size_t i=0; i<device_ids.size(); ++i)
		device_ids[i] = devices[i].handler;
	cl_assert(clBuildProgram(program, device_ids.size(), device_ids.data(), options.c_str(), build_callback, &e));
	e.wait_for_signal();
	for (size_t i=0; i<devices.size(); ++i)
	{
		cl_build_status sts;
		cl_assert(clGetProgramBuildInfo(program, devices[i].handler, CL_PROGRAM_BUILD_STATUS, sizeof(sts), &sts, nullptr));
		if (CL_BUILD_SUCCESS != sts)
		{
			size_t logsize;
			cl_assert(clGetProgramBuildInfo(program, devices[i].handler, CL_PROGRAM_BUILD_LOG, 0, nullptr, &logsize));
			array<char> log(logsize+1); log[logsize] = '\0';
			cl_assert(clGetProgramBuildInfo(program, devices[i].handler, CL_PROGRAM_BUILD_LOG, logsize, log.data(), nullptr));
			throw std::runtime_error(std::string(log.data(), log.size()));
		}
	}
	cl_uint num_kernels;
	cl_assert(clCreateKernelsInProgram(program, 0, nullptr, &num_kernels));
	array<cl_kernel> kernels(num_kernels);
	cl_assert(clCreateKernelsInProgram(program, num_kernels, kernels.data(), nullptr));
	container<kernel> all_kernels;
	for (size_t i=0; i<num_kernels; ++i)
		all_kernels.push_back(new kernel(kernels[i]));
	return all_kernels;
}
}
#endif
