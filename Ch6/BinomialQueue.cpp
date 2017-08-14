#include <iostream>
#include <exception>
#include <vector>
using namespace std;

template <typename Comparable>
class BinomialQueue
{
    public:
        BinomialQueue();
        BinomialQueue(const Comparable& item);
        BinomialQueue(const BinomialQueue& rhs);
        BinomialQueue(BinomialQueue&& rhs);

        ~BinomialQueue();

        BinomialQueue& operator= (const BinomialQueue& rhs);
        BinomialQueue& operator= (BinomialQueue&& rhs);

        bool isEmpty() const;
        const Comparable& findMin() const;

        void insert(const Comparable& x);
        void insert(Comparable&& x);
        void deleteMin();
        void deleteMin(Comparable& minItem);

        void makeEmpty();
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
                for (int i = oldNewTrees; i < newNumTrees; ++i)
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
                    case 0:
                    case 1:
                        break;
                    case 2:
                        theTrees[i] = t2;
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 4:
                        theTrees[i] = carry;
                        carry = nullptr;
                        break;
                    case 3:
                        carry = combineTrees(t1, t2);
                        theTrees[i] = rhs.theTrees[i] = nullptr;
                        break;
                    case 5:
                        carry = combineTrees(t1, carry);
                        theTrees[i] = nullptr;
                        break;
                    case 6:
                        carry = combineTrees(t2, carry);
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 7:
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

        const static int DEFUALT_TREES = 1;

        vector<BinomialNode*> theTrees;
        int currentSize;

        int findMinIndex() const;
        int capacity() const;
        Binomial* clone(BinomialNode* t) const;

        BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2)
        {
            if (t2->element < t1->element)
                return combineTrees(t2, t1);

            t2->nextSibling = t1->leftChild;
            t1->leftChild = t2;

            return t1;
        }
        void makeEmpty(BinomialNode*& t);
};
