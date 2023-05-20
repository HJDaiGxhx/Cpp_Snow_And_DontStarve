#pragma once

#include "test.h"
#include "Vector.h"
#include "Vector.cpp"
#include "BinNode.h"
#include "BinNode.cpp"
#include "Queue.h"
#include "C:\Users\qazse\Documents\GitHub\dsacpp-src\src\_share\release.h"

template <typename T>
class BinTree
{
protected:
    int _size;
    BinNodePosi<T> _root;
    virtual int updateHeight(BinNodePosi<T> x);
    void updateHeightAbove(BinNodePosi<T> x);

public:
    BinTree()
    {
        _size = 0;
        _root = NULL;
    }

    void gen(BinNodePosi<T> &x, BinNodePosi<T> p, T *A, int lo, int hi)
    {
        // if (hi - lo <= 0) // hi - lo = 1 or 0.
        //     return;
        // int mi = (hi + lo) / 2;
        // x->data = A[mi];
        // if (hi - lo <= 1) // hi - lo = 1 or 0.
        //     return;
        // x->lc = new BinNode<T>();
        // x->lc->parent = x;
        // gen(x->lc, A, lo, mi);
        // if (hi - lo <= 1) // hi - lo = 1 or 0.
        //     return;
        // x->rc = new BinNode<T>();
        // x->rc->parent = x;
        // gen(x->rc, A, mi + 1, hi);

        // 怎么感觉一头雾水，根本没有明确的思路知道我做了什么，好像就是瞎写了一通。
        if (hi == lo)
            return;

        // visit()
        int mi = (hi + lo) / 2;
        x = new BinNode<T>(A[mi], p);
        _size++;

        // lc、rc recursion
        // 感觉反而没办法用迭代的方式做，因为递归相当于用堆栈隐式保存了所有的参数，特别是p和mi等等，所以我如果非要那么做，就要先创建几个堆栈，性能允许的情况下还是先这样吧。
        gen(x->lc, x, A, lo, mi);
        gen(x->rc, x, A, mi + 1, hi);
    }

    /* 首先要一个有序数组，输入是先序遍历的原理，然后输出是用中序遍历实现，并做成一颗树的形状，print是最重要的？
    话说，这样生成的是否是最优logn树？然后做成这种形式，包括print，就是为了继承之后其他类型树也可以用，感觉有点妙。 */
    BinTree(T *B, int size)
    {
        Vector<T> A(B, size);
        if (A.disordered())
            A.sort(0, A.size());

        gen(_root, NULL, A.array(), 0, A.size());
    }

    /* 进一步优化，如果Vector事先不有序，在这里转换为有序，只是牺牲了时间。 */
    BinTree(Vector<T> A)
    {
        if (A.disordered())
            A.sort(0, A.size());

        gen(_root, NULL, A.array(), 0, A.size());
    }

    ~BinTree()
    {
        if (_size > 0)
            remove(_root);
    }

// 成员方法
#pragma region
    BinNodePosi<T> insert(T const &e);
    BinNodePosi<T> insert(T const &, BinNodePosi<T>);
    BinNodePosi<T> insert(BinNodePosi<T>, T const &);
    BinNodePosi<T> attach(BinNodePosi<T>, BinTree<T> *&);
    BinNodePosi<T> attach(BinTree<T> *&, BinNodePosi<T>);

    int removeAt(BinNodePosi<T> x);
    int remove(BinNodePosi<T> x);

    BinTree<T> *secede(BinNodePosi<T> x);

    void print();
    void print2Vec();
    void print2Tree();
#pragma endregion
};