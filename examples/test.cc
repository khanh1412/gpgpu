#include"CL/opencl.h"
int main(int argc, char **argv)
{
	auto all_devices = cl::device::get_all_devices();
	return 0;
}
