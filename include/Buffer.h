#ifndef _BUFFER_H_
#define _BUFFER_H_
#include<CL/cl.h>
#include"Singleton.h"
class Buffer: public Singleton
{
	public:
		cl_mem buffer;
	public:
		Buffer(const cl_context& context, cl_mem_flags flags, size_t size, void *host_ptr);
	public:
		~Buffer();
};
#endif
