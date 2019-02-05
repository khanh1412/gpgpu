#include"all.h"
#include<iostream>
int main()
{
	cl::array<float> arr1({1,2,3,4});
	cl::container<float> arr2({1,2,3,4});
	try
	{
		cl_assert(CL_SUCCESS);
		cl_assert(CL_INVALID_VALUE);
	}
	catch (std::exception& err)
	{
		std::cout<<"error catched"<<std::endl;
		std::cout<<err.what()<<std::endl;
	}
	auto all_platforms = cl::platform::get_all_platforms();
	for (size_t i=0; i<all_platforms.size(); ++i)
	{
		auto platform = all_platforms[i];
		std::cout<<"Platform name: "<<platform.name()<<std::endl;
		std::cout<<"Platform version: "<<platform.version()<<std::endl;
		try
		{
			auto all_devices = cl::device::get_all_devices(platform);
			std::cout<<"Number of devices: "<<all_devices.size()<<std::endl;
			for (size_t j=0; j<all_devices.size(); ++j)
			{
				auto device = all_devices[j];
				std::cout<<"\tDevice name: "<<device.name()<<std::endl;
				std::cout<<"\tDevice version: "<<device.version()<<std::endl;
			}
		}
		catch (cl::error& err)
		{
			std::cout<<"catched error: "<<err.what()<<std::endl;
			continue;
		}
	}
	return 0;
}
