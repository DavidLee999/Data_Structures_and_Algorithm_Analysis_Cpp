#include <initializer_list>
#include <algorithm>
#include <ostream>
#include <iostream>

template <typename Type>
class Stack {
    private:
        size_t theSize;
        size_t theCapacity;
        static const int SPARE_CAPACITY = 2;
        Type* arr;

        void reserve( size_t newCapacity )
        {
            Type* new_arr = new Type[newCapacity]{};

            std::copy( &arr[0], &arr[theSize], new_arr );

            std::swap( arr, new_arr );

            theCapacity = newCapacity;

            delete[] new_arr;
        }
    public:
        explicit Stack( int initSize = 0 ) : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
        {
            arr = new Type[theCapacity]{};
        }

        Stack( const std::initializer_list<Type>& init_list ) : theSize{ init_list.size() }
        {
            theCapacity = 2 * theSize;

            arr = new Type[theCapacity]{};

            std::copy( init_list.begin(), init_list.end(), arr );
        }

        Stack( const Stack& rhs ) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }
        {
            arr = new Type[theCapacity]{};

            std::copy( &rhs.arr[0], &rhs.arr[rhs.theSize], arr );
        }

        Stack& operator = ( const Stack& rhs )
        {
            Stack temp = rhs;
            std::swap( *this, temp );

            return *this;
        }

        Stack( Stack&& rhs ) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, arr{ rhs.arr }
        {
            rhs.theSize = 0;
            rhs.theCapacity = 0;
            rhs.arr = nullptr;
        }

        Stack& operator = ( Stack&& rhs )
        {
            std::swap( theSize, rhs.theSize );
            std::swap( theCapacity, rhs.theCapacity );
            std::swap( arr, rhs.arr );

            return *this;
        }

        ~Stack() { delete[] arr; }

        void push_back( const Type& item )
        {
            if( theSize == theCapacity )
                reserve( 2 * theCapacity );

            arr[theSize++] = item;
        }

        Type pop_back()
        {
            if( isEmpty() )
                throw std::out_of_range( "The Stack is Empty!" );

            Type item = arr[--theSize];

            arr[theSize] = Type{};

            if( theSize > 0 && theSize == theCapacity / 4 )
                reserve( theCapacity / 2 );

            return item;
        }

        const Type& back() const
        {
            return arr[theSize - 1];
        }
        // Type operator [] ( int i ) const { return arr[i]; }

        int size() const { return theSize; }
        int capacity() const { return theCapacity; }
        bool isEmpty() const { return theSize == 0; }
};


// template <typename T>
// std::ostream& operator << ( std::ostream& out, const Stack<T>& obj )
// {
//     for( int i = 0; i < obj.size(); ++i )
//         out << obj[i] << '\t';

//     return out;
// }


int main()
{
    Stack<int> a {1,3,4,5};
    std::cout << a.back();
    // std::cout << a << '\n';
    // std::cout << a.size() << '\t' << a.capacity() << '\n';

    // int b {};
    // while( std::cin >> b )
    // {
    //     if( b == 0 )
    //         std::cout << a.pop_back() << '\n';
    //     else if( b == 9 )
    //     {
    //         std::cout << a << '\n';
    //         std::cout << a.size() << a.capacity() << '\n';
    //     }
    //     else
    //         a.push_back(b);
    // }

    return 0;
}
