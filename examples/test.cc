#include"all.h"
int main()
{
	cl::array<float> arr1({1,2,3,4});
	cl::container<float> arr2({1,2,3,4});
	assert(CL_SUCCESS);
	assert(CL_INVALID_VALUE);
	return 0;
}
