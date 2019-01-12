#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<signal.h>
int main()
{
	{
		auto h0 = Handler::initHandler(SIGSEGV);
		*(int*) nullptr = 0;
	}
		*(int*) nullptr = 0;
 	return 0; 
	
}
