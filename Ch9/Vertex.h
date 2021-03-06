#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <List>
#include <algorithm>
#include <memory>
using namespace std;

// template <typename Name>
struct Vertex
{
    int name;
    int indegree;
    list< shared_ptr<Vertex> > adj;

    
    Vertex(const int& n) : name { n }, indegree { 0 }, adj { }
    {
    }

    void add(const shared_ptr<Vertex>& ptr)
    {
        if (find(adj.begin(), adj.end(), ptr) == adj.end())
        {
            adj.push_back(ptr);
        }
    }

    bool isLinked(const shared_ptr<Vertex>& ptr) const
    {
        auto it = find(adj.begin(), adj.end(), ptr);
        if ( it != adj.end())
            return true;
        else
            return false;
    }

};

inline bool operator== (const shared_ptr<Vertex>& p, const shared_ptr<Vertex>& q)
{
    return p->name == q->name;
}

inline bool operator== (const shared_ptr<Vertex>& p, const Vertex& q)
{
    return p->name == q.name;
}

inline bool operator== (const Vertex& q, const shared_ptr<Vertex>& p)
{
    return p->name == q.name;
}

inline bool operator== (const Vertex& p, const Vertex& q)
{
    return p.name == q.name;
}

#endif

