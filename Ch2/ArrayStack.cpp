#include <initializer_list>
#include <algorithm>
#include <ostream>
#include <iostream>

template <typename Type>
class Stack {
    private:
        size_t theSize;
        size_t theCapacity;
        static const int SPARE_CAPACITY = 10;
        Type* arr;
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

        Type operator [] ( int i ) const { return arr[i]; }

        int size() const { return theSize; }
};


template <typename T>
std::ostream& operator << ( std::ostream& out, const Stack<T>& obj )
{
    for( int i = 0; i < obj.size(); ++i )
        out << obj[i] << '\t';

    return out;
}


int main()
{
    Stack<int> a {1,3,4,5};
    
    Stack<int> b;
    b = std::move( a );
    std::cout << b << '\n';
    std::cout << b.size() << '\n';

    return 0;
}
