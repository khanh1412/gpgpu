#ifndef _SINGLETON_H_
#define _SINGLETON_H_
class Singleton
{
	private:
		Singleton(const Singleton& obj);
		Singleton& operator=(const Singleton& obj);
	public:
		Singleton(){}
		virtual ~Singleton(){}
};
#endif
