#include"CL.h"
using namespace CL;
Event::Event(const cl_context& context)
{
	event = clCreateUserEvent(context, nullptr);
}
Event::~Event()
{
	clReleaseEvent(event);
}
void Event::wait()
{
	clWaitForEvents(1, &event);
}
