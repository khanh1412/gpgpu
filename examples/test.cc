#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<thread>
int main()
{
	{
		auto h = Handler::initHandler(SIGSEGV);

		std::thread t(&Handler::wait, &h);

		*(int*) nullptr = 0;
		t.join();
	}
//		*(int*) nullptr = 0;
 	return 0; 
	
}
