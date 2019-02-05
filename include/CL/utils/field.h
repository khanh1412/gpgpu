#ifndef _FIELD_H_
#define _FIELD_H_
#include<stdexcept>
namespace cl {
class field
{
	public:
		field(){}
		field(const field& obj)
		{
			throw std::runtime_error("a child class of field did not implement copy constructor!");
		}
		~field(){}
};
}
#endif
