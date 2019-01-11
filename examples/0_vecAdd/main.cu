#include<iostream>
#include<cstdlib>
#include<ctime>

__global__ void add(float *s, float *a, float *b)
{
	uint64_t i = blockIdx.x;
	s[i] = a[i] + b[i];
}

const uint64_t COUNT = 10000000;
void ADD(float *s, float *a, float *b, uint64_t COUNT)
{

	float *ds; cudaMalloc(&ds, COUNT*sizeof(float));
	float *da; cudaMalloc(&da, COUNT*sizeof(float));
	float *db; cudaMalloc(&db, COUNT*sizeof(float));

	cudaStream_t queue; cudaStreamCreate(&queue);
	{
	auto t1 = std::clock();

	cudaMemcpyAsync(da, a, COUNT*sizeof(float), cudaMemcpyHostToDevice, queue);
	cudaMemcpyAsync(db, b, COUNT*sizeof(float), cudaMemcpyHostToDevice, queue);
	dim3 global_dim(COUNT, 1, 1);
	dim3 local_dim(1, 1, 1);
	add<<<global_dim, local_dim>>>(ds, da, db);
	cudaMemcpyAsync(s, ds, COUNT*sizeof(float), cudaMemcpyDeviceToHost, queue);
	cudaStreamSynchronize(queue);
	auto t2 = std::clock();
	std::cout<<"Total time: "<<(t2-t1)<<" ticks"<<std::endl;
	}
}
void print_array(float *a)
{
	for (uint64_t i=0; i<10; i++)
		std::cout<<a[i]<<"\t";
	std::cout<<"..."<<std::endl;
}
int main()
{
std::srand(std::time(nullptr));
	auto a = new float[COUNT];
	auto b = new float[COUNT];
	auto s = new float[COUNT];

	for (uint64_t i=0; i<COUNT; i++)
	{
		a[i] = static_cast<float>(std::rand()%10)/10;
		b[i] = static_cast<float>(std::rand()%10)/10;
		s[i] = 0;
	}
	ADD(s, a, b, COUNT);
	print_array(a);
	print_array(b);
	print_array(s);
	return 0;


}
