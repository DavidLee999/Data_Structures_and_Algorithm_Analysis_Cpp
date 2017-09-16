#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

#include "Vertex.h"

template <typename Container, typename Contained>
void readEdges(Container& points, Contained& p1, Contained& p2)
{
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
