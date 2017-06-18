#include <iostream>
#include <ostream>
#include <initializer_list>
#include <memory>
#include <algorithm>
using namespace std;

template <typename Type>
class Collection{
private:
	size_t length;
	size_t capacity;
	Type* array;
	
	
	bool enlarge(size_t new_capac)  //increasing capacity
	{
		if ( new_capac <= length || new_capac <= capacity )
			return false;
		
		Type* new_arr = new Type[new_capac];
		
		capacity = new_capac;
		
		for( size_t i = 0; i < length; ++i ) 
		{
			new_arr[i] = array[i];
		}
		
		swap( array, new_arr );		
		
		delete[] new_arr;
		
		return true;
	}
	
public:
	Collection() : length { 0 }, array { nullptr } , capacity { 10 } {} // default constructor
	
	Collection( int ); // constructor
	
	Collection( const initializer_list<Type> &  ); // constructor
	
	Collection ( const Collection & ); // copy constructor
	
	Collection ( Collection && ); // move constructor
	
	Collection ( Type* ini_arr, Type* end_arr ); // array constructor
	
	Collection & operator = ( const Collection & ); // copy assignment
	
	Collection & operator = ( Collection && ); //move assignment
	
	~Collection() { delete[] array; }
	
	Type & at( int ) const; //element accessor
	
	Type & operator[] ( int i ) const { return at(i); }	
		
	size_t size() const { return length; }
	
	bool isEmpty() const { return ( length == 0 ); }
	
	void makeEmpty(); // to be done
	
	bool insert( int , const Type & );
	
	bool remove( int );
	
	size_t getCapacity() const { return capacity; }
	
	bool contain(const Type &) const;
	
};

template <typename Type>
Collection<Type>::Collection( int len ) // constructor
{
	if (len <= 0)
	{
		length = 0;
		array = nullptr;
		cout << "wrong input." << endl;
		return;
	}
		
	length = len;
	capacity = 2*length + 1;
	array = new Type[capacity]{};
}

template <typename Type>	
Collection<Type>::Collection(const initializer_list<Type> & ini_list) : length { ini_list.size() }// constructor
{		
	capacity = 2*length + 1;
		
	array = new Type[capacity] {};
		
		/* int counter { 0 };
		for ( auto i:ini_list) //(initializer_list<Type>::interator ini_iter = ini_list.begin(); ini_iter != ini_list.end; ++ini_iter)
			array[counter++] = i; */
		
	uninitialized_copy( ini_list.begin(), ini_list.end(), array );
}
template <typename Type>
Collection<Type>::Collection ( const Collection &rhs ):length{ rhs.size() }, capacity { rhs.getCapacity() } //copy constructor
{	
	array = new Type[capacity] {};
		
		/* for ( int i = 0; i < length; ++i)
			array[i] = rhs[i]; */
		
	uninitialized_copy( &rhs[0], &rhs[0] + rhs.size(), array );
}
	
template <typename Type>
Collection<Type>::Collection ( Collection &&rhs ) : length { rhs.size() }, capacity { rhs.getCapacity() }, array { rhs.array }// move constructor
{	
	rhs.length = 0;
	rhs.array = nullptr;
}

template <typename Type> 
Collection<Type> & Collection<Type>::operator = (const Collection &rhs) //copy assignment
{
	if ( this !=  &rhs )
	{
		length = rhs.size();
			
		capacity = 2*length + 1;
			
		array = new Type[capacity] {};
			
		for ( int i = 0; i < length; ++i )
			array[i] = rhs[i]; 
			
	}
		
	return *this;
}
	
template <typename Type>
Collection<Type> & Collection<Type>::operator = ( Collection &&rhs ) //move assignment
{
	length = rhs.size();
		
	capacity = rhs.getCapacity();
		
	swap( array, rhs.array );
		
	return *this;
}	

template <typename Type>
Collection<Type>::Collection ( Type* ini_arr, Type* end_arr ) //array constructor
{
	length = end_arr - ini_arr;
		
	capacity = 2*length + 1;
		
	array = new Type[capacity] {};
		
	for ( size_t i = 0; i < length; ++i )
		array[i] = ini_arr[i];
}
	

template <typename Type> 
Type & Collection<Type>::at( int i ) const //element accessor
{
	if ( i < 0 || i >= length )
	{
		cout << "wrong index." << endl;
		exit(0);
	}
		
	return array[i];
}
	
template <typename Type>
void Collection<Type>::makeEmpty()// to be done
{
	for(size_t i = 0; i < length; ++i)
		array[i] = 0;
		
 	length = 0;
}
	
template <typename Type>
bool Collection<Type>::insert( int index, const Type &t)
{
	if ( index < 0 || index > length )
	{
		cout << "wrong index." << endl;
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
	
	++length;
	
	return true;
	
}

template <typename Type>
bool Collection<Type>::remove(int index)
{
	if ( index < 0 || index >= length )
	{
		cout << "wrong index." << endl;
		return false;
	}
	
	if( index == 0 && length == 1)
	{
		makeEmpty();
		return true;
	}
	
	for ( size_t i = index; i < length - 1; ++i)
	{
		array[i] = array[i + 1];
	}
	
	--length;
	
	return true;
	
}

template <typename Type>
bool Collection<Type>::contain(const Type &t) const
{
	for ( size_t i = 0; i < length; ++i)
	{
		if (array[i] == t)
			return true;
	}
	
	return false;
}

template <typename Type>
ostream & operator << (ostream &out, const Collection<Type> &obj)
{
	for ( size_t i = 0; i < obj.size(); ++i )
		out << obj[i] <<" ";
	
	out<<endl;
	
	return out;
}





int main()
{	
	Collection<int> c {1, 2, 3};
	c.insert(3, 4);
	
	cout << c << c.size();
	
	return 0;
}
