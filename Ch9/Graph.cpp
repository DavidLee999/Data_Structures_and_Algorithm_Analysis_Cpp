#include <unordered_map>
#include <iostream>
using namespace std;

#include "Graph.h"

void printPath(const unordered_map<int, int>& path, int name, ostream& out = cout)
{
    if (path.find(name)->scond != 0)
    {
        printSingelVertex(path, path.find(name)->second);
        out << " -> ";
    }

    out << name;
}
