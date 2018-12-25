#include"CL.h"
using namespace CL;
Buffer::Buffer(const cl::Context& context, cl_mem_flags flag, size_t size)
	: context(context)
{
	buffer = cl::Buffer(context, flag, size);
}
Buffer::~Buffer()
{}
