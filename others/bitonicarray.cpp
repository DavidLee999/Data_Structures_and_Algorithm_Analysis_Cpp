#include <iostream>
#include <vector>
using namespace std;

template <typename Comparable>
int ascendingBinarySearch(const vector<Comparable>& arr, int low, int high, const Comparable& x)
{
    if (low >  high)
        return -1;

    int mid = (low + high) / 2;
    if(arr[mid] == x)
        return mid;

    // if (low + 1 == high)
    //     return -1;

    if (x < arr[mid])
        return ascendingBinarySearch(arr, low, mid - 1, x);
    else
        return ascendingBinarySearch(arr, mid + 1, high, x);
}

template <typename Comparable>
int descendingBinarySearch(const vector<Comparable>& arr, int low, int high, const Comparable& x)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;
    if (arr[mid] == x)
        return mid;

    // if (low + 1 == high)
    //     return -1;

    if (x < arr[mid])
        return descendingBinarySearch(arr, mid + 1, high, x);
    else
        return descendingBinarySearch(arr, low, mid - 1, x);
}

template <typename Comparable>
int bitonicSearch(const vector<Comparable>& arr, int low, int high, const Comparable& x)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;
    if (arr[mid] == x)
        return mid;

    if (arr[mid] < x)
    {
        if (arr[mid] > arr[mid + 1])
            return bitonicSearch(arr, low, mid - 1, x);
        else
            return bitonicSearch(arr, mid + 1, high, x);
    }
    else
    {
        int i = descendingBinarySearch(arr, mid + 1, high, x);
        if (i != -1)
            return i;
        else
            return ascendingBinarySearch(arr, low, mid - 1, x);
    }
}
int main()
{
    vector<int> a {1,3,5,7,8,6,4,2};
    // vector<int> b {9,8,7,6,5,4,3,2,1};
    int pos = bitonicSearch(a, 0, a.size() - 1, 2);
    cout << pos << endl;

    return 0;
}
