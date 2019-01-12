#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<thread>
#include<chrono>
void func()
{
		*(int*) 0 = 0;
}
int main()
{
	{
		Handler::initHandler(SIGTERM);
		Handler::initHandler(SIGSEGV);
		Handler::initHandler(SIGINT);
		Handler::initHandler(SIGILL);
		Handler::initHandler(SIGABRT);
		Handler::initHandler(SIGFPE);

		func();

	}
 	return 0;	
}
