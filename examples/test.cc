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

	auto& buffer = context.createBuffer(CL_MEM_READ_WRITE, sizeof(float));	

	auto& program = context.createProgram("./examples/add.cl", ""); 







 	return 0;	
}
