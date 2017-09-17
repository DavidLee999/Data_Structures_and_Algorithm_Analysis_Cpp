#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

#include "Vertex.h"
#include "Edges.h"

#include "Vertex.cpp"

struct Graph
{
    vector<shared_ptr<Vertex> > points;
    vector<Edge> lines;

    explicit Graph() {}

    const Edge* findEdge(const Edge& line) const
    {
        auto it = find(lines.begin(), lines.end(), line);

        if (it == lines.end())
            return nullptr;
        else
            return &(*it);
    }

    const Edge* findEdge(const shared_ptr<Vertex>& from, const shared_ptr<Vertex>& to) const
    {
        Edge line {from, to};
        
        auto it = find(lines.begin(), lines.end(), line);

        if (it == lines.end())
            return nullptr;
        else
            return &(*it);
    }

    void addEdge(const shared_ptr<Vertex>& p1, const shared_ptr<Vertex>& p2, int w = 1)
    {
        auto it1 = find(points.begin(), points.end(), p1);
        auto it2 = find(points.end(), points.end(), p2);

         if (it1 == points.end() && it2 == points.end())
        {
            ++(p2->indegree);
            p1->add(p2);

            Edge line {p1, p2, w};

            points.push_back(p1);
            points.push_back(p2);
            lines.push_back(line);
        }

        else if (it1 != points.end() && it2 == points.end())
        {
            ++(p2->indegree);
            (*it1)->add(p2);

            Edge line{*it1, p2, w};

            points.push_back(p2);
            lines.push_back(line);
        }

        else if (it1 == points.end() && it2 != points.end())
        {
            ++((*it2)->indegree);
            p1->add(*it2);

            Edge line {p1, *it2, w};

            points.push_back(p1);
            lines.push_back(line);
        }

        else if (it1 != points.end() && it2 != points.end())
        {
            if ((*it1)->isLinked(*it2) == false)
            {
                ++((*it2)->indegree);
                (*it1)->add(*it2);

                Edge line{*it1, *it2, w};

                lines.push_back(line);
            }
        }
    }

    void printGraph(ostream& out = cout)
    {
        for (auto it = points.begin(); it != points.end(); ++it)
        {
            for (auto it2 = (*it)->adj.begin(); it2 != (*it)->adj.end(); ++it2)
            {
                out << (*it)->name << " -> ";
                out << (*it2)->name << " w: " << findEdge(*it, *it2)->weight << '\n';
            }
        }
    }
};


#endif
