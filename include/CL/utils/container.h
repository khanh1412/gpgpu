#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include"CL/utils/array.h"
namespace cl {
//holder : support class used for initializaer_list of references
template<class obj_type>
class holder 
{
	public:
		const obj_type *ptr;
	public:
		holder(const obj_type& obj);
		~holder();
};
template<class obj_type>
class container
{
	public:
		array<obj_type*> arr;

	public:	
		container();
		container(const container<obj_type>& obj);
		container& operator=(const container<obj_type>& obj);
		virtual ~container();
		container(const std::initializer_list<holder<obj_type>>& list);

	public:	
		inline size_t size() const;
		inline obj_type& operator[](size_t i) const;
		inline void push_back(const obj_type* ptr);
		inline void pop_back();
		inline void clear(const obj_type& obj);
		inline void clear_all();
		inline void flush_back();
		inline void flush(const obj_type& obj);
		inline void flush_all();
		inline size_t find(const obj_type& obj) const;
};
template<class obj_type> holder<obj_type>::holder(const obj_type& obj)
	: ptr(&obj)
{}
template<class obj_type> holder<obj_type>::~holder()
{}
template<class obj_type> container<obj_type>::container()
	:arr()
{}
template<class obj_type> container<obj_type>::container(const container<obj_type>& obj)
{
	arr = obj.arr;
}
template<class obj_type> container<obj_type>& container<obj_type>::operator=(const container<obj_type>& obj)
{
	arr = obj.arr;
	return *this;
}
template<class obj_type> container<obj_type>::~container()
{
	clear_all();
}
template<class obj_type> container<obj_type>::container(const std::initializer_list<holder<obj_type>>& list)
	:arr(list.size())
{
	size_t i=0;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		arr[i] = (obj_type*)it->ptr;
		++i;
	}
}
template<class obj_type> inline size_t container<obj_type>::size() const
{
	return arr.size();
}
template<class obj_type> inline obj_type& container<obj_type>::operator[](size_t i) const
{
	return *arr[i];
}
template<class obj_type> inline void container<obj_type>::push_back(const obj_type* ptr)
{
	arr.push_back((obj_type*)ptr);
}
template<class obj_type> inline void container<obj_type>::pop_back()
{
	arr.pop_back();
}
template<class obj_type> inline void container<obj_type>::clear(const obj_type& obj)
{
	size_t i = find(obj);
	arr[i] = nullptr;
}
template<class obj_type> inline void container<obj_type>::clear_all()
{
	while (size() > 0) pop_back();
}
template<class obj_type> inline void container<obj_type>::flush_back()
{
	delete arr[size() - 1];
	arr.pop_back();
}
template<class obj_type> inline void container<obj_type>::flush(const obj_type& obj)
{
	size_t i = find(obj);
	delete arr[i];
	arr[i] = nullptr;
}
template<class obj_type> inline void container<obj_type>::flush_all()
{
	while (size() > 0)
		flush_back();
}
template<class obj_type> inline size_t container<obj_type>::find(const obj_type& obj) const
{
	return arr.find((obj_type*)&obj);
}
}
#endif
