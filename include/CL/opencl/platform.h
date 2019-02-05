#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include"CL/utils/singleton.h"
#include"CL/utils/container.h"
#include<CL/cl.h>
namespace cl {
class platform: public singleton
{
	private:
		cl_platform handler;
		platform() {}
	public:
		~platform() {}
		static container<platform> get_all_platforms();
};
container<platform> platform::get_all_platforms()
{
	cl_uint num_entries;
	
}
}
#endif
