#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"CL/cl.hpp"
#include<vector>
#include"Buffer.h"
#include"Kernel.h"
class Queue
{
	private:
		cl::Context context;
		cl::Device device;
		friend class Context;
		Queue(const cl::Context& context, const cl::Device& device);
	public:
		cl::CommandQueue queue;
		
		~Queue();
		inline void writeBuffer(const Buffer& buffer, cl_bool sync, size_t size, void* host_ptr)
		{
			queue.enqueueWriteBuffer(buffer.buffer, sync, 0, size, host_ptr);
		}
		inline void readBuffer(const Buffer& buffer, cl_bool sync, size_t size, void* host_ptr)
		{
			queue.enqueueReadBuffer(buffer.buffer, sync, 0, size, host_ptr);
		}
		void executeKernel(Kernel& kernel, const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim, const std::vector<Buffer>& arguments);
		inline void synchronize() const
		{
			queue.finish();
		}
};

#endif
