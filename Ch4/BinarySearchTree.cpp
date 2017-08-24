#include <exception>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
    public:
        BinarySearchTree() : root{ nullptr } {}

        BinarySearchTree(const BinarySearchTree& rhs) : root{ nullptr }
        { root = clone(rhs.root); }

        BinarySearchTree(BinarySearchTree&& rhs) : root{ rhs.root }
        { rhs.root = nullptr; }

        BinarySearchTree& operator= (const BinarySearchTree& rhs)
        {
            BinarySearchTree copy = rhs;
            std::swap(*this, copy);

            return *this;
        }

        BinarySearchTree& operator= (BinarySearchTree&& rhs)
        {
            std::swap(root, rhs.root);
            return *this;
        }

        ~BinarySearchTree()
        {
            makeEmpty();
        }

        const Comparable& findMin() const
        {
            if (isEmpty())
                throw underflow_error("The binary tree is empty!");

            return findMin(root)->element;

        }
        const Comparable& findMax() const
        {
            if (isEmpty())
                throw underflow_error("The binary tree is empty!");

            return findMax(root)->element;
        }

        bool constains(const Comparble& x) const
        {
            return constains(x, root);
        }

        bool isEmpty() const
        { return root == nullptr; }

        void printTree(ostream& out = cout) const;

        void makeEmpty();
        void insert(const Comparable& x)
        {
            insert(x, root);
        }

        void insert(Comparable&& x)
        {

            insert(std::move(x), root);
        }

        void remove(const Comparable& x)
        {
            remove(x, root);
        }

    private:
        struct BinaryNode
        {
            Comparable element;
            BinaryNode* left;
            BinaryNode* right;

            BinaryNode(const Comparable& e, BinaryNode* lt, BinaryNode* rt)
                : element{ e }, left{ lt }, right{ rt } {}

            BinaryNode(Comparable&& e, BinaryNode* lt, BinaryNode* rt)
                : element{ e }, left{ lt }, right{ rt } {}
        };

        BinaryNode* root;

        void insert(const Comparable& x, BinaryNode* &t)
        {
            if (t == nullptr)
                t = new BinaryNode{ x, nullptr, nullptr };
            else if (x < t->element)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
            else
                ;
        }

        void insert(Comparable&& x, BinaryNode* &t)
        {
            if (t == nullptr)
                t = new BinaryNode{ std::move(x), nullptr, nullptr };
            else if (x < t->element)
                insert(std::move(x), t->left);
            else if (t->element < x)
                insert(std::move(x), t->right);
            else
                ;
        }

        void remove(const Comparable& x, BinaryNode* &t)
        {
            if (t == nullptr)
                return;
            if (x < t->element)
                remove(x, t->left);
            else if (t->element < x)
                remove(x. t->right);
            else if (t->left != nullptr && t->right != nullptr)
            {
                t->element = findMin(t->right)->element;
                remove(t->element, t->right);
            }
            else
            {
                BinaryNode* oldNode = t;
                t = (t->right == nullptr) ? t->left : t->right;
                delete oldNode;
            }
        }

        void makeEmpty(BinaryNode* &t)
        {
            if (t != nullptr)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }

            t = nullptr;
        }

        BinaryNode* findMin(BinaryNode* t) const
        {
            if (t == nullptr)
                return nullptr;
            if (t.left == nullptr)
                return t;
            
            return findMin(t->left);
        }

        BinaryNode* findMax(BinaryNode* t) const
        {
            if (t != nullptr)
                while (t->right != nullptr)
                    t = t->right;

            return t;
        }

        bool constains(const Comparable& x, BinaryNode* t) const
        {
            if (t == nullptr)
                return false;
            else if (x < t->element)
                return contains(x, t->left);
            else if (t->element < x)
                return contains(x, t->right);
            else
                return true;
        }

        void printTree(BinaryNode* t, ostream& out) const;

        BinaryNode* clone(BinaryNode* t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new BinaryNode{ t->element, t->left, t->right };
        }

};
int main()
{
    return 0;
}
