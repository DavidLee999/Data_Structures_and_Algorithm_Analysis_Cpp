#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "UniformRandom.h"

template <typename AnyType>
class CuckooHashFamily
{
    public:
        size_t hash(const AnyType& x, int which) const;
        int getNumberofFunctions();
        void generateNewFunctions();
};

template <typename AnyType, typename HashFamily>
class CuckooHashTable
{
    public:
        explicit CuckooHashTbale(int size = 101);

        bool contains(const AnyType& x) const;


        void makeEmpty();
        bool remove(const AnyType& x);
        bool insert(const AnyType& x);
        bool insert(AnyType&& x);

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

        bool insertHelper1(const AnyType& xx);
        bool insertHelper1(AnyType&& xx);
        void expand();
        void rehash();
        void rehash(int newSize);

        size_t myhash(const AntType& x, int which) const;
        int findPos(const AnyType& x) const;

        static const double MAX_LOAD = 0.40;
        static const int ALLOWED_REHASHES = 5;

        vector<HashEntry> array;
        int currentSize;
        int numHashFunctions;
        int rehashes;
        UniformRandom r;
        HashFamily hashFunctions;

};
