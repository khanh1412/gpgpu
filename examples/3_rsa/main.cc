#include"CL/opencl.h"
#include"keypair.h"
#include<cstdint>
#include<vector>
#include<thread>
#include<gmpxx.h>
#include<omp.h>
#include<fstream>
const size_t pubkey = 31;
int_t factorization(const int_t& modulo)
{
	int_t p = 2;
	int64_t modulo64 = modulo.get_ui();
	int64_t i;
	for (i = 3; i < modulo64; i += 2)
		if (modulo64 % i ==0)
			p = i;
	return p;
}
key crack(const key& pub)
{
	const int_t& modulo = pub.modulo;
	const int_t& pubkey = pub.value;

	if (modulo % 2 == 0)
	{
		keypair pair(2-1, modulo/2-1, pubkey);
		return pair.pri;
	}
	else
	{
		int_t sqrt_modulo = sqrt(modulo);
		
		int_t p = factorization(modulo);

		keypair pair(p-1, modulo/p-1, pubkey);
		return pair.pri;
	}
}
int_t omp_factorization(const int_t& modulo)
{
	int_t p = 2;
	int64_t modulo64 = modulo.get_ui();
	int threads = 4;
	omp_set_num_threads(threads);
	int64_t i;
	#pragma omp parallel
	{
	#pragma omp for nowait
	for (i = 3; i < modulo64; i += 2)
		if (modulo64 % i ==0)
			p = i;
	}
	return p;
}
key omp_crack(const key& pub)
{
	const int_t& modulo = pub.modulo;
	const int_t& pubkey = pub.value;

	if (modulo % 2 == 0)
	{
		keypair pair(2-1, modulo/2-1, pubkey);
		return pair.pri;
	}
	else
	{
		int_t sqrt_modulo = sqrt(modulo);
		
		int_t p = omp_factorization(modulo);

		keypair pair(p-1, modulo/p-1, pubkey);
		return pair.pri;
	}
}

//SET UP
inline std::string read_file(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
	return content;
}
auto device = cl::device::get_all_devices()[0];
auto context = cl::context({device});
auto queue = cl::queue(context, device);
auto kernel = cl::kernel(context, device, {read_file("examples/3_rsa/factorization.cl.c")}, "-cl-std=CL1.1");
auto factor = cl::buffer(context, CL_MEM_WRITE_ONLY, sizeof(uint64_t));
int_t cl_factorization(const int_t& modulo)
{
	//CL CALL
	std::cout<<"USING DEVICE: "<<device.name()<<std::endl;
	uint64_t factor64;
	uint64_t modulo64 = modulo.get_ui();
	int_t global_dim = ((sqrt(modulo)-1)/2);
	uint64_t global_dim64 = global_dim.get_ui();
	{
		auto k = queue.enqueueNDRangeKernel(kernel, {factor, modulo64}, {global_dim64});
		queue.enqueueBarrier({k});
		auto w = queue.enqueueReadBuffer(factor, &factor64, sizeof(uint64_t));
	}
	queue.join();
	std::cout<<"one of the factors = "<<factor64<<std::endl;
	return int_t(factor64);
}
key cl_crack(const key& pub)
{
	const int_t& modulo = pub.modulo;
	const int_t& pubkey = pub.value;

	if (modulo % 2 == 0)
	{
		keypair pair(2-1, modulo/2-1, pubkey);
		return pair.pri;
	}
	else
	{
		int_t sqrt_modulo = sqrt(modulo);
		
		int_t p = cl_factorization(modulo);

		keypair pair(p-1, modulo/p-1, pubkey);
		return pair.pri;
	}
}

int main(int argc, char **argv)
{
	int_t bit_length = (argc < 2) ? 8 : std::stoi(argv[1]);

	gmp_randclass randomizer(gmp_randinit_default);
	randomizer.seed(std::time(nullptr));
	int_t seed = randomizer.get_z_bits((bit_length-1)/2);

	keypair pair(seed, seed/2, pubkey);

	std::cout<<"bit length: "<<mpz_sizeinbase(pair.pub.modulo.get_mpz_t(), 2)<<std::endl;
	std::cout<<pair<<std::endl;

	std::cout<<"brute-force loop: "<<((sqrt(pair.pub.modulo)-1)/2)<<std::endl;
	{
		auto t1 = omp_get_wtime();
		std::cout<<"cracked "<<cl_crack(pair.pub)<<std::endl;
		auto t2 = omp_get_wtime();
		std::cout<<"OCL Time: "<<(t2-t1)<<" sec"<<std::endl;
	}
	{
		auto t1 = omp_get_wtime();
		std::cout<<"cracked "<<omp_crack(pair.pub)<<std::endl;
		auto t2 = omp_get_wtime();
		std::cout<<"OMP Time: "<<(t2-t1)<<" sec"<<std::endl;
	}
	/*
	{
		auto t1 = omp_get_wtime();
		std::cout<<"cracked "<<crack(pair.pub)<<std::endl;
		auto t2 = omp_get_wtime();
		std::cout<<"Single thread Time: "<<(t2-t1)<<" sec"<<std::endl;
	}
	*/
	return 0;
}
