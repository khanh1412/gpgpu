#include"CL.h"
using namespace CL;
Argument::Argument(const Buffer& buffer)
{
	data = (void*)(&(buffer.buffer));
	size = sizeof(cl_mem);
}
Argument::Argument(const float& num)
{
	data = (void*)(&num);
	size = sizeof(float);
}
Argument::Argument(const Event& event)
{
	data = (void*)(&(event.event));
	size = sizeof(cl_event);
}
