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
	auto all_devices = cl::device::get_all_devices(all_platforms[0]);
	std::cout<<all_devices[0].name()<<std::endl;
	return 0;
}
