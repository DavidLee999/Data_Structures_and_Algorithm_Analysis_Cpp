#include <iostream>
#include <initializer_list>
using namespace std;

template <typename Type>
class Collection{
private:
	size_t length;
	Type* array;
	size_t capacity;
	
	bool enlarge(size_t new_capac)
	{
		if (new_capac <= length || new_capac <= capacity)
			return false;
		
		Type* new_arr = new Type[new_capac];
		
		capacity = new_capac;
		
		for( size_t i = 0; i < length; ++i)
		{
			new_arr[i] == array[i];
		}
		
		swap(array, new_arr);
		
		delete[] new_arr;
		
		return true;
	}
	
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
		capacity = 2*length + 1;
		array = new Type[capacity]{};
	}
	
	Collection(initializer_list<Type> ini_list)
	{
		length = ini_list.size();
		
		capacity = 2*length + 1;
		
		array = new Type[capacity] {};
		
		int counter { 0 };
		for ( auto i:ini_list) //(initializer_list<Type>::interator ini_iter = ini_list.begin(); ini_iter != ini_list.end; ++ini_iter)
			array[counter++] = i;
	}
	
	Collection ( const Collection &rhs ): length{ rhs.size() }, capacity { 2*length + 1 }
	{
		array = new Type[capacity] {};
		
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
			
			array = new Type[capacity] {};
			
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
		//delete[] array;
		array = nullptr;
	}
	
	bool insert( int index, const Type &t)
	{
		if ( index < 0 || index > length )
		{
			cout << "wrong index." <<endl;
			return false;
		}
		
		if ( index == 0 && length == 0)
		{
			++length;
			capacity = 2*length + 1;
			array = new Type[capacity] {};
			
			array[index] = t;
		}
		
		if ( length == capacity )
		{
			bool su = enlarge(2*capacity);
			
			if (!su) return false;
		}
		
		for ( size_t i = length-1; i >= index; --i )
		{
			array[i+1] = array[i];
		}
		
		array[index] = t;
		
		length++;
		
		return true;
		
	}
	
	bool remove(int index)
	{
		if ( index < 0 || index >= length )
		{
			cout << "wrong index." <<endl;
			return false;
		}
		
		if( index == 0 && length == 1)
			return makeEmpty();
		
		for ( size_t i = length - 1; i > index; --i)
		{
			array[i-1] = array[i];
		}
		
		array[--length] = Type{};
		
	}
	
	void print()
	{
		for ( size_t i = 0; i < length; ++i)
			cout << array[i] << " ";
		
		cout<<endl;
	}
	
	size_t getCapacity() { return capacity; }
};
int main()
{
	Collection<int> c {1,2,3};
	
	c.insert(1,0);
	
	cout<<c.size()<<endl;
	
	c.insert(c.size(),4);
	
	cout<<c.size()<<endl;
	
	c.insert(c.size(),5);
	
	c.insert(c.size(),6);
	
	c.insert(c.size(),7);
	
	cout<<c.size()<<endl<<c.getCapacity()<<endl;;
	
	c.print();
	return 0;
}