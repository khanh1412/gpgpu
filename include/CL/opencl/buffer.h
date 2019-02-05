#ifndef _BUFFER_H_
#define _BUFFER_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/context.h"
namespace cl {
class param;
class buffer: public singleton
{
	private:
		friend class param;
	private:
		cl_mem handler;
		context *target_context;
	public:
		buffer(context& target, cl_mem_flags flags, size_t size, void *host_ptr = nullptr);
		~buffer();
};
buffer::buffer(context& target, cl_mem_flags flags, size_t size, void *host_ptr)
	: target_context(&target)
{
	cl_int err; handler = clCreateBuffer(target.handler, flags, size, host_ptr, &err); cl_assert(err);
}
buffer::~buffer()
{
	clReleaseMemObject(handler);
}
}
#endif
