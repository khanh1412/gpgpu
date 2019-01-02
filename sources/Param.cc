#include"CL.h"
using namespace CL;
Param::Param(const Buffer& buffer)
{
	param = (void*)(&buffer);
	type = BUFFER;
	data = (void*)(&(buffer.buffer));
	size = sizeof(cl_mem);
}
Param::Param(const Event& event)
{
	param = (void*)(&event);
	type = EVENT;
	data = (void*)(&(event.event));
	size = sizeof(cl_event);
}
