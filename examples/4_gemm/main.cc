#include<iostream>
#include<random>
#include<ctime>
#include<cstring>
template<class type>
class matrix
{
	public:
		static std::default_random_engine gen;
		size_t m, n;
		type *dataptr;
	public:
		matrix(size_t m, size_t n = 1)
			: m(m), n(n)
		{
			dataptr = (type*)std::malloc(m*n*sizeof(type));
		}
		matrix(const matrix<type>& M)
			: m(M.m), n(M.n)
		{
			dataptr = (type*)std::malloc(m*n*sizeof(type));
			std::memcpy(dataptr, M.dataptr, m*n*sizeof(type));
		}
		~matrix()
		{
			std::free(dataptr);
		}
		type& index(size_t i, size_t j) const
		{
			return dataptr[i*m + j];
		}
		void set(type value = 0)
		{
			for (size_t i=0; i<m*n; ++i)
				dataptr[i] = value;
		}
		void randomize()
		{
			std::normal_distribution<type> dist(0, 1);
			for (size_t i=0; i<m*n; ++i)
				dataptr[i] = dist(gen);
		}
		template<class objtype> friend std::ostream& operator<<(std::ostream& out, const matrix<objtype>& M);
};
template<> std::default_random_engine matrix<float>::gen(std::time(nullptr));
template<class objtype>
std::ostream& operator<<(std::ostream& out, const matrix<objtype>& M)
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
template<class type>
void HOST_GEMM(type alpha, type beta, const matrix<type>& A, const matrix<type>& B, const matrix<type>& C)
{
	for (size_t i=0; i<A.m; ++i)
	for (size_t k=0; k<B.n; ++k)
	{
		type c = 0;
		for (size_t j=0; j<A.n; ++j)
			c += alpha*A.index(i, j)*B.index(j, k);
		C.index(i, k) = c + beta*C.index(i, k);
	}
}
template<class type>
void CL_GEMM(type alpha, type beta, const matrix<type>& A, const matrix<type>& B, const matrix<type>& C)
{
	
}
int main()
{
	matrix<float> A(2, 2), B(2, 2), C(2, 2);
	A.randomize(); B.randomize(); C.randomize();
	std::cout<<A<<std::endl;
	std::cout<<B<<std::endl;
	std::cout<<C<<std::endl;
	HOST_GEMM(1.0f, 0.5f, A, B, C);
	std::cout<<C<<std::endl;
	return 0;
}
