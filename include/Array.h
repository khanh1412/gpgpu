#ifndef _ARRAY_H_
#define _ARRAY_H_
#include<cstdlib>
template<class type>
class Array
{
	private:
		size_t count;
		type *ptr;

	private:
		inline void extend() {++count; ptr = (type*)std::realloc(ptr, count*sizeof(type));}
		inline void reduce() {--count; ptr = (type*)std::realloc(ptr, count*sizeof(type));}

	public:	
		Array(size_t count = 0): count(count) {ptr = (type*)std::malloc(count*sizeof(type));}
		Array(const Array& obj): count(obj.count) {ptr = (type*)std::malloc(count*sizeof(type)); for (size_t i=0; i<count; ++i) ptr[i] = obj.ptr[i];}
		Array& operator=(const Array& obj) {count = obj.count; std::free(ptr); ptr = (type*)std::malloc(count*sizeof(type)); for (size_t i=0; i<count; ++i) ptr[i] = obj.ptr[i]; return *this;}
		~Array() {clear();}

	public:	
		inline size_t size() const {return count;}
		inline type*  data() const {return ptr;}
		inline type& operator[](size_t i) const {return ptr[i];}
		inline void push_back(const type& obj) {extend(); data()[size()-1] = obj;}
		inline void pop_back() {reduce();}
		inline void clear() {count = 0; std::free(ptr);}
		inline bool empty() const {return (count == 0) ? true : false;}
};
#endif
