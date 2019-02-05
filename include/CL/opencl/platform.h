#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include"CL/utils/singleton.h"
#include"CL/utils/container.h"
#include<CL/cl.h>
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
};
container<platform> platform::get_all_platforms()
{
	cl_uint num_platforms;
	assert(clGetPlatformIDs(0, nullptr, &num_platforms));
	array<cl_platform_id> all_platform_ids(num_platforms);
	assert(clGetPlatformIDs(num_platforms, all_platform_ids.data(), nullptr));
	container<platform> all_platforms;
	for (size_t i=0; i<num_platforms; ++i)
		all_platforms.push_back(new platform(all_platform_ids[i]));
	return all_platforms;
}
platform::platform(const cl_platform_id& platform_id)
	: handler(platform_id)
{}
}
#endif
