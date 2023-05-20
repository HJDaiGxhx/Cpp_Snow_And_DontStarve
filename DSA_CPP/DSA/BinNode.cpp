#include "BinNode.h"

/*  */
template <typename T>
int BinNode<T>::size()
{              //统计当前节点后代总数，即以其为根的子树规模
    int s = 1; //计入本身
    if (lc)
        s += lc->size(); //递归计入左子树规模
    if (rc)
        s += rc->size(); //递归计入右子树规模
    return s;
}

/*  */
template <typename T>
void travPre_R(BinNodePosi<T> x, void (*visit)(T &))
{
    if (!x)
        return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

/* 那它和下面的I2不就是整理一下的差别，原理都是一个吗？就是下面把内循环封装成为一个新函数，吓死我了。而且被它误导，还险些把下面的新函数优化错了，导致致命问题。 */
template <typename T>
void travPre_I1(BinNodePosi<T> x, void (*visit)(T &))
{
    Stack<BinNodePosi<T>> S;
    if (x)
        S.push(x);

    while (!S.empty())
    {
        x = S.pop();
        visit(x->data);
        if (HasRChild(*x))
            S.push(x->rc);
        if (HasLChild(*x))
            S.push(x->lc);
    }
}

/*  */
template <typename T>
static void visitAlongVine(BinNodePosi<T> x, void (*visit)(T &), Stack<BinNodePosi<T>> &S)
{
    while (x)
    {
        visit(x->data);
        if (HasRChild(*x))
            S.push(x->rc);
        x = x->lc;
    }
}

/*  */
template <typename T>
void travPre_I2(BinNodePosi<T> x, void (*visit)(T &))
{
    Stack<BinNodePosi<T>> S;
    while (true)
    {
        visitAlongVine(x, visit, S); //从当前节点出发，逐批访问
        if (S.empty())
            break;   //直到栈空
        x = S.pop(); //弹出下一批的起点
    }
}

/*  */
template <typename T>
void travIn_R(BinNodePosi<T> x, void (*visit)(T &))
{
    if (!x)
        return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

/*  */
template <typename T>
void goAlongVine(BinNodePosi<T> x, void (*visit)(T &), Stack<BinNodePosi<T>> &S)
{
    while (x)
    {
        S.push(x);
        x = x->lc;
    }
}

/*  */
template <typename T>
void travIn_I1(BinNodePosi<T> x, void (*visit)(T &))
{
    Stack<BinNodePosi<T>> S;
    while (true)
    {
        goAlongVine(x, visit, S);
        if (S.empty())
            break;
        x = S.pop();
        visit(x->data);
        if (HasRChild(*x))
            x = x->rc;
    }
}

/* #N 顶多就是学到了，当需要递归转迭代的时候，牢记Stack是应该第一时间想起的数据结构。但是我在写迭代的时候完全没联想起递归，觉得两者长得不像啊。 */
template <typename T>
void travIn_I2(BinNodePosi<T> x, void (*visit)(T &))
{
    Stack<BinNodePosi<T>> S;
    while (true)
    {
        if (x)
        {
            S.push(x);
            x = x->lc;
        }
        else if (!S.empty())
        {
            x = S.pop();
            visit(x->data);
            if (HasRChild(*x))
                x = x->rc;
        }
        else
            break;
    }
}

/* #M */
template <typename T>
BinNodePosi<T> BinNode<T>::succ()
{
    BinNodePosi<T> s = this; // #N this是指针
    if (HasRChild(*s))
    {
        s = rc;
        while (HasLChild(*s))
            s = s->lc;
        return s;
    }
    else
    {
        while (IsRChild(*s))
            s = s->parent;
        s = s->parent;
    }
    return s;
}

/* #M */
template <typename T>
void travIn_I3(BinNodePosi<T> x, void (*visit)(T &))
{
    bool backtrack = false; // 回溯标志代表：因为遍历有两种情况，一种是持续向下延伸，深度不断增大；然后等到它触底之后，它无法再深入了，这时的“折返”其实就是回溯。而触底条件就是它没有右子树，因为延伸时先是一路直线往左，然后走S形进入右子树的新地图，然后再一路直线往左……所以停止延伸先要没有左子树，然后没有右子树，满足这两个条件就触发回溯，折返跃迁。
    while (true)
        if (!backtrack && HasLChild(*x)) // 左孩子
            x = x->lc;
        else
        {
            visit(x->data);
            if (HasRChild(*x)) // 右孩子
            {
                x = x->rc;
                backtrack = false;
            }
            else
            {
                if (!(x = x->succ()))
                    break;
                backtrack = true;
            }
        }
}

/* #H 二叉树中序遍历（迭代版#4，无需栈或标志位） */
template <typename T>
void travIn_I4(BinNodePosi<T> x, void (*visit)(T &))
{
    while (true)
        if (HasLChild(*x)) //若有左子树，则
            x = x->lc;     //深入遍历左子树
        else
        { //否则
            visit(x->data);
            // x = x->succ(); visit(x->data).(需要succ在于，如果x是rc，parent已经访问过了，它要找grandp.)
            while (!HasRChild(*x))
                if (!(x = x->succ()))
                    return; //回溯至直接后继（在没有后继的末节点处，直接退出）
                else
                    visit(x->data); //访问新的当前节点
            x = x->rc;              //（直至有右分支处）转向非空的右子树
        }
}

/*  */
template <typename T>
void travPost_R(BinNodePosi<T> x, void (*visit)(T &))
{
    if (!x)
        return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

/* 这个最高左侧可见叶节点（HLVFL）其实语义有点不清啊，因为逻辑上来讲，它就是一路深潜（能向下就不回溯的原则）找到第一个叶子节点，优先选择左结点，但如果没有左，勉为其难也可以选右节点的意思？导致我心理上感觉后序很难，不能这样啊。 */
template <typename T>
static void gotoHLVFL(Stack<BinNodePosi<T>> &S)
{
    while (BinNodePosi<T> x = S.top()) // while x not NULL
    {
        if (HasLChild(*x)) // #N 学到了把重要的条件放在前面，可以实现循环第一条件直到不满足，然后实现一次或几次第二条件，又开始循环第一条件。比起while && while来说要好很多。
        {
            if (HasRChild(*x))
                S.push(x->rc);
            S.push(x->lc);
        }
        else // !HasLChild && push is NULL == !HasChild
            S.push(x->rc);
    }
    S.pop();
}

/* #M 主要是我也写出来了，但突然感觉优化很困难，很搞脑子，所以最好再做一下。 */
template <typename T>
void travPost_I(BinNodePosi<T> x, void (*visit)(T &))
{
    Stack<BinNodePosi<T>> S;
    S.push(x);

    while (!S.empty())
    {
        if (S.top() != x->parent)
        {
            gotoHLVFL(S); // 后序原来是进入右子树而不visit啊，都怪我，被图片迷惑而忘记了本质。
        }
        x = S.pop();
        visit(x->data);
    }
}

/*  */
template <typename T>
void BinNode<T>::travLevel(void (*visit)(T &))
{
    Queue<BinNodePosi<T>> Q;
    Q.enqueue(this);

    while (!Q.empty())
    {
        BinNodePosi<T> x = Q.dequeue();
        visit(x->data);
        if (HasLChild(*x))
            Q.enqueue(x->lc);
        if (HasRChild(*x))
            Q.enqueue(x->rc);
    }
}