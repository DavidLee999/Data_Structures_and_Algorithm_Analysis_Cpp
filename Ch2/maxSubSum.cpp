#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
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

int maxSubSum4( const vector<int> & a )
{
	int maxSum { 0 }, thisSum { 0 };
	
	for ( int i = 0; i < a.size(); ++i )
	{
		thisSum += a[ i ];
		
		if ( thisSum > maxSum )
			maxSum = thisSum;
		else if ( thisSum < 0 )
			thisSum = 0;
	}
	
	return maxSum;
}


int main()
{
	int n { 5000 };
	
	vector<int> arr ( n, 0 );
	
	for ( int i = 0; i < n; ++i )
		arr[ i ] = rand() % 201 - 100;
	
	
	clock_t begin1 = clock();
	
	int max1 = maxSubSum1( arr );
	
	clock_t end1 = clock();
	
	clock_t spentTime1 = end1 - begin1;
	
	clock_t begin2 = clock();
	
	int max2 = maxSubSum2( arr );
	
	clock_t end2 = clock();
	
	clock_t spentTime2 = end2 - begin2;
	
	clock_t begin3 = clock();
	
	int max3 = maxSubSum3( arr );
	
	clock_t end3 = clock();
	
	clock_t spentTime3 = end3 - begin3;
	
	clock_t begin4 = clock();
	
	int max4 = maxSubSum4( arr );
	
	clock_t end4 = clock();
	
	clock_t spentTime4 = end4 - begin4;
	
	cout << max1 << "\t" << spentTime1 << "msce.\n";
	cout << max2 << "\t" << spentTime2 << "msce.\n";
	cout << max3 << "\t" << spentTime3 << "msce.\n";
	cout << max4 << "\t" << spentTime4 << "msce.\n";
	
}