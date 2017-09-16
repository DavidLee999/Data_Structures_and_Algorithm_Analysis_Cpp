#include <iostream>
// #include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
using namespace std;

#include "Vertex.h"
#include "Vertex.cpp"

void topSort(const vector<shared_ptr<Vertex> >& points)
{
    std::vector<shared_ptr<Vertex> > p = points;
    std::queue<shared_ptr<Vertex> > q;
    
    for (auto it = p.begin(); it != p.end(); ++it)
    {
        if ((*it)->indegree == 0)
            q.push(*it);
    }

    while (!q.empty()) {
        shared_ptr<Vertex>& v = q.front();
        q.pop();

        cout << v->name << " ";

        for (auto it = v->adj.begin(); it != v->adj.end(); ++it)
        {
            if (--((*it)->indegree) == 0)
                q.push(*it);
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

        readEdges(points, p1, p2);
        // auto it1 = find(points.begin(), points.end(), p1);
        // auto it2 = find(points.begin(), points.end(), p2);

        // if (it1 == points.end() && it2 == points.end())
        // {
            // ++(p2->indegree);
            // p1->add(p2);

            // points.push_back(p1);
            // points.push_back(p2);
        // }

        // else if (it1 != points.end() && it2 == points.end())
        // {
            // ++(p2->indegree);
            // (*it1)->add(p2);

            // points.push_back(p2);
        // }

        // else if (it1 == points.end() && it2 != points.end())
        // {
            // ++((*it2)->indegree);
            // p1->add(*it2);

            // points.push_back(p1);
        // }

        // else if (it1 != points.end() && it2 != points.end())
        // {
            // if ((*it1)->isLinked(*it2) == false)
            // {
                // ++((*it2)->indegree);
                // (*it1)->add(*it2);
            // }
        // }

    }

    for (auto it = points.begin(); it != points.end(); ++it)
    {
        cout << (*it)->name << " " << (*it)->indegree <<  ": ";
        for (auto it2 = (*it)->adj.begin(); it2 != (*it)->adj.end(); ++it2)
            cout << (*it2)->name << " ";
        cout << endl;
    }

    cout << "topological sort: ";
    topSort(points);
    cout << endl;

    return 0;
}
