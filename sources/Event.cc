#include"CL.h"
using namespace CL;
Event::Event(const cl_context& context)
{
	event = clCreateUserEvent(context, nullptr);
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
