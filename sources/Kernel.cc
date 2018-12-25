#include"CL.h"
#include<fstream>
using namespace CL;
std::string readKernel(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)), 
			std::istreambuf_iterator<char>());
	return content;
}

Kernel::Kernel(const cl::Context& context, const cl::Device& device, const std::string& kernel_path, const std::string& kernel_name)
	: context(context), device(device)
{
	cl::Program::Sources sources;

	std::string kernel_code = readKernel(kernel_path);
	sources.push_back({kernel_code.c_str(), kernel_code.length()});

	cl::Program program(context, sources);

	if (CL_SUCCESS != program.build({device}))
		throw std::runtime_error("Error building: " + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device));
	

	kernel = cl::Kernel(program, kernel_name.c_str());
}
Kernel::~Kernel()
{}

