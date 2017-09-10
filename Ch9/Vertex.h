#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <List>
using namespace std;

// template <typename Name>
struct Vertex
{
    int name;
    list<Vertex> adj;

    Vertex () {}
    
    Vertex(const int& n) : name { n }
    {
    }
};

bool operator== (const Vertex& p, const Vertex& q)
{
    return q.name == p.name;
}

#endif

