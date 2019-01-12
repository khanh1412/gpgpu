#include"Context.h"
#include<iostream>
#include"Handler.h"

class a
{
	public:
		int x;
		a(int x): x(x) {}
		a(const a& obj): x(obj.x) {}
		~a()
		{std::cout<<"destructor "<<this<<std::endl;}
};

int main()
{
	/*
	Container<Context> all_contexts;
	{
		Handler::initHandler(SIGSEGV);
		Handler::initHandler(SIGABRT);

		all_contexts = Context::initContexts();
	}

	auto& context = all_contexts[0];

	auto& buffer = context.createBuffer(CL_MEM_READ_WRITE, sizeof(float));	

	auto& kernel = context.createKernel("./examples/add.cl", ""); 

	auto& queue = context.devices[0].createQueue(false);
	*/

	{
	a x1(1);
	a x2(2);
	a x3(3);


	Container<a> x({x1, x2, x3});

	for (size_t i=0; i<3; i++)
		std::cout<<x[i].x<<" ";
	std::cout<<std::endl;
	}



 	return 0;	
}
