#ifndef _ASSERT_H_
#define _ASSERT_H_
#include<string>
#include<stdexcept>
#include<CL/cl.h>
namespace cl {
void assert(cl_int err, const std::string& line);
void assert(int line, const std::string& file, cl_int err)
{
	if (err != CL_SUCCESS)
		throw std::runtime_error(std::string("ERROR CODE: ") + std::to_string(err) + std::string("\nline: ") + std::to_string(line) + std::string("\nfile: ") + file);
}
}
#endif
