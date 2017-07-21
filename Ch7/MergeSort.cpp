#include <iostream>
#include <vector>

template <typename Comparable>
void merge( std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
    for( int i = leftPos; i <= rightEnd; ++i )
        tmpArray[i] = a[i];

    int i = leftPos, j = rightPos, k = leftPos;
    while( k <= rightEnd )
    {
        if( i > rightPos - 1 )
            a[k++] = std::move( tmpArray[j++] );
        else if( j > rightEnd )
            a[k++] = std::move( tmpArray[i++] );
        else if( tmpArray[i] <= tmpArray[j] )
            a[k++] = std::move( tmpArray[i++] );
        else
            a[k++] = std::move( tmpArray[j++] );
    }
}

template <typename Comparable>
void mergeSort( std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int left, int right )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;

        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );

        merge( a, tmpArray, left, center + 1, right );
    }
}

template <typename Comparable>
void mergeSort( std::vector<Comparable>& a )
{
    std::vector<Comparable> tmpArray( a.size() );

    mergeSort( a, tmpArray, 0, a.size() - 1 );
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
