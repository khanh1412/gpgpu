#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"CL/cl.hpp"
class Queue
{
	private:
		cl::Context context;
		cl::Device device;
		cl::CommandQueue queue;
		friend class Context;
	public:
		Queue(const cl::Context& context, const cl::Device& device);
		~Queue();
};

#endif
