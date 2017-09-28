#include <iostream>
using namespace std;

long long fibonacci(int n)
{
    if (n <= 2)
        return 1;

    long long last = 1;
    long long nextToLast = 1;
    long long answer = 0;

    for (int i = 2; i <= n; ++i)
    {
        answer = last + nextToLast;
        nextToLast = last;
        last = answer;
    }

    return answer;
}

int main()
{
    cout << "Fibonacci(3) = " << fibonacci(3) << endl;
    cout << "Fibonacci(40) = " << fibonacci(40) << endl;

    return 0;
}
