#include <iostream>
#include <memory>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

#include "Vertex.h"
#include "Graph.h"
#include "Graph.cpp"

void Prim(const Graph& g, const shared_ptr<Vertex>& item, unordered_map<int, int>& dist, unordered_map<int, int>& path)
{
    const int MAX = 100;
    unordered_map<int, bool> known;
    std::priority_queue<pair<int, int>, std::vector< pair<int, int> >, std::greater< pair<int, int> > > pq;

    for (auto it = g.points.begin(); it != g.points.end(); ++it)
    {
        dist.insert( make_pair((*it)->name, MAX) );
        path.insert( make_pair((*it)->name, 0) );
        known.insert( make_pair((*it)->name, false) );
    }

    dist.find(item->name)->second = 0;
    pq.push( make_pair(0, item->name) );

    int numVertex = g.points.size();
    int count = 0;

    while (count < numVertex) {
        int name = pq.top().second;
        // int dist_v = pq.top().first;
        pq.pop();

        auto v = find(g.points.begin(), g.points.end(), Vertex { name });

        known.find((*v)->name)->second = true;
        ++count;

        for (auto w = (*v)->adj.begin(); w != (*v)->adj.end(); ++w)
        {
            if (known.find((*w)->name)->second == false)
            {
                int cvw = g.findEdge((*v), (*w))->weight;
                int dist_w = dist.find((*w)->name)->second;

                if (cvw < dist_w)
                {
                    dist.find((*w)->name)->second = cvw;
                    path.find((*w)->name)->second = name;


                    pq.push( make_pair(cvw, (*w)->name) );
                }
            }
        }
    }
    
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

    int start;

    cin.clear();
    cout << "input start point: ";
    cin >> start;

    auto it = find(g.points.begin(), g.points.end(), Vertex { start });
    
    unordered_map<int, int> dist;
    unordered_map<int, int> path;

    Prim(g, *it, dist, path);

    cout << "Distances: " << '\n';
    for (auto it = dist.begin(); it != dist.end(); ++it)
        cout << it->first << " " << it->second << '\n';

    cout << "Path: " << '\n';
    for (auto it = path.begin(); it != path.end(); ++it)
        cout << it->first << " " << it->second <<'\n';

    // for (auto it = g.points.begin(); it != g.points.end(); ++it)
    // {
        // cout << (*it)->name << " " << (*it)->indegree <<  ": ";
        // for (auto it2 = (*it)->adj.begin(); it2 != (*it)->adj.end(); ++it2)
            // cout << (*it2)->name << " ";
        // cout << endl;
    // }

    return 0;
}
