#ifndef _HANDLER_H_
#define _HANDLER_H_
#include<signal.h>
#include<string.h>
#include<stdio.h>
#include<stdexcept>
#include<mutex>
#include<condition_variable>
static void ignore_handler(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
	fprintf(stderr, "Segmentation fault ignored\n");
}
static void exit_handler(int signum, siginfo_t *si, void *context)
{
	((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]++;
	fprintf(stderr, "Segmentation fault handled\n");
	exit(1);
}
void enable_handler()
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = ignore_handler;
        sigaction(SIGSEGV, &action, NULL);	
}
void disable_handler()
{
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = exit_handler;
        sigaction(SIGSEGV, &action, NULL);	
}
#endif
