#include<iostream>
#include"CL.h"

const uint64_t COUNT = 10;

void REDUCE_SUM(float *s, float *a, uint64_t COUNT)
{
	auto context = CL::Context::initContext(1,0);

	auto da = context.createBuffer(CL_MEM_READ_WRITE , COUNT*sizeof(float));

	auto q = context.createQueue();
	auto k = context.createKernel("./examples/3_reduce_sum/sum.cl.c", "sum", "-cl-std=CL1.2");

	auto write = q.enqueueWriteBuffer(da, a, COUNT*sizeof(float));
	auto barrier1 = q.enqueueBarrier({write});
	auto kernel = q.enqueueNDRangeKernel(k, {da}, {COUNT, 1, 1}, {256,1,1});
	auto barrier2 = q.enqueueBarrier({kernel});
	auto read = q.enqueueReadBuffer(da, s, 1*sizeof(float));
	auto barrier3 = q.enqueueBarrier({read});
	barrier3.wait();

	q.synchronize();
}
void print_array(float *a)
{
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}
int main()
{
	auto a = new float[COUNT];
	auto s = new float[1]; s[0] = 0;

	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(i);
	}
	print_array(a);
	REDUCE_SUM(s, a, COUNT);
	std::cout<<"SUM: "<<s[0]<<std::endl;
	return 0;


}
