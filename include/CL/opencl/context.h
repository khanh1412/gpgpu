#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/platform.h"
#include"CL/opencl/device.h"
namespace cl {
class queue;
class context: public singleton
{
	private:
		friend class queue;
	private:
		cl_context handler;
		container<device> all_devices;
	public:
		context(const device& target);
		~context();
};
context::context(const device& target)
{
	cl_int err; handler = clCreateContext(nullptr, 1, &target.handler, nullptr, nullptr, &err); cl_assert(err);
	all_devices.push_back(new device(target));
}
context::~context()
{
	clReleaseContext(handler);
}
}
#endif
