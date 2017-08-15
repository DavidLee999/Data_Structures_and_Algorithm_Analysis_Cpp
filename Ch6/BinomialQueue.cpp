#include <iostream>
#include <exception>
#include <vector>
using namespace std;

template <typename Comparable>
class BinomialQueue
{
    public:
        BinomialQueue() : theTrees(DEFAULT_TREES)
        {
            for (auto& root : theTrees)
                root = nullptr;
            currentSize = 0;
        }

        BinomialQueue(const Comparable& item) : theTrees(1), currentSize {1}
        {
            theTrees[0] = new BinomialNode {item, nullptr, nullptr};
        }

        BinomialQueue(const BinomialQueue& rhs) : theTrees (rhs.theTrees.size()), currentSize {rhs.currentSize}
        {
            for (int i = 0; i < rhs.theTrees.size(); ++i)
                theTrees[i] = clone(rhs.theTrees[i]);
        }

        BinomialQueue(BinomialQueue&& rhs) : theTrees {std::move(rhs.theTrees)}, currentSize {rhs.currentSize} {}

        ~BinomialQueue()
        { makeEmpty(); }

        BinomialQueue& operator= (const BinomialQueue& rhs)
        {
            BinomialQueue copy = rhs;
            std::swap(*this, copy);

            return *this;
        }

        BinomialQueue& operator= (BinomialQueue&& rhs)
        {
            std::swap(currentSize, rhs.currentSize);
            std::swap(theTrees, rhs.theTrees);

            return *this;
        }

        bool isEmpty() const
        { return currentSize == 0; }
        const Comparable& findMin() const
        {
            if (isEmpty())
                throw underflow_error("The Binomial Queue is empty!");

            return theTrees[findMinIndex()]->element;
        }

        void insert(const Comparable& x)
        {
            BinomialQueue oneItem {x};
            merge(oneItem);
        }
        void insert(Comparable&& x)
        {
            BinomialQueue oneItem {std::move(x)};
            merge(oneItem);
        }
        void deleteMin()
        {
            Comparable x;
            deleteMin(x);
        }

        void deleteMin(Comparable& minItem)
        {
            if (isEmpty())
                throw underflow_error("The Binomial Queue is empty!");

            int minIndex = findMinIndex();
            minItem = theTrees[minIndex]->element;

            BinomialNode* oldRoot = theTrees[minIndex];
            BinomialNode* deletedTree = oldRoot->leftChild;
            delete oldRoot;

            // forming H''
            BinomialQueue deletedQueue;
            deletedQueue.theTrees.resize(minIndex + 1);
            deletedQueue.currentSize = (1 << minIndex) - 1;
            for (int j = minIndex - 1; j >= 0; --j)
            {
                deletedQueue.theTrees[j] = deletedTree;
                deletedTree = deletedTree->nextSibling;
                deletedQueue.theTrees[j]->nextSibling = nullptr;
            }

            // forming H'
            theTrees[minIndex] = nullptr;
            currentSize -= deletedQueue.currentSize + 1;

            merge(deletedQueue);
        }

        void makeEmpty()
        {
            currentSize = 0;

            for (auto& root : theTrees)
                makeEmpty(root);
        }

        void merge(BinomialQueue& rhs)
        {
            if (this == &rhs)
                return;

            currentSize += rhs.currentSize;

            if (currentSize > capacity())
            {
                int oldNumTrees = theTrees.size();
                int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
                theTrees.resize(newNumTrees);
                for (int i = oldNumTrees; i < newNumTrees; ++i)
                    theTrees[i] = nullptr;
            }

            BinomialNode* carry = nullptr;
            for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2)
            {
                BinomialNode* t1 = theTrees[i];
                BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

                int whichCase = t1 == nullptr ? 0 : 1;
                whichCase += t2 == nullptr ? 0 : 2;
                whichCase += carry == nullptr ? 0 : 4;

                switch(whichCase) {
                    case 0: // none
                    case 1: // only this
                        break;
                    case 2: // only rhs
                        theTrees[i] = t2;
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 4: // only carry
                        theTrees[i] = carry;
                        carry = nullptr;
                        break;
                    case 3: // this and rhs. combine them to form a new tree the this position empty
                        carry = combineTrees(t1, t2);
                        theTrees[i] = rhs.theTrees[i] = nullptr;
                        break;
                    case 5: // this and carry. combine them to form a new tree the this position empty
                        carry = combineTrees(t1, carry);
                        theTrees[i] = nullptr;
                        break;
                    case 6: // rhs and carry. combine them to form a new tree the this position empty
                        carry = combineTrees(t2, carry);
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 7: // all three. place carry in this position. combine this and rhs to form a new tree the this position empty
                        theTrees[i] = carry;
                        carry = combineTrees(t1, t2);
                        rhs.theTrees[i] = nullptr;
                        break;
                }
            }

            for (auto& root : rhs.theTrees)
                root = nullptr;
            rhs.currentSize = 0;
        }

    private:
        struct BinomialNode
        {
            Comparable element;
            BinomialNode* leftChild;
            BinomialNode* nextSibling;

            BinomialNode(const Comparable& e, BinomialNode* lt, BinomialNode* rt) : element {e}, leftChild (lt), nextSibling {rt} {}
            BinomialNode(const Comparable&& e, BinomialNode* lt, BinomialNode* rt) : element {e}, leftChild (lt), nextSibling {rt} {}

        };

        const static int DEFAULT_TREES = 1;

        vector<BinomialNode*> theTrees;
        int currentSize;

        int findMinIndex() const
        {
            int i, minIndex;
            for (i = 0; theTrees[i] == nullptr; ++i) // skip
                ;

            for (minIndex = i; i < theTrees.size(); ++i)
                if (theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element)
                    minIndex = i;

            return minIndex;
        }

        int capacity() const
        {
            return (1 << theTrees.size()) - 1; // 2^size() - 1
        }

        BinomialNode* clone(BinomialNode* t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new BinomialNode{t->element, clone(t->leftChild), clone(t->nextSibling)};
        }

        BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2)
        {
            if (t2->element < t1->element)
                return combineTrees(t2, t1);

            t2->nextSibling = t1->leftChild;
            t1->leftChild = t2;

            return t1;
        }

        void makeEmpty(BinomialNode*& t)
        {
            if (t != nullptr)
            {
                makeEmpty(t->leftChild);
                makeEmpty(t->nextSibling);

                delete t;
                t = nullptr;
            }
        }
};

int main()
{
    BinomialQueue<char> a {};
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

    BinomialQueue<char> b = a;

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
