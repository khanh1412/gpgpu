#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_
template<class obj_type>
class Argument
{
	public:
		const obj_type *ptr;
	public:
		Argument(const obj_type& obj): ptr(&obj) {}
		~Argument(){}
};
#endif
