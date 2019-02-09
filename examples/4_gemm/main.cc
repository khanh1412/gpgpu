#include<iostream>
#include<random>
#include<ctime>
template<class type>
class matrix
{
	public:
		std::default_random_engine gen;
		size_t m, n;
		type *data;
		matrix(size_t m, size_t n = 1)
			:gen(std::time(nullptr)), m(m), n(n)
		{
			data = (type*)std::malloc(m*n*sizeof(type));
		}
		~matrix()
		{
			std::free(data);
		}
		type& index(size_t i, size_t j) const
		{
			return data[i*m + j];
		}
		void set(type value = 0)
		{
			for (size_t i=0; i<m*n; ++i)
				data[i] = value;
		}
		void randomize()
		{
			std::normal_distribution<type> dist(0, 1);
			for (size_t i=0; i<m*n; ++i)
				data[i] = dist(gen);
		}
		template<class objtype> friend std::ostream& operator<<(std::ostream& out, const matrix<objtype>& M);
};
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
int main()
{
	matrix<float> M(2, 3);
	M.randomize();
	std::cout<<M<<std::endl;
	return 0;
}
