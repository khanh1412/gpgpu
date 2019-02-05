#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
namespace cl {
class queue;
class buffer;
class program;
class event;
class kernel;
class context: public singleton
{
	private:
		friend class queue;
		friend class buffer;
		friend class program;
		friend class kernel;
		friend class event;
	private:
		cl_context handler;
		device default_device;
	public:
		context(const container<device>& target);
		~context();
	public:
		inline buffer createBuffer(cl_mem_flags flags, size_t size, void *host_ptr = nullptr);
		inline queue createQueue();
		inline kernel createKernel(const container<std::string>& source, const std::string& options);
		inline event createUserEvent();
};
#include"CL/opencl/platform.h"
#include"CL/opencl/device.h"
#include"CL/opencl/buffer.h"
#include"CL/opencl/kernel.h"
context::context(const container<device>& target)
	: default_device(target[0])
{
	array<cl_device_id> all_device_ids(target.size());
	for (size_t i=0; i<all_device_ids.size(); ++i)
		all_device_ids[i] = target[i].handler;
	cl_int err; handler = clCreateContext(nullptr, all_device_ids.size(), all_device_ids.data(), nullptr, nullptr, &err); cl_assert(err);
}
context::~context()
{
	clReleaseContext(handler);
}
inline buffer context::createBuffer(cl_mem_flags flags, size_t size, void *host_ptr)
{return buffer(*this, flags, size, host_ptr);}
inline queue context::createQueue()
{return queue(*this, default_device);}
inline kernel context::createKernel(const container<std::string>& source, const std::string& options)
{return kernel(*this, default_device, source, options);}
inline event context::createUserEvent()
{return event(*this);}
}
#endif
