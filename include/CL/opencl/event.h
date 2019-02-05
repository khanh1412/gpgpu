#ifndef _EVENT_H_
#define _EVENT_H_
#include"CL/utils/container.h"
#include"CL/utils/singleton.h"
#include"CL/opencl/error.h"
namespace cl {
class param;
class call;
class event
{
	private:
		friend class param;
		friend class call;
	private:
		cl_event handler;
	private:
		event(const cl_event& event_id);
	public:
		event(const context& target);
		~event();
		void set_complete();
		void join();
		cl_ulong profiling_queued();
		cl_ulong profiling_submit();
		cl_ulong profiling_start();
		cl_ulong profiling_end();
		cl_ulong profiling_complete();
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
void event::set_complete()
{
	cl_assert(clSetUserEventStatus(handler, CL_COMPLETE));
}
void event::join()
{
	cl_assert(clWaitForEvents(1, &handler));
}
cl_ulong event::profiling_queued()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_QUEUED, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profiling_submit()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_SUBMIT, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profiling_start()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_START, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profiling_end()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_END, sizeof(res), &res, nullptr));
	return res;
}
cl_ulong event::profiling_complete()
{
	cl_ulong res;
	cl_assert(clGetEventProfilingInfo(handler, CL_PROFILING_COMMAND_COMPLETE, sizeof(res), &res, nullptr));
	return res;
}

}	
#endif
