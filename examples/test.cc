#include"all.h"
#include<iostream>
int main()
{
	cl::array<float> arr1({1,2,3,4});
	cl::container<float> arr2({1,2,3,4});
	throw cl::error(CL_SUCCESS, __LINE__, __FILE__);
	return 0;
}
