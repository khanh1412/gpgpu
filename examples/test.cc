#include"Context.h"
#include<iostream>
#include"Handler.h"
void func()
{
	*(int*) 0 = 0;
}

int main()
{
	{
		auto h = Handler::initHandler(SIGSEGV);
		func();
	}
		
 	return 0;	
}
