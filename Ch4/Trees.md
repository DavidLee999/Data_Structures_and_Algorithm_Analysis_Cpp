# Trees

The average running time of most operations is O(logN).

The *binary search tree* is the basis for the implementation of two library collections classes, `set` and `map`.

## Preliminaries

**Definition** (recursive): A tree is **a collection of nodes**. The collection can be empty; otherwise, a tree consists of a distinguished node, *r*, called the **root**, and zero or more nonempty (sub)trees *T~1~ , T~2~ , ..., T~k~*, each of whose roots are connected by a **directed edge** from *r*.

The root of each subtree is said to be a **child** of *r*, and *r* is the **parent** of each subtree root.

From the recursive deﬁnition, we ﬁnd that a tree is a collection of N nodes, one of which is the root, and N − 1 edges.

Nodes with no children are known as **leaves**; Nodes with the same parent are **siblings**;

A **path** from node n~1~ to n~k~ is deﬁned as **a sequence of nodes** n~1~ , n~2~ , ..., n~k~ such that n~i~ is the parent of n~i+1~ for 1 ≤ i < k. The **length** of this path is **the number of edges** on the path, namely, k − 1. There is a path of length zero from every node to itself.

For any node n~i~ , the **depth** of n~i~ is **the length of the unique path from the root to n~i~** . The root is at depth 0. The **height** of n~i~ is **the length of the longest path** from n~i~ to a leaf. All leaves are at height 0. The **height of a tree** is equal to **the height of the root**.

The **depth of a tree** is equal to **the depth of the deepest leaf** and is **equal to the height of the tree**.

If there is a path from n~1~ to n~2~, then n~1~ is an **ancestor** of n~2~ and n~2~ is a **descendant** of n~1~ . If n~1~ != n~2~ , then n~1~ is a **proper ancestor** of n~2~ and n~2~ is a** proper descendant** of n~1~.

### Implmentation of Trees

```c++
struct TreeNode
{
  Object element;
  TreeNode *firstChild;
  TreeNode *nextSibling; 
};
```

![Snip20171215_11](/Users/lipenghua/Downloads/Snip20171215_11.png)

### Tree Traversals

- **Preorder traversal**: In a preorder traversal, work at a node is performed **before (pre) its children** are processed.
- **Postorder traversal**: In a postorder traversal, the work at a node is performed **after (post) its children** are evaluated.
- **Inorder traversal**: In a inorder traversal, the work at a node is performed **after its left-children and before its right-child** are evaluated.

## Binary Trees

**DEFINITION**:  A binary tree is a tree in which no node can have more than two children.

**Properities**:

- The depth of an average binary tree is considerably smaller than N (largest N - 1). The **average depth** is $O(\sqrt{N})$. The**average depth of *binary search tree*** is $O(logN)$.
- 二叉树第 i 层上的结点数目最多为2^i-1^.
- 深度为 k 的二叉树至多有2^k^-1个结点。
- 一个节点含有的子树的个数称为该节点的度。度为i 的节点的个数设为n~i~。一棵二叉树的总节点为n~0~ + n~1~ + n~2~ = n~1~ + 2n~2~ + 1.
- 由上一条可知：n~0~=n~2~ + 1.
- 一棵树的总结点数为N，其总度数为N - 1.

### Implementation

```c++
struct BinaryNode
{
  Object element; // The data in the node
  BinaryNode *left; // Left child
  BinaryNode *right; // Right child
};
```

## Binary Search Trees

**DEFINITION**: The property that makes a binary tree into a binary search tree is that for every node, X, in the tree, the values of all the items in its left subtree are smaller than the item in X, and the values of all the items in its right subtree are larger than the item in X.

**Note**: Because of the **recursive deﬁnition** of trees, it is common to write these routines **recursively**.

An implementation of binary search tree can be found in *[BinarySearchTree](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch4/BinarySearchTree.cpp)*. In this implementation:

- the dtat member is merely **a pointer to the root node**. 
- The public member functions use the general technique of calling **private recursive functions**.
- The private member function uses **reference to a pointer** (`*&`) as the parameter (形参) to ensure that the function can change the pointer to the root.

### Consturctor

The copy constructor can be done by simply calling the `clone` function which do all the dirty work.

```c++
BinaryNode * clone( BinaryNode *t ) const
{
  if( t == nullptr )
    return nullptr;
  else
    return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
}
```

### `contains` function

Make use the recursive definition of the tree, we **make a recursive call** on a subtree of T, either left or right, depending on the relationship of item X and the item of T.

```c++
bool contains( const Comparable & x, BinaryNode *t ) const 
{ 
  if( t == nullptr ) 
    return false; 
  else if( x < t->element ) 
    return contains( x, t->left ); 
  else if( t->element < x ) 
    return contains( x, t->right ); 
  else 
    return true; // Match
}
```

### `insert` function

To insert X into tree T, proceed down the tree as you would with a`contains`. If X is found, do nothing. Otherwise, insert X at the last spot on the path traversed.

```c++
if( t == nullptr )
  t = new BinaryNode{ x, nullptr, nullptr };
```

