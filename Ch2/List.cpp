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
};