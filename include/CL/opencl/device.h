#ifndef _DEVICE_H_
#define _DEVICE_H_
#include"CL/utils/array.h"
#include"CL/utils/container.h"
#include<CL/cl.h>
#include"CL/opencl/error.h"
#include"CL/opencl/platform.h"
namespace cl {
class device
{
	private:
		cl_device_id handler;
		device(const cl_device_id& device_id);
	public:
		~device() {}
		static container<device> get_all_devices();
		static container<device> get_all_devices(const platform& target);
	public:
		std::string version();
		std::string name();
};
device::device(const cl_device_id& device_id)
	: handler(device_id)
{}
container<device> device::get_all_devices()
{
	auto all_platforms = platform::get_all_platforms();
	container<device> all_devices;
	for (size_t i=0; i<all_platforms.size(); ++i)
	{
		auto some_devices = get_all_devices(all_platforms[i]);
		for (size_t j=0; j<some_devices.size(); ++j)
			all_devices.push_back(new device(some_devices[j].handler));	
	}
	return all_devices;
}
container<device> device::get_all_devices(const platform& target)
{
	cl_uint num_devices;
	cl_assert(clGetDeviceIDs(target.handler, CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices));
	array<cl_device_id> all_device_ids(num_devices);
	cl_assert(clGetDeviceIDs(target.handler, CL_DEVICE_TYPE_ALL, num_devices, all_device_ids.data(), nullptr));
	container<device> all_devices;
	for (size_t i=0; i<num_devices; ++i)
		all_devices.push_back(new device(all_device_ids[i]));
	return all_devices;
}
std::string device::version()
{
	size_t size;
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_VERSION, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_VERSION, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string device::name()
{
	size_t size;
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_NAME, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_NAME, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
}
#endif
