#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<thread>
int main()
{
	{
	auto h = Handler::initHandler();
	int *x = 0;
	int y = *x;
	}
	{
	auto h = Handler::initHandler();
	int *x = 0;
	int y = *x;
	}
 	return 0; 
	
}
