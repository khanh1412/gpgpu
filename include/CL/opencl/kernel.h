#ifndef _KERNEL_H_
#define _KERNEL_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
#include"CL/opencl/context.h"
namespace cl {
class compiler
{
	public:
		static container<kernel> build(context& target, const container<std::string>& source);
};
compiler::compiler(context& target, const container<std::string>& source)
	: target_context(&target)
{
	cl_uint count = source.size();
	array<const char*> charsource(count);
	for (size_t i=0; i<count; ++i)
		charsource[i] = source[i].c_str();
	array<size_t> lengthsource(count);
	for (size_t i=0; i<count; ++i)
		lengthsource[i] = source[i].length();
	cl_int err; handler = clCreateProgramWithSource(target.handler, count, charsource.data(), lengthsource.data(), &err); cl_assert(err);
}
compiler::~compiler()
{
	clReleaseProgram(handler);
}
}
class kernel
{
	private:
		cl_kernel handler
};
#endif
