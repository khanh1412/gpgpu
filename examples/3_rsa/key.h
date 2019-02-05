#ifndef _KEY_H_
#define _KEY_H_
#include<iostream>
#include<gmpxx.h>
using int_t = mpz_class;

class key
{
	public:
		key(){}
		key(const int_t& value, const int_t& modulo) : value(value), modulo(modulo) {}
		key& operator=(const key& obj) {value = obj.value; modulo = obj.modulo; return *this;}
		int_t value;
		int_t modulo;
	public:
		~key() {}
		int_t code(const int_t& message) const;
		inline friend std::ostream& operator<<(std::ostream& out, const key& k);
};
inline std::ostream& operator<<(std::ostream& out, const key& k)
{
	out<<"key: "<<std::endl;
	out<<"\tvalue : "<<k.value<<std::endl;
	out<<"\tmodulo: "<<k.modulo<<std::endl;
	return out;
}
static inline int_t crypto_raise(const int_t& a, const int_t& n, const int_t& modulo)
{
	int_t pow;
	mpz_powm_sec(pow.get_mpz_t(), a.get_mpz_t(), n.get_mpz_t(), modulo.get_mpz_t());
	return pow;
}

int_t key::code(const int_t& message) const
{
	return crypto_raise(message, value, modulo); 
}
#endif
