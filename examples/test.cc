#include"Context.h"
#include<iostream>
#include"Handler.h"
int main()
{
	{
		auto h1 = Handler::initHandler(SIGABRT);
		auto h2 = Handler::initHandler(SIGSEGV);

		*(int*) 0 = 0;
	}
 	return 0;	
}
