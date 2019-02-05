#include<random>
#include<iostream>
#include<ctime>
#include<cstdint>
#include<vector>
template<class type>
class array
{
	public:
		type *data;
		size_t count;
		array(size_t count): count(count)
		{
			data = (type*)std::malloc(count*sizeof(type));
		}
		~array()
		{
			free(data);
		}
};

const float eps = 0.00001;
static void heapPermutation(uint8_t *perm, uint64_t *count, uint8_t *a, uint8_t size, uint8_t n)
{
	if (1 == size)
		for (uint8_t i=0; i<n; ++i)
		{
			perm[*count] = a[i];
			++*count;
		}
	else
		for (uint8_t i=0; i<size; ++i)
		{
			heapPermutation(perm, count, a, size-1, n);
			
			uint8_t *x1 = a + ((size%2==1) ? 0 : i);
			uint8_t *x2 = a + size - 1;
			uint8_t temp = *x1;
			*x1 = *x2;
			*x2 = temp;
		}
}

void Permutation(uint8_t *perm, uint8_t size)
{
//	auto a = new uint8_t[size];
	array<uint8_t> _a(size); auto a = _a.data;

	for (uint8_t i=0; i<size; ++i) a[i] = i;

	uint64_t count = 0;
	heapPermutation(perm, &count, a, size, size);

//	delete a;
}
void randomizer(float *arr, uint64_t size)
{
        std::uniform_real_distribution<float> dist(0, 1);
	std::default_random_engine gen;
	gen.seed(std::time(nullptr));

	for (uint64_t i=0; i<size*size; i++)
		arr[i] = dist(gen);
}
uint64_t hm_permutations(uint8_t size)
{
	uint64_t permutations = 1;
	for (uint8_t i=2; i<=size; ++i)
		permutations *= i;
	return permutations;
}

uint64_t host_call(float *result, const float *arr, uint8_t size, const uint8_t *perm)
{
	auto t1 = std::clock();
	const uint64_t num_threads = hm_permutations(size);
	#pragma omp parallel
	{
	#pragma omp for nowait
	for (uint64_t global_id=0; global_id<num_threads; global_id++)
	{
		uint64_t perm_addon = global_id*size;
	
		float cost = 0;
		uint8_t lastp, currp;
	
		for (uint8_t i=0; i < size-1; i++)
		{	
			lastp = perm[perm_addon + i];
			currp = perm[perm_addon + i+1];
			cost += arr[lastp*size + currp];
		}
		lastp = perm[perm_addon + size-1];
		currp = perm[perm_addon + 0];
		cost += arr[lastp*size + currp];
		result[global_id] = cost;
	}
	}
	auto t2 = std::clock();
	return (1000000*(t2-t1))/CLOCKS_PER_SEC;

}
uint64_t cu_call(float *result, const float *arr, const uint8_t size, const uint8_t *perm);
uint64_t cl_call(float *result, const float *arr, const uint8_t size, const uint8_t *perm);

int main(int argc, char *argv[])
{
	uint8_t size = (argc == 1) ? 2 : std::stoi(argv[1]);
	uint64_t num_threads = hm_permutations(size);
//	float *arr = new float[size*size];
	array<float> _arr(size*size); auto arr = _arr.data;

	randomizer(arr, size);

//	uint8_t *perm = new uint8_t[size*num_threads];
	array<uint8_t> _perm(size*num_threads); auto perm = _perm.data;

	auto t1 = std::clock();
	std::cout<<"permutation started!"<<std::endl;
	Permutation(perm, size);
	std::cout<<"permutation done!"<<std::endl;
	auto t2 = std::clock();
	std::cout<<"permutation time: "<<1000*static_cast<float>(t2-t1)/CLOCKS_PER_SEC<<" (millisec)"<<std::endl;

//	float *result1 = new float[num_threads];
	array<float> _result1(num_threads); auto result1 = _result1.data;

	for (uint64_t i=0; i<num_threads; ++i) result1[i] = 0;
//	float *result2 = new float[num_threads];
	array<float> _result2(num_threads); auto result2 = _result2.data;

	for (uint64_t i=0; i<num_threads; ++i) result2[i] = 0;

	uint64_t host_time = host_call(result1, arr, size, perm);
#ifdef CL
	uint64_t device_time = cl_call(result2, arr, size, perm);
#else
	uint64_t device_time = cu_call(result2, arr, size, perm);
#endif
	
	std::cout<<"TSP of "<<(int)size<<" vertices, "<<num_threads<<" threads (vertices!)"<<std::endl;
	std::cout<<"cpu    time = "<<host_time<<" (millisec)"<<std::endl;
	std::cout<<"device time = "<<device_time<<" (millisec)"<<std::endl;

	uint64_t pass = 0;
	for (uint64_t i=0; i<num_threads; ++i)
		if ((result1[i] - result2[i]) < +eps and (result1[i] - result2[i]) > -eps)
			++pass;
	std::cout<<"passed threads: "<<pass<<"/"<<num_threads<<std::endl;

	for (uint64_t i=0; i<5; ++i)
		std::cout<<result1[i]<<" ";
	std::cout<<"..."<<std::endl;
	for (uint64_t i=0; i<5; ++i)
		std::cout<<result2[i]<<" ";
	std::cout<<"..."<<std::endl;
}	
