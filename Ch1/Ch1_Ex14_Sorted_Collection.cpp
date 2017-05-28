#include <iostream>
#include <ostream>
#include <initializer_list>
using namespace std;

//template <typename Tpye>
//ostream& operator<< (ostream &out, const Collection<Tpye> &obj);

template <typename Type>
class Collection{
private:
	size_t length;
	Type* array;
	size_t capacity;
	
	bool enlarge(size_t new_capac)  //increasing capacity
	{
		if (new_capac <= length || new_capac <= capacity)
			return false;
		
		Type* new_arr = new Type[new_capac];
		
		capacity = new_capac;
		
		for( size_t i = 0; i < length; ++i)
		{
			new_arr[i] = array[i];
		}
		
		swap(array, new_arr);		
		
		delete[] new_arr;
		
		return true;
	}
	
	void bubbleSort()
	{
		for ( size_t i = 0; i < length - 1; ++i)
		{
			for ( size_t j = 0; j < length - i - 1; ++j)
			{
				if ( array[j] > array[j+1] )
					swap(array[j+1], array[j]);
			}
		}
	}
	
public:
	Collection() : length { 0 }, array { nullptr } , capacity { 10 } {} //default constructor
	
	Collection( int len ) // constructor
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
	
	Collection(initializer_list<Type> ini_list) // constructor
	{
		length = ini_list.size();
		
		capacity = 2*length + 1;
		
		array = new Type[capacity] {};
		
		int counter { 0 };
		for ( auto i:ini_list) //(initializer_list<Type>::interator ini_iter = ini_list.begin(); ini_iter != ini_list.end; ++ini_iter)
			array[counter++] = i;
		
		bubbleSort();

	}
	
	Collection ( Collection &rhs ):length{ rhs.size() } //copy constructor
	{
		capacity = 2*length + 1;
		
		array = new Type[capacity] {};
		
		for ( int i = 0; i < length; ++i)
			array[i] = rhs[i];
	}
	
	Collection ( Collection &&rhs ) // move constructor
	{
		swap( length, rhs.size() );
		
		capacity = 2*length + 1;
		
		array = new Type[capacity] {};		
		
		swap(array, rhs.array);
	}
	
	Collection (Type* ini_arr, Type* end_arr) //array constructor
	{
		length = end_arr - ini_arr;
		
		//length = sizeof(ini_arr) / sizeof(Type);
		
		capacity = 2*length + 1;
		
		array = new Type[capacity]{};
		
		for ( size_t i = 0; i < length; ++i)
			array[i] = ini_arr[i];
		
		bubbleSort();
	}
	
	
	~Collection() { delete[] array; }
	
	Type & at( int i ) //element accessor
	{
		if ( i < 0 || i >= length )
		{
			cout << "wrong index." << endl;
			exit(0);
		}
		
		return array[i];
	}
	
	Type & operator[] ( int i ) { return at(i); }	
	
	Collection & operator= (const Collection &rhs) //copy assignment
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
	
	Collection & operator= ( Collection &&rhs ) //move assignment
	{
		swap(*this, rhs);
		
		return *this;
	}
	
	size_t size() const { return length; }
	
	bool isEmpty() const { return (length == 0); }
	
	void makeEmpty()
	{
		length = 0;
		//delete[] array;
		//array = nullptr;
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
		
		bubbleSort();
		
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
	
	/* void print()
	{
		for ( size_t i = 0; i < length; ++i)
			cout << array[i] << " ";
		
		cout<<endl;
	} */
	
	size_t getCapacity() { return capacity; }
	
	bool contain(const Type &t) const
	{
		for ( size_t i = 0; i < length; ++i)
		{
			if (array[i] == t)
				return true;
		}
		
		return false;
	}
	
	Type findMin() const { return array[0]; }
	Type findMax() const { return array[length-1]; }
	
	friend ostream& operator<<(ostream &out, Collection<Type> &obj)
	{
		for ( size_t i = 0; i < obj.size(); ++i )
			out << obj[i] <<" ";
	
		out<<endl;
	
		return out;
	}
};



int main()
{
	Collection<int> c {1,2,3};
	
	Collection<int> a {c};
	
	c.insert(1,0);
	
	c.insert(c.size(),4);
	
	c.insert(c.size(),5);
	
	c.insert(c.size(),6);
	
	c.insert(c.size(),7);
	
	//c.print();
	
	cout << c;
	
	cout<<c.size()<<endl<<c.getCapacity()<<endl;
	
	c.remove(3);
	
	cout<<c.size()<<endl;
	
	cout << c;
	
	cout << c;
	
	a.remove(0);
	
	a.remove(0);
	
	a.remove(0);
	
	cout<<a.size()<<endl;
	
	cout<<c.contain(4)<<" "<<c.contain(100)<<endl;
	
	Collection<int> b = c;
	
	cout << b;
	
	int d[4] {4,3,2,1};
	
	Collection<int> e{&d[0], &d[4]}; //one beyond the array's length is required
	
	cout << e;

	cout<<e.size()<<endl<<e.getCapacity()<<endl;
	return 0;
}