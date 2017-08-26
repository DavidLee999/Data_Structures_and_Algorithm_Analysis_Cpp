#include <iostream>
#include <algorithm>
#include <exception>
using namespace std;

template <typename Comparable>
class AvlTree
{
    public:
        AvlTree() : root{ nullptr } {};

        AvlTree(const AvlTree& rhs) : root{ nullptr }
        {
            root = clone(rhs.root);
        }

        AvlTree(AvlTree&& rhs) : root{ rhs.root }
        {
            rhs.root = nullptr;
        }

        AvlTree& operator= (const AvlTree& rhs)
        {
            AvlTree copy = rhs;
            std::swap(*this, copy);

            return *this;
        }

        AvlTree& operator= (AvlTree&& rhs)
        {
            std::swap(root, rhs.root);

            return *this;
        }

        ~AvlTree() { makeEmpty(); }


        const Comparable& findMin() const
        {
            if (isEmpty())
                throw underflow_error("The AVL Tree is Empty!");
            return findMin(root)->element;
        }

        const Comparable& findMax() const
        {
            if (isEmpty())
                throw underflow_error("The AVL Tree is Empty!");
            return findMax(root)->element;
        }

        bool contains(const Comparable& x) const
        {
            return contains(x, root);
        }

        bool isEmpty() const
        {
            return root == nullptr;
        }

        void printTree() const;


        void makeEmpty()
        {
            makeEmpty(root);
        }

        void insert(const Comparable& x)
        {
            insert(x, root);
        }

        void insert(Comparable&& x)
        {
            insert(std::move(x), root);
        }

        void remove(const Comparable& x);

    private:
        struct AvlNode
        {
            Comparable element;
            AvlNode* left;
            AvlNode* right;
            int height;

            AvlNode(const element& e, AvlNode* lt, AvlNode* rt, int h = 0)
                : element{ e }, left{ lt }, right{ rt }, height{ h } {};
            AvlNode(element&& e, AvlNode* lt, AvlNode* rt, int h = 0)
                : element{ std::move(e) }, left{ lt }, right{ rt }, height{ h } {};
        };
        
        AvlNode* root;
        static const int ALLOWED_IMBALANCE = 1;

        AvlNode* findMin(AvlNode *t) const
        {
            if (t == nullptr)
                return nullptr;
            else if (t->left == nullptr)
                return t;
            else
                return findMin(t->left);
        }

        AvlNode* findMax(AvlNode *t) const
        {
            if (t != nullptr)
                while (t->right != nullptr)
                    t = t->right;
            return t;
        }

        bool contains(const Comparable& x, AvlNode *t) const
        {
            if (t == nullptr)
                return false;
            else if (x < t->element)
                return contains(x, t->left);
            else if (t->element < x)
                return contains(x, t->right);
            else if
                return true;
        }

        void printTree(AvlNode *t) const;
        AvlNode* clone(AvlNode *t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new AvlNode{ t->element, clone(t->left), clone(t->right), t->hight };
        }

        int height(AvlNode* t) const;
        int max(int lhs, int rhs) const;

        void makeEmpty(AvlNode* &t)
        {
            if (t != nullptr)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t = nullptr;
        }

        void insert(const Comparable& x, AvlNode* &t)
        {
            if (t == nullptr)
                t = new AvlNode{ x, nullptr, nullptr};
            else if (x < t->element)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);

            balance(t);
        }
        void insert(Comparable&& x, AvlNode* &t)
        {
            if (t == nullptr)
                t = new AvlNode(std::move(x), nullptr, nullptr);
            else if (x < t->element)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);

            balance(t);
        }

        void remove(const Comparable& x, AvlNode* &t);
        void balance(AvlNode* &t)
        {
            if (t == nullptr)
                return;

            if (height(t-left) - height(t->right) > ALLOWED_IMBALANCE)
                // case 1
                if (height(t->left->left) >= height(t->left->right))
                    rotateWithLeftChild(t);
                // case 2
                else
                    doubleWithLeftChild(t);
            else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
                // case 4
                if (height(t->right->right) >= height(t->right->left))
                    rotateWithRightChild(t);
                // case 3
                else
                    doubleWithRightChild(t);

            t->height = max(height(t->left), height(t->right)) + 1;
        }

        // case 1
        void rotateWithLeftChild(AvlNode* &k2)
        {
            AvlNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;

            k2->height = max(height(k2->left), height(k2->right)) + 1;
            k1->height = max(height(k1->left), k2->height) + 1;

            k2 = k1;
        }

        // case 4
        void rotateWithRightChild(AvlNode* &k1)
        {
            AvlNode* k2 = k1->righ;
            k1->right = k2->left;
            k2->left = k1;

            k1->height = max(height(k1->left), height(k1->right)) + 1;
            k2->height = max(height(k2->right), k1->height) + 1;

            k1 = k2;
        }

        // case 2
        void doubleWithLeftChild(AvlNode* &k3)
        {
            rotateWithRightChild(k3->left);
            rotateWithLeftChild(k3);
        }

        // case 3
        void doubleWithRightChild(AvlNode* &k1)
        {
            roateWithLeftChild(k1->right);
            ratateWithRightChild(k1);
        }

};
