#include <vector>
#include <iostream>
using namespace std;

class DisjSets
{
    public:
        explicit DisjSets(int numElements) : s(numElements, -1) {}

        int find(int x) const
        {
            if (s[x] < 0)
                return x;
            else
                return find(s[x]);
        }

        int find(int x)
        {
            if (s[x] < 0)
                return x;
            else
                return s[x] = find(s[x]);
        }

        void setUnion(int root1, int root2)
        {
            if (s[root2] < s[root1])
                s[root1] = root2;
            else
            {
                if (s[root1] == s[root2])
                    --s[root1];
                s[root2] = root1;
            }
        }

    private:
        vector<int> s;
};

int main()
{
    int numElements = 128;
    int numInSameSet = 16;

    DisjSets ds{ numElements };
    int set1, set2;

    for( int k = 1; k < numInSameSet; k *= 2 )
    {
        for( int j = 0; j + k < numElements; j += 2 * k )
        {
            set1 = ds.find( j );
            set2 = ds.find( j + k );
            ds.setUnion( set1, set2 );
        }
    }

    for( int i = 0; i < numElements; ++i )
    {
        cout << ds.find( i ) << "*";
        if( i % numInSameSet == numInSameSet - 1 )
            cout << endl;
    }
    cout << endl;

    return 0;
}
