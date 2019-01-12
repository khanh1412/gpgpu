#ifndef _HANDLER_H_
#define _HANDLER_H_
#include<signal.h>
#include<stdio.h>
#include<string.h>
static void ignore_handler(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
}
static void exit_handler(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
	fprintf(stderr, "ERROR CODE: %d\n", signum);
	exit(1);
}
static void set_handler(int signum, void (*handler_func)(int, siginfo_t*, void*))
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = handler_func;
        sigaction(signum, &action, NULL);	
}
#include<unordered_map>
class Handler
{
	private:
		int signum;
		static std::unordered_map<int, Handler*> pool;
		Handler(int signum) : signum(signum)
		{
			set_handler(signum, ignore_handler);
			pool.emplace(signum, this);
		}
	public:
		static Handler& initHandler(int signum)
		{
			if (pool.end() == pool.find(signum))
				new Handler(signum);
			return *pool.find(signum)->second;
		}
		~Handler()
		{
			set_handler(signum, exit_handler);
			pool.erase(signum);
		}
};
std::unordered_map<int, Handler*> Handler::pool;
#endif
