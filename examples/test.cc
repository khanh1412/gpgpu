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
		auto h1 = Handler::initHandler(SIGSEGV);
		std::thread t(func); t.detach();
		h1.wait();
		std::cout<<"Done!"<<std::endl;
	}
 	return 0;	
}
