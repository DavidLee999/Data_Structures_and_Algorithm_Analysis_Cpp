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
	
	Collection(initializer_list<Type> ini_list)
	{
		length = ini_list.size();
		
		array = new Type[length] {};
		
		int counter { 0 };
		for ( auto i:ini_list) //(initializer_list<Type>::interator ini_iter = ini_list.begin(); ini_iter != ini_list.end; ++ini_iter)
			array[counter++] = i;
	}
	
	size_t size() { return length; }
};
int main()
{
	Collection<int> c {1,2,3};
	cout << c.size();
	return 0;
}