#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

int maxSubSum1( const vector<int> & a )
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

int maxSubSum2( const vector<int> & a )
{
	int maxSum = 0;
	
	for( int i = 0; i < a.size(); ++i )
	{
		int thisSum = 0;
		for ( int j = i; j < a.size(); ++j )
		{
			thisSum += a[ j ];
			
			if ( thisSum > maxSum )
				maxSum = thisSum;
		}
	}
	
	return maxSum;
}

int maxSumRec( const vector<int> & a, int left, int right )
{
	if ( left == right )
		if ( a[ left ] > 0 )
			return a[ left ];
		else
			return 0;
	
	int center = ( left + right ) / 2;
	int maxLeftSum = maxSumRec( a, left, center );
	int maxRightSum = maxSumRec( a, center + 1, right );
	
	int maxLeftBorderSum { 0 }, leftBorderSum { 0 };
	for ( int i = center; i >= left; --i )
	{
		leftBorderSum += a[ i ];
		if( leftBorderSum > maxLeftBorderSum )
			maxLeftBorderSum = leftBorderSum;
			
	}
	
	int maxRightBorderSum { 0 }, rightBorderSum { 0 };
	for ( int i = center + 1; i <= right; ++i )
	{
		rightBorderSum += a[ i ];
		if( rightBorderSum > maxRightBorderSum )
			maxRightBorderSum = rightBorderSum;
			
	}
	
	return max( max( maxLeftSum, maxRightSum ), maxLeftBorderSum + maxRightBorderSum );
}

int maxSubSum3( const vector<int> & a )
{
	return maxSumRec( a, 0, a.size() - 1 );
}


int main()
{
	vector<int> arr { -2, 11, -4, 13, -5, -2 };
	
	//clock_t begin = clock();
	
	int max1 = maxSubSum3( arr );
	
	//clock_t end = clock();
	
	//clock_t spentTime = end - begin;
	
	cout << max1 << endl; //"\t" << spentTime << "msce.\n";
	
	cout<<max(max(1,2),3);
}