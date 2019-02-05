#include"all.h"
#include<iostream>
int main()
{
	cl::array<float> arr1({1,2,3,4});
	cl::container<float> arr2({1,2,3,4});
	cl_assert(CL_SUCCESS);
	cl_assert(CL_INVALID_VALUE);
	return 0;
}
