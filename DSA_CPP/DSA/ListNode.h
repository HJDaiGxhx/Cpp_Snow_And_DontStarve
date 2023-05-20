#pragma once

#include <cstddef> // #Q NULL被定义在这里？

typedef int Rank;
template <typename T>
struct ListNode;
template <typename T>
using ListNodePosi = ListNode<T> *; // #Q 列表节点位置

template <typename T>
struct ListNode
{
    T data;
    ListNodePosi<T> pred;
    ListNodePosi<T> succ;

    ListNode()
    {
    }
    // #Q 总的来说就是完善了自己的pred和next指针，而x的前驱还要修改它的后继指向x；x的后继也要修改自己的前驱指向x。而这个通过insertAsPred或Succ可以一条龙式完成。
    ListNode(T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL) : data(e), pred(p), succ(s) {}

    ListNodePosi<T> insertAsPred(T const &e)
    {
        ListNodePosi<T> x = new ListNode(e, pred, this);
        pred->succ = x;
        pred = x;

        return x;
    }
    ListNodePosi<T> insertAsSucc(T const &e)
    {
        ListNode<T> *x = new ListNode(e, this, succ);
        succ->pred = x;
        succ = x;

        return x;
    }
};