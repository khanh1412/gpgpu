#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include<CL/cl.h>
#include"Singleton.h"
#include"Container.h"
#include"Device.h"
class Context: public Singleton
{
	public:
		cl_context context;
		Container<Device> devices;
		Container<Buffer> buffers;
		Container<Kernel> kernels;
		Container<Event> user_events;
	private:
		Context(const Array<cl_device_id>& device_ids);
	public:
		~Context();
		static Container<Context> all_contexts;
		static Container<Context>& initContexts();
	public:
		Buffer& createBuffer(cl_mem_flags flags, size_t size, void *host_ptr = nullptr);
		Kernel& createKernel(const std::string& program_path, const std::string& build_flags);
		Event& createUserEvent();
};
#endif
