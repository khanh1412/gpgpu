#include<cstdint>
#include<string>
#include<iostream>

/* This code is written base on generate algorithm 
 * */
static void generate(int8_t *it, int8_t *arr, int8_t count)
{
	auto buffer = new int8_t[count];
	for (int8_t c=0; c<count; ++c) buffer[c] = 0;

	for (int8_t c=0; c<count; ++c, ++it) *it = arr[c];

	for (int8_t i=0; i<count; )
	{
		if (buffer[i] < i)
		{
			if (i%2 == 0)
				std::swap(arr[0], arr[i]);
			else
				std::swap(arr[buffer[i]], arr[i]);

			for (int8_t c=0; c<count; ++c, ++it) *it = arr[c];
			++buffer[i];
			i = 0;
		}
		else
		{
			buffer[i] = 0;
			++i;
		}
	}
}
void permutation(int8_t *data, int8_t size)
{
	auto a = new int8_t[size];

	for (int8_t i=0; i<size; ++i) a[i] = i;

	generate(data, a, size);

	delete a;
}
int64_t fac(int8_t count)
{
	int64_t f = 1;
	for (int8_t i=2; i<=count; ++i) f *= i;
	return f;
}
#include<ctime>
int main(int argc, char *argv[])
{
	int8_t count = (argc != 2) ? 2 : std::stoi(argv[1]);
	int64_t num_threads = fac(count);

	int8_t *data = new int8_t[count*num_threads];

	auto t1 = std::clock();
	permutation(data, count);
	auto t2 = std::clock();
	std::cout<<"count  : "<<(int)count<<std::endl;
	std::cout<<"threads: "<<num_threads<<std::endl;
	std::cout<<"avg time   : "<<(1000*(t2-t1)/CLOCKS_PER_SEC)/2<<" millisec"<<std::endl;
	/*
	for (int64_t i=0; i<count*num_threads; ++i)
	{
		if (i%count == 0) std::cout<<(i/count)<<": ";
		std::cout<<(int)data[i]<<" ";
		if ((1+i)%count == 0) std::cout<<std::endl;
	}
	*/
	delete data;
	return 0;
}
