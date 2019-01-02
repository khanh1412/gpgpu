#ifndef _CLWRAPPER_H_
#define _CLWRAPPER_H_
#include<CL/cl.h>
#include<vector>
#include<string>
#ifdef DEBUG
#include<stdexcept>
void print_data(const std::string& name, const void *data, size_t size);
#endif
namespace CL
{
	class Singleton;
	class Argument;
	class Buffer;
	class Kernel;
	class Queue;
	class Context;
	class Event;
	class Singleton
	{
		private:
			Singleton(const Singleton& obj);
			void operator=(const Singleton& obj);
		public:
			Singleton(){}
			virtual ~Singleton(){}
	};
	class Argument
	{
		public:
			void *data;
			size_t size;
		public:
			Argument(){}
			Argument(const Buffer& buffer);
			Argument(const float& num);
			Argument(const Event& event);
			~Argument(){};
	};
	class Context: public Singleton
	{
		private:
			cl_device_id device;
			cl_context context;
			Context(const cl_device_id& device);
		public:
			static Context initContext(uint32_t PlatformID, uint32_t DeviceID);
			Buffer allocateBuffer(cl_mem_flags flags, size_t size);
			Queue createQueue();
			Kernel loadKernel(const std::string& program_path, const std::string& kernel_name);
			Event createUserEvent();
			~Context();
	};
	class Buffer: public Singleton
	{
		private:
			friend class Queue; friend class Context; friend class Argument;
			cl_mem buffer;
			Buffer(const cl_context& context, cl_mem_flags flags, size_t size);
		public:
			~Buffer();
	};
	class Kernel: public Singleton
	{
		private:
			friend class Queue; friend class Context;
			cl_program program;
			cl_kernel kernel;
			Kernel(const cl_context& context, const cl_device_id& device, const std::string& program_path, const std::string& kernel_name);
		public:	
			~Kernel();
	};
	class Queue: public Singleton
	{
		private:
			friend class Context;
			cl_command_queue queue;
			Queue(const cl_context& context, const cl_device_id& device);
		public:
			~Queue();
			Event enqueueWriteBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset=0);
			Event enqueueReadBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset=0);
			Event enqueueCopyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset=0, size_t src_offset=0);
			Event enqueueFillBuffer(const Buffer& buffer, void* pattern, size_t pattern_size, size_t size, size_t offset=0);
			Event enqueueNDRangeKernel(	Kernel& kernel, const std::vector<Argument>& arguments, 
							const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim);
			//used in out-of-order exeution
			Event enqueueMarker(const std::vector<Argument>& events);
			//used in both in-order and out-of-order
			Event enqueueBarrier(const std::vector<Argument>& events);
			void flush();
			void synchronize();
	};
	class Event: public Singleton
	{
		private:
			friend class Context; friend class Queue; friend class Argument;
			cl_event event;
			Event(const cl_context& context);
			Event(const cl_event& event);
		public:
			void wait();
			void setCompleted();
			~Event();
	};
}
#endif