**Duplicates** can be handled by keeping all of the structures that have the same key in an **auxiliary data structure**, such as a `list` or another search tree.

In the recursive routine, **the only time that `t` changes** is when a **new leaf** is created. When this happens, it means that the recursive routine has been called from some other node, `p`, which is to be the leaf’s parent.

### `findMin` and `findMax`

To perform a `findMin`, start at the root and **go left** as long as there is a left child. The stopping point is the smallest element. 

The `findMax` routine is the same, except that branching is to the **right child**.

### `remove` function

Three cases:

- If the node is a **leaf**, it can be **deleted immediately**;
- If the node has **one child**, the node can be deleted after its parent **adjusts a link to bypass the node**;
- For a node with **two children**, the general strategy is to **replace the data of this node with the smallest data of the right subtree** (which is easily found) and recursively **delete that node** (which is now empty).

```c++
void remove( const Comparable & x, BinaryNode * & t )
{ 
  if( t == nullptr ) 
    return; // Item not found; do nothing 
  if( x < t->element ) 
    remove( x, t->left ); 
  else if( t->element < x ) 
    remove( x, t->right ); 
  else if( t->left != nullptr && t->right != nullptr ) // Two children
  {
    t->element = findMin( t->right )->element; 
    remove( t->element, t->right ); 
  }
  else 
  {
    BinaryNode *oldNode = t; 
    t = ( t->left != nullptr ) ? t->left : t->right; 
    delete oldNode;
  }
}
```

### Desturctor

The destructor calls `makeEmpty`. The public `makeEmpty` simply calls the private recursive version. After **recursively processing** `t`’s children, a call to delete is made for `t`. Thus all nodes are recursively reclaimed.

### Remark

综上，对于二叉搜索树的实现，只需要牢牢把握住其定义的递归性。利用定义上的递归性来用递归函数来完成其实现。

### Average-Case Analysis

The running time of all operations (except `makeEmpty` and copying) is O(d), where d is the depth of the node containing the accessed item. The **average depth** over all nodes in a tree is O(log N) on the **assumption that all insertion sequenes are equally likely**.

**internal path length**: The sum of the depths of all nodes in a tree.

The average running time of all the operations is O(log N), but this is not entirely true. The reason for this is that **because of deletions**, it is not clear that all binary search trees are equally likely. In particular, the deletion algorithm described above favors **making the left subtrees deeper than the right**.

**Problem**:

- If we alternate insertions and deletions $\Theta(N^2)$ times, then the trees will have an expected depth of $\Theta(\sqrt{N})$.
- If the input comes into a tree **presorted**, then a series of inserts will take quadratic time and the tree will consist only of nodes with no left children.

**Solutions**:

1. One solution to the problem is to insist on an extra structural condition called **balance**: No node is allowed to get too deep.
2. A second method is to allow the tree to be arbitrarily deep, but after every operation, a restructuring rule is applied that tends to make future operations efﬁcient which is called **self-adjusting**.

## AVL Trees

An *AVL tree* is a binary search tree with a **balance condition**. The balance condition ensures that the depth of the tree is O(log N).

**DEFINITION**: An AVL tree is identical to a binary search tree, except that for every node in the tree, **the height of the left and right subtrees can differ by at most 1**. (The height of an empty tree is deﬁned to be −1.) 

Height information is kept for **each node** (in the node structure).

**PROPERTY**: The minimum number of nodes, S(h), in an AVL tree of height *h* is given by S(h) = S(h − 1) + S(h − 2) + 1. For h = 0, S(h) = 1. For h = 1, S(h) = 2.

Thus, all the tree operations can be performed in O(log N) time, except possibly insertion and deletion. When we do an **insertion**, we need to **1) update all the balancing information** for the nodes on the path back to the root, but the insertion could **2) violate the balance**. If this is the case, then the property has to be **restored before the insertion** step is considered over and the operation is called **rotate**.

After an insertion, only **nodes that are on the path from the insertion point to the root** might have their balance altered because only those nodes have their subtrees altered. 

Let us call the node tht must be balanced $$\alpha$$. A height imbalance requires that $\alpha$’s **two subtrees’ heights differ by two**, it is easy to see that a violation might occur in **four cases**:

1. $\alpha \to left \to h > \alpha \to right \to h$
   1. An insertion into the left subtree of the left child of $\alpha$. ($\alpha \to left \to left \to h  \ge \alpha \to  left \to right \to h$);
   2. An insertion into the right subtree of the left child of $\alpha$. ($\alpha \to left \to left \to h < \alpha \to  left \to right \to h$);
2. $\alpha \to right \to h > \alpha \to left \to h$
   1. An insertion into the left subtree of the right child of $\alpha$. ($\alpha \to right \to right \to h < \alpha \to right \to left \to h$)
   2. An insertion into the right subtree of the right child of $\alpha$. ($\alpha \to right \to right \to h  \ge\alpha \to  right \to left \to h$)

Case 1.1 and 2.2 are mirror image symmetries w.r.t. $\alpha$, as are case 1.2 and 2.1. The first situation, in which the insertion occurs on the "**outside**", is fixed by a **single rotation** of the tree. The second case, in which the insertion occurs on the "**inside**", is handle by the **double rotation**.

