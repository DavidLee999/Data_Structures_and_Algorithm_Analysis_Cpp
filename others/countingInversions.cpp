#include <iostream>
#include <vector>
using namespace std;

template <typename T>
int merge(vector<T>& a, vector<T>& tmp, int left, int right, int end)
{
    int count = 0;
    int i = left, j = right, k = left;
    while (k <= end) {
        if (i > right - 1)
            tmp[k++] = std::move(a[j++]);
        else if (j > end)
            tmp[k++] = std::move(a[i++]);
        else if (a[i] <= a[j])
            tmp[k++] = std::move(a[i++]);
        else
        {
            tmp[k++] = std::move(a[j++]);
            count += right - i;
        }
    }
    
    for (int p = left; p <= end; ++p)
        a[p] = std::move(tmp[p]);

    return count;
}

template <typename T>
int countInversions(vector<T>& arr, vector<T>& tmp, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        int count = 0;
        
        count += countInversions(arr, tmp, left, mid);
        count += countInversions(arr, tmp, mid + 1, right);
        count += merge(arr, tmp, left, mid + 1, right);
        
        return count;
    }
    
    return 0;
}

template <typename T>
int countInversions(const vector<T>& arr)
{
    vector<T> b { arr };
    vector<T> tmp( b.size() );

    return countInversions(b, tmp, 0, b.size() - 1);
}

int main()
{
    vector<int> a {9,8,7,6,5,4,3,2,1};
    cout << countInversions(a) << endl;

    return 0;
}
