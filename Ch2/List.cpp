template <typename Object>
class List
{
public:
    class const_iterator
    {
    public:
        const_iterator() : current{ nullptr } {}
        
        const Object* operator * () const
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
        
        bool operator == ( const const_iterator& rhs ) const
        { return current == rhs.current; }
        
        bool operator != ( const const_iterator& rhs ) const
        { return !( *this == rhs ); }
        
    protected:
        Node* current;
        
        Object& retrieve() const
        { return current->data; }
        
        const_iterator( Node* p ) : current{ p } {}
        
        friend class List<Object>;
    };
    
    class iterator : public const_iterator
    {};
    
    List()
    {}
    
    List( const List& rhs )
    {}
    
    ~List()
    {}
    
    List& operator = ( const List& rhs )
    {}
    
    List( List&& rhs )
    {}
    
    List& operator = ( List&& rhs )
    
    iterator begin()
    { return { head->next }; }
    const_iterator begin() const
    { return { head->next }; }
    
    iterator end()
    { return { tail }; }
    const_iterator end() const
    { return { tail }; }
    
    int size() const
    { return the Size; }
    
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
    { insert( begin(), std::move(x); }
    
    void push_back( const Object& x )
    { insert( end(), x ); }
    void push_back( Object&& x )
    { insert( end(), std::move(x) ); }
    
    void pop_front()
    { erase( begin() ); }
    void pop_back()
    { erase( --end() ); }
    
    iterator insert( iterator itr, const Object& x )
    {}
    iterator insert( iterator itr, Object&& x )
    {}
    
    iterator erase( iterator itr )
    {}
    iterator erase( iterator from, iterator to )
    {}
    
private:

    struct Node
    {
        Object data;
        Node* prev;
        Node* next;
        
        Node( const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr ) : data { d }, prev{ p }, next{ n } {}
        Node( Object&& d = Object{}, Node* p = nullptr, Node* n = nullptr ) : data { d }, prev{ p }, next{ n } {} 
    };
    
    int theSize;
    Node* head;
    Node* tail;
    
    void init()
    {}
};