#include<cstdint>
#include<string>
#include<iostream>
/* This code is written base on the algorithm sited in 
 * https://www.codeproject.com/articles/380399/permutations-with-cuda-and-opencl
 * */
int64_t fac(int8_t count)
{
	int64_t perms = 1;
	for (int8_t i=2; i<=count; i++) perms *= i;
	return perms;
}
int8_t index(int8_t *source, int8_t count, int8_t pos)
{
	int8_t i; ++pos;
	for (i = 0; i < count; ++i)
	{
		if (source[i] >= 0)
			--pos;
		if (0 == pos)
			return i;
	}
	return -1;
}
int8_t findj(int8_t i, int64_t& value)
{
	int8_t j;
	for (j = i; j>=0; --j)
		if (j*fac(i) <= value) 
		{
			value = value - j*fac(i);
			return j;
		}
	return -1;
}

void permute(int8_t *data, int8_t count, int64_t value)
{
	int8_t *source = new int8_t[count];
	for (int8_t i=0; i<count; ++i) source[i] = i;
	
	//STUFF
	int8_t i = count - 1; //i+1 is number of remaining numbers in source;
	for (i = count - 1; i >= 0; --i)
	{
		int8_t j = findj(i, value); //find maximum j that j*fac(i) <= value and update value;
		data[count-i-1] = source[index(source, count, j)]; //push number at position j in source;
		source[index(source, count, j)] = -1; //remove that number from source;
	}

	//END STUFF	

	delete[] source;
}
#include<ctime>
int main(int argc, char *argv[])
{
	int8_t count = (argc != 2) ? 2 : std::stoi(argv[1]);
	int64_t num_threads = fac(count);

	int8_t *data = new int8_t[count];

	auto t1 = std::clock();
	for (int64_t value=0; value<num_threads; ++value)
	{
		permute(data, count, value);
//		std::cout<<value<<": "; for (int8_t i=0; i<count; i++) std::cout<<(int)data[i]<<" "; std::cout<<std::endl;
	}
	auto t2 = std::clock();
	std::cout<<"count  : "<<(int)count<<std::endl;
	std::cout<<"threads: "<<num_threads<<std::endl;
	std::cout<<"avg time   : "<<(1000*(t2-t1)/CLOCKS_PER_SEC)/num_threads<<" millisec"<<std::endl;
	delete[] data;
	return 0;
}


