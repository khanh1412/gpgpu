#include"CL.h"
using namespace CL;
Buffer::Buffer(const cl_context& context, cl_mem_flags flags, size_t size)
{
	buffer = clCreateBuffer(context, flags, size, nullptr, nullptr);
}
Buffer::~Buffer()
{
	clReleaseMemObject(buffer);
}
