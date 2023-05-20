#pragma once

#include "BST.h"

// 这个AVL是为了打造渐进树高logn，而破坏树高的操作只有动态操作，所以它重载动态操作就好，像search就可以沿用BST的二分查找。
template <typename T>
class AVL : public BST<T>
{
public:
    BinNodePosi<T> insert(T const &e);
    bool remove(T const &e);
};

// #Q 为什么要给x加括号？
#define Balanced(x) (return stature((x).lc) == stature((x).rc))
#define BalFac(x) (return stature((x).lc) - stature((x).rc))
#define AVLBalanced(x) (return (-2 < BalFac(x)) && (BalFac(x) < 2)) // -1~1
#define tallerChild(x) ( \
    stature((x).lc) > stature((x).rc) ? (x).lc : (stature((x).lc) < stature((x).rc) ? (x).rc : (IsLChild(x) ? (x).lc : (x).rc)))
