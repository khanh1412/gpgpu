#include<cstdint>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<initializer_list>
#include<iostream>
#include<ctime>
#include<random>
#include<omp.h>
#include"opencl.h"
#include"GEMM.h"
class matrix
{
	public:
		uint64_t m;
		uint64_t n;
		float *data;
	public:
		matrix(uint64_t m, uint64_t n)
			: m(m), n(n)
		{
			data = (float*)std::malloc(m*n*sizeof(float));
			for (uint64_t i=0; i<m*n; ++i)
				data[i] = 0;
		}
		matrix(uint64_t m, uint64_t n, float *data)
			: m(m), n(n)
		{
			data = (float*)std::malloc(m*n*sizeof(float));
			std::memcpy(this->data, data, m*n*sizeof(float));
		}	
		matrix(const matrix& obj)
			: m(obj.m), n(obj.n)
		{
			data = (float*)std::malloc(m*n*sizeof(float));
			std::memcpy(data, obj.data, m*n*sizeof(float));
		}
		matrix& operator=(const matrix& obj)
		{
			m = obj.m;
			n = obj.n;
			std::free(data);
			data = (float*)std::malloc(m*n*sizeof(float));
			std::memcpy(data, obj.data, m*n*sizeof(float));
			return *this;
		}
		~matrix()
		{
			std::free(data);
		}
		matrix(const std::initializer_list<float>& list)
			: m(list.size()), n(1)
		{
			data = (float*)std::malloc(m*n*sizeof(float));
			uint64_t i=0;
			for (auto it=list.begin(); it != list.end(); ++it, ++i)
				data[i] = *it;
		}
	public:
		void randomize()
		{
			float size = 1/std::sqrt((float)((m>n) ? m : n));
			std::default_random_engine gen(std::time(nullptr));
			std::normal_distribution<float> dist(0, size);
			for (uint64_t i=0; i<m*n; ++i)
				data[i] = dist(gen);
		}
	public:
		matrix reshape(uint64_t i, uint64_t j) const
		{
			assert(i*j == m*n);
			matrix res(*this);
			res.m = i; res.n = j;
			return res;
		}
		float& index(uint64_t i, uint64_t j) const
		{
			return data[i*n + j];
		}
		size_t size() const
		{
			return m*n*sizeof(float);
		}
	public:
		static double GEMM(float alpha, float beta, const matrix& A, const matrix& B, matrix& C)
		{
			assert(A.n == B.m);
			assert(A.m == C.m);
			assert(B.n == C.n);

			double t1 = omp_get_wtime();
			#pragma omp parallel
			{
			#pragma omp for nowait
			for (uint64_t i=0; i<C.m; ++i)
			for (uint64_t j=0; j<C.n; ++j)
			for (uint64_t k=0; k<C.n; ++k)
			{
				C.index(i, j) += alpha * A.index(i, k) * B.index(k, j) + beta * C.index(i, j);
			}
			}
			double t2 = omp_get_wtime();
			return (t2-t1)*1e9;
		}
		friend std::ostream& operator<<(std::ostream& out, const matrix& obj);
		static float L2(const matrix& A, const matrix& B)
		{
			assert(A.m == B.m);
			assert(A.n == B.n);
			float sum = 0;
			for (uint64_t i=0; i<A.m; i++)
			for (uint64_t j=0; j<B.m; j++)
			{
				float diff = (A.index(i, j) - B.index(i, j));
				sum += diff*diff;
			}
			sum /= A.m*A.n;
			return sum;
		}
};
std::ostream& operator<<(std::ostream& out, const matrix& obj)
{
	out<<std::fixed;
	for (uint64_t i=0; i<obj.m; ++i)
	for (uint64_t j=0; j<obj.n; ++j)
	{
		if (obj.index(i, j) > 0) out<<"+";
		out<<obj.index(i, j)<<" ";
		if (j == obj.n-1) out<<std::endl;
	}
	out<<std::defaultfloat;
	return out;
}

//auto& context = Context::initContext("Portable");
auto& context = Context::initContext("CUDA");
//auto& context = Context::initContext("Intel");
auto& device = context.all_devices[0]; auto& queue = device.createQueue();

double gemm1(float alpha, float beta, const matrix& A, const matrix& B, const matrix& C)
{
	assert(A.n == B.m);
	assert(A.m == C.m);
	assert(B.n == C.n);
	auto& d_A = context.createBuffer(CL_MEM_READ_ONLY, A.size());
	auto& d_B = context.createBuffer(CL_MEM_READ_ONLY, B.size());
	auto& d_C = context.createBuffer(CL_MEM_READ_ONLY, C.size());

	uint64_t time = 0;
	{
		auto& w_A = queue.enqueueWriteBuffer(d_A, A.data, A.size());
		auto& w_B = queue.enqueueWriteBuffer(d_B, B.data, B.size());
		auto& w_C = queue.enqueueWriteBuffer(d_C, C.data, C.size());
		queue.enqueueBarrier({w_A, w_B, w_C});
		//SGEMM
		auto& k = GEMM<float>(queue, alpha, beta, d_A, d_B, d_C, C.m, C.n, A.n);
		//END SGEMM

		queue.enqueueBarrier({k});
		queue.enqueueReadBuffer(d_C, C.data, C.size());
		queue.join();
		time = k.profileEnd() - k.profileStart();
	}
	return double(time);
}

int main(int argc, char **argv)
{
	uint64_t COUNT = (argc < 2) ? 1 : std::stoi(argv[1]);

	matrix A(COUNT, COUNT);
	A.randomize();
	matrix B(COUNT, COUNT);
	B.randomize();
	matrix C1(COUNT, COUNT);
	matrix C2(COUNT, COUNT);
	double time1 = gemm1(1, 0, A, B, C1);
//	double time2 = matrix::GEMM(1, 0, A, B, C2);

	std::cout<<"O(n^2*log(n) + 3*n^2)"<<std::endl;
	std::cout<<"ocl performance: "<<(COUNT*COUNT*std::log(COUNT)/0.693 + 3*COUNT*COUNT)/time1<<" GFLOPS"<<std::endl;
	std::cout<<"theoretical ocl performance: "<<(COUNT*COUNT*COUNT)/time1<<" GFLOPS"<<std::endl;
//	std::cout<<"omp performance: "<<(COUNT*COUNT*COUNT)/time2<<" GFLOPS"<<std::endl;


	return 0;
}
