#include <exception>
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

        void printTree(ostream& out = cout) const
        {
            if (isEmpty())
                out << "Empty binary tree.\n";
            else
                printTree(root, out);
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
                remove(x, t->right);
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
                return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
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
    BinarySearchTree<Employee> a {};

    a.insert(Employee{"Mike", 2000});
    a.insert(Employee{"John", 3000});
    a.insert(Employee{"David", 4000});
    a.insert(Employee{"Thomi", 5000});
    a.insert(Employee{"Felix", 6000});

    a.remove(Employee{"Thomi", 5000});

    cout << a.contains(Employee{"John", 3000});
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
