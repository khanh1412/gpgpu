#include<iostream>
#include"Context.h"

#include<ctime>

const uint64_t COUNT = 1936*1096;

void clCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto context = Context::initContext(0,0);

	auto ds = context.allocateBuffer(CL_MEM_WRITE_ONLY, COUNT*sizeof(float));
	auto da = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));
	auto db = context.allocateBuffer(CL_MEM_READ_ONLY , COUNT*sizeof(float));

	auto queue = context.createQueue();
	auto add = context.compileKernel("kernels/add.cl.c", "add");
	auto mul = context.compileKernel("kernels/mul.cl.c", "mul");
	auto sub = context.compileKernel("kernels/sub.cl.c", "sub");
	auto div = context.compileKernel("kernels/div.cl.c", "div");


	auto t1 = std::clock();
	queue.writeBuffer(da, COUNT*sizeof(float), a);
	queue.writeBuffer(db, COUNT*sizeof(float), b);
	queue.executeKernel(add, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(mul, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(sub, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.executeKernel(div, {COUNT, 1, 1}, {1,1,1}, {ds, da, db});
	queue.readBuffer(ds, COUNT*sizeof(float), s);
	queue.synchronize();
	auto t2 = std::clock();
	std::cout<<"CL time: "<<t2-t1<<" ticks"<<std::endl;
}

void add(float *s, float *a, float *b, uint64_t COUNT)
{
	for (uint64_t i = 0; i<COUNT; i++)
		s[i] = a[i] + b[i];
}	
void sub(float *s, float *a, float *b, uint64_t COUNT)
{
	for (uint64_t i = 0; i<COUNT; i++)
		s[i] = a[i] - b[i];
}	
void mul(float *s, float *a, float *b, uint64_t COUNT)
{
	for (uint64_t i = 0; i<COUNT; i++)
		s[i] = a[i] * b[i];
}	
void div(float *s, float *a, float *b, uint64_t COUNT)
{
	for (uint64_t i = 0; i<COUNT; i++)
		s[i] = a[i] / b[i];
}	

void nativeCAL(float *s, float *a, float *b, uint64_t COUNT)
{
	auto t1 = std::clock();
	add(s, a, b, COUNT);
	mul(s, a, b, COUNT);
	sub(s, a, b, COUNT);
	div(s, a, b, COUNT);
	auto t2 = std::clock();
	std::cout<<"native time: "<<t2-t1<<" ticks"<<std::endl;
}


int main()
{
	auto a = new float[COUNT];
	auto b = new float[COUNT];
	auto s = new float[COUNT];

	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(i);
		b[i] = static_cast<float>(COUNT - i);
		s[i] = 0;
	}
	/*
	std::cout<<"a = "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;

	std::cout<<"b = "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<b[i]<<" ";
	std::cout<<std::endl;
	*/

	clCAL(s, a, b, COUNT);

	/*

	std::cout<<"CL : s = a + b "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<s[i]<<" ";
	std::cout<<std::endl;
	*/
	nativeCAL(s, a, b, COUNT);
	/*
	std::cout<<"Native : s = a + b "<<std::endl<<"\t";
	for (uint64_t i=0; i<COUNT; i++)
		std::cout<<s[i]<<" ";
	std::cout<<std::endl;
	*/
	return 0;


}
