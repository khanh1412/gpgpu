#ifndef _SINGLETON_H_
#define _SINGLETON_H_
namespace cl {
class singleton
{
	private:
		singleton(const singleton& obj);
		singleton& operator=(const singleton& obj);
	public:
		singleton(){}
		virtual ~singleton(){}
};
}
#endif
