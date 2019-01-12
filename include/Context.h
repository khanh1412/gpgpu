#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include<CL/cl.h>
#include"Singleton.h"
#include"Device.h"
#include"Container.h"
#include"Array.h"
class Context: public Singleton
{
	public:
		cl_context context;
		Container<Device> devices;
		static Container<Context> all_contexts;
	private:
		Context(const Array<cl_device_id>& device_ids);
	public:
		~Context();
		static void initContexts();
};
#endif
