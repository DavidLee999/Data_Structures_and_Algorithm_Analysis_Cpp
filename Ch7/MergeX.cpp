#include <iostream>
#include <vector>

template <typename Comparable>
void merge( std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
    int i = leftPos, j = rightPos, k = leftPos;
    while( k <= rightEnd )
    {
        if( i > rightPos - 1 )
            tmpArray[k++] = std::move( a[j++] );
        else if( j > rightEnd )
            tmpArray[k++] = std::move( a[i++] );
        else if( a[i] <= a[j] )
            tmpArray[k++] = std::move( a[i++] );
        else
            tmpArray[k++] = std::move( a[j++] );
    }
}
template <typename Comparable>
void insertionSort( std::vector<Comparable>& a, int left, int right )
{
    for( int i = left + 1; i <= right; ++i )
    {
        Comparable temp = std::move( a[i] );
        int j;

        for( j = i; j > left && temp < a[j - 1]; --j )
            a[j] = std::move( a[j - 1] );

        a[j] = std::move( temp );
    }
}
template <typename Comparable>
void mergeSort( std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int left, int right )
{
    if( right <= left + 7 )
    {
        insertionSort( tmpArray, left, right );
        return;
    }

    int center = ( left + right ) / 2;

    mergeSort( tmpArray, a, left, center );
    mergeSort( tmpArray, a, center + 1, right );

    if( a[center] <= a[center + 1] )
    {
        std::copy( a.begin(), a.end(), tmpArray.begin() );
        return;
    }

    merge( a, tmpArray, left, center + 1, right );
}

template <typename Comparable>
void mergeSort( std::vector<Comparable>& a )
{
    std::vector<Comparable> tmpArray = a;

    mergeSort( tmpArray, a, 0, a.size() - 1 );
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
