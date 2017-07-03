template <typename Type>
class Queue{
	private:
	    int head;
		int last;
		int theSize;
		int theCapacity;
		static const int SPARE_CAPACITY = 2;
		Type* arr;
		
            void reserve( int newCapacity )
	    {
	        Type* new_arr = new Type[newCapacity]{};
		
		for( int i = 0; i < theSize; ++i )
		    new_arr[i] = arr[(head + i) % theCapacity];
		    
		std::swap( arr, new_arr );
		theCapacity = newCapacity;
		
		delete[] new_arr;
	    }
	    
	public:
	    Queue() : theSize{ 0 }, theCapacity{ theSize + SPARE_CAPACITY }, head{ 0 }, last{ 0 }
		{
			arr = new Type[theCapacity]{};
		}
		
		Queue( const Queue& rhs ) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }
		{
		    arr = new Type[theCapacity]{};
			for( int i = 0; i < rhs.theSize; ++i )
				arr[i] = rhs.arr[(rhs.head + i) % rhs.theCapacity]
			
			head = 0;
			last = rhs.theSize;
		}
		
		Queue§ operator = ( const Queue& rhs )
		{
			Queue copy = rhs;
			std::swap( *this, copy );
			
			return *this;
		}
		
		Queue( Queue&& rhs ) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, head{ rhs.head }, last{ rhs.last }, arr{ rhs.arr }
		{
			rhs.theSize = 0;
			rhs.theCapacity = 0;
			rhs.head = 0;
			rhs.last = 0;
			rhs.arr = nullptr;
		}
		
		Queue& operator = ( Queue&& rhs )
		{
			std::swap( theSize, rhs.theSize );
            std::swap( theCapacity, rhs.theCapacity );
            std::swap( head, rhs.head );
            std::swap( last, rhs.last );
            std::swap( arr, rhs.arr );
			
			return *this;
		}
		
		~Queue() { delete[] arr; }
		
		void enqueue( const Type& x )
		{
			if( theSize == theCapacity )
				reserve( 2 * theCapacity );
			
			arr[last++] = x;
			theSize++;
			
			if( last == theCapacity )
				last = 0;
		}
		
		Type dequeue()
		{
			Type item = arr[head];
			
			arr[head++] = Type{};
			theSize--;
			
			if( head == theCapacity )
				head = 0;
			
			if( theSize > 0 && theSize == theCapacity / 4 )
				reserve( theCapacity / 2 );
			
			return item;
		}
		
		bool isEmpty() const { return theSize == 0; }
		int size() const { return theSize; }
		
};
