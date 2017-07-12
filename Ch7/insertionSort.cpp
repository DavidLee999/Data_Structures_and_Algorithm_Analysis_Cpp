#include <vector>
#include <functional>
#include <iostream>

template <typename Comparable>
void insertionSort( std::vector<Comparable>& a )
{
    for( int p = 1; p < a.size(); ++p )
    {
        Comparable temp = std::move( a[p] );

        int j;
        for( j = p; j > 0 && temp < a[j - 1]; --j )
            a[j] = std::move( a[j - 1] );

        a[j] = std::move( temp );
    }
}

template <typename Iterator>
void InsertionSort( const Iterator& begin, const Iterator& end)
{
    insertionSort( begin, end, std::less<decltype( *begin )>{} );
}

template <typename Iterator,  typename Comparator>
void InsertionSort( const Iterator& begin, const Iterator& end, Comparator lessThan )
{
    if( begin == end )
        return;

    for( Iterator p = begin + 1; p != end; ++p )
    {
        auto temp = std::move( *p );

        Iterator j;
        for( j = p; j != begin && lessThan( temp, *(j - 1) ); --j )
            *j = std::move( *(j - 1) );

        *j = std::move( temp );
    }
}

int main()
{
    std::vector<int> a { 4, 6, 1, 0, 3, 2, 6, 32, 12 };

    std::cout << a;
    return 0;
}
