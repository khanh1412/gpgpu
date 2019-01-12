#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<csignal>
int main()
{
	{
		auto h = Handler::initHandler(SIGSEGV);
		*(int*) nullptr = 0;
	}
		*(int*) nullptr = 0;
 	return 0; 
	
}
