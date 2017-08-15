#include <vector>
#include <queue>
#include <functional>
#include <string>
#include <iostream>
using namespace std;

template <typename PriorityQueue>
void dumpContents(const string& msg, PriorityQueue& pq)
{
    cout << msg << ":" << " ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
}

int main()
{
    priority_queue<int> maxPQ;
    priority_queue<int, vector<int>, greater<int>> minPQ;

    minPQ.push(4);
    minPQ.push(5);
    minPQ.push(3);


    maxPQ.push(4);
    maxPQ.push(5);
    maxPQ.push(3);

    dumpContents("minPQ", minPQ);
    dumpContents("maxPQ", maxPQ);

    return 0;
}
