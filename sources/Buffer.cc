#include"Buffer.h"
#include<stdexcept>
Buffer::Buffer(const cl_context& context, cl_mem_flags flags, size_t size, void *host_ptr)
{
	cl_int err;
	buffer = clCreateBuffer(context, flags, size, host_ptr, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Buffer failed!");	
}
Buffer::~Buffer()
{
	clReleaseMemObject(buffer);
}
