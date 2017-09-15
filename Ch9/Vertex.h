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

    // Vertex () {}
    
    Vertex(const int& n) : name { n }, indegree { 0 }, adj { }
    {
    }

    void add(shared_ptr<Vertex> ptr)
    {
        // shared_ptr<Vertex> ptr (t);
        if (find(adj.begin(), adj.end(), ptr) == adj.end())
        {
            adj.push_back(ptr);
            // ++indegree;
        }
    }

    bool isLinked(const shared_ptr<Vertex>& ptr) const
    {
        // shared_ptr<Vertex> ptr (t);
        auto it = find(adj.begin(), adj.end(), ptr);
        if ( it != adj.end())
            return true;
        else
            return false;
    }

};

bool operator== (const shared_ptr<Vertex>& p, const shared_ptr<Vertex>& q)
{
    return p->name == q->name;
}

#endif

