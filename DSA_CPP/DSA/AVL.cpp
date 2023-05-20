#include "AVL.h"

/* #M 其实我觉得它是很难的，但是因为讲解，才能让我觉得很简单。 */
template <typename T>
BinNodePosi<T> AVL<T>::insert(T const &e)
{
    BinNodePosi<T> x = search(e);
    BinNodePosi<T> xx = x = new BinNode<T>(e, _hot);
    _size++;

    for (BinNodePosi<T> g = _hot; g; g = g->parent)
    {
        if (!AVLBalanced(*g))
        {
            fromParentTo(*g) = rotateAt(tallerChild(tallerChild(*g)));
            break; // 居然只做一次，P217，祖先必然复原
        }
        else
            updateHeight(g);
    }
    return xx;
}

/* #M */
template <typename T>
bool AVL<T>::remove(T const &e)
{
    BinNodePosi<T> &x = search(e);
    if (!x)
        return false;
    removeAt(x, _hot); // _hot = x->parent
    _size--;

    for (BinNodePosi<T> g = _hot; g; g = g->parent)
    {
        if (!AVLBalanced(*g))
            g = fromParentTo(*g) = rotateAt(tallerChild(tallerChild(*g)));
        updateHeight(g); // 和insert不同，g还要作为update的参数，因此上一行赋值了它
    }
    return true;
}