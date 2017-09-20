#include <iostream>
#include <memory>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

#include "Vertex.h"
#include "Graph.h"
#include "Graph.cpp"


int main()
{
    Graph g {};
    int from, to, weight;

    cout << "Input Edges: start_point, end_point, weight: \n";
    while (cin >> from >> to >> weight) {
        shared_ptr<Vertex> p1 { new Vertex { from } };
        shared_ptr<Vertex> p2 { new Vertex { to } };

        g.addEdge_undirected(p1, p2, weight);
    }

    for (auto it = g.points.begin(); it != g.points.end(); ++it)
    {
        cout << (*it)->name << " " << (*it)->indegree <<  ": ";
        for (auto it2 = (*it)->adj.begin(); it2 != (*it)->adj.end(); ++it2)
            cout << (*it2)->name << " ";
        cout << endl;
    }

    return 0;
}
