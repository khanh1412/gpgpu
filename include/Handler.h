#ifndef _HANDLER_H_
#define _HANDLER_H_
#include<signal.h>
#include<stdio.h>
#include<string.h>
static void handler_func(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
	fprintf(stderr, "ERROR CODE: 0x%X\n", signum);
}
static void custom_handler(int signum, void (*handler_func)(int, siginfo_t*, void*))
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = handler_func;
        sigaction(signum, &action, NULL);	
}
static void default_handler(int signum)
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_handler = SIG_DFL;
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
		~Handler()
		{
			default_handler(signum);
			pool.erase(signum);
		}
};
std::unordered_map<int, Handler*> Handler::pool;
#endif
