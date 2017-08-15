#include <iostream>
#include <vector>
using namespace std;


inline int leftChild(int i)
{ return 2*i + 1; }

template <typename Comparable>
void percDown(vector<Comparable>& a, int i, int n)
{
    int child;
    Comparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[i] = std::move(a[child]);
        else
            break;
    }

    a[i] = std::move(tmp);
}

template <typename Comparable>
void heapsort(vector<Comparable>& a)
{
    for (int i = a.size() / 2 - 1; i >= 0; --i) // build heap
        percDown(a, i, a.size());

    for (int j = a.size() - 1; j > 0; --j) // deleteMax
    {
        std::swap(a[0], a[j]);
        percDown(a, 0, j);
    }
}

int main()
{
    char p;
    std::vector<char> a;
    while( std::cin >> p )
        a.push_back(p);

    heapsort( a );

    for( int i = 0; i < a.size(); ++i )
        std::cout << a[i] << " ";

    return 0;
}
