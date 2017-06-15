#include <iostream>

long gcd (long m, long n)
{
	while (n != 0)
	{
		long rem = m % n;
		m = n;
		n = rem;
	}
	
	return m;
}

int main()
{
	long m, n;
	
	std::cin >> m >> n;
	
	long d = gcd( m, n );
	
	std::cout << d << std::endl;
}