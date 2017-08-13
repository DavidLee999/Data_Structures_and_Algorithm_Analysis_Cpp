#include <exception>
#include <iostream>
using namespace std;

template <typename Comparable>
class LeftistHeap
{
    public:
        LeftistHeap():root {nullptr} {}
        LeftistHeap(const LeftistHeap& rhs):root {nullptr}
        { root = clone(rhs.root); }
        LeftistHeap(const LeftistHeap&& rhs):root {rhs.root}
        { rhs.root = nullptr; }

        ~LeftistHeap()
        { makeEmpty(); }

        LeftistHeap& operator= (const LeftistHeap& rhs)
        {
            LeftistHeap copy = rhs;
            std::swap(copy, *this);

            return *this;
        }
        LeftistHeap& operator= (LeftistHeap&& rhs)
        {
            std::swap(root, rhs.root);
            return *this;
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
            root = merge(new LeftistNode{x}, root);
        }

        void insert(Comparable&& x)
        {
            root = merge(new LeftistNode{x}, root);
        }

        void deleteMin()
        {
            if (isEmpty())
                throw underflow_error("The priority queue is empty!");

            LeftistNode* oldRoot = root;
            root = merge(root->left, root->right);

            delete oldRoot;
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
        void merge(LeftistHeap& rhs)
        {
            if (this == &rhs)
                return;

            root = merge(root, rhs.root);
            rhs.root = nullptr;
        }

    private:
        struct LeftistNode
        {
            Comparable element;
            LeftistNode* left;
            LeftistNode* right;
            int npl;

            LeftistNode(const Comparable& e, LeftistNode* lt = nullptr, LeftistNode* rt = nullptr, int np = 0)
                :element {e}, left {lt}, right {rt}, npl {np} {}

            LeftistNode(const Comparable&& e, LeftistNode* lt = nullptr, LeftistNode* rt = nullptr, int np = 0)
                :element {std::move(e)}, left {lt}, right {rt}, npl {np} {}

        };

        LeftistNode* root;

        LeftistNode* merge(LeftistNode* h1, LeftistNode* h2)
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

        LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2)
        {
            if (h1->left == nullptr)
                h1->left = h2;
            else
            {
                h1->right = merge(h1->right, h2);
                if (h1->left->npl < h1->right->npl)
                    swapChildren(h1);
                h1->npl = h1->right->npl + 1;
            }
            return h1;
        }

        void swapChildren(LeftistNode* t)
        {
            LeftistNode* tmp = t->left;
            t->left = t->right;
            t->right = tmp;
        }

        void reclaimMemory(LeftistNode* t)
        {
            if (t != nullptr)
            {
                reclaimMemory(t->left);
                reclaimMemory(t->right);
                delete t;
            }
        }

        LeftistNode* clone(LeftistNode *t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new LeftistNode{t->element, clone(t->left), clone(t->right), t->npl};
        }
};

int main()
{
    LeftistHeap<char> a {};
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

    LeftistHeap<char> b = a;

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
