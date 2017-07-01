#include <stdexcept>
#include <ostream>
#include <iostream>

template <typename Object>
class List
{
private:
    struct Node
    {
        Object data;
        Node* prev;
        Node* next;
        
        Node( const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr ) : data { d }, prev{ p }, next{ n } {}
        //Node( Object&& d = Object{}, Node* p = nullptr, Node* n = nullptr ) : data { d }, prev{ p }, next{ n } {}
    };
    
public:
    class const_iterator
    {
    public:
        const_iterator() : current{ nullptr } {}
        
        const Object& operator * () const
        { return retrieve(); }
        
        const_iterator& operator ++ ()
        {
            current = current->next;
            return *this;
        }
        const_iterator& operator ++ ( int )
        {
            const_iterator old = *this;
            ++( *this );
            return *old;
        }
        
        const_iterator& operator -- ()
        {
            current = current->prev;
            return *this;
        }
        const_iterator& operator -- ( int )
        {
            const_iterator old = *this;
            --( *this );
            return *old;
        }
        
        const_iterator& operator + ( const int i )
        {
            //const_iterator* res = this;
            for(int j = 0; j < i; ++j )
            {
                if( this->current->next == nullptr )
                    throw std::out_of_range{ "Iterator error!" };

                this->current = this->current->next;
            }

            return *this;
        }
        const_iterator& operator - ( const int i )
        {
            //const_iterator* res = this;
            for(int j = i; j >0; --j )
            {
                if( this->current->prev == nullptr )
                    throw std::out_of_range{ "Iterator error!" };

                this->current = this->current->prev;
            }
            return *this;
        }
        
        bool operator == ( const const_iterator& rhs ) const
        { return current == rhs.current; }
        
        bool operator != ( const const_iterator& rhs ) const
        { return !( *this == rhs ); }
        
    protected:
        //Node* current;
        
        Object& retrieve() const
        { return current->data; }
        
        //const_iterator( Node* p ) : current{ p } {}
        
        friend class List<Object>;
        
        const List<Object> *theList;
        Node* current;
        
        const_iterator( const List<Object>& lst, Node* p ) : theList{ &lst }, current{ p } {}
        
        void assertIsValid() const
        {
            if( theList == nullptr || current == nullptr || current == theList->head )
                throw std::out_of_range{ "Iterator error!" };
        }
    };
    
    class iterator : public const_iterator
    {
    public:
        iterator() {}
        
        Object& operator * ()
        { return const_iterator::retrieve(); }
        const Object& operator * () const
        { return const_iterator::operator * (); }
        
        iterator& operator ++ ()
        {
            this->current = this->current->next;
            
            return *this;
        }
        iterator& operator ++ ( int )
        {
            iterator old = *this;
            ++(*this);
            
            return old;
        }
        
        iterator& operator -- ()
        {
            this->current = this->current->prev;
            
            return *this;
        }
        iterator& operator -- ( int )
        {
            iterator old = *this;
            --(*this);
            
            return old;
        }
        
        iterator& operator + ( const int& i )
        {
            //iterator* res = this;
            for(int j = 0; j < i; ++j )
                this->current = this->current->next;
            return *this;
        }
        iterator& operator - ( const int& i )
        {
            //iterator* res = this;
            for(int j = i; j >0; --j )
                this->current = this->current->prev;
            return *this;
        }
        
    protected:
        iterator ( const List<Object>& lst, Node* p ) : const_iterator{ lst, p } {}
        
        friend class List<Object>;
    };
    
    List()
    { init(); }
    
    List( const List& rhs )
    {
        init();
        for( auto& x : rhs )
            push_back(x);
    }
    
    ~List()
    {
        clear();
        delete head;
        delete tail;
    }
    
    List& operator = ( const List& rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        
        return *this;
    }
    
    List( List&& rhs ) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    
    List& operator = ( List&& rhs )
    {
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );
        
        return *this;
    }
    
    iterator begin()
    { 
        iterator itr{ *this, head };
        return ++itr; 
    }
    const_iterator begin() const
    { 
        const_iterator itr{ *this, head };
        return ++itr; 
    }
    
    iterator end()
    { return { *this, tail }; }
    const_iterator end() const
    { return { *this, tail }; }
    
    int size() const
    { return theSize; }
    
    bool empty() const
    { return size() == 0; }
    
    void clear()
    {
        while( !empty() )
            pop_front();
    }
    
    Object& front()
    { return *begin(); }
    const Object& front() const
    { return *begin(); }
    
    Object& back()
    { return *--end(); }
    const Object& back() const
    { return *--end(); }
    
    void push_front( const Object& x )
    { insert( begin(), x); }
    void push_front( Object&& x )
    { insert( begin(), std::move(x) ); }
    
    void push_back( const Object& x )
    { insert( end(), x ); }
    void push_back( Object&& x )
    { insert( end(), std::move(x) ); }
    
    void pop_front()
    { erase( begin() ); }
    void pop_back()
    { erase( --end() ); }
    
    iterator insert( iterator itr, const Object& x )
    {
        itr.assertIsValid();
        if( itr.theList != this )
            std::invalid_argument{ "The iterator does not belong to this List!" };
        
        Node* p = itr.current;
        theSize++;
        
        return iterator{*this, p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }
    iterator insert( iterator itr, Object&& x )
    {
        itr.assertIsValid();
        if( itr.theList != this )
            std::invalid_argument{ "The iterator does not belong to this List!" };
        
        Node* p = itr.current;
        theSize++;
        
        return iterator{*this, p->prev = p->prev->next = new Node{ std::move(x), p->prev, p} };
    }
    
    iterator erase( iterator itr )
    {
        itr.assertIsValid();
        if( itr.theList != this )
            std::invalid_argument{ "The iterator does not belong to this List!" };
        
        Node* p = itr.current;
        iterator retVal{ *this, p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        
        delete p;
        theSize--;
        
        return retVal;
    }
    iterator erase( iterator from, iterator to )
    {
        from.assertIsValid();
        if( from.theList != this )
            std::invalid_argument{ "The iterator does not belong to this List!" };
        to.assertIsValid();
        if( to.theList != this )
            std::invalid_argument{ "The iterator does not belong to this List!" };
        
        for( iterator itr = from; itr != to; )
            itr = erase( itr );
        
        return to;
    }
    
private:
    int theSize;
    Node* head;
    Node* tail;
    
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        
        head->next = tail;
        tail->prev = head;
    }
};

template <typename T>
std::ostream& operator << ( std::ostream& out, const List<T>& obj )
{
    for( typename List<T>::const_iterator itr = obj.begin(); itr != obj.end(); ++itr )
        out << *itr << " ";
    
    return out;
}

int main()
{
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_front(0);
    
    a.pop_back();
    a.pop_front();
    
    std::cout << a << std::endl;
    
    std::cout << a.front() << '\n';
    std::cout << a.back() << '\n';
   
    a.insert( a.end()-2, 10 );
    a.erase( a.begin()+1 );
    std::cout << a << std::endl;
    
    a.clear();
    
    std::cout << a << std::endl;
    return 0;
}
