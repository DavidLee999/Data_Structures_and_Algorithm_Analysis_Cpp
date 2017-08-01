#include <iostream>
#include <vector>

template <typename Comparable>
void SORT( std::vector<Comparable>& items )
{
    if( items.size() > 1 )
    {
        std::vector<Comparable> smaller;
        std::vector<Comparable> same;
        std::vector<Comparable> larger;

        Comparable chosenItem = items[items.size() / 2];

        for( Comparable& i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );

            else if( chosenItem < i )
                larger.push_back( std::move( i ) );

            else
                same.push_back( std::move( i ) );
        }

        SORT( smaller );
        SORT( larger );

        std::move( std::begin( smaller ), std::end( smaller ), std::begin ( items ) );
        std::move( std::begin( same ), std::end( same ), std::begin ( items ) + smaller.size() );
        std::move( std::begin( larger ), std::end( larger ), std::end ( items ) - larger.size() );
    }
}


template <typename Comparable>
const Comparable& median3( std::vector<Comparable>& a, int left, int right )
{
    int center = ( left + right ) / 2;

    if( a[center] < a[left] )
        std::swap( a[left], a[center] );
    if( a[right] < a[left] )
        std::swap( a[left], a[right] );
    if( a[right] < a[center] )
        std::swap( a[center], a[right] );

    std::swap( a[center], a[right - 1] );

    return a[right - 1];
}

template<typename Comparable>
void insertionSort( std::vector<Comparable>& a, int left, int right )
{
    if( left == right )
        return;

    for( int i = left + 1; i <= right; ++i )
    {
        Comparable tmp = std::move( a[i] );
        int j;
        for( j = i; j > left && tmp < a[j - 1]; --j )
            a[j] = std::move( a[j - 1] );

        a[j] = std::move( tmp );
    }
}

template <typename Comparable>
void quicksort( std::vector<Comparable>& a, int left, int right )
{
    if( left + 10 <= right )
    {
        const Comparable& pivot = median3( a, left, right );

        int i = left, j = right - 1;
        while( true ) {
            while( a[++i] < pivot ) {}
            while( pivot < a[--j] ) {}

            if( i < j )
                std::swap( a[i], a[j] );
            else
                break;
        }

        std::swap( a[i], a[right - 1] );

        quicksort( a, left, i - 1 );
        quicksort( a, i + 1, right );
    }
    else
        insertionSort( a, left, right );
}

template <typename Comparable>
void quicksort( std::vector<Comparable>& a )
{
    quicksort( a, 0, a.size() - 1 );
}

template <typename Comparable>
void quickselect( std::vector<Comparable>& a, int left, int right, int k )
{
    if( left + 10 <= right )
    {
        const Comparable& pivot = median3( a, left, right );

        int i = left, j = right - 1;
        while( true ) {
            while( a[++i] < pivot ) {}
            while( pivot < a[--j] ) {}

            if( i < j )
                std::swap( a[i], a[j] );
            else
                break;
        }

        std::swap( a[i], a[right - 1] );

        if( k < i )
            quickselect( a, left, i - 1, k );
        else if( k > i )
            quickselect( a, i + 1, right, k );
        else
            return;
    }
    else
        insertionSort( a, left, right );
}
template <typename Comparable>
Comparable& quickselect( const std::vector<Comparable>& a, int k )
{
    if( k < 1 || k > a.size() )
    {
        std::cerr << "The index is out of range!" << std::endl;
        exit(0);
    }

    std::vector<Comparable> aux = a;
    quickselect( aux, 0, a.size() - 1, k - 1 );
    return aux[k - 1];
}

int main()
{
    int s;
    std::vector<int> a;
    while( std::cin >> s )
        a.push_back( s );

    std::cout << quickselect( a, 4 ) << '\n';
    quicksort( a );

    for( size_t i = 0; i < a.size(); ++i )
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
