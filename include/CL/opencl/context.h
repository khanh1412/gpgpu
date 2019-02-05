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
class compiler;
class context: public singleton
{
	private:
		friend class queue;
		friend class buffer;
		friend class compiler;
	private:
		cl_context handler;
		container<device> all_devices;
	public:
		context(const container<device>& target);
		~context();
};
context::context(const container<device>& target)
{

	array<cl_device_id> all_device_ids(target.size());
	for (size_t i=0; i<all_device_ids.size(); ++i)
	{
		all_device_ids[i] = target[i].handler;
		all_devices.push_back(new device(target[i]));
	}
	cl_int err; handler = clCreateContext(nullptr, all_device_ids.size(), all_device_ids.data(), nullptr, nullptr, &err); cl_assert(err);
}
context::~context()
{
	clReleaseContext(handler);
}
}
#endif
