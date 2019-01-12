#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<thread>
void func()
{
	while (true)
	*(int*) 0 = 0;
}

int main()
{
	{
		auto h0 = Handler::initHandler(SIGABRT);
		auto h1 = Handler::initHandler(SIGSEGV);
		std::thread(func).detach();
		while (true) std::cout<<signal_status<<std::endl;
	}
 	return 0;	
}
