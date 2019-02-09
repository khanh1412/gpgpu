#ifndef _ERROR_H_
#define _ERROR_H_
#include<stdexcept>
#include<string>
#include<CL/cl.h>
namespace cl {
class error: public std::exception
{
	public:
		cl_int error_code;
		int line;
		std::string file;
	private:
		std::string errorname();
		std::string message;
	public:
		static void assert(const cl_int err, int line, const std::string& file);
		error(const cl_int& error_code, int line, const std::string& file);
		~error() {}
		virtual const char *what() const throw();
};
std::string error::errorname()
{
	switch (error_code)
	{
		case  0 : return std::string("CL_SUCCESS                                  ");
		case -1 : return std::string("CL_DEVICE_NOT_FOUND                         ");
		case -2 : return std::string("CL_DEVICE_NOT_AVAILABLE                     ");
		case -3 : return std::string("CL_COMPILER_NOT_AVAILABLE                   ");
		case -4 : return std::string("CL_MEM_OBJECT_ALLOCATION_FAILURE            ");
		case -5 : return std::string("CL_OUT_OF_RESOURCES                         ");
		case -6 : return std::string("CL_OUT_OF_HOST_MEMORY                       ");
		case -7 : return std::string("CL_PROFILING_INFO_NOT_AVAILABLE             ");
		case -8 : return std::string("CL_MEM_COPY_OVERLAP                         ");
		case -9 : return std::string("CL_IMAGE_FORMAT_MISMATCH                    ");
		case -10: return std::string("CL_IMAGE_FORMAT_NOT_SUPPORTED               ");
		case -11: return std::string("CL_BUILD_PROGRAM_FAILURE                    ");
		case -12: return std::string("CL_MAP_FAILURE                              ");
		case -13: return std::string("CL_MISALIGNED_SUB_BUFFER_OFFSET             ");
		case -14: return std::string("CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
		case -15: return std::string("CL_COMPILE_PROGRAM_FAILURE                  ");
		case -16: return std::string("CL_LINKER_NOT_AVAILABLE                     ");
		case -17: return std::string("CL_LINK_PROGRAM_FAILURE                     ");
		case -18: return std::string("CL_DEVICE_PARTITION_FAILED                  ");
		case -19: return std::string("CL_KERNEL_ARG_INFO_NOT_AVAILABLE            ");
		case -30: return std::string("CL_INVALID_VALUE                            ");
		case -31: return std::string("CL_INVALID_DEVICE_TYPE                      ");
		case -32: return std::string("CL_INVALID_PLATFORM                         ");
		case -33: return std::string("CL_INVALID_DEVICE                           ");
		case -34: return std::string("CL_INVALID_CONTEXT                          ");
		case -35: return std::string("CL_INVALID_QUEUE_PROPERTIES                 ");
		case -36: return std::string("CL_INVALID_COMMAND_QUEUE                    ");
		case -37: return std::string("CL_INVALID_HOST_PTR                         ");
		case -38: return std::string("CL_INVALID_MEM_OBJECT                       ");
		case -39: return std::string("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR          ");
		case -40: return std::string("CL_INVALID_IMAGE_SIZE                       ");
		case -41: return std::string("CL_INVALID_SAMPLER                          ");
		case -42: return std::string("CL_INVALID_BINARY                           ");
		case -43: return std::string("CL_INVALID_BUILD_OPTIONS                    ");
		case -44: return std::string("CL_INVALID_PROGRAM                          ");
		case -45: return std::string("CL_INVALID_PROGRAM_EXECUTABLE               ");
		case -46: return std::string("CL_INVALID_KERNEL_NAME                      ");
		case -47: return std::string("CL_INVALID_KERNEL_DEFINITION                ");
		case -48: return std::string("CL_INVALID_KERNEL                           ");
		case -49: return std::string("CL_INVALID_ARG_INDEX                        ");
		case -50: return std::string("CL_INVALID_ARG_VALUE                        ");
		case -51: return std::string("CL_INVALID_ARG_SIZE                         ");
		case -52: return std::string("CL_INVALID_KERNEL_ARGS                      ");
		case -53: return std::string("CL_INVALID_WORK_DIMENSION                   ");
		case -54: return std::string("CL_INVALID_WORK_GROUP_SIZE                  ");
		case -55: return std::string("CL_INVALID_WORK_ITEM_SIZE                   ");
		case -56: return std::string("CL_INVALID_GLOBAL_OFFSET                    ");
		case -57: return std::string("CL_INVALID_EVENT_WAIT_LIST                  ");
		case -58: return std::string("CL_INVALID_EVENT                            ");
		case -59: return std::string("CL_INVALID_OPERATION                        ");
		case -60: return std::string("CL_INVALID_GL_OBJECT                        ");
		case -61: return std::string("CL_INVALID_BUFFER_SIZE                      ");
		case -62: return std::string("CL_INVALID_MIP_LEVEL                        ");
		case -63: return std::string("CL_INVALID_GLOBAL_WORK_SIZE                 ");
		case -64: return std::string("CL_INVALID_PROPERTY                         ");
		case -65: return std::string("CL_INVALID_IMAGE_DESCRIPTOR                 ");
		case -66: return std::string("CL_INVALID_COMPILER_OPTIONS                 ");
		case -67: return std::string("CL_INVALID_LINKER_OPTIONS                   ");
		case -68: return std::string("CL_INVALID_DEVICE_PARTITION_COUNT           ");
		case -69: return std::string("CL_INVALID_PIPE_SIZE                        ");
		case -70: return std::string("CL_INVALID_DEVICE_QUEUE                     ");
		case -71: return std::string("CL_INVALID_SPEC_ID                          ");
		case -72: return std::string("CL_MAX_SIZE_RESTRICTION_EXCEEDED            ");
		default:  return std::string("ERROR_CODE_DOES_NOT_EXIST                   ");
	}
}
error::error(const cl_int& error_code, int line, const std::string& file)
	: error_code(error_code), line(line), file(file)
{
	message = 
	std::string("ERROR CODE: ") + std::to_string(error_code) + std::string("\n") +
	std::string("ERROR NAME: ") + errorname() + std::string("\n") +
	std::string("LINE: ") + std::to_string(line) + std::string("\n") +
	std::string("FILE: ") + file;
}
const char* error::what() const throw()
{
	return message.c_str();
}
void error::assert(const cl_int err, int line, const std::string& file)
{
	if (err != CL_SUCCESS)
		throw error(err, line, file);
}
}
#define cl_assert(x) cl::error::assert(x, __LINE__, __FILE__)
#endif
