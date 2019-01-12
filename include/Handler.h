#ifndef _HANDLER_H_
#define _HANDLER_H_
#include<signal.h>
#include<string.h>
#include<stdio.h>
static void ignore_handler(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
}
static void exit_handler(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
	fprintf(stderr, "Segmentation fault (core dumped)\n");
	exit(1);
}
class Handler
{
	private:
		Handler()
		{
			set_handler(ignore_handler);
		}
		static Handler *h;
		static void set_handler(void (*handler_func)(int, siginfo_t*, void*))
		{
		        struct sigaction action;
		        memset(&action, 0, sizeof(struct sigaction));
		        action.sa_flags = SA_SIGINFO;
		        action.sa_sigaction = handler_func;
		        sigaction(SIGSEGV, &action, NULL);	
		}
	public:
		static Handler& initHandler()
		{
			if (h == nullptr)
				h = new Handler();
			return *h;
		}
		~Handler()
		{
			set_handler(exit_handler);
			h = nullptr;
		}
};
Handler *Handler::h = nullptr;
#endif
