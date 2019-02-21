#include"CL/opencl.h"
#include<iostream>
int main(int argc, char **argv)
{
	auto all_devices = cl::device::get_all_devices();
	auto& device = all_devices[1];
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	std::cout<<device.name()<<std::endl;
	auto context = cl::context({device});
	std::cout<<device.name()<<std::endl;
	std::cout<<"test ok"<<std::endl;
	return 0;
}
