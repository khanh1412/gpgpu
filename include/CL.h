#ifndef _CLWRAPPER_H_
#define _CLWRAPPER_H_
#include<vector>
#include<string>
namespace CL
{
	#include<CL/cl.h>
	void print_data(const std::string& name, void *data, size_t size);
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
			~Context();
	};
	class Buffer
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
			void writeBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset=0);
			void readBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset=0);
			void copyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset=0, size_t src_offset=0);
			void fillBuffer(const Buffer& buffer, void* pattern, size_t pattern_size, size_t size, size_t offset=0);
			void executeNDRangeKernel(
					Kernel& kernel, const std::vector<Argument>& arguments, 
					const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim);
			void enqueueBarrierWaitForEvents(std::vector<Event*> events);
			void synchronize();
	};
	class Argument
	{
		public:
			void *data;
			size_t size;
		public:
			Argument(){}
			Argument(const Buffer& buffer)
			{
				data = (void*)(&(buffer.buffer));
				size = sizeof(cl_mem);
			}
			Argument(const float& num)
			{
				data = (void*)(&num);
				size = sizeof(float);
			}
			~Argument(){};
	};
}
#endif
