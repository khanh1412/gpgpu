#include"CL.h"
#include<fstream>
using namespace CL;
inline std::string read_program(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)), 
			std::istreambuf_iterator<char>());
	return content;
}

Kernel::Kernel(const cl_context& context, const cl_device_id& device, const std::string& program_path, const std::string& kernel_name)
{
	auto content = read_program(program_path);
	auto program_string = content.c_str();
	auto program_length = content.length();

	program = clCreateProgramWithSource(context, 1, &program_string, &program_length, nullptr);
	clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
	kernel = clCreateKernel(program, kernel_name.c_str(), nullptr);
}
Kernel::~Kernel()
{
	clReleaseKernel(kernel);
	clReleaseProgram(program);
}
