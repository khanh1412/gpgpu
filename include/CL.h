#ifndef _CLWRAPPER_H_
#define _CLWRAPPER_H_
#include<CL/cl.h>
#include<vector>
#include<string>
	char num2char(uint8_t i);
	void print_data(const std::string& name, void *data, size_t size);
namespace CL
{
	class Singleton
	{
		private:
			Singleton(const Singleton& obj);
			void operator=(const Singleton& obj);
		public:
			Singleton(){}
			virtual ~Singleton(){}
	};
	class Buffer;
	class Kernel;
	class Queue;
	class Context;
	class Event;
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
			friend class Queue; friend class Context;
		public:	cl_mem buffer;
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
					Kernel& kernel, const std::vector<Buffer*>& arguments, 
					const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim);
			void enqueueBarrierWaitForEvents(std::vector<Event*> events);
			void synchronize();
	};
}
#endif
