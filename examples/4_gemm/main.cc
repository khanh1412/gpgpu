#include<iostream>
#include<random>
#include<ctime>
#include<cstring>
#include"CL/opencl.h"
#include"CL/builtin/gemm.h"
#include<omp.h>
std::default_random_engine gen(std::time(nullptr));
std::normal_distribution<float> dist(0, 1);
class matrix
{
	public:
		size_t m, n;
		float *data;
	public:
		matrix(size_t m, size_t n = 1)
			: m(m), n(n)
		{
			data = (float*)std::malloc(m*n*sizeof(float));
		}
		matrix(const matrix& M)
			: m(M.m), n(M.n)
		{
			data = (float*)std::malloc(m*n*sizeof(float));
			std::memcpy(data, M.data, m*n*sizeof(float));
		}
		~matrix()
		{
			std::free(data);
		}
		float& index(size_t i, size_t j) const
		{
			return data[i*m + j];
		}
		void set(float value = 0)
		{
			for (size_t i=0; i<m*n; ++i)
				data[i] = value;
		}
		void randomize()
		{
			for (size_t i=0; i<m*n; ++i)
				data[i] = dist(gen);
		}
		friend std::ostream& operator<<(std::ostream& out, const matrix& M);
};
std::ostream& operator<<(std::ostream& out, const matrix& M)
{
	out<<std::fixed;
	for (size_t i=0; i<M.m; ++i)
	{
		for (size_t j=0; j<M.n; ++j)
			out<<M.index(i, j)<<" ";
		out<<"\n";
	}
	out<<std::defaultfloat;
	return out;
}
double HOST_GEMM(float alpha, float beta, const matrix& A, const matrix& B, const matrix& C)
{
	auto t1 = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for nowait
		for (size_t i=0; i<A.m; ++i)
		for (size_t k=0; k<B.n; ++k)
		{
			float c = 0;
			for (size_t j=0; j<A.n; ++j)
				c += A.index(i, j)*B.index(j, k);
			C.index(i, k) = alpha*c + beta*C.index(i, k);
		}
	}
	auto t2 = omp_get_wtime();
	return (t2-t1)*1e9;
}
auto device = cl::device::get_all_devices()[1];
auto context = cl::context({device});
auto queue = cl::queue(context, device);
double CL_GEMM(float alpha, float beta, const matrix& A, const matrix& B, const matrix& C)
{
	double time = 0;
	auto bA = cl::buffer(context, CL_MEM_READ_ONLY, A.m*A.n*sizeof(float));
	auto bB = cl::buffer(context, CL_MEM_READ_ONLY, B.m*B.n*sizeof(float));
	auto bC = cl::buffer(context, CL_MEM_READ_WRITE, C.m*C.n*sizeof(float));
	{
		auto wA = queue.enqueueWriteBuffer(bA, A.data, A.m*A.n*sizeof(float));
		auto wB = queue.enqueueWriteBuffer(bB, B.data, B.m*B.n*sizeof(float));
		auto wC = queue.enqueueWriteBuffer(bC, C.data, C.m*C.n*sizeof(float));
		queue.enqueueBarrier({wA, wB, wC});
		auto k = cl::builtin::gemm(queue, A.m, A.n, B.n, alpha, beta, bA, bB, bC);
		queue.enqueueBarrier({k});
		auto rC = queue.enqueueReadBuffer(bC, C.data, C.m*C.n*sizeof(float));
		queue.join();
		time = k.profileEnd() - k.profileStart();
	}
	return time;
}
int main(int argc, char **argv)
{
	size_t size = (argc >= 2) ? std::stoi(argv[1]) : 1;
	/*
	size_t hfo = (3+size)*size*size;
	std::cout<<"host floating pointer operations: "<<hfo<<std::endl;
	{
		matrix A(size, size); A.randomize();
		matrix B(size, size); B.randomize();
		matrix C(size, size); C.randomize();
		double time = HOST_GEMM(dist(gen), dist(gen), A, B, C);
		std::cout<<"time: "<<time<<std::endl;
		std::cout<<"gflops: "<<hfo/time<<std::endl;
	}
	*/
	size_t dfo = (3+std::log(size)/std::log(2))*size*size;
	std::cout<<"device floating pointer operations: "<<dfo<<std::endl;
	{
		matrix A(size, size); A.randomize();
		matrix B(size, size); B.randomize();
		matrix C(size, size); C.randomize();
		double time = CL_GEMM(dist(gen), dist(gen), A, B, C);
		std::cout<<"time: "<<time<<std::endl;
		std::cout<<"gflops: "<<dfo/time<<std::endl;
	}

	return 0;
}
