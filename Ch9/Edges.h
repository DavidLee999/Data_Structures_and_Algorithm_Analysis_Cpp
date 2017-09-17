#ifndef EDGE_H
#define EDGE_H


#include <iostream>
#include <memory>
using namespace std;

#include "Vertex.h"

struct Edge
{
    shared_ptr<Vertex> start;
    shared_ptr<Vertex> end;

    int weight;

    Edge(const shared_ptr<Vertex>& s, const shared_ptr<Vertex>& e, int w = 1) : start { s }, end { e }, weight { w } {}

    Edge(Vertex& s, Vertex& e,int w = 1) : start { &s }, end { &e }, weight { w } {}
};

bool operator== (const Edge& p, const Edge& q)
{
    return ((p.start == q.start) && (p.end == q.end));
}

bool operator< (const Edge& p, const Edge& q)
{
    return p.weight < q.weight;
}

bool operator> (const Edge& p, const Edge& q)
{
    return p.weight > q.weight;
}

#endif
