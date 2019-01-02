#include"CL.h"
using namespace CL;
Event::Event(const cl_context& context)
{
	cl_int err;
	event = clCreateUserEvent(context, &err);
#ifdef DEBUG
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create User Event failed!");
#endif
}
Event::Event(const cl_event& event)
	: event(event)
{}
Event::~Event()
{
//	clReleaseEvent(event);
}
void Event::wait()
{
	clWaitForEvents(1, &event);
}
void Event::setCompleted()
{
	clSetUserEventStatus(event, CL_COMPLETE);
}
