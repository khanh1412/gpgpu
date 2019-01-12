#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<csignal>
void handler(int signum)
{

}
int main()
{
	{
		auto h = Handler::initHandler(SIGSEGV);

		*(int*) nullptr = 0;

	}
 	return 0; 
	
}
