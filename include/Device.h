#ifndef _DEVICE_H_
#define _DEVICE_H_
#include<CL/cl.h>
#include"Singleton.h"
class Device: public Singleton
{
	public:
		cl_device_id device_id;
	public:
		Device(const cl_device_id& device_id);
		~Device();
};
#endif
