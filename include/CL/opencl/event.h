#ifndef _EVENT_H_
#define _EVENT_H_
#include<CL/cl.h>
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
namespace cl {
class event
{
	public:
		cl_event handler;
	public:
		event(const cl_event& event_id);
		event(const context& target);
		~event();
		void setComplete();
		void join() const;
		cl_ulong profileQueued() const;
		cl_ulong profileSubmit() const;
		cl_ulong profileStart() const;
		cl_ulong profileEnd() const;
		cl_ulong profileComplete() const;
};
event::event(const cl_event& event_id)
	: handler(event_id)
{}
event::event(const context& target)
{
	cl_int err; handler = clCreateUserEvent(target.handler, &err); cl_assert(err);
}
event::~event()
{
	join();
	clReleaseEvent(handler);
}
void event::setComplete()
{
	cl_assert(clSetUserEventStatus(handler, CL_COMPLETE));
}
void event::join() const
{
	cl_assert(clWaitForEvents(1, &handler));
}
cl_ulong event::profileQueued() const
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_QUEUED, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileSubmit() const
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_SUBMIT, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileStart() const
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_START, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileEnd() const
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_END, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileComplete() const
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_COMPLETE, sizeof(res), &res, nullptr));
	return res;
}

}	
#endif
