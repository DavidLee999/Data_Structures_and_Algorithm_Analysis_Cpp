#include <iostream>
// #include <list>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <memory>
using namespace std;

#include "Vertex.h"

void shortestPath(const vector<shared_ptr<Vertex> >& points, const shared_ptr<Vertex>& item, map<int, int>& dist, map<int, int>& path)
{
    const int MAX = 100;

    std::queue<shared_ptr<Vertex> > q;
    for (auto it = points.begin(); it != points.end(); ++it)
    {
        dist.insert(make_pair((*it)->name, MAX));
        path.insert(make_pair((*it)->name, 0));
    }

    dist.find(item->name)->second = 0;
    
    auto ptr = find(points.begin(), points.end(), item);
    q.push(*ptr);

    while (!q.empty()) {
        shared_ptr<Vertex>& v = q.front();
        q.pop();

        int currDist = dist.find(v->name)->second;
        for (auto it = v->adj.begin(); it != v->adj.end(); ++it)
        { 
            if (dist.find((*it)->name)->second == MAX)
            {
                dist.find((*it)->name)->second = currDist + 1;
                path.find((*it)->name)->second = v->name;
                q.push(*it);
            }
        }
    }
}

int main()
{
    vector<shared_ptr<Vertex> > points;
    int from, to;

    while (cin >> from >> to) {

        shared_ptr<Vertex> p1 { new Vertex { from } };
        shared_ptr<Vertex> p2 { new Vertex { to } };

        auto it1 = find(points.begin(), points.end(), p1);
        auto it2 = find(points.begin(), points.end(), p2);

        if (it1 == points.end() && it2 == points.end())
        {
            ++(p2->indegree);
            p1->add(p2);

            points.push_back(p1);
            points.push_back(p2);
        }

        else if (it1 != points.end() && it2 == points.end())
        {
            ++(p2->indegree);
            (*it1)->add(p2);

            points.push_back(p2);
        }

        else if (it1 == points.end() && it2 != points.end())
        {
            ++((*it2)->indegree);
            p1->add(*it2);

            points.push_back(p1);
        }

        else if (it1 != points.end() && it2 != points.end())
        {
            if ((*it1)->isLinked(*it2) == false)
            {
                ++((*it2)->indegree);
                (*it1)->add(*it2);
            }
        }
    }

    cin.clear();
    int start;
    cout << "input start point: ";
    cin >> start;

    shared_ptr<Vertex> item (new Vertex { start });
    map<int, int> dist;
    map<int, int> path;

    shortestPath(points, item, dist, path);

    cout << "Distances: " << '\n';
    for (auto it = dist.begin(); it != dist.end(); ++it)
        cout << it->first << " " << it->second << '\n';

    cout << "Path: " << '\n';
    for (auto it = path.begin(); it != path.end(); ++it)
        cout << it->first << " " << it->second <<'\n';

    return 0;
}
