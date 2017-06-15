#include <iostream>

long long power( long long x, int n )
{
	if ( n == 0 )
		return 1;
	if ( n % 2 == 0 )
		return pow( x * x, n / 2 );
	else
		return pow( x * x, n / 2 ) * x;
}

int main()
{
	long long m { 0 };
	int n { 0 };
	
	std::cin >> m >> n;
	
	long long re1 = power( m, n );
	
	std::cout << re << std::endl;
}