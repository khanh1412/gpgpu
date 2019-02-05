#include"all.h"
#include<iostream>
class child: public cl::field
{
	public:
	child(){}
	~child(){}
};
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
		std::cout<<"error catched: "<<err.what()<<std::endl;
	}
	auto all_platforms = cl::platform::get_all_platforms();
	auto all_devices = cl::device::get_all_devices(all_platforms[0]);
	std::cout<<all_devices[0].name()<<std::endl;

	auto context = cl::context(all_devices[0]);

	cl::device device(all_devices[0]);

	child a;
	try
	{
		child b(a);
	}
	catch (std::exception& err)
	{
		std::cout<<"error catched: "<<err.what()<<std::endl;
	}


	return 0;
}
