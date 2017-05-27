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
	
	Collection ( const Collection &rhs ): length{ rhs.size() }
	{
		array = new Type[length] {};
		
	}
	
	Type & operator[] ( int i )
	{
		if ( i < 0 || i > length )
		{
			cout << "wrong index." << endl;
			exit(0);
		}
		
		return array[i];
	}
	
	size_t size() { return length; }
	
	bool isEmpty() { return (length == 0); }
};
int main()
{
	Collection<int> c {1,2,3};
	c[0] = c[1];
	cout<<c[0];
	return 0;
}