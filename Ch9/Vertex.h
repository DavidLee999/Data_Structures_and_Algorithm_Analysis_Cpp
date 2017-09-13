#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <List>
#include <algorithm>
using namespace std;

// template <typename Name>
struct Vertex
{
    int name;
    int indegree;
    list<Vertex> adj;

    Vertex () {}
    
    Vertex(const int& n) : name { n }, indegree { 0 }, adj { }
    {
    }

    void add(Vertex& t)
    {
        if (find(adj.begin(), adj.end(), t) == adj.end())
        {
            adj.push_back(t);
            // ++indegree;
        }
    }

    bool isLinked(const Vertex& t) const
    {
        auto it = find(adj.begin(), adj.end(), t);
        if ( it != adj.end())
            return true;
        else
            return false;
    }

};

bool operator== (const Vertex& p, const Vertex& q)
{
    return q.name == p.name;
}

#endif

