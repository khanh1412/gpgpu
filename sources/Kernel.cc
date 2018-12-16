#include"Kernel.h"
#include<fstream>
std::string readKernel(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)), 
			std::istreambuf_iterator<char>());
	return content;
}

cl::Kernel compileKernel(const std::string& filepath, const std::string& kernelname, const cl::Context& context, const cl::Device& default_device)
{
	cl::Program::Sources sources;

	std::string kernel_code = readKernel(filepath);
	sources.push_back({kernel_code.c_str(), kernel_code.length()});

	cl::Program program(context, sources);

	if (CL_SUCCESS != program.build({default_device}))
		throw std::runtime_error("Error building: " + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device));
	

	cl::Kernel kernel(program, kernelname.c_str());
	return kernel;
}

Kernel::Kernel(const cl::Context& context, const cl::Device& device, const std::string& kernel_path, const std::string& kernel_name)
	: context(context), device(device)
{
	auto code = readKernel(kernel_path);
	cl::Program::Sources source;
	source.push_back({code.c_str(), code.length()});
	auto program = cl::Program(context, source);
	kernel = cl::Kernel(program, kernel_name.c_str());
}
Kernel::~Kernel()
{}

