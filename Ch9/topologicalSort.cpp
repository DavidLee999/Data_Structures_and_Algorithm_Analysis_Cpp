#include <iostream>
// #include <list>
#include <vector>
#include <queue>
#include <algorithm>
// #include <memory>
using namespace std;

#include "Vertex.h"

void topSort(const vector<Vertex>& points)
{
    std::vector<Vertex> p = points;
    std::queue<Vertex> q;
    
    for (auto it = p.begin(); it != p.end(); ++it)
    {
        if (it->indegree == 0)
        {
            q.push(*it);
            // p.erase(it);
        }
    }

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();

        cout << v.name << " ";

        for (auto it = v.adj.begin(); it != v.adj.end(); ++it)
        {
            auto it2 = find(p.begin(), p.end(), *it);
            if (--(it2->indegree) == 0)
                q.push(*it2);

            // if (it->isLinked(v))
            // {
                // if (--(it->indegree) == 0)
                    // q.push(*it);
            // }
        }
    }

}

int main()
{
    vector<Vertex> points;
    int from, to;

    // Vertex p1, p2;
    while (cin >> from >> to) {
        Vertex p1 = Vertex {from};
        Vertex p2 = Vertex {to};

        auto it = find(points.begin(), points.end(), p1);
        if (it != points.end()) // included
            it->add(p2);
        // {
            // if (find(it->adj.begin(), it->adj.end(), p2) == it->adj.end())
                // it->adj.push_back(p2);
        // }
        else if (it == points.end())
        {
            p1.add(p2);
            points.push_back(p1);
        }

        auto it2 = find(points.begin(), points.end(), p2);
        if (it2 == points.end())
        {
            ++p2.indegree;
            points.push_back(p2);
        }
        else
            (it2->indegree)++;
    }

    for (auto it = points.begin(); it != points.end(); ++it)
    {
        cout << it->name << " " << it->indegree <<  ": ";
        for (auto it2 = it->adj.begin(); it2 != it->adj.end(); ++it2)
            cout << it2->name << " ";
        cout << endl;
    }

    cout << "topological sort: ";
    topSort(points);
    cout << endl;

    return 0;
}
