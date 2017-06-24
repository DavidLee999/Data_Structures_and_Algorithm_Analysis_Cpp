#include <iostream>
#include <ostream>
#include <initializer_list>
#include <memory>
#include <algorithm>
#include <typeinfo>
using namespace std;

template <typename Type>
class Collection{
private:
	size_t length;
	size_t capacity;
	Type* array;
	
	
	bool resize(size_t new_capac)  //increasing capacity
	{
		/* if ( new_capac <= length || new_capac <= capacity )
			return false; */
		
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
	
	bool check( int n ) const
	{
	    if ( n < 0 || length <= n ) {
	        return false;
	        throw std::out_of_range( "The index is out of range" );
	    }
	    
	    return true;
	}
	
public:
	Collection() : length { 0 }, array { nullptr } , capacity { 2 } {} // default constructor
	
	explicit Collection( const int, const Type t = Type {} ); // constructor
	
	Collection( const initializer_list<Type> &  ); // constructor
	
	Collection ( const Collection & ); // copy constructor
	
	Collection ( Collection && ); // move constructor
	
	Collection ( Type* ini_arr, Type* end_arr ); // array constructor
	
	Collection & operator = ( const Collection & ); // copy assignment
	
	Collection & operator = ( Collection && ); //move assignment
	
	~Collection() { delete[] array; }
	
	Type & at( int ); //element accessor
	Type at( int ) const;
	
	Type & operator[] ( int );
	Type operator [] ( int ) const;
		
	size_t size() const { return length; }
	
	bool isEmpty() const { return ( length == 0 ); }
	
	void makeEmpty(); // to be done
	
	bool insert( int , const Type & );
	
	bool remove( int );
	
	bool push_back ( const Type & t ) { return insert( length, t ); }
	
	Type pop_back ();
	
	Type* begin() const { return array; }
	
	Type* end() const { return array + length; }
	
	size_t getCapacity() const { return capacity; }
	
	bool contain(const Type &) const;
	
};



template <typename Type>
Collection<Type>::Collection( const int len, const Type t) // constructor
{
	if (len <= 0)
	{
		length = 0;
		array = nullptr;
		cout << "wrong input." << endl;
		return;
	}
		
	length = len;
	capacity = 2*length;
	array = new Type[capacity] {};
	
	if ( t != Type {} )
		fill( array, array + length, t );
}

template <typename Type>	
Collection<Type>::Collection( const initializer_list<Type> & ini_list ) : length { ini_list.size() }// constructor
{
	capacity = 2*length;
		
	array = new Type[capacity] {};
		
	/* int counter { 0 };
	typename initializer_list<Type>::const_iterator ini_iter = ini_list.begin();
	for (; ini_iter != ini_list.end(); ++ini_iter)
		array[counter++] = *ini_iter; */
		
	uninitialized_copy( ini_list.begin(), ini_list.end(), array );
}
template <typename Type>
Collection<Type>::Collection ( const Collection &rhs ):length{ rhs.size() }, capacity { rhs.getCapacity() } //copy constructor
{	
	array = new Type[capacity] {};
		
		/* for ( int i = 0; i < length; ++i)
			array[i] = rhs[i]; */
		
	uninitialized_copy( rhs.begin(), rhs.end(), array );
}
	
template <typename Type>
Collection<Type>::Collection ( Collection &&rhs ) : length { rhs.size() }, capacity { rhs.getCapacity() }, array { rhs.array }// move constructor
{	
	rhs.length = 0;
	rhs.array = nullptr;
}

template <typename Type> 
Collection<Type> & Collection<Type>::operator = ( const Collection &rhs ) //copy assignment
{
	if ( this !=  &rhs )
	{
		length = rhs.size();
			
		capacity = 2*length;
			
		array = new Type[capacity] {};
			
		/* for ( int i = 0; i < length; ++i )
			array[i] = rhs[i];  */
		copy( rhs.begin(), rhs.end(), array );
			
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
Collection<Type>::Collection ( Type* ini_arr, Type* end_arr ) // array constructor
{
	length = end_arr - ini_arr;
		
	capacity = 2*length;
		
	array = new Type[capacity] {};
	
	copy( ini_arr, end_arr, array );
}

template <typename Type> 
inline Type & Collection<Type>::at( int i ) // element accessor
{
	/* if ( i < 0 || i >= length )
	{
		cout << "wrong index." << endl;
		exit(0);
	} */
	
	check( i );
		
	return array[i];
}

template <typename Type> 
inline Type Collection<Type>::at( int i ) const // element accessor
{
	check( i );
		
	return array[i];
}

template <typename Type> 
inline Type & Collection<Type>:: operator [] ( int i ) // element accessor
{
	check( i );
		
	return array[i];
}

template <typename Type> 
inline Type Collection<Type>:: operator [] ( int i ) const // element accessor
{
	check( i );
		
	return array[i];
}

template <typename Type>
void Collection<Type>::makeEmpty()// to be done
{
	fill( array, array + length, Type{} );
 	
	length = 0;
}
	
template <typename Type>
bool Collection<Type>::insert( int index, const Type &t)
{
	check( index );
		
	if ( index == 0 && length == 0)
	{
		++length;
		capacity = 2*length;
		array = new Type[capacity] {};
		
		array[index] = t;
	}
	
	if ( length == capacity )
	{
		bool su = resize(2*capacity); 
		
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
	check ( index );
	
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
	
	if( length > 0 && length == capacity / 4 )
        resize(capacity / 2);
	
	return true;
	
}

template <typename Type>
Type Collection<Type>::pop_back()
{
	if ( length == 0 )
	{
		cout << "The Collection is empty!." << endl;
		exit(0);
	}
	
	Type item = array[length-1];
	remove( length-1 );
	
	return item;
}

template <typename Type>
bool Collection<Type>::contain(const Type &t) const
{
	Type* result = find( array, array + length, t );
	
	if ( result == array + length ) return false;
	else return true;
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
    char p[] = "li";
	Collection<char> e (p, p+2);

	
	char ch;
	while( cin >> ch && !isspace( ch ) ){
		if ( ch == '-' )
			char temp = e.pop_back();	
		else
			e.push_back(ch);
		
		cout << e << e.size() << '\t' << e.getCapacity() << endl;
	}
	return 0;
}
