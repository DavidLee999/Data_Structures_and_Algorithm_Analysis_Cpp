#include <algorithm>
#include <iostream>

template <typename Type>
class Queue {
	private:
        struct Node{
            Type data;
            Node* next;
        };

        size_t theSize;
        Node* head;
        Node* tail;

        void init()
        {
            theSize = 0;
            // head = new Node;
            // tail = new Node;

            // head->next = tail;
            // tail->next = nullptr;

            head = nullptr;
            tail = nullptr;
        }

        void clear()
        {
            while( !isEmpty() )
                dequeue();
        }

	public:
        Queue()
        {
            init();
        }

        Queue( const Queue& rhs )
        {
            init();

            Node* current = rhs.head;
            if (current == nullptr)
                return;

            while( current->next != nullptr )
            {
                enqueue(current->data);
                current = current->next;
            }
        }

        Queue& operator = ( const Queue& rhs )
        {
            Queue copy = rhs;
            std::swap( *this, copy );

            return *this;
        }

        Queue( Queue&& rhs ) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
        {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        Queue& operator = ( Queue&& rhs )
        {
            std::swap( theSize, rhs.theSize );
            std::swap( head, rhs.head );
            std::swap( tail, rhs.tail );

            return *this;
        }

        ~Queue()
        {
            clear();
            delete head;
            delete tail;
        }

        void enqueue( const Type& x )
        {
            Node* oldtail = tail;
            tail = new Node;

            tail->data = x;
            tail->next = nullptr;

            if (isEmpty())
                head = tail;
            else
                oldtail->next = tail;
            // oldtail->next = tail;

            // if( isEmpty() )
            // {
                // delete oldtail;
                // delete head;
                // head = tail;
            // }

            theSize++;
        }

        Type dequeue()
        {
            if( isEmpty() )
                throw std::out_of_range( "The Queue is Empty!" );

            Node* oldhead = head;
            head = head->next;

            Type item = oldhead->data;

            delete oldhead;
            oldhead = nullptr;

            theSize--;

            if( isEmpty() )
                init();

            return item;
        }


        bool isEmpty() const { return theSize == 0; }
        size_t size() const { return theSize; }
};

int main()
{
    Queue<int> a{};

    a.enqueue(1);

    std::cout << a.dequeue() << '\n';

    a.enqueue(2);

    std::cout << a.dequeue() << '\n';

    Queue<int> b = a;

    b.enqueue(3);
    b.enqueue(4);
    b.enqueue(5);
    b.enqueue(5);
    b.enqueue(5);
    b.enqueue(5);
    b.enqueue(5);
    b.enqueue(5);
    b.enqueue(5);
    b.enqueue(5);

    std::cout << "size: " << b.size() << '\n';

    while (b.size() != 0)
        std:: cout << b.dequeue() << '\n';

    return 0;
}
