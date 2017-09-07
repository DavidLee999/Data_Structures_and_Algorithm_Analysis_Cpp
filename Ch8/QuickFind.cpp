#include <vector>
#include <iostream>
using namespace std;

class QuickFind
{
    public:
        explicit QuickFind(int numElements) : s(numElements)
        {
            for (int i = 0; i < numElements; ++i)
                s[i] = i;
        }

        int find(int x) const
        { return s[x]; }

        bool connected(int p, int q) const
        { return s[p] == s[q]; }

        void unionSets(int p, int q)
        {
            if (s[p] == s[q])
                return;

            int pid = s[p];
            int qid = s[q];

            for (int i = 0; i < s.size(); ++i)
                if (s[i] == pid)
                    s[i] = qid;
        }

    private:
        vector<int> s;
};

