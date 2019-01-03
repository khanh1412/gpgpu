#include"CL.h"
using namespace CL;
Buffer::Buffer(const cl_context& context, cl_mem_flags flags, size_t size)
{
#ifdef DEBUG
	cl_int err;
	buffer = clCreateBuffer(context, flags, size, nullptr, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Buffer failed!");
#else
	buffer = clCreateBuffer(context, flags, size, nullptr, nullptr);
#endif
}
Buffer::~Buffer()
{
	clReleaseMemObject(buffer);
}
