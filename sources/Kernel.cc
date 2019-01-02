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
	cl_int err;
	auto content = read_program(program_path);
	auto program_string = content.c_str();
	auto program_length = content.length();

	program = clCreateProgramWithSource(context, 1, &program_string, &program_length, &err);
#ifdef DEBUG
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Program failed!");
#endif
	clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
#ifdef DEBUG
	cl_build_status status;
	while (1)
	{
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &status, nullptr);
		if (CL_BUILD_IN_PROGRESS != status)
			break;
	}
	char log[1024];
	if (CL_BUILD_SUCCESS != status)
	{
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 1024, &(log[0]), nullptr);
		throw std::runtime_error(log);
	}
#endif

	kernel = clCreateKernel(program, kernel_name.c_str(), &err);
#ifdef DEBUG
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Kernel failed!");
#endif
}
Kernel::~Kernel()
{
	clReleaseKernel(kernel);
	clReleaseProgram(program);
}
