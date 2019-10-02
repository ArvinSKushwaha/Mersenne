#include <iostream>
#include <gmpxx.h>

int NUM_THREADS = 12;

bool mersfac(mpz_class p, uint_fast32_t n){
	std::string bin = p.get_str(2);
	mpz_class a(1);
	for(int i = 0; i < bin.length(); i++)
	{
		a = (a*a)%n;
		if(bin[i] == '1'){
			a = a*2;
		}
	}
	if(a == 1){
		return true;
	}
	return false;
}

bool trialfac(mpz_class p){
	for(int i = 2; i < 1000; i++){
		if(mersfac(p,i)){
			return false;
		}
	}
	return true;
}

bool is_mersenne_prime(mpz_class p)
{
	if( 2 == p )
		return true;
	else
	{
		mpz_class two = mpz_class(2);
		mpz_class s = two*two;
		mpz_t tmpz;
		mpz_init(tmpz);
		mpz_set_d(tmpz,two.get_d());
		mpz_class div( (mpz_class(1) << p.get_ui()) - 1 );
		mpz_t sqr;
		mpz_init(sqr);
		for( mpz_class i(3);  i <= p;  ++i )
		{
			mpz_powm(sqr, s.get_mpz_t(), tmpz, div.get_mpz_t());
			s = mpz_class(sqr) - two;
		}
		return (s == 0 || s == div || s == -div);
	}
}

bool check_mersenne(mpz_class n){
	if(mpz_probab_prime_p(n.get_mpz_t(), 10) && trialfac(n) && is_mersenne_prime(n))
	{
		std::cout << std::endl << "\033[1;31m"<< "M" << n << "\033[0m" << std::endl;
		return true;
	}
	return false;
}

void thread_Mersenne(mpz_class starting_point, uint_fast32_t step){
	mpz_class check = starting_point;
	while(true)
	{
		check_mersenne(check-1);
		check_mersenne(check+1);
		std::cout << check;
		std::cout << '\r';
		std::flush(std::cout);
		check += step;
	}
}

int main()
{
	mpz_class check = 0/*44496*/;
	while(true)
	{
		check_mersenne(check-1);
		check_mersenne(check+1);
		std::cout << check;
		std::cout << '\r';
		std::flush(std::cout);
		check += 6;
	}
	return 0;
}