### Single Rotation

Following figure shows the *single rotation* that fixes case 1.1.

![屏幕快照 2017-12-20 17.02.28](../../../Downloads/屏幕快照 2017-12-20 17.02.28.png)

**OBJECT**: To ideally rebalance the tree, we would like to move X up a level and Z down a level.

The **result** is that k~1~ will be the new root and k~2~ becomes the right child of k~1~ in the new tree. X and Z remain as the left child of k~1~ and right child of k~2~ , respectively. Subtree Y, which holds **items that are between k~1~ and k~2~** in the original tree, can be placed as k~2~ ’s left child in the new tree and satisfy all the ordering requirements.

**PROCEDURE**: This result only requires a few **pointer changes**. k~2~ and k~1~ not only satisfy the AVL requirements, but they also have subtrees that are exactly **the same height**. Furthermore, the new height of the entire subtree is **exactly the same** as the height of the original subtree **prior** to the insertion that caused X to grow. Only the heights of k~1~ and k~2~ need to be changed. No further updating of heights on the path to the root is needed, and consequently no further rotations are needed.

Case 2.2 is a symmetric case as shown in follows.

![屏幕快照 2017-12-20 17.30.25](../../../Downloads/屏幕快照 2017-12-20 17.30.25.png)

**NOTE**: Besides the local change caused by the rotation, it should be remembered that the rest of the tree has to be informed of this change.

### Double Rotation

The algorithm described above cannot solve the case 1.2 and 2.1. The following figure shows the *left-right double rotation* to fix case 1.2. For case 1.2, the tree may be viewed as four subtrees connected by three nodes. As the diagram suggests, exactly one of tree B or C is two levels deeper than D (unless all are empty), but we cannot be sure which one.

![屏幕快照 2017-12-20 17.40.32](../../../Downloads/屏幕快照 2017-12-20 17.40.32.png)

We need to place k~2~ as the new root. This forces k~1~ to be k~2~ ’s left child and k~3~ to be its right child, and it also completely determines the resulting locations of the four subtrees.

Following figure shows the *right-left double rotation* to fix case 2.1.

![屏幕快照 2017-12-20 17.59.15](../../../Downloads/屏幕快照 2017-12-20 17.59.15.png)

### Summary

平衡AVL树，我们可以利用一下步骤：

1. Which case -> which strategy;
2. 确定k~1~, k~2~, k~3~;
3. 确定A, B, C, D;
4. Rotation。

### Implementation

Description: To insert a new node with item X into an AVL tree T, we recursively insert X into the appropriate subtree of T (let us call this T~LR~ ). 

- If the height of T~LR~ does not change, then we are done.
- If a height imbalance appears in T, we do the appropriate single or double rotation depending on X and the items in T and T~LR~ , updating the heights and making the connection from the rest of the tree above.

A full relization of AVL tree is in [AVLTree](https://github.com/DavidLee999/Data_Structures_and_Algorithm_Analysis_Cpp/blob/master/Ch4/AVLTree.cpp).

#### Node

```C++
struct AvlNode 
{
  Comparable element; 
  AvlNode *left; 
  AvlNode *right; 
  int height;
};
```

#### `insert` method

```c++
void insert( const Comparable & x, AvlNode * & t ) 
{
  if( t == nullptr )
    t = new AvlNode{ x, nullptr, nullptr };
  else if( x < t->element )
    insert( x, t->left );
  else if( t->element < x )
    insert( x, t->right );
  
  balance( t );
}
```

#### `balance` method

```c++
void balance( AvlNode * & t ) 
{
  if( t == nullptr ) 
    return; 
  if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) // case 1 
    if( height( t->left->left ) >= height( t->left->right ) ) // case 1.1
      rotateWithLeftChild( t ); 
  	else // case 1.2
      doubleWithLeftChild( t ); 
  else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )  // case 2
    if( height( t->right->right ) >= height( t->right->left ) ) // case 2.2
      rotateWithRightChild( t ); 
  	else // case 2.1
      doubleWithRightChild( t ); 
  
  t->height = max( height( t->left ), height( t->right ) ) + 1;
}
```

```C++
void rotateWithLeftChild( AvlNode * & k2 ) 
{
  AvlNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  k2 = k1;
}
```

```C++
void doubleWithLeftChild( AvlNode * & k3 )
{
  rotateWithRightChild( k3->left );
  rotateWithLeftChild( k3 ); 
}
```

#### `remove` mthod

```C++
void remove( const Comparable & x, AvlNode * & t )
{
  if( t == nullptr )
    return; // Item not found; do nothing
  
  if( x < t->element ) 
    remove( x, t->left ); 
  else if( t->element < x )
    remove( x, t->right ); 
  else if( t->left != nullptr && t->right != nullptr ) // two children
  {
    t->element = findMin( t->right )->element;
    remove( t->element, t->right );
  } 
  else 
  {
    AvlNode *oldNode = t;
    t = ( t->left != nullptr ) ? t->left : t->right;
    delete oldNode; 
  }
  
  balance( t );
}
```

