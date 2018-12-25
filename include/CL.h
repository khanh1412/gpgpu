#ifndef _CL_H_
#define _CL_H_
#include<CL/cl.hpp>
#include<string>
namespace CL
{
	class Buffer;
	class Kernel;
	class Queue;
	class Context;
	class Context
	{
		private:
			cl::Device device;
			cl::Context context;
			Context(const cl::Device& device);
		public:
			static Context initContext(uint8_t PlatformID, uint8_t DeviceID);
			Buffer allocateBuffer(cl_mem_flags flag, size_t size);
			Queue createQueue();
			Kernel compileKernel(const std::string& kernelpath, const std::string& kernelname);
			~Context();
	};
	class Buffer
	{
		private:
			cl::Context context;
			friend class Context; friend class Queue;
			cl::Buffer buffer;
			Buffer(const cl::Context& context, cl_mem_flags flag, size_t size);
		public:
			~Buffer();
	};
	class Kernel
	{
		private:
			cl::Context context;
			cl::Device device;
			friend class Context; friend class Queue;
			cl::Kernel kernel;
			Kernel(const cl::Context& context, const cl::Device& device, const std::string& kernel_path, const std::string& kernel_name);
		public:	
			~Kernel();
	};
	class Queue
	{
		private:
			cl::Context context;
			cl::Device device;
			friend class Context;
			cl::CommandQueue queue;	
			Queue(const cl::Context& context, const cl::Device& device);
		public:
			~Queue();
			void writeBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset=0);
			void readBuffer(const Buffer& buffer, void* host_ptr, size_t size, size_t offset=0);
			void copyBuffer(const Buffer& dst, const Buffer& src, size_t size, size_t dst_offset=0, size_t src_offset=0);
			void executeKernel(
					Kernel& kernel, const std::vector<Buffer>& arguments,
					const std::vector<uint64_t>& global_dim, const std::vector<uint64_t>& local_dim);
			void synchronize();
	};
}
#endif
