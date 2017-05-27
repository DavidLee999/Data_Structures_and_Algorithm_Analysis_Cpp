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
	
	Collection( int len )
	{
		if (len <= 0)
		{
			length = 0;
			array = nullptr;
			cout<<"wrong input."<<endl;
			return;
		}
		
		length = len;
		array = new Type[len]{};
	}
	
	size_t size() { return length; }
};
int main()
{
	Collection<int> c {-1};
	cout << c.size();
	return 0;
}