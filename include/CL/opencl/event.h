#ifndef _EVENT_H_
#define _EVENT_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
namespace cl {
class param;
class queue;
class event
{
	private:
		friend class param;
		friend class queue;
	private:
		cl_event handler;
	private:
		event(const cl_event& event_id);
	public:
		event(const context& target);
		~event();
		void setComplete();
		void join();
		cl_ulong profileQueued();
		cl_ulong profileSubmit();
		cl_ulong profileStart();
		cl_ulong profileEnd();
		cl_ulong profileComplete();
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
	clReleaseEvent(handler);
}
void event::setComplete()
{
	cl_assert(clSetUserEventStatus(handler, CL_COMPLETE));
}
void event::join()
{
	cl_assert(clWaitForEvents(1, &handler));
}
cl_ulong event::profileQueued()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_QUEUED, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileSubmit()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_SUBMIT, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileStart()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_START, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileEnd()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_END, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profileComplete()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_COMPLETE, sizeof(res), &res, nullptr));
	return res;
}

}	
#endif
