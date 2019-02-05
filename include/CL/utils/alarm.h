#ifndef _ALARM_H_
#define _ALAMR_H_
#include<mutex>
#include<condition_variable>
namespace cl {
class alarm: public singleton
{
	private:
		std::mutex signal_m;
		std::condition_variable signal_v;
	public:
		alarm(){}
		~alarm(){}
		inline void signal()
		{signal_v.notify_all();}
		inline void wait_for_signal()
		{std::unique_lock<std::mutex> signal_lock(signal_m);signal_v.wait(signal_lock);}
};
}
