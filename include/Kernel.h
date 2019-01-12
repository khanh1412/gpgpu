#ifndef _KERNEL_H_
#define _KERNEL_H_
#include<CL/cl.h>
#include"Singleton.h"
class Kernel: public Singleton
{
	public:
		cl_kernel kernel;
	public:
		Kernel(const cl_program& program);
};
#endif
