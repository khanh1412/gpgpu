#include"cl.hpp"
#include<iostream>
int main()
{
	cl::Context::initContexts();
	std::cout<<"Done"<<std::endl;
	return 0;
}
