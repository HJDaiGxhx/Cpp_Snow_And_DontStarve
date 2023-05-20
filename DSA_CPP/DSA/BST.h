#pragma once

#include "BinTree.h"

template <typename T>
class BST : public BinTree<T>
{
protected:
    BinNodePosi<T> _hot;
    BinNodePosi<T> connect34(BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>,
                             BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>);
    BinNodePosi<T> rotateAt(BinNodePosi<T> x);

public:
    virtual BinNodePosi<T> &search(T const &e);
    virtual BinNodePosi<T> insert(T const &e);
    virtual bool remove(T const &e);
};