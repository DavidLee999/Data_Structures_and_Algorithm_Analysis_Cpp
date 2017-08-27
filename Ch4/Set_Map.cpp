#include <set>
#include <string>
#include <strings.h>
#include <iostream>
using namespace std;

class CaseInsensitiveCompare
{
    public:
        bool operator() (const string& lhs, const string& rhs) const
        { return strcasecmp(lhs.c_str(), rhs.c_str()) < 0; }
};

int main()
{
    set<string, CaseInsensitiveCompare> s;
    
    s.insert("Hello");
    s.insert("HeLLo");

    cout << s.size() << endl;

    return 0;
}
