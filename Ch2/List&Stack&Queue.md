## 3.1 Abstract Data Type

an abstract data type is a set of **objects** together with a set of **operations**.

### The List ADT

**Definition**: 

- A general list of the form A~0~, A~2~, … , A~N-1~.
- Operations: `printList`, `makeEmpty`, `find`, `insert`, `remove`, `findKth` and so on.

#### Simple Array Implementation of Lists

All these instructions can be implemented just by using an array.

**Pros & Cons**

- An array implementation allows `printList` to be carried out in linear time and `findKth` operation takes constant time.
- `insert`  and `remove` are expensive. On average, **half** of the list needs to be moved for either operation.

**Application**

- Situation where the list is **1)** built up by `insert` at he high end and **2)** only array accesses occur.

#### Simple Linked Lists

To avoid the linear cost of insertion and deletion, the list should **not** be **stored contiguously**.

The linked list consists of a series of nodes, which are not necessarily adjacent in memory. **Each node contains 1) the element and 2) a link to a node containing its successor**.

- For `printList()` or `find(x)`, we merely **1)** start at the ﬁrst node in the list and **2)** traverse the list by following the next links. This operation is **linear-time**.

- The `findKth()` operation takes *O(i)* times and works by traversing down the list.

- The `remove()` method can be executed in one `next` pointer change.![Snip20171214_4](/Users/lipenghua/Downloads/Snip20171214_4.png)

- The `insert()` method can be executed by using a `new` call and tow `next` pointer maneuvers.

  ![Snip20171214_5](/Users/lipenghua/Downloads/Snip20171214_5.png)

**NOTE**: The special case of adding ath the end can be constant-time, as long as we maintain a link to the last node. Thus, a typical linked list keeps links to **both ends** of the list and each node maintains **a link to its previous node** in the list.

A implementation of *Vector* can be found in [Vector](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch2/Vector.cpp) and *List* with `iterator` and `const_iterator` can be found in [List](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch2/LinkedListQueue.cpp).

**NOTE**: 

- For teh `List` class, it make scene to create **an extra node at the end** of the list tp representing the endmarker and **an extra node at the front** representing the beginning marker.

![Snip20171214_6](/Users/lipenghua/Downloads/Snip20171214_6.png)

- the `insert()` and `erase()` function:

  ```c++
  // Insert x before itr.
  iterator insert( iterator itr, const Object & x ) 
  {
    Node *p = itr.current;
    theSize++;
    return { p->prev = p->prev->next = new Node{ x, p->prev, p } }; 
  }

  // Erase item at itr.
  iterator erase( iterator itr )
  {
    Node *p = itr.current; 
    iterator retVal{ p->next };
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;

    return retVal;
  }
  ```

  Insert:

  ![Snip20171214_7](/Users/lipenghua/Downloads/Snip20171214_7.png)

  Erase:

  ![Snip20171214_8](/Users/lipenghua/Downloads/Snip20171214_8.png)

- However, in order to determine if an iterator passed to `erase()` or `insert()` is an iterator for the correct list, the iterator must store an additional data member representing **a pointer to the List** from which it was constructed.

### The Stack ADT

A stack is a list with the restriction that **insertions and deletions** can be performed in only **the end of the list**, called the top.

Essentially all that you can do to a stack is `puch` and `pop`.

The general model is that there is some element that is **at the top of the stack**, and it is the only element that is visible.

![Snip20171214_9](/Users/lipenghua/Downloads/Snip20171214_9.png)

**Applications**:

- Balancing Symbols;
- Postfix Expressions (Infix to Postfix conversion).

An implementation of *Stack* can be found in [ArrayStack](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch2/ArrayStack.cpp).

### The Queue Model

*Queue* are lists. With a queue, insertion is done at one end whereas deletion is perfromed at the other end.

Basic operations:

1. `enqueue()`;
2. `dequeue()`.

#### Array Implementation of Queues

Like *stack*, both the linked list and array implementation give fast *O(1)* running time for every operation. The linked list implementation is very straightforward.

For array implementation, for each queue data structure, we keep an array, `theArray`, and the positions `front` and `back`, which represents the ends of the queue, and the number of elements, `currentSize`.

![Snip20171214_1](/Users/lipenghua/Downloads/Snip20171214_1.png)

- `enqueue()`: Increasing `currentSize` and `back`, then setting `theArray[back] = x`.
- `dequeue()`: Return `theArray[front]`; decrement `currentSize`; increment `front`.

**Circular array**: Whenever `front` and `back` gets to the end of the array, it is **wrapped around** to the beginning. If incrementing either `back` or `front` causes it to go past the array, the value is reset to the first position in the array.

The implementation of queue can be found in [LinkedListQueue](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch2/LinkedListQueue.cpp) and [ResizingArrayQueue](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch2/ResizingArrayQueue.cpp).