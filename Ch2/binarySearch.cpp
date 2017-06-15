#include<iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

template <typename Comparable>
int binarySearch( const vector<Comparable> & a, const Comparable & x)
{
	int low { 0 }, high = a.size() - 1;
	
	while ( low <= high )
	{
		int mid = ( low + high ) / 2;
		
		if ( a[ mid ] < x )
			low = mid + 1;
		else if ( a[ mid ] > x )
			high = mid - 1;
		else
			return mid;
	}
	
	return -1;
}

int main()
{
	int n { 1000 };
	
	vector<int> arr ( n );
	
	for ( int i = 0; i < n; i++ )
		arr[ i ] = rand() % 2001 - 1000;

	sort( arr.begin(), arr.end() );

	int a = binarySearch( arr, 88 );
	

	if ( a == -1 )
		cout << "not found." << endl;
	else
		cout << "index: " << a << "\t" << arr[ a ] << endl;
	
	return 0;
	
}