#include <vector>
#include <iostream>
#include <ctime>
using namespace std;

int maxSubSum1( const vector<int> a )
{
	int maxSum = 0;
	
	for ( int i = 0; i < a.size(); ++i )
		for ( int j = i; j < a.size(); ++j )
		{
			int thisSum = 0;
			
			for ( int k = i; k <= j; ++k )
				thisSum += a[ k ];
			
			if ( thisSum > maxSum )
				maxSum = thisSum;
		}
		
	return maxSum;
}

int main()
{
	vector<int> arr { -2, 11, -4, 13, -5, -2 };
	
	clock_t begin = clock();
	
	int max1 = maxSubSum1( arr );
	
	clock_t end = clock();
	
	clock_t spentTime = end - begin;
	
	cout << max1 << "\t" << spentTime << "msce.\n";
}