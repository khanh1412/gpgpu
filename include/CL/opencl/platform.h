#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include<CL/cl.h>
#include"CL/utils/field.h"
#include"CL/utils/container.h"
#include"CL/opencl/error.h"
namespace cl {
class device;
class platform: public field
{
	private:
		friend class device;
	private:
		cl_platform_id handler;
		platform(const cl_platform_id& platform_id);
	public:
		platform(const platform& target);
		~platform() {}
		static container<platform> get_all_platforms();
	public:
		std::string version() const;
		std::string name() const;
};
platform::platform(const cl_platform_id& platform_id)
	: handler(platform_id)
{}
platform::platform(const platform& target)
	: handler(target.handler)
{}
container<platform> platform::get_all_platforms()
{
	cl_uint num_platforms;
	try {
	cl_assert(clGetPlatformIDs(0, nullptr, &num_platforms));
	} catch (cl::error& err) { if (CL_OUT_OF_HOST_MEMORY == err.error_code) return container<platform>();}
	array<cl_platform_id> all_platform_ids(num_platforms);
	cl_assert(clGetPlatformIDs(num_platforms, all_platform_ids.data(), nullptr));
	container<platform> all_platforms;
	for (size_t i=0; i<num_platforms; ++i)
		all_platforms.push_back(new platform(all_platform_ids[i]));
	return all_platforms;
}
std::string platform::version() const
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_VERSION, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_VERSION, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
std::string platform::name() const
{
	size_t size;
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_NAME, 0, nullptr, &size));
	array<char> string(size+1); string.data()[size] = '\0';
	cl_assert(clGetPlatformInfo(handler, CL_PLATFORM_NAME, size, string.data(), nullptr));
	return std::string(string.data(), string.size());
}
}
#endif
