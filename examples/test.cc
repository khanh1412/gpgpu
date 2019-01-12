#include"Context.h"
#include<iostream>
#include"Handler.h"
#include<thread>
int main()
{
	enable_handler();
		int *x = 0;
		int y = *x;
	disable_handler();
 	return 0; 
	
}
