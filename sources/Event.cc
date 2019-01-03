#include"CL.h"
using namespace CL;
Event::Event(const cl_context& context)
{
#ifdef DEBUG
	cl_int err;
	event = clCreateUserEvent(context, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create User Event failed!");
#else
	event = clCreateUserEvent(context, nullptr);
#endif
}
Event::Event(const cl_event& event)
	: event(event)
{}
Event::~Event()
{
	clReleaseEvent(event);
}
void Event::wait()
{
	clWaitForEvents(1, &event);
}
void Event::setCompleted()
{
	clSetUserEventStatus(event, CL_COMPLETE);
}
