#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/platform.h"
#include"CL/opencl/device.h"
namespace cl {
class queue;
class buffer;
class program;
class event;
class context: public singleton
{
	private:
		friend class queue;
		friend class buffer;
		friend class program;
		friend class event;
	private:
		cl_context handler;
		device default_device;
	public:
		context(const container<device>& target);
		~context();
	public:
//		inline buffer createBuffer(cl_mem_flags flags, size_t size, void *host_ptr = nullptr)
//		{return buffer(*this, flags, size, host_ptr);}
//		inline queue createQueue()
//		{return queue(*this, default_device);}
};
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
}
#endif
