#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "UniformRandom.h"


int nextPrime(int);

template <typename AnyType>
class CuckooHashFamily
{
    public:
        size_t hash(const AnyType& x, int which) const;
        int getNumberofFunctions();
        void generateNewFunctions();
};

template <int count>
class StringHashFamily
{
    public:
        StringHashFamily() : MULTIPLIERS (count)
        {
            generateNewFunctions();
        }

        int getNumberofFunctions() const
        {
            return count;
        }

        void generateNewFunctions()
        {
            for (auto& mult : MULTIPLIERS)
                mult = r.nextInt();
        }

        size_t hash(const string& x, int which) const
        {
            const int multiplier = MULTIPLIERS[which];
            size_t hashVal = 0;

            for (auto ch : x)
                hashVal = multiplier * hashVal + ch;

            return hashVal;
        }

    private:
        vector<int> MULTIPLIERS;
        UniformRandom r;

};

template <typename AnyType, typename HashFamily>
class CuckooHashTable
{
    public:
        explicit CuckooHashTable(int size = 101) : array( nextPrime(size) )
        {
            numHashFunctions = hashFunctions.getNumberofFunctions();
            rehashes = 0;
            makeEmpty();
        }

        bool contains(const AnyType& x) const
        {
            return findPos(x) != -1;
        }

        int size() const
        { return currentSize; }

        int capacity() const
        { return array.size(); }


        void makeEmpty()
        {
            currentSize = 0;
            for (auto& entry : array)
                entry.isActive = false;
        }

        bool remove(const AnyType& x)
        {
            int currentPos = findPos(x);

            if (!isActive(currentPos))
                return false;

            array[currentPos].isActive = false;
            --currentSize;

            return true;
        }

        bool insert(const AnyType& x)
        {
            if (contains(x))
                return false;

            if (currentSize >= array.size() * MAX_LOAD)
                expand();

            return insertHelper1(x);
        }

        bool insert(AnyType&& x)
        {
            if (contains(x))
                return false;

            if (currentSize >= array.size() * MAX_LOAD)
                expand();

            return insertHelper1(std::move(x));
        }

    private:
        struct HashEntry
        {
            AnyType element;
            bool isActive;

            HashEntry(const AnyType& e = AnyType{}, bool a = false)
                : element { e }, isActive { a } {}
            HashEntry(AnyType&& e, bool a = false)
                : element { e }, isActive { a } {}
        };

        bool insertHelper1(AnyType&& x)
        {
            const int COUNT_LIMIT = 100;

            while (true) {
                int lastPos = -1;
                int pos;

                for (int count = 0; count < COUNT_LIMIT; ++count)
                {
                    for (int i = 0; i < numHashFunctions; ++i)
                    {
                        pos = myhash(x, i);

                        if (!isActive(pos))
                        {
                            array[pos] = std::move(HashEntry {std::move(x), true});
                            ++currentSize;
                            return true;
                        }
                    }

                    int i = 0;
                    do {
                        pos = myhash(x, r.nextInt(numHashFunctions));
                    } while (pos == lastPos && i++ < 5);

                    lastPos = pos;
                    std::swap(x, array[pos].element);
                }

                if (++rehashes > ALLOWED_REHASHES)
                {
                    expand();
                    rehashes = 0;
                }
                else
                    rehash();
            }
        }

        bool insertHelper1(const AnyType& xx)
        {
            const int COUNT_LIMIT = 100;
            AnyType x = xx;

            while (true) {
                int lastPos = -1; // position of the be-replaced item
                int pos; // position of the inserted item

                // max number of attempts, otherwise rehash the table
                for (int count = 0; count < COUNT_LIMIT; ++count)
                {
                    // find a valid spot, insert it
                    for (int i = 0; i < numHashFunctions; ++i)
                    {
                        pos = myhash(x, i);

                        if (!isActive(pos))
                        {
                            array[pos] = std::move(HashEntry{ std::move(x), true });
                            ++currentSize;
                            return true;
                        }
                    }

                    // none of the spots are available, evict a random one
                    int i = 0;
                    do {
                        pos = myhash(x, r.nextInt(numHashFunctions));
                    } while (pos == lastPos && i++ < 5); // no circle and the max jump times is 5

                    lastPos = pos; // record the position where the item be inserted
                    std::swap(x, array[pos].element); // exchange
                }

                if (++rehashes > ALLOWED_REHASHES) // already maxium rehashed time, expand the table
                {
                    expand();
                    rehashes = 0;
                }
                else // otherwise, rehash the table
                    rehash();
            }
        }

        void expand()
        {
            rehash(static_cast<int>(array.size() / MAX_LOAD));
        }

        void rehash()
        {
            hashFunctions.generateNewFunctions();
            rehash(array.size());
        }

        void rehash(int newSize)
        {
            vector<HashEntry> oldArray = array;

            array.resize(nextPrime(newSize));
            for (auto& entry : array)
                entry.isActive = false;

            currentSize = 0;
            for (auto& entry : oldArray)
                if (entry.isActive)
                    insert(std::move(entry.element));
        }


        bool isActive(int currentPos) const
        {
            return currentPos != -1 && array[currentPos].isActive;
        }

        size_t myhash(const AnyType& x, int which) const
        {
            return hashFunctions.hash(x, which) % array.size();
        }

        int findPos(const AnyType& x) const
        {
            for (int i = 0; i < numHashFunctions; ++i)
            {
                int pos = myhash(x, i);

                if (isActive(pos) && array[pos].element == x)
                    return pos;
            }

            return -1;
        }

        static constexpr double MAX_LOAD = 0.40;
        static const int ALLOWED_REHASHES = 5;

        vector<HashEntry> array;
        int currentSize;
        int numHashFunctions;
        int rehashes;
        UniformRandom r;
        HashFamily hashFunctions;

};

bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

int nextPrime( int n )
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

template <typename Object>
string toString( Object x )
{
    ostringstream oss;
    oss << x;
    return oss.str( );
}

int main( )
{
    const int NUMS = 2000000;
    const int GAP  =   37;
    const int ATTEMPTS = 1;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( int att = 0; att < ATTEMPTS; ++att )
    { 
        cout << "ATTEMPT: " << att << endl;
        
        CuckooHashTable<string,StringHashFamily<3>> h1;
        CuckooHashTable<string,StringHashFamily<3>> h2;
        
        for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        {
            if( !h1.insert( toString( i ) ) )
            {
                cout << "OOPS insert fails???!!!! " << i << endl;
            }
            
        }

        for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
            if( h1.insert( toString( i ) ) )
                cout << "INSERT OOPS!!! " << i << endl;
        
        h2 = h1;
        
        for( i = 1; i < NUMS; i += 2 )
            h2.remove( toString( i ) );
        
        for( i = 2; i < NUMS; i += 2 )
            if( !h2.contains( toString( i ) ) )
                cout << "Contains fails " << i << endl;
        
        for( i = 1; i < NUMS; i += 2 )
        {
            if( h2.contains( toString( i ) ) )
                cout << "CONTAINS OOPS!!! " <<  i << endl;
        }
        
        cout << "END OF ATTEMPT" << endl;
        
        if( h2.capacity( ) > NUMS * 4 )
            cout << "LARGE CAPACITY " << h2.capacity( ) << endl;
        
    }

    return 0;
}
