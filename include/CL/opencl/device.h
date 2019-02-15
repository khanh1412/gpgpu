#ifndef _DEVICE_H_
#define _DEVICE_H_
#include<CL/cl.h>
#include"CL/utils/field.h"
#include"CL/utils/container.h"
#include"CL/opencl/error.h"
#include"CL/opencl/platform.h"
#include<string>
namespace cl {
class device: public field
{
	public:
		cl_device_id handler;
	public:
		device(const cl_device_id& device_id);
		device(const device& target);
		~device() {}
		static container<device> get_all_devices();
		static container<device> get_all_devices(const platform& target);
	public:
		std::string version() const;
		std::string name() const;
};
device::device(const cl_device_id& device_id)
	: handler(device_id)
{}
device::device(const device& target)
	: handler(target.handler)
{}
container<device> device::get_all_devices()
{
	auto all_platforms = platform::get_all_platforms();
	container<device> all_devices;
	for (size_t i=0; i<all_platforms.size(); ++i)
	{
		auto some_devices = get_all_devices(all_platforms[i]);
		for (size_t j=0; j<some_devices.size(); ++j)
			all_devices.emplace_back(some_devices[j]);
	}
	return all_devices;
}
container<device> device::get_all_devices(const platform& target)
{
	cl_uint num_devices;
	try {
	cl_assert(clGetDeviceIDs(target.handler, CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices));
	} catch (cl::error& err) { if (CL_DEVICE_NOT_FOUND == err.error_code) return container<device>();}
	array<cl_device_id> all_device_ids(num_devices);
	cl_assert(clGetDeviceIDs(target.handler, CL_DEVICE_TYPE_ALL, num_devices, all_device_ids.data(), nullptr));
	container<device> all_devices;
	for (size_t i=0; i<num_devices; ++i)
		all_devices.emplace_back(all_device_ids[i]);
	return all_devices;
}
std::string device::version() const
{
	size_t size;
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_VERSION, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_VERSION, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string device::name() const
{
	size_t size;
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_NAME, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetDeviceInfo(handler, CL_DEVICE_NAME, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
}
#endif
