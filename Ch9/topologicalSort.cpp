#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

#include "Vertex.h"


int main()
{
    vector<Vertex> points;
    int from, to;

    Vertex p1, p2;
    while (cin) {
        cin >> from >> to;
        p1 = Vertex {from};
        p2 = Vertex {to};

        auto it = find(points.begin(), points.end(), p1);
        if (it != points.end()) // included
        {
            if (find(it->adj.begin(), it->adj.end(), p2) == it->adj.end())
                it->adj.push_back(p2);
        }
        else if (it == points.end())
        {
            p1.adj.push_back(p2);
            points.push_back(p1);
        }

        if (find(points.begin(), points.end(), p2) == points.end()) {
            points.push_back(p2);
        }
    }

    for (auto it = points.begin(); it != points.end(); ++it)
    {
        cout << it->name << ": ";
        for (auto it2 = it->adj.begin(); it2 != it->adj.end(); ++it2)
            cout << it2->name << " ";
        cout << endl;
    }

    return 0;
}
