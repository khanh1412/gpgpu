#include"Context.h"

#include <iostream>

#include <string.h>
#include <signal.h>


void handler(int nSignum, siginfo_t* si, void* vcontext)
{
  
	ucontext_t* context = (ucontext_t*)vcontext;
	context->uc_mcontext.gregs[REG_RIP]++;
	std::cout << "Segmentation fault" << std::endl;
	exit(1);
}


int main() {
	std::cout << "Start" << std::endl;
  
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;
	sigaction(SIGSEGV, &action, NULL);
  
//	int* x = 0;
//	int y = *x;
	auto contexts = Context::initContexts();
  
	std::cout << "End" << std::endl;
  
	return 0;
}
