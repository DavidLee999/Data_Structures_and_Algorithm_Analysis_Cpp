#include <exception>
#include <cmath>
#include <algorithm>
#include <string>
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

        bool contains(const Comparable& x) const
        {
            return contains(x, root);
        }

        bool isEmpty() const
        { return root == nullptr; }
        
        size_t size() const
        { return size(root); }

        int size(const Comparable& lo, const Comparable& hi) const
        {
            if (contains(hi))
                return rank(hi) - rank(lo) + 1;
            else
                return rank(hi) - rank(lo);
        }

        void printTree(ostream& out = cout) const
        {
            if (isEmpty())
                out << "Empty binary tree.\n";
            else
                printTree(root, out);
        }

        Comparable floor(const Comparable& item) const
        {
            if (isEmpty())
                throw underflow_error("The binary tree is empty!");

            BinaryNode* x = floor(root, item);
            if (x == nullptr)
                return NULL;
            else
                return x->element;
        }
        
        Comparable ceiling(const Comparable& item) const
        {
            if (isEmpty())
                throw underflow_error("The binary tree is empty!");

            BinaryNode* x = ceiling(root, item);
            if (x == nullptr)
                return NULL;
            else
                return x->element;
        }

        Comparable select(int k) const
        {
            if (k < 0 || k > size(root))
                throw out_of_range("The index k is out of range!");

            BinaryNode* x = select(root, k);
            if (x == nullptr)
                return NULL;
            else
                return x->element;
        }

        int rank(const Comparable& item) const
        {
            return rank(root, item);
        }

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
            size_t size;

            BinaryNode(const Comparable& e, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr, size_t s = 0)
                : element{ e }, left{ lt }, right{ rt }, size{ s } {}

            BinaryNode(Comparable&& e, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr, size_t s = 0)
                : element{ e }, left{ lt }, right{ rt }, size{ s } {}
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

            t->size = 1 + size(t->left) + size(t->right);
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

            t->size = 1 + size(t->left) + size(t->right);
        }

        void remove(const Comparable& x, BinaryNode* &t)
        {
            if (t == nullptr)
                return;
            if (x < t->element)
                remove(x, t->left);
            else if (t->element < x)
                remove(x, t->right);
            else if (t->left != nullptr && t->right != nullptr)
            {
                t->element = findMin(t->right)->element;
                remove(t->element, t->right);
            }
            else
            {
                BinaryNode* oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }
            if (t != nullptr)
                t->size = 1 + size(t->left) + size(t->right);

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

        int rank(BinaryNode* t, const Comparable& x) const
        {
            if (t == nullptr)
                return NAN;
            if (x < t->element)
                return rank(t->left, x);
            else if (x > t->element)
                return size(t->left) + rank(t->right, x) + 1;
            else
                return size(t->left);
        }

        BinaryNode* select(BinaryNode* t, int k) const
        {
            if (t == nullptr)
                return nullptr;

            int x = size(t->left);
            if (x < k)
                return select(t->right, k - x - 1);
            else if (k < x)
                return select(t->left, k);
            else
                return t;
        }

        BinaryNode* floor(BinaryNode* t, const Comparable& x) const
        {
            if (t == nullptr)
                return nullptr;

            if (x < t->element)
                return floor(t->left, x);
            else if (t->element < x)
            {
                BinaryNode* tmp = floor(t->right, x);
                if (tmp == nullptr)
                    return t;
                else
                    return tmp;
            }
            else
                return t;
        }

        BinaryNode* ceiling(BinaryNode* t, const Comparable& x) const
        {
            if (t == nullptr)
                return nullptr;

            if (x < t->element)
            {
                BinaryNode* tmp = ceiling(t->left, x);
                if (tmp == nullptr)
                    return t;
                else
                    return tmp;
            }
            else if (t->element < x)
                return ceiling(t->right, x);
            else
                return t;
        }

        size_t size(BinaryNode* t) const
        {
            if (t == nullptr)
                return 0;
            else
                return t->size;
        }

        BinaryNode* findMin(BinaryNode* t) const
        {
            if (t == nullptr)
                return nullptr;
            if (t->left == nullptr)
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

        bool contains(const Comparable& x, BinaryNode* t) const
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

        void printTree(BinaryNode* t, ostream& out) const
        {
            if (t != nullptr)
            {
                printTree(t->left, out);
                out << t->element << " ";
                printTree(t->right, out);
            }
        }

        BinaryNode* clone(BinaryNode* t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new BinaryNode{ t->element, clone(t->left), clone(t->right), t->size };
        }

};

class Employee
{
    public:
        explicit Employee(const string& n, const double& d)
            : name{ n }, salary{ d } {};

        const string& getName() const
        { return name; }

        bool operator< (const Employee& rhs) const
        { return getName() < rhs.getName(); }

    private:
        string name;
        double salary;
};

bool operator< (const string& name, const Employee& e)
{ return name < e.getName(); }

bool operator< (const Employee& e, const string& name)
{ return e.getName() < name; }

int main()
{
    BinarySearchTree<int> a {};

    a.insert(2);
    a.insert(3);
    a.insert(6);
    a.insert(8);
    a.insert(11);
    
    a.remove(6);

    cout << a.contains(3) << endl;
    
    int b = a.findMin();
    int c = a.findMax();

    cout << b  << " " << c << endl;
    a.printTree();
    cout << endl;
    cout << a.size() << endl;

    cout << a.floor(7) << endl;
    cout << a.ceiling(9) << endl;
    cout << a.select(2) << endl;
    cout << a.rank(5) << endl;
    cout << a.size(2,8) << endl;
    return 0;
}

// int main()
// {
    // BinarySearchTree<int> t;
    // int NUMS = 400000;
    // const int GAP  =   3711;
    // int i;

    // cout << "Checking... (no more output means success)" << endl;

    // for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        // t.insert( i );

    // for( i = 1; i < NUMS; i+= 2 )
        // t.remove( i );

    // if( NUMS < 40 )
        // t.printTree( );
    // if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        // cout << "FindMin or FindMax error!" << endl;

    // for( i = 2; i < NUMS; i+=2 )
        // if( !t.contains( i ) )
            // cout << "Find error1!" << endl;

    // for( i = 1; i < NUMS; i+=2 )
    // {
        // if( t.contains( i ) )
            // cout << "Find error2!" << endl;
    // }

    // BinarySearchTree<int> t2;
    // t2 = t;

    // for( i = 2; i < NUMS; i+=2 )
        // if( !t2.contains( i ) )
            // cout << "Find error1!" << endl;

    // for( i = 1; i < NUMS; i+=2 )
    // {
        // if( t2.contains( i ) )
            // cout << "Find error2!" << endl;
    // }

    // cout << "Finished testing" << endl;

    // return 0;
// }

