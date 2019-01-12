#include"Event.h"
#include<stdexcept>
Event::Event(const cl_context& context)
{
	cl_int err;
	event = clCreateUserEvent(context, &err);
	if (CL_SUCCESS != err)
		throw std::runtime_error("Create User Event failed!");
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
uint64_t Event::profileQueued()
{
	uint64_t res;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_QUEUED, sizeof(uint64_t), &res, nullptr);
	return res;
}
uint64_t Event::profileSubmit()
{
	uint64_t res;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_SUBMIT, sizeof(uint64_t), &res, nullptr);
	return res;
}
uint64_t Event::profileStart()
{
	uint64_t res;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(uint64_t), &res, nullptr);
	return res;
}
uint64_t Event::profileEnd()
{
	uint64_t res;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(uint64_t), &res, nullptr);
	return res;
}
uint64_t Event::profileComplete()
{
	uint64_t res;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_COMPLETE, sizeof(uint64_t), &res, nullptr);
	return res;
}
