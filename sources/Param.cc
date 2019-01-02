#include"CL.h"
using namespace CL;
Param::Param(const Buffer& buffer)
{
	data = (void*)(&(buffer.buffer));
	size = sizeof(cl_mem);
}
Param::Param(const float& num)
{
	data = (void*)(&num);
	size = sizeof(float);
}
Param::Param(const Event& event)
{
	data = (void*)(&(event.event));
	size = sizeof(cl_event);
}
