#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include<CL/cl.h>
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/platform.h"
#include"CL/opencl/device.h"
namespace cl {
class context: public singleton
{
	public:
		cl_context handler;
	public:
		context(cl_context handler);
		context(const container<device>& target);
		~context();
};
context::context(cl_context handler)
	: handler(handler)
{}
context::context(const container<device>& target)
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
