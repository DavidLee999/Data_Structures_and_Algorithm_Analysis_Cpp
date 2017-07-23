#include <iostream>
#include <vector>
#include <algorithm>

template <typename Comparable>
void merge( std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int lo, int mid, int hi )
{
    int i = lo, j = mid + 1, k = lo;
    while( k <= hi )
    {
        if( i > mid )
            tmpArray[k++] = std::move( a[j++] );
        else if( j > hi )
            tmpArray[k++] = std::move( a[i++] );
        else if( a[i] <= a[j] )
            tmpArray[k++] = std::move( a[i++] );
        else
            tmpArray[k++] = std::move( a[j++] );
    }

    for( int p = lo; p <= hi; ++p )
        a[p] = std::move( tmpArray[p] );
}

template <typename Comparable>
void mergeSort( std::vector<Comparable>& a )
{
    int n = a.size();
    std::vector<Comparable> tmpArray( n );

    for( int sz = 1; sz < n; sz *= 2 )
    {
        for( int lo = 0; lo < n - sz; lo += sz + sz )
        {
            int mid = lo + sz - 1;
            int hi = std::min(lo + sz + sz - 1, n - 1 );

            merge( a, tmpArray, lo, mid, hi );
        }
    }
}

int main()
{
    char p;
    std::vector<char> a;
    while( std::cin >> p )
        a.push_back(p);

    mergeSort( a );

    for( int i = 0; i < a.size(); ++i )
        std::cout << a[i] << " ";

    return 0;
}
