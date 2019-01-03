#include"CL.h"
#include<iostream>
#define a (1<<0)
#define b (1<<1)
int main()
{
	int x[] = {a|b};
	std::cout<<x[0]<<std::endl;
	return 0;
}
