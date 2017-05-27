#include <iostream>
#include <initializer_list>
using namespace std;

template <typename Type>
class Collection{
private:
	size_t length;
	Type* array;
	
public:
	Collection() : length { 0 }, array { nullptr } {};
	
	size_t size() { return length; }
};
int main()
{
	Collection<int> c {};
	cout << c.size();
	return 0;
}