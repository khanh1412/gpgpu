#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include"Array.h"
template<class obj_type>
class Container
{
	private:
		Array<obj_type*> array;

	public:	
		Container(): array(0) {}
		Container(const Container<obj_type>& obj) {array = obj.array;}
		Container& operator=(const Container<obj_type>& obj) {array = obj.array; return *this;}
		~Container() {clear();}

	public:	
		inline size_t size() const {return array.size();}
		inline obj_type& operator[](size_t i) const {return *array[i];}
		inline void push_back(const obj_type* ptr) {array.push_back((obj_type*)ptr);}
		inline void pop_back() {array.pop_back();}
		inline void clear() {while (not empty()) pop_back();}
		inline void flush_back() {delete array[size() - 1]; array.pop_back();}
		inline void flush() {while (not empty()) flush_back();}
		inline bool empty() const {return array.empty();}
};
#endif
