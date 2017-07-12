#include <vector>
#include <functional>
#include <iostream>
#include <ostream>

template <typename Comparable>
void InsertionSort( std::vector<Comparable>& a )
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

template <typename RandomIterator, typename Comparator>
void InsertionSort( const RandomIterator & begin, const RandomIterator & end, Comparator lessThan )
{
    if( begin == end )
        return;

    RandomIterator j;

    for( RandomIterator p = begin + 1; p != end; ++p )
    {
        // auto temp = std::move( *p );
        for( j = p; j != begin && lessThan( *j, *(j - 1) ); --j )
            // *j = std::move( *(j - 1) );
            std::swap( *j, *(j-1) );
        // *j = std::move( temp );
    }
}

template <typename RandomIterator>
void  InsertionSort( const RandomIterator & begin, const RandomIterator & end)
{
    InsertionSort( begin, end, std::less<decltype(*begin )>{ } );
}

template <typename T>
std::ostream& operator << ( std::ostream& out, const std::vector<T>& obj )
{
    typename std::vector<T>::const_iterator it;
    for( it = obj.begin(); it != obj.end(); ++it )
        out << *it << " ";

    return out;
}

int main()
{
    std::vector<char> a { 'l','a','q','e','o','q','v','i' };

    InsertionSort( a.begin(), a.end() );
   // InsertionSort( a );

    std::cout << a;
    return 0;
}
