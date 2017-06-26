template <typename Object>
class List
{
private:
    struct Node
    {};
    
public:
    class const_iterator
    {};
    
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
    int theSize;
    Node* head;
    Node* tail;
    
    void init()
    {}
};