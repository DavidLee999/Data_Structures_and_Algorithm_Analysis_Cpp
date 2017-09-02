#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

int nextPrime(int);
int prevPrime(int);

template <typename HashedObj>
class HashTable
{
    public:
        explicit HashTable(int size = 101) : array (nextPrime(size))
        { makeEmpty(); }


        bool contains(const HashedObj& x) const
        { return isActive(findPos(x)); }


        void makeEmpty()
        {
            currentSize = 0;
            for (auto& entry : array)
                entry.info = EMPTY;
        }

        bool insert(const HashedObj& x)
        {
            int currentPos = findPos(x);
            if(isActive(currentPos))
                return false;

            array[currentPos].element = x;
            array[currentPos].info = ACTIVE;

            if (++currentSize > array.size() / 2)
                rehash();

            return true;
        }

        bool insert(HashedObj&& x)
        {
            int currentPos = findPos(std::move(x));
            if(isActive(currentPos))
                return false;

            array[currentPos].element = std::move(x);
            array[currentPos].info = ACTIVE;

            if (++currentSize > array.size() / 2)
                rehash();

            return true;
        }

        bool remove(const HashedObj& x)
        {
            int currentPos = findPos(x);
            if(!isActive(currentPos))
                return false;

            array[currentPos].info = DELETE;

            return true;
        }

        enum EntryType { ACTIVE, EMPTY, DELETE };

    private:
        struct HashEntry
        {
            HashedObj element;
            EntryType info;

            HashEntry(const HashedObj& e = HashedObj {}, EntryType i = EMPTY)
                : element { e }, info { i } {};

            HashEntry(HashedObj&& e, EntryType i = EMPTY)
                : element { e }, info { i } {};
        };

        vector<HashEntry> array;
        int currentSize;

        bool isActive(int currentPos) const
        { return array[currentPos].info == ACTIVE; }

        int findPos(const HashedObj& x) const
        {
            int offset =  myhash2(x);
            int currentPos = myhash(x);

            if (array[currentPos].info != EMPTY && array[currentPos].element != x)
            {
                currentPos += offset;

                if (currentPos > array.size())
                    currentPos -= array.size();
            }

            return currentPos;
        }

        size_t myhash(const HashedObj& x) const
        {
            static hash<HashedObj> hf;
            return hf(x) % array.size();
        }

        size_t myhash2(const HashedObj& x) const
        {
            size_t hashVal = myhash(x);
            int R = prevPrime(array.size());
            size_t hashVal2 = 7 - hashVal % 7;
            return hashVal2 % array.size();
        }

        void rehash()
        {
            vector<HashEntry> oldArray = array;
            array.resize( nextPrime(2 * oldArray.size()));

            for (auto& entry : array)
                entry.info = EMPTY;

            currentSize = 0;
            for (auto& entry : oldArray)
                if (entry.info == ACTIVE)
                    insert(std::move(entry.element));
        }
};


bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

int prevPrime(int n)
{
    --n;
    if (n % 2 == 0)
        --n;

    while (!isPrime(n))
    {
        if (n > 2)
            n -= 2;
        else
            n = 3;
    }

    return n;
}

int nextPrime(int n)
{
    if (n % 2 == 0)
        ++n;

    while (!isPrime(n))
        n += 2;

    return n;
}


int main()
{
HashTable<int> h1;
    HashTable<int> h2;

    const int NUMS = 4000;
    const int GAP  =   37;
    int i;

   cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        h1.insert( i );

    h2 = h1; 
    for( i = 1; i < NUMS; i += 2 )
        h2.remove( i );

    for( i = 2; i < NUMS; i += 2 )
        if( !h2.contains( i ) )
            cout << "Contains fails " << i << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( h2.contains( i ) )
            cout << "OOPS!!! " <<  i << endl;
    }

    return 0;   
}
