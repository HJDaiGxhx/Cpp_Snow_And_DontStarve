#include <BST.h>

/*  */
template <typename T>
static BinNodePosi<T> &searchIn(BinNodePosi<T> v, T const &e, BinNodePosi<T> hot)
{
    if (!v || (e == v->data))
        return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}

/* 二叉查找 */
template <typename T>
BinNodePosi<T> &BST<T>::search(T const &e)
{
    return searchIn(_root, e, _hot = NULL);
}

/*  */
template <typename T>
BinNodePosi<T> BST<T>::insert(T const &e)
{
    BinNodePosi<T> &x = search(e);
    if (x)
        return x;
    x = new BinNode(e, _hot); // 这里相当于获得了x->parent->lc/rc处刚开始随机的一个地址，然后到那个地址上覆盖了新的值。
    _size++;
    updateHeightAbove(x);
    return x;
}

/* #H 其实我才发现我以前划的并没有太大帮助，看来笔记框架仍然在完善中啊。 */
template <typename T>
static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot) // 其实我不是太懂，但&说明它要深入子函数做参吧，*与此无关？
{
    BinNodePosi<T> w = x; // #Q 为什么不用succ就好？
    BinNodePosi<T> succ = NULL;

    if (!HasLChild(*x))
        succ = x = x->rc;
    else if (!HasRChild(*x))
        succ = x = x->lc;
    else
    {
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi<T> u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;
    }

    hot = w->parent; // 那这里参数hot不是用来输入的，而是单纯输出的，根本用不上hot。
    if (succ)        // if no child
        succ->parent = hot;
    release(w->data);
    release(w);
    return succ;
}

/*  */
template <typename T>
bool BST<T>::remove(T const &e)
{
    BinNodePosi<T> &x = search(e);
    if (!x)
        return false;
    removeAt(x, _hot); // _hot = x->parent
    _size--;
    updateHeightAbove(_hot);
    return true;
}

/* #H 感觉想出这个的人是怎么想出来的……思路很难。

注意——其实都对上了，T0就是a->lc/rc/both（如果是v），以此类推。 */
template <typename T>
BinNodePosi<T> BST<T>::connect34(BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
                                 BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3)
{
    // 其实这里也可以用attachAsLChild接口……显得好看一点，而且inline不亏吧？（卑微地打了一个问号）
    if (T0)
        T0->parent = a;
    if (T1)
        T1->parent = a;
    a->lc = T0;
    a->rc = T1;
    updateHeight(a);

    if (T2)
        T2->parent = c;
    if (T3)
        T3->parent = c;
    c->lc = T2;
    c->rc = T3;
    updateHeight(c);

    a->parent = b;
    c->parent = b;
    b->lc = a;
    b->rc = c;
    updateHeight(b);

    return b;
}

/* #M 所以说我都差一点因为之前听到别人说写很多ifelseswitch的人很菜而伤心自卑了。

注意——尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成。 */
template <typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> v)
{
    BinNodePosi<T> p = v->parent;
    BinNodePosi<T> g = p->parent;

    if (IsLChild(*p))
    {
        if (IsLChild(*v)) // zig-zig（谐音这个，所以从左往右，我只能这么记了）
        {
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else // zag-zig
        {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    }
    else
    {
        if (IsRChild(*v)) // zag-zag（那个）
        {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
        else // zig-zag
        {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}
