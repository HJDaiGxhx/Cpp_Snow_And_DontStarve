#pragma once

#include "Stack.h"
#include "Queue.h"

template <typename T>
struct BinNode;
template <typename T>
using BinNodePosi = BinNode<T> *;

#define stature(p) ((p) ? (p)->height : -1) // p->height / -1
typedef enum
{
    RB_RED,
    RB_BLACK
} RBColor;

template <typename T>
struct BinNode
{
    // 为简化描述起见统一开放
    T data;
    BinNodePosi<T> parent;
    BinNodePosi<T> lc;
    BinNodePosi<T> rc;
    int height;
    int npl;
    RBColor color;

    // #N NULL只针对指针，而不是基础类型。
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    int size();

    BinNodePosi<T> insertAsLC(T const &e) // 其实我想过的，但以前不会在这里用构造函数，我以为没有这种语法。
    {
        return lc = new BinNode(e, this); // this.lc √; lc.data, parent √
    }
    BinNodePosi<T> insertAsRC(T const &e)
    {
        return rc = new BinNode(e, this);
    }

    void TravPre(void (*visit)(T &))
    {
        switch (rand() % 3)
        {
        case 1:
            travPre_I1(this, visit);
            break;
        case 2:
            travPre_I2(this, visit);
            break;

        default:
            travPre_R(this, visit);
            break;
        }
    }
    /* #N 中序遍历是尤为重要的，因为它赋予二叉树一个次序，使得它可以被看待为线性结构。

    这么说其实不太清楚，就是向量可以表达为二叉树，只要它在下标上按那个规则跳跃，比如二叉查找；而中序遍历则反之，使得二叉树能被表达为向量。并且依此定的前驱后继，可被看做是vector[r-+1]，在逻辑上这么一想是很妙、很精炼简洁啊。

    （其实我刚才都没想到前驱后继是为了向量服务……是灵光一闪想到的，那感觉有点low了啊，辛辛苦苦只是为了反而把二叉树变成一个简单能实现的数据结构，当然并不是这样的，是很有用的。）*/
    void TravIn(void (*visit)(T &))
    {
        switch (rand() % 5)
        {
        case 1:
            travIn_I1(this, visit);
            break;
        case 2:
            travIn_I2(this, visit);
            break;
        case 3:
            travIn_I3(this, visit);
            break;
        case 4:
            travIn_I4(this, visit);
            break;
        default:
            travIn_R(this, visit);
            break;
        }
    }
    void travPost(void (*visit)(T &))
    { //二叉树后序遍历算法统一入口
        switch (rand() % 2)
        { //此处暂随机选择以做测试，共两种选择
        case 1:
            travPost_I(this, visit);
            break; //迭代版
        default:
            travPost_R(this, visit);
            break; //递归版
        }
    }
    void travLevel(void (*visit)(T &));

    /* 我本来觉得很妙的是，中序遍历可以看做是二叉搜索树变向量，而调用succ，就相当于每次访问[r+=1]，如果从第[x]开始，实际上也是逻辑上完成遍历向量的功能。

    神奇的事情是，它既然像遍历数组一样访问二叉树，完成的不就是中序遍历的工作吗？因此它又是中序遍历的一块拼图，逻辑上的封装、抽象、自洽程度真的太妙了，可能逻辑上的封装真的是这一块很重要的事，因为我很多次都发现有这种倾向。 */
    BinNodePosi<T> succ();
};

// MACROS
#pragma region
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))

#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) (sibling((x)->parent)) // #Q 但是这里为什么x是指针形式？
#define fromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#pragma endregion

// 遍历（先见struct里面的）
#pragma region
template <typename T>
void travPre_I1(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
static void visitAlongVine(BinNodePosi<T> x, void (*visit)(T &), Stack<BinNodePosi<T>> &S);
template <typename T>
void travPre_I2(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
void travPre_R(BinNodePosi<T> x, void (*visit)(T &));

template <typename T>
void goAlongVine(BinNodePosi<T>, void (*visit)(T &), Stack<BinNodePosi<T>> &S);
template <typename T>
void travIn_I1(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
void travIn_I2(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
void travIn_I3(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
void travIn_I4(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
void travIn_R(BinNodePosi<T> x, void (*visit)(T &));

template <typename T>
static void gotoHLVFL(Stack<BinNodePosi<T>> &S);
template <typename T>
void travPost_I(BinNodePosi<T> x, void (*visit)(T &));
template <typename T>
void travPost_R(BinNodePosi<T> x, void (*visit)(T &));
#pragma endregion

// #H 哈夫曼编码问题