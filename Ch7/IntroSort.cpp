#include <iostream>
#include <vector>
using namespace std;

template <typename Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
    int center = (left + right) / 2;

    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[left], a[right]);
    if (a[right] < a[center])
        std::swap(a[center], a[right]);

    std::swap(a[center], a[right - 1]);

    return a[right - 1];
}

template <typename Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
    if(right == left)
        return;

    for (int i = left + 1; i <= right; ++i)
    {
        Comparable tmp = std::move(a[i]);
        int j;
        for (j = i; j > left && tmp < a[j - 1]; --j)
            a[j] = std::move(a[j - 1]);
        
        a[j] = std::move(tmp);
    }
}

inline int leftChild(int i)
{ return 2 * i + 1; }

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
    for (int i = a.size() / 2 - 1; i >= 0; --i)
        percDown(a, i, a.size());

    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]);
        percDown(a, 0, j);
    }
}

template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right, int depth)
{
    if (depth == 0)
    {
        heapsort(a);
        return;
    }

    if (left + 10 <= right)
    {
        const Comparable& pivot = median3(a, left, right);

        int i = left, j = right - 1;
        while (true) {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}

            if (i < j)
                std::swap(a[i], a[j]);
            else 
                break;
        }
        
        std::swap(a[i], a[right - 1]);

        quicksort(a, left, i - 1, depth - 1);
        quicksort(a, i + 1, right, depth - 1);
    }
    else
        insertionSort(a, left, right);
}
template <typename Comparable>
void introsort(vector<Comparable>& a, int depth)
{
    quicksort(a, 0, a.size() - 1, depth);
}

int main()
{
    int maxDepth {};
    cout << "Enter max recursive depth: ";
    cin >> maxDepth;
    cout << '\n';

    char p {};
    vector<char> a {};
    while (cin >> p)
        a.push_back(p);

    introsort(a, maxDepth);

    for (char i : a)
        cout << i << " ";
    cout << endl;

    return 0;
}
