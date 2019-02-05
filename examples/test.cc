#include"all.h"
int main()
{
	cl::array<float> arr1({1,2,3,4});
	cl::container<float> arr2({1,2,3,4});
	cl::assert(__LINE__, __FILE__, CL_SUCCESS);
	cl::assert(__LINE__, __FILE__, CL_INVALID_VALUE);
	return 0;
}
