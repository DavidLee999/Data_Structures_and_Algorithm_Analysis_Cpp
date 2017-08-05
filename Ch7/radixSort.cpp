#include <iostream>
#include <string>
#include <vector>
using namespace std;

void radixSortA( vector<string>& arr, int stringLen )
{
    const int BUCKETS = 256;
    vector<vector<string>> buckets( BUCKETS );

    for ( int pos = stringLen - 1; pos >= 0; --pos )
    {
        for( string s : arr )
            buckets[s[pos]].push_back( std::move( s ) );

        int idx = 0;
        for( auto& thisBucket : buckets )
        {
            for( string& s : thisBucket )
                arr[idx++] = std::move( s );

            thisBucket.clear();
        }
    }
}

void countingRadixSort( vector<string>& arr, int stringLen )
{
    const int BUCKETS = 256;

    int N = arr.size();
    vector<string> buffer( N );

    vector<string>* in = &arr;
    vector<string>* out = &buffer;

    for( int pos = stringLen - 1; pos >= 0; --pos )
    {
        vector<int> count( BUCKETS + 1 );

        for( int i = 0; i < N; ++i )
            ++count[(*in)[i][pos] + 1];

        for( int b = 1; b <= BUCKETS; ++b)
            count[b] += count[b - 1];

        for( int i = 0; i < N; ++i )
            (*out)[count[(*in)[i][pos]]++] = std::move( (*in)[i] );

        std::swap( in, out );
    }

    if( stringLen % 2 == 1 )
    {
        for( int i = 0; i < arr.size(); ++i )
            (*out)[i] = std::move( (*in)[i] );
    }
}

void radixSort( vector<string>& arr, int maxLen )
{
    const int BUCKETS = 256;

    vector<vector<string>> wordsByLength( maxLen + 1 );
    vector<vector<string>> buckets( BUCKETS );

    for( string& s: arr )
        wordsByLength[ s.length() ].push_back( std::move( s ) );

    int idx = 0;
    for( auto& wordList : wordsByLength )
        for( string& s : wordList )
            arr[idx++] = std::move( s );

    int startingIndex = arr.size();
    for( int pos = maxLen - 1; pos >= 0; --pos )
    {
        startingIndex -= wordsByLength[pos + 1].size();

        for( int i = startingIndex; i < arr.size(); ++i )
            buckets[ arr[i][pos] ].push_back( std::move( arr[i] ) );

        idx = startingIndex;
        for( auto& thisBucket : buckets )
        {
            for( string& s : thisBucket )
                arr[idx++] = std::move( s );

            thisBucket.clear();
        }
    }
}

int main()
{
    vector<string> a { "this", "that", "well", "very", "much", "game", "part", "dare", "know" };
    countingRadixSort( a, 4 );
    for( string s : a )
        cout << s << ' ';
    cout << endl;

    vector<string> b { "this", "is", "nothing", "radix", "fast", "general", "usual", "test", "normalization" };
    radixSort( b, 13 );
    for( string s : b )
        cout << s << ' ';
    cout << endl;

    return 0;
}
