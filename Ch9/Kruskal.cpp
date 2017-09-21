#include <vector>
#include <memory>
#include <queue>
#include <iostream>
using namespace std;

#include "Graph.h"
#include "../Ch8/QuickUnion.cpp"

vector<Edge> kruskal(const vector<Edge>& edges, int numVertices)
{
    QuickUnion qu { numVertices };
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > pq;
    vector<Edge> mst;

    for (int i = 0; i < edges.size(); ++i)
        pq.push(edges[i]);

    while (mst.size() != numVertices - 1) {
        Edge e = pq.top();
        pq.pop();

        if (!qu.connected(e.start->name - 1, e.end->name - 1))
        {
            mst.push_back(e);
            qu.unionSets(e.start->name - 1, e.end->name - 1);
        }
    }

    return mst;
}

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

    vector<Edge> mst = kruskal(g.lines, g.points.size());

    int totalWeight = 0;
    for (int i = 0; i < mst.size(); ++i)
    {
        cout << mst[i].start->name << " -> " << mst[i].end->name << ". w: " << mst[i].weight << endl;
        totalWeight += mst[i].weight;
    }
    cout << "The weight of the MST is " << totalWeight << '\n';

    return 0;
}
