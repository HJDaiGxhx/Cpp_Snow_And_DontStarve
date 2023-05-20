#include "BinTree.h"

/* 保护级的虚方法，以便派生类在必要时重写。 */
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x) //更新节点x高度
{
    return x->height = 1 + max(stature(x->lc), stature(x->rc)); // 因为高度是从下往上计算的，因此关注重心放在最下方的叶子结点开始，应该明白这点。
}

/* 包含x。 */
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x)
{
    while (x) // 因为这是从下自上的，所以不适合travIn
    {
        updateHeight(x);
        x = x->parent;
    }
}

/* 当空树，没有任何结点时作为根节点插入。 */
template <typename T>
BinNodePosi<T> BinTree<T>::insert(T const &e)
{
    return _root = new BinNode(e);
    _size++;
}

/*  */
template <typename T>
BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, T const &e)
{
    x->insertAsRC(e);
    updateHeightAbove(x);
    _size++;
    return x->rc;
}

/* 将一颗树的根节点作为x的RC附着到x所属的树上去。 */
template <typename T>
BinNodePosi<T> BinTree<T>::attach(BinNodePosi<T> x, BinTree<T> *&S)
{
    if (x->rc = S->_root)
        x->rc->parent = x;
    updateHeightAbove(x);
    _size += S->_size;

    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;

    return x;
}

/* #M 等等，这好像是remove子树。返回被删除节点的个数。 */
template <typename T>
int BinTree<T>::remove(BinNodePosi<T> x)
{
    fromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

/*  */
template <typename T>
int BinTree<T>::removeAt(BinNodePosi<T> x)
{
    // 可能叶结点就是没必要判断，但if空树的形式真的更高效吗？
    // 或许只有实验才能知道，算了吧。或者是因为空树return 0，而其他情况return n。可以一开头就声明int n = 0，但是如果这样亡羊补牢，或许就牵强了，还不如就用空树判断。
    // if (IsLeaf(x))
    // {
    //     release(x->data);
    //     release(x);
    //     return n;
    // }

    if (!x)
        return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

/*  */
template <typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi<T> x)
{
    fromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    BinTree<T> *bt = new BinTree<T>;
    bt->_root = x;
    x->parent = NULL;

    bt->_size = x->size();
    _size -= bt->_size;
    return bt;
}

// template <typename T>
void visit(int &e)
{
    cout << e << ", ";
}

/* 本来是想做出一颗像画出来的那种树的，但是能力不足，先分层搞一个吧。

基本上成功了，唯一一个问题是叶子结点的下面一行全部被写出来，但其实都是x，如何避免？
还有就是，我通过向量二叉生成的树都有一个特征，是叶子结点并不会像完全二叉树，而是很好理解地，优先每个上级的左孩子，甚至大家都有左孩子，都不愿意把孩子集中挤在左边，像完全二叉树那样。 */
template <typename T>
void BinTree<T>::print2Tree()
{
    Queue<BinNodePosi<T>> Q;
    Q.enqueue(_root);
    int limit = 1;

    while (!Q.empty())
    {
        for (int i = 0; (i < limit) && (!Q.empty()); i++)
        {
            BinNodePosi<T> x = Q.dequeue();
            if (x)
            {
                cout << x->data << ", ";
                Q.enqueue(x->lc);
                Q.enqueue(x->rc);
            }
            else
                cout << 'x' << ", ";
        }
        limit *= 2;
        p();
    }
}

/* 以有序向量的形式顺序显示树的内容，格式：1,2,3,4\n

实现——1. 从_root开始TravIn前面写的一个visit函数（cout），中序遍历。
    2. 创建一个向量V，利用中序遍历（复制粘贴）进行V.insert，然后利用向量的print函数打印。

注意——后者几乎是前者两倍的执行时间（待实验）。 */
template <typename T>
void BinTree<T>::print2Vec()
{
    // _root->TravIn(*(Test::p));
    // _root->TravIn(*(visit));

    // 慢速逃课版（利用遍历赋值给Vector，然后调用向量的print函数打印）
    Vector<T> V;

    // travIn（可惜的是没办法写成一句简单的函数，否则将绝杀）
    BinNodePosi<T> x = _root;
    while (true)
        if (HasLChild(*x)) //若有左子树，则
            x = x->lc;     //深入遍历左子树
        else
        {
            // visit(x->data);
            V.insert(x->data);

            while (!HasRChild(*x)) //不断地在无右分支处
                if (!(x = x->succ()))
                {
                    V.print(); // <--------------------------结束点
                    return; //回溯至直接后继（在没有后继的末节点处，直接退出）
                }
                else
                    V.insert(x->data); //访问新的当前节点
            x = x->rc;                 //（直至有右分支处）转向非空的右子树
        }
}

/*  */
template <typename T>
void BinTree<T>::print()
{
    print2Tree();
    p();
    print2Vec();
}