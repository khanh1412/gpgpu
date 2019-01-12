#include"Program.h"
#include<fstream>
#include<stdexcept>
inline std::string read_file(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
	return content;
}
Program::Program(const cl_context& context, const Container<Device>& devices, const std::string& program_path, const std::string& build_flags)
{
	auto source = read_file(program_path);
	auto program_string = source.c_str();
	auto program_length = source.length();

	cl_int err;
	program = clCreateProgramWithSource(context, 1, &program_string, &program_length, &err);
	std::printf("---------------------\n");
	std::printf("PROGRAM: %ld bytes\n", program_length);
	std::printf("---------------------\n");
	std::printf("%s\n", program_string);
	std::printf("---------------------\n");
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create Program failed!");


	cl_device_id device_ptr[256];
	for (size_t i=0; i<devices.size(); ++i)
		device_ptr[i] = devices[i].device_id;

	clBuildProgram(program, devices.size(), &(device_ptr[0]), build_flags.c_str(), nullptr, nullptr);
	cl_build_status status;

	for (size_t i=0; i<devices.size(); ++i)
	{
		auto& device = device_ptr[i];
		std::printf("Device: 0x%lX : ", (unsigned long)device);
		while (1)
		{
			clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &status, nullptr);
			if (CL_BUILD_IN_PROGRESS != status)
				break;
			std::printf("Kernel build is in progress ...\n");
		}
		std::printf("Kernel build ...Done\n");
		std::printf("---------------------\n");
		char log[1024];
		if (CL_BUILD_SUCCESS != status)
		{
			clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 1024, &(log[0]), nullptr);
			throw std::runtime_error("Build Error: " + std::string(log));
		}
	}
}
Program::~Program()
{
	clReleaseProgram(program);
}
