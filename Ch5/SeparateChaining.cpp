#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Employee;
size_t hash(const string&);
size_t hash(const Employee&);
int isPrime(int);
int nextPrime(int);

template <typename HashedObj>
class HashTable
{
    public:
        explicit HashTable(int size = 101) : currentSize{ 0 }
        { theLists.resize(size); }

        bool contains(const HashedObj& x) const
        {
            auto& whichList = theLists[myhash(x)];
            return find(begin(whichList), end(whichList), x) != end(whichList);
        }

        void makeEmpty()
        {
            for (auto& thisList : theLists)
                thisList.clear();
        }

        bool insert(const HashedObj& x)
        {
            auto& whichList = theLists[myhash(x)];
            if (find(begin(whichList), end(whichList), x) != end(whichList))
                return false;

            whichList.push_back(x);

            if (++currentSize > theLists.size())
                rehash();

            return true;
        }
        
        bool insert(HashedObj&& x)
        {
            auto& whichList = theLists[myhash(x)];
            if (find(begin(whichList), end(whichList), x) != end(whichList))
                return false;

            whichList.push_back(std::move(x));

            if (++currentSize > theLists.size())
                rehash();

            return true;
        }

        bool remove(const HashedObj& x)
        {
            auto& whichList = theLists[myhash(x)];
            auto itr = find(begin(whichList), end(whichList), x);

            if (itr == end(whichList))
                return false;

            whichList.erase(itr);
            --currentSize;

            return true;
        }

    private:
        vector< list<HashedObj> > theLists;
        int currentSize;

        void rehash()
        {
            vector< list<HashedObj> > oldLists = theLists;

            theLists.resize(nextPrime(2 * theLists.size()));

            for (auto& thisList : theLists)
                thisList.clear();

            currentSize = 0;
            
            for (auto& thisList : oldLists)
                for (auto& x : thisList)
                    insert(std::move(x));
        }

        size_t myhash(const HashedObj& x) const
        {
            return ::hash(x) % theLists.size();
        }
};

class Employee
{
    public:
        explicit Employee(const string& n, const double& d)
            : name{ n }, salary{ d } {};

        const string& getName() const
        { return name; }

        bool operator== (const Employee& rhs) const
        { return getName() == rhs.getName(); }
        bool operator!= (const Employee& rhs) const
        { return !(*this == rhs); }

    private:
        string name;
        double salary;
};

size_t hash(const string& key)
{
    size_t hashVal = 0;

    for (char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal;
}

int isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;
    
    for (int i = 3; i * i < n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

int nextPrime(int n)
{
    if (n % 2 == 0)
        ++n;

    while (!isPrime(n))
        n += 2;

    return n;
}

size_t hash(const Employee& e)
{
    return ::hash(e.getName());
}

int main()
{
    HashTable<string> a;
    a.insert("Mike");
    a.insert("John");
    a.insert("David");
    a.insert("Thomi");
    a.insert("Felix");

    a.remove("Thomi");

    cout << a.contains("John");
    return 0;
}
