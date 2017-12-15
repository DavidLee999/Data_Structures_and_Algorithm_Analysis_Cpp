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

