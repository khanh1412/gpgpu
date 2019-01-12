#ifndef _PROGRAM_H_
#define _PROGRAM_H_
#include<CL/cl.h>
#include"Singleton.h"
#include"Container.h"
#include"Device.h"
#include<string>
class Program: public Singleton
{
	public:
		cl_program program;
	public:
		Program(const cl_context& context, const Container<Device>& devices, const std::string& program_path, const std::string& build_flags);
		~Program();
};
#endif
