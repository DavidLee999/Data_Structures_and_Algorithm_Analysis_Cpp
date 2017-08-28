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

        void printTree(ostream& out = std::cout) const
        {
            if(isEmpty())
                out << "Empty Tree" << endl;
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
        struct AvlNode
        {
            Comparable element;
            AvlNode* left;
            AvlNode* right;
            int height;

            AvlNode(const Comparable& e, AvlNode* lt, AvlNode* rt, int h = 0)
                : element{ e }, left{ lt }, right{ rt }, height{ h } {};
            AvlNode(Comparable&& e, AvlNode* lt, AvlNode* rt, int h = 0)
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
            else
                return true;
        }

        void printTree(AvlNode *t, ostream& out) const
        {
            if (t != nullptr)
            {
                printTree(t->left, out);
                out << t->element << " ";
                printTree(t->right, out);
            }
        }

        AvlNode* clone(AvlNode *t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
        }

        int height(AvlNode* t) const
        {
            return t == nullptr ? -1 : t->height;
        }

        int max(int lhs, int rhs) const
        {
            return lhs > rhs ? lhs : rhs;
        }

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
                insert(std::move(x), t->left);
            else if (t->element < x)
                insert(std::move(x), t->right);

            balance(t);
        }

        void remove(const Comparable& x, AvlNode* &t)
        {
            if (t == nullptr)
                return;
            
            if ( x < t->element)
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
                AvlNode* oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }

            balance(t);
        }

        void balance(AvlNode* &t)
        {
            if (t == nullptr)
                return;

            if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
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

            t->height = max(height(t->left), height(t->right)) + 1; // update the height everytime
        }

        // case 1
        void rotateWithLeftChild(AvlNode* &k2)
        {
            AvlNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;

            // update the height of involved nodes
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            k1->height = max(height(k1->left), k2->height) + 1;

            k2 = k1;
        }

        // case 4
        void rotateWithRightChild(AvlNode* &k1)
        {
            AvlNode* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;

            // update the height of involved nodes
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
            rotateWithLeftChild(k1->right);
            rotateWithRightChild(k1);
        }

};

// int main()
// {
    // AvlTree<char> a;
    // char p;
    // while (cin >> p)
        // a.insert(p);
    // a.printTree();
    // cout << endl;

    // AvlTree<char> b = a;
    // b.remove(a.findMax());
    // b.remove(a.findMin());
    // cout << b.contains('a') << '\n';
    // b.printTree();
// }

int main( )
{
    AvlTree<int> t;
    int NUMS = 2000000;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );
    t.remove( 0 );
    for( i = 1; i < NUMS; i += 2 )
        t.remove( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 2; i < NUMS; i += 2 )
        if( !t.contains( i ) )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( t.contains( i )  )
            cout << "Find error2!" << endl;
    }

    AvlTree<int> t2;
    t2 = t;

    for( i = 2; i < NUMS; i += 2 )
        if( !t2.contains( i ) )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( t2.contains( i ) )
            cout << "Find error2!" << endl;
    }

    cout << "End of test..." << endl;
    return 0;
}
