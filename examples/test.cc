#include"Context.h"
#include<iostream>
#include"Handler.h"

int main()
{
	Container<Context> all_contexts = Context::initContexts();

	auto& context = all_contexts[0];

	auto& buffer = context.createBuffer(CL_MEM_READ_WRITE, sizeof(float));	

	auto& kernel = context.createKernel("./examples/add.cl", ""); 

	auto& queue = context.devices[0].createQueue(false);


 	return 0;	
}
