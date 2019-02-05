#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include"CL/utils/singleton.h"
#include"CL/utils/container.h"
#include<CL/cl.h>
#include"CL/opencl/error.h"
namespace cl {
class platform: public singleton
{
	private:
		cl_platform_id handler;
		platform() {}
		platform(const cl_platform_id& platform_id);
	public:
		~platform() {}
		static container<platform> get_all_platforms();
	public:
		std::string profile();
		std::string version();
		std::string name();
		std::string vendor();
		std::string extensions();
};
container<platform> platform::get_all_platforms()
{
	cl_uint num_platforms;
	cl_assert(clGetPlatformIDs(0, nullptr, &num_platforms));
	array<cl_platform_id> all_platform_ids(num_platforms);
	cl_assert(clGetPlatformIDs(num_platforms, all_platform_ids.data(), nullptr));
	container<platform> all_platforms;
	for (size_t i=0; i<num_platforms; ++i)
		all_platforms.push_back(new platform(all_platform_ids[i]));
	return all_platforms;
}
platform::platform(const cl_platform_id& platform_id)
	: handler(platform_id)
{}
std::string platform::profile()
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_PROFILE, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_PROFILE, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string platform::version()
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_VERSION, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_VERSION, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string platform::name()
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_NAME, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_NAME, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string platform::vendor()
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_VENDOR, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_VENDOR, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string platform::extensions()
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_EXTENSIONS, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_EXTENSIONS, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
}
#endif
