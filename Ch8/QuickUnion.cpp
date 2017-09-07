#include <iostream>
#include <vector>
using namespace std;

class QuickUnion
{
    public:
        explicit QuickUnion(int numElements) : s (numElements, -1) {}

        int find(int x)
        {
            return findRoot(x);
        }

        bool connected(int p, int q)
        {
            return (findRoot(p) == findRoot(q));
        }

        void unionSets(int p, int q)
        {
            int root1 = findRoot(p);
            int root2 = findRoot(q);

            if (s[root2] < s[root1])
                s[root1] = root2;
            else
            {
                if (s[root1] == s[root2])
                    --s[root1];
                s[root2] = root1;
            }
        }

    private:
        int findRoot(int x)
        {
            if (s[x] < 0)
                return x;
            else
                return s[x] = findRoot(s[x]);
        }

        vector<int> s;
};

