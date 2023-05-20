#pragma once

#include "ListNode.h"

template <typename T>
class List
{
private:
    int _size;
    ListNodePosi<T> header, trailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi<T> h, int n);

public:
    // 构造函数
    List() { init(); }     //默认
    List(List<T> const &L) //整体复制列表L
    {
        copyNodes(L.first(), L._size);
    }
    List(List<T> const &L, Rank r, int n) //复制列表L中自第r项起的n项
    {
        ListNodePosi<T> p = L.first();
        while (0 < r--)
            p = p->succ;
        copyNodes(p, n); // 好像因为[]返回的是值，所以这里选择重新再复制一遍？
    }
    List(ListNodePosi<T> p, int n) //复制列表中自位置p起的n项
    {
        copyNodes(p, n);
    }
    List(T *A, Rank size)
    {
        init();
        while (--size >= 0) // size-1 ~ 0
            insertAsFirst(A[size]);
    }

    // 析构函数
    ~List() //释放（包含头、尾哨兵在内的）所有节点
    {
        clear();
        delete header;
        delete trailer;
    }

    Rank size() const { return _size; }
    bool empty() { return _size <= 0; }
    ListNodePosi<T> first() const { return header->succ; }
    ListNodePosi<T> last() const { return trailer->pred; } //末节点位置

    ListNodePosi<T> find(T const &e, int n, ListNodePosi<T> p) const;
    ListNodePosi<T> search(T const &e, int n, ListNodePosi<T> p) const;

    void sort(ListNodePosi<T> p, int n);
    void insertionSort(ListNodePosi<T> p, int n);
    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n);
    void selectionSort(ListNodePosi<T> p, int n);
    void mergeSort(ListNodePosi<T> &p, int n);                                    //对从p开始连续的n个节点归并排序
    ListNodePosi<T> merge(ListNodePosi<T>, int, List<T> &, ListNodePosi<T>, int); //归并

    ListNodePosi<T> insertAsFirst(T const &e);
    ListNodePosi<T> insertAsLast(T const &e);
    ListNodePosi<T> insertA(ListNodePosi<T> p, T const &e);
    ListNodePosi<T> insertB(ListNodePosi<T>, T const &e);
    // ListNodePosi<T> insertAsPred(T const &e);
    // ListNodePosi<T> insertAsSucc(T const &e);

    T remove(ListNodePosi<T> p);
    int deduplicate();
    int uniquify();

    void traverse(void (*visit)(T &));
    // void traverse(VST& visit);

    void print();

    T &operator[](Rank r) const;
    List<T> *operator=(List<T> *);
};