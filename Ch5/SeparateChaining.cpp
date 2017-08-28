#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

template <>
class hash<string>;

class Employee;

template <>
class hash<Employee>;
template <typename HashedObj>
class HashTable
{
    public:
        explicit HashTable(int size = 101);

        bool contains(const HashedObj& x) const;

        void makeEmpty();
        bool insert(const HashedObj& x);
        bool insert(HashedObj&& x);
        bool remove(const HashedObj& x);

    private:
        vector< list<HashedObj> > theLists;
        int currentSize;

        void rehash();
        size_t myhash(const HashedObj& x) const;
};

class Employee
{
    public:
        explicit Employee(const string& n, const double& d, const int& s)
            : name{ n }, salary{ d }, seniority{ s } {};

        const string& getName() const
        { return name; }

        bool operator==(const Employee& rhs) const
        { return getName() == rhs.getName(); }
        bool operator!=(const Employee& rhs) const
        { return !(*this == rhs); }

    private:
        string name;
        double salary;
        int seniority;
};

template <>
class hash<string>
{
    public:
        size_t operator= (const string& key)
        {
            size_t hashVal = 0;

            for (char ch : key)
                hashVal = 37 * hashVal + ch;

            return hashVal;
        }
};

template<>
class hash<Employee>
{
    public:
        size_t operator() (const Employee& item)
        {
            static hash<string> hf;
            return hf(item.getName());
        }
};

int main()
{
    return 0;
}
