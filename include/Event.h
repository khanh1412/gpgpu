#ifndef _EVENT_H_
#define _EVENT_H_
#include<CL/cl.h>
#include"Singleton.h"
class Event: public Singleton
	{
		public:
			cl_event event;
			Event(const cl_context& context);
			Event(const cl_event& event);
		public:
			void join();
			void setCompleted();
			uint64_t profileQueued();
			uint64_t profileSubmit();
			uint64_t profileStart();
			uint64_t profileEnd();
			uint64_t profileComplete();
			~Event();
};
#endif
