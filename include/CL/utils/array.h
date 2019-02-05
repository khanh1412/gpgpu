#ifndef _ARRAY_H_
#define _ARRAY_H_
#include<cstdlib>
#include<cstring>
#include<initializer_list>
namespace cl {
template<class type>
class array
{
	private:
		size_t count;
		type *ptr;
	private:
		inline void extend();
		inline void reduce();

	public:	
		array(size_t count = 0);
		array(const array& obj);
		array& operator=(const array& obj);
		~array();
		array(const char *cstr);
		array(const std::initializer_list<type>& list);

	public:	
		inline size_t size() const;
		inline type*  data() const;
		inline type& operator[](size_t i) const;
		inline void push_back(const type& obj);
		inline void pop_back();
		inline void clear();
		inline size_t find(const type& obj) const;
		inline size_t find(const array<type>& obj) const;
};

template<class type> inline void array<type>::extend()
{
	++count;
	ptr = (type*)std::realloc(ptr, count*sizeof(type));
}
template<class type> inline void array<type>::reduce()
{
	--count;
	ptr = (type*)std::realloc(ptr, count*sizeof(type));
}
template<class type> array<type>::array(size_t count)
	: count(count)
{
	ptr = (type*)std::malloc(count*sizeof(type));
}
template<class type> array<type>::array(const array& obj)
	: count(obj.count)
{
	ptr = (type*)std::malloc(count*sizeof(type));
	std::memcpy(ptr, obj.ptr, count*sizeof(type));
}
template<class type> array<type>& array<type>::operator=(const array& obj)
{
	count = obj.count;
	std::free(ptr);
	ptr = (type*)std::malloc(count*sizeof(type));
	std::memcpy(ptr, obj.ptr, count*sizeof(type));
	return *this;
}
template<class type> array<type>::~array()
{
	clear();
}
template<class type> array<type>::array(const char *cstr)
{
	size_t size = std::strlen(cstr);
	count = 1 + (size-1)/sizeof(type);
	ptr = (type*)std::malloc(count*sizeof(type));
	std::memcpy(ptr, cstr, count*sizeof(type));
}
template<class type> array<type>::array(const std::initializer_list<type>& list): count(list.size())
{
	ptr = (type*)std::malloc(count*sizeof(type));
	size_t i=0;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		ptr[i] = *it;
		++i;
	}
}

template<class type> inline size_t array<type>::size() const
{
	return count;
}
template<class type> inline type*  array<type>::data() const
{
	return ptr;
}
template<class type> inline type& array<type>::operator[](size_t i) const
{
	return ptr[i];
}
template<class type> inline void array<type>::push_back(const type& obj)
{
	extend();
	data()[size()-1] = obj;
}
template<class type> inline void array<type>::pop_back()
{
	reduce();
}
template<class type> inline void array<type>::clear()
{
	count = 0;
	std::free(ptr);
}
template<class type> inline size_t array<type>::find(const type& obj) const
{
	for (size_t i=0; i<count; ++i)
		if (obj == ptr[i])
			return i;
	return -1;
}
template<class type> inline size_t array<type>::find(const array<type>& obj) const
{
	if (count < obj.count) return -1;
	for (size_t i=0; i<count-obj.count; i++)
	{
		bool found = true;
		for (size_t j=0; j<obj.count; j++)
		{
			if (ptr[i+j] != obj.ptr[j])
			{
				found = false;
				break;
			}
		}
		if (found) return i;
	}
	return -1;
}
}
#endif
