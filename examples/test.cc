#include"Context.h"
#include<iostream>
#include"Handler.h"
int main()
{
	Container<Context> all_contexts;
	{
		Handler::initHandler(SIGSEGV);
		Handler::initHandler(SIGABRT);

		all_contexts = Context::initContexts();
	}

	auto& context = all_contexts[0];

	









 	return 0;	
}
