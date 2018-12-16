#ifndef _BUFFER_H_
#define _BUFFER_H_
#include"CL/cl.hpp"
class Buffer
{
	private:
		cl::Context context;
		cl::Buffer buffer;
		friend class Context;
	public:
		Buffer(const cl::Context& context, cl_mem_flags flag, size_t size);
		~Buffer();
};



#endif
