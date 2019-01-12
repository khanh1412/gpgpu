#ifndef _CLWRAPPER_H_
#define _CLWRAPPER_H_
#include<CL/cl.h>
#include<vector>
namespace cl
{
	class Singleton
	{
		protected:
			bool release;
			Singleton(Singleton& obj): release(true)
			{obj.release = false;}
			Singleton& operator=(Singleton& obj)
			{release = true; obj.release = false; return *this;}
		public:
			Singleton(): release(true) {}
			virtual ~Singleton(){}
	};
	class Device: public Singleton
	{
		public:
			cl_device_id device_id;
			Device(const cl_device_id& device_id);
			~Device();
	};
	class Context: public Singleton
	{
		public:
			cl_context context;
			std::vector<Device> all_devices;
			Context(const std::vector<cl_device_id>& device_ids);
			~Context();
			static std::vector<Context> all_contexts;
			static void initContexts();
	};
}
#endif
