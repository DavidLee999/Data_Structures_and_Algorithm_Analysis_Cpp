#include <iostream>
#include <initializer_list>
using namespace std;

template <typename Type>
class Collection{
private:
	size_t length;
	Type* array;
	size_t capacity;
	
public:
	Collection() : length { 0 }, array { nullptr } , capacity { 10 } {}
	
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
		capacity = 2*length + 1;
	}
	
	Collection(initializer_list<Type> ini_list)
	{
		length = ini_list.size();
		
		capacity = 2*length + 1;
		
		array = new Type[length] {};
		
		int counter { 0 };
		for ( auto i:ini_list) //(initializer_list<Type>::interator ini_iter = ini_list.begin(); ini_iter != ini_list.end; ++ini_iter)
			array[counter++] = i;
	}
	
	Collection ( const Collection &rhs ): length{ rhs.size() }, capacity { 2*length + 1 }
	{
		array = new Type[length] {};
		
		for ( int i = 0; i < length; ++i)
			array[i] = rhs[i];
	}
	
	~Collection() { delete[] array; }
	
	Type & at( int i )
	{
		if ( i < 0 || i >= length )
		{
			cout << "wrong index." << endl;
			exit(0);
		}
		
		return array[i];
	}
	
	Type & operator[] ( int i ) { return at(i); }	
	
	Collection & operator= (const Collection &rhs)
	{
		if ( this !=  &rhs )
		{
			length = rhs.size();
			
			capacity = 2*length + 1;
			
			array = new Type[length] {};
			
			for (int i = 0; i < length; ++i)
				array[i] = rhs[i];
		}
		
		return *this;
	}
	
	size_t size() { return length; }
	
	bool isEmpty() { return (length == 0); }
	
	void makeEmpty()
	{
		length = 0;
		delete[] array;
		array = nullptr;
	}
};
int main()
{
	Collection<int> c {1,2,3};
	
	c.makeEmpty();
	
	cout<<c.size();
	return 0;
}