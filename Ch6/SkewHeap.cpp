#include <iostream>
#include <exception>
using namespace std;

template <typename Comparable>
class SkewHeap {
    public:
        SkewHeap():root{nullptr} {}
        
        SkewHeap(const SkewHeap& rhs):root{nullptr}
        { root = clone(rhs.root); }
        
        SkewHeap(SkewHeap&& rhs):root{rhs.root}
        { rhs.root = nullptr; }

        ~SkewHeap()
        { makeEmpty(); }

        SkewHeap& operator= (const SkewHeap& rhs)
        {
            SkewHeap copy = rhs;
            std::swap(copy, *this);

            return *this;
        }
        
        SkewHeap& operator= (SkewHeap&& rhs)
        {
            std::swap(root, rhs.root);
            return *rhs;
        }

        bool isEmpty() const
        { return root == nullptr; }
        
        const Comparable& findMin() const
        {
            if (isEmpty())
                throw underflow_error("The priority queue is empty!");

            return root->element;
        }

        void insert(const Comparable& x)
        {
            root = merge(new SkewNode{x}, root);
        }
        
        void insert(Comparable&& x)
        {
            root = merge(new SkewNode{x}, root);
        }
        
        void deleteMin()
        {
            if (isEmpty())
                throw underflow_error("The priority queue is empty!");

            SkewNode* oldroot = root;
            root = merge(root->left, root->right);

            delete oldroot;
        }
        
        void deleteMin(Comparable& minItem)
        {
            minItem = findMin();
            deleteMin();
        }
        
        void makeEmpty()
        {
            reclaimMemory(root);
            root = nullptr;
        }
        
        void merge(SkewHeap& rhs)
        {
            if (this == &rhs)
                return;

            root = merge(root, rhs.root);
            rhs.root = nullptr;
        }

    private:
        struct SkewNode {
            Comparable element;
            SkewNode* left;
            SkewNode* right;

            SkewNode(const Comparable& e, SkewNode* lt = nullptr, SkewNode* rt = nullptr):element{e}, left{lt}, right{rt} {}
            SkewNode(const Comparable&& e, SkewNode* lt = nullptr, SkewNode* rt = nullptr):element{e}, left{lt}, right{rt} {}

        };

        SkewNode* root;

        SkewNode* merge(SkewNode* h1, SkewNode* h2)
        {
            if (h1 == nullptr)
                return h2;
            if (h2 == nullptr)
                return h1;
            if (h1->element < h2->element)
                return merge1(h1, h2);
            else
                return merge1(h2, h1);
        }

        SkewNode* merge1(SkewNode* h1, SkewNode* h2)
        {
            if (h1->left == nullptr)
                h1->left = h2;
            else
            {
                h1->right = merge(h1->right, h2);
                swapChildren(h1);
            }

            return h1;
        }
        
        void swapChildren(SkewNode* r)
        {
            SkewNode* tmp = r->left;
            r->left = r->right;
            r->right = tmp;
        }

        SkewNode* clone(SkewNode* r) const
        {
            if (r == nullptr)
                return nullptr;
            else
                return new SkewNode {r->element, clone(r->left), clone(r->right)};
        }
        
        void reclaimMemory(SkewNode* r)
        {
            if (r != nullptr)
            {
                reclaimMemory(r->left);
                reclaimMemory(r->right);
                delete r;
            }
        }
};


int main()
{
    SkewHeap<char> a {};
    char item;
    while (cin >> item) {
        if (item == '-')
        {
            char tmp;
            a.deleteMin(tmp);
            cout << tmp << '\n';
        }
        else if (item == '?')
            cout << a.isEmpty() << '\n';
        else
            a.insert(item);
    }

    SkewHeap<char> b = a;

    b.deleteMin();
    b.deleteMin();
    b.insert('a');

    while (!b.isEmpty()) {
        char tmp;
        b.deleteMin(tmp);
        cout << tmp << " ";
    }
    cout << endl;

    a.merge(b);

    while (!a.isEmpty()) {
        char tmp;
        a.deleteMin(tmp);
        cout << tmp << " ";
    }
}
