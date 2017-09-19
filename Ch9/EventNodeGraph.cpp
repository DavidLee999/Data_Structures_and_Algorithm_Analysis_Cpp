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

void earliestTime(const Graph& g, const shared_ptr<Vertex>& item, unordered_map<int, int>& dist, unordered_map<int, int>& path)
{
    const int MAX = -1; // std::numeric_limits<int>::min();

    vector<int> tp_order = topSort(g.points);

    for (auto it = g.points.begin(); it != g.points.end(); ++it)
    {
        dist.insert( make_pair((*it)->name, MAX) );
        path.insert( make_pair((*it)->name, 0) );
    }

    dist.find(item->name)->second = 0;

    for (auto start = find(tp_order.begin(), tp_order.end(), item->name); start != tp_order.end(); ++start)
    {
        int name = *start;
        int dist_v = dist.find(name)->second;

        auto v = find(g.points.begin(), g.points.end(), Vertex{ name });

        for (auto it = (*v)->adj.begin(); it != (*v)->adj.end(); ++it)
        {
            int cvw = g.findEdge((*v), (*it))->weight;

            int dist_w =  dist.find((*it)->name)->second;

            if (dist_v + cvw > dist_w)
            {
                dist.find((*it)->name)->second = dist_v + cvw;
                path.find((*it)->name)->second = (*v)->name;
            }
        }

    } 
}

void latestTime(const Graph& g, const shared_ptr<Vertex>& item, unordered_map<int, int>& dist, int latestWeight)
{
    const int MAX = 100; std::numeric_limits<int>::min();

    vector<int> tp_order = topSort(g.points);

    for (auto it = g.points.begin(); it != g.points.end(); ++it)
        dist.insert( make_pair((*it)->name, MAX) );

    dist.find(item->name)->second = latestWeight;


    for (auto start = tp_order.rbegin(); start != tp_order.rend(); ++start)
    {
        int name = *start;
        int dist_v = dist.find(name)->second;

        auto v = find(g.points.begin(), g.points.end(), Vertex{ name });

        // for (auto it = (*v)->adj.begin(); it != (*v)->adj.end(); ++it)
        for (auto it = g.points.begin(); it != g.points.end(); ++it)
        {
            if ((*it)->isLinked((*v)))
            {
                int cvw = g.findEdge((*it), (*v))->weight;

                int dist_w =  dist.find((*it)->name)->second;

                if (dist_v - cvw < dist_w)
                    dist.find((*it)->name)->second = dist_v - cvw;
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

    // earliestTime(g, *it, dist, path);
    latestTime(g, *it, dist, 10);

    // int end;
    // cout << "\ninput end point: ";
    // cin >> end;

    // printPath(path, end);

    // cout << "\nShortest weighted path is " << dist.find(end)->second << endl;
    
    cout << "Distances: " << '\n';
    for (auto it = dist.begin(); it != dist.end(); ++it)
        cout << it->first << " " << it->second << '\n';

    cout << "Path: " << '\n';
    for (auto it = path.begin(); it != path.end(); ++it)
        cout << it->first << " " << it->second <<'\n';
    return 0;
}
