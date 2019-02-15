#include"CL/opencl.h"
#include<iostream>
class vector
{
	public:
	int x;
	int y;
	vector(int x, int y): x(x), y(y) {}
	~vector(){std::cout<<"destructor is called!\n";}
};
std::ostream& operator<<(std::ostream& out, const vector& v)
{
	out<<"("<<v.x<<", "<<v.y<<")";
	return out;
}
int main(int argc, char **argv)
{
{
	auto c = cl::container<vector>();
	c.push_back(new vector(1,2));
	c.push_back(new vector(3,4));
	for (auto& i : c)
	{
		std::cout<<i<<std::endl;
	}
	auto it = c.begin();
	++it;
	std::cout<<*it<<std::endl;
	--it;
	std::cout<<*it<<std::endl;
	it++;
	std::cout<<*it<<std::endl;
	it--;
	std::cout<<*it<<std::endl;
	it += 1;
	std::cout<<*it<<std::endl;
	it -= 1;
	std::cout<<*it<<std::endl;
}
	return 0;
}
