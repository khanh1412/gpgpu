#ifndef _KEYPAIR_H_
#define _KEYPAIR_H_
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
class keypair
{
	public:
		key pub;
		key pri;
		inline friend std::ostream& operator<<(std::ostream& out, const keypair& pair);
		keypair(int_t p, int_t q, const int_t& pubkey = 3);
		~keypair(){}
};
inline std::ostream& operator<<(std::ostream& out, const keypair& pair)
{
	out<<"public  "<<pair.pub<<std::endl;
	out<<"private "<<pair.pri<<std::endl;
	return out;
}
static inline void setnextprime(int_t& num)
{
	mpz_nextprime(num.get_mpz_t(), num.get_mpz_t());
}
static inline int_t fast_inverse(const int_t& num, const int_t& modulo)
{
	int_t inv;
	mpz_invert(inv.get_mpz_t(), num.get_mpz_t(), modulo.get_mpz_t());
	return inv;
}
keypair::keypair(int_t p, int_t q, const int_t& pubkey)
{
	setnextprime(p);
	setnextprime(q);

	int_t n = p*q;
	int_t phi = (p-1)*(q-1);
	int_t e = pubkey;
	int_t d = fast_inverse(e, phi);

	pub = key(e, n);
	pri = key(d, n);
}
#endif

