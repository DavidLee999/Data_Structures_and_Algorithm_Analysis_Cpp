#include <iostream>
#include <memory>
#include <unordered_map>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;

#include "Vertex.h"
#include "Graph.h"
#include "Graph.cpp"
#include "topologicalSort.cpp"

void djikstra(const Graph& g, const shared_ptr<Vertex>& item, unordered_map<int, int>& dist, unordered_map<int, int>& path)
{
    const int MAX = 100;
    // unordered_map<int, bool> known;

    vector<int> tp_order = topSort(g.points);

    for (auto it = g.points.begin(); it != g.points.end(); ++it)
    {
        dist.insert( make_pair((*it)->name, MAX) );
        path.insert( make_pair((*it)->name, 0) );
        // known.insert( make_pair((*it)->name, false) );
    }

    dist.find(item->name)->second = 0;

    for (auto start = find(tp_order.begin(), tp_order.end(), item->name); start != tp_order.end(); ++start)
    {
        int name = *start;
        int dist_v = dist.find(name)->second;

        auto v = find(g.points.begin(), g.points.end(), Vertex{ name });

        // known.find((*v)->name)->second = true;

        for (auto it = (*v)->adj.begin(); it != (*v)->adj.end(); ++it)
        {
            // if (known.find( (*it)->name )->second == false)
            // {
            int cvw = g.findEdge((*v), (*it))->weight;

            int dist_w =  dist.find((*it)->name)->second;

            if (dist_v + cvw < dist_w)
            {
                dist.find((*it)->name)->second = dist_v + cvw;
                path.find((*it)->name)->second = name;
            }
            // }
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

        g.addEdge(p1, p2, weight);
    }

    g.printGraph();

    int start;

    cin.clear();
    cout << "input start point: ";
    cin >> start;

    auto it = find(g.points.begin(), g.points.end(), Vertex { start });
    
    unordered_map<int, int> dist;
    unordered_map<int, int> path;

    djikstra(g, *it, dist, path);

    int end;
    cout << "\ninput end point: ";
    cin >> end;

    printPath(path, end);

    cout << "\nShortest weighted path is " << dist.find(end)->second << endl;
    

    cout << "Distances: " << '\n';
    for (auto it = dist.begin(); it != dist.end(); ++it)
        cout << it->first << " " << it->second << '\n';

    cout << "Path: " << '\n';
    for (auto it = path.begin(); it != path.end(); ++it)
        cout << it->first << " " << it->second <<'\n';
    
    return 0;
}
