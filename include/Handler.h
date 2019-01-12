#ifndef _HANDLER_H_
#define _HANDLER_H_
#include<signal.h>
#include<stdio.h>
#include<string.h>

volatile int signal_status = 0;

static void handler_func(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
	signal_status = signum;
}
static inline void custom_handler(int signum, void (*handler_func)(int, siginfo_t*, void*))
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = handler_func;
        sigaction(signum, &action, NULL);	
}
static inline void default_handler(int signum)
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_handler = SIG_DFL;
        sigaction(signum, &action, NULL);	
}
static inline void wait_for_handler(int signum)
{
	while (signal_status != signum);
}
#include<unordered_map>
class Handler
{
	private:
		int signum;
		static std::unordered_map<int, Handler*> pool;
		Handler(int signum) : signum(signum)
		{
			custom_handler(signum, handler_func);
			pool.emplace(signum, this);
		}
	public:
		static Handler& initHandler(int signum)
		{
			if (pool.end() == pool.find(signum))
				new Handler(signum);
			return *pool.find(signum)->second;
		}
		void wait()
		{
			wait_for_handler(signum);
		}
		~Handler()
		{
			default_handler(signum);
			pool.erase(signum);
		}
};
std::unordered_map<int, Handler*> Handler::pool;
#endif
