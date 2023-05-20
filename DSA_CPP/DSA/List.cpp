#include "List.h"
#include <iostream>
using namespace std;
// #include "ListNode.h"
// #include "ListNode.cpp"

/*  */
template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = NULL;
    header->succ = trailer;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

/*  */
template <typename T>
T &List<T>::operator[](Rank r) const
{
    ListNodePosi<T> p = first();

    // if (p = trailer)
    //     return header;
    while (0 < r--)  // #Q 为什么要0<，r本身是0的话就会直接结束循环了啊？应该测试的，但是print什么的都还没搞好，比较麻烦，等之后再说。
        p = p->succ; // 如果极端情况，succ=trailer。那么应该……？
    return p->data;  // 可能因为返回的是data，所以不需要为了方便结点插入返回header，而且其实也可以插在前面啊。
}

template <typename T>
/* 对于p之前的n个真前驱查找是否有e的值，如果过界，返回NULL。

注意——T(n)为O(n)。 */
ListNodePosi<T> List<T>::find(T const &e, int n, ListNodePosi<T> p) const
{
    while (n-- > 0) // n-1 == n-1~0。n时p->pred，1时
        if ((p = p->pred)->data == e)
            return p;
    return NULL;
}

/* #M */
template <typename T>
ListNodePosi<T> List<T>::insertAsFirst(T const &e)
{
    _size++;
    return header->insertAsSucc(e);
}

/*  */
template <typename T>
ListNodePosi<T> List<T>::insertAsLast(T const &e)
{
    _size++;
    return trailer->insertAsPred(e);
}

/* insertAfter，在p之后插入。 */
template <typename T>
ListNodePosi<T> List<T>::insertA(ListNodePosi<T> p, T const &e)
{
    _size++;
    return p->insertAsSucc(e);
}

/*  */
template <typename T>
ListNodePosi<T> List<T>::insertB(ListNodePosi<T> p, T const &e)
{
    _size++;
    return p->insertAsPred(e);
}

/*  */
// template <typename T>
// ListNodePosi<T> List<T>::insertAsPred(T const &e)
// {
//     ListNodePosi<T> x = new ListNode(e, pred, this);
//     pred->succ = x;
//     pred = x;

//     return x;
// }

// /*  */
// template <typename T>
// ListNodePosi<T> List<T>::insertAsSucc(T const &e)
// {
//     ListNodePosi<T> x = new ListNode(e, this, succ);
//     succ->pred = x;
//     succ = x;

//     return x;
// }

/* #M 复制列表中自位置p起的n项。 */
template <typename T>
void List<T>::copyNodes(ListNodePosi<T> p, int n)
{
    // assert x-_size的个数>=n
    init();
    while (n--) // n~1 or n-1~0
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}

/* 调整p前驱后继的前驱后继，delete p，_size--, return p->data */
template <typename T>
T List<T>::remove(ListNodePosi<T> p)
{
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;

    T e = p->data;
    delete p;
    _size--;

    return e;
}

/*  */
template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while (_size > 0) // _size~1 == _size-1~0
        remove(header->succ);
    return oldSize;
}

/* #M

实现——无序向量除重是从前往后制造清零区；有序向量除重是通过i和j来swap。

注意——T(n)=O(n^2)。
它这里使得最右边的同值元素被保留，而vector的则是最左边。按照查找的逻辑来看，保留最右边是正确的。 */
template <typename T>
int List<T>::deduplicate()
{
    int oldSize = _size;
    ListNodePosi<T> p = header;
    Rank r = 0;
    // int i = 0(p的前驱); p = p->succ; find(p->data, p, i); if !NULL, remove(p); else, i++

    while (trailer != (p = p->succ))
    {
        ListNodePosi<T> q = find(p->data, r, p); // 现在总会find，区别只在于是哨兵到了自己，还是真的找到。
        q ? remove(q) : r++;
    }

    return oldSize - _size;
}

/*  */
template <typename T>
void List<T>::print()
{
    ListNodePosi<T> p = first();

    for (int i = 0; i < _size - 1; i++) // 0~size-1
    {
        cout << p->data << ", ";
        p = p->succ;
    }
    cout << p->data << "\n";
}

/*  */
template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    for (ListNodePosi<T> p = first(); p != trailer; p = p->succ)
        visit(p->data);
}

/* #M

实现——比较两个相邻。

注意——T(n)=O(n)。
虽然这个是为有序列表提供的除重方式，但它也能适用于无序列表，为什么？是我创造列表的时候搞得有点问题，变成了新指针指向旧列表，而不是复制为一个新列表，本质上是没搞懂构造函数的格式，以为是Java那种。
但又有个问题，为什么我实验了一下，它即使对有序列表除重，效率仍然没有deduplicate好？奇怪。
#N 根据实际测试来看，在createSorted(E, 100, 0, 5, 0, 10);的情况下和deduplicate的时间差大概在700-300ns。
而在E, aSize, 0, 5, 0, 5且aSize=1000时，uniquify的时间已经是deduplicate的十分之一，是十万级纳秒与万级纳秒的差距，确实是渐进复杂度提升迅速。（有待进一步观察） */
template <typename T>
int List<T>::uniquify()
{
    // version A
    // 好像确实这个只适合有序列表，但P77给出的是能兼容无序列表的方式。
    // ListNodePosi<T> p = first();
    // ListNodePosi<T> q = first();
    // int oldSize = _size;
    // _size = 1;
    // while (q != trailer->pred)
    // {
    //     if (p->data != (q = q->succ)->data)
    //     {
    //         (p = p->succ)->data = q->data;
    //         _size++;
    //     }
    // }
    // return oldSize - _size;

    // version B
    ListNodePosi<T> p = first();
    ListNodePosi<T> q;
    int oldSize = _size;

    while ((q = p->succ) != trailer) // 好像写在这里更好，当_size为1时，就跳转到trailer。
    {
        if (p->data != q->data)
            p = q;
        else
            remove(q);
    }

    return oldSize - _size;
}

/* #H 从后往前找到<=e的第一个结点p，然后返回p。有可能返回header？

注意——有个细节是n-- >= 0，而在find里是n-- > 0，可能说明search会返回第n+1个前驱结点，超过明面上的允许范围。但因为header保证了边界的稳定，不会发生错误。
另外这里给出的指针p似乎不会被修改，有待观察。
T(n)最好情况下为O(1)，最坏情况下为O(n)。
在1000个数组个数情况下，似乎和find拉不开100以上ns的差距。来到10000个数，还是能看到差距的，契合search从算法逻辑上来看，存在优越的地方的特征。 */
template <typename T>
ListNodePosi<T> List<T>::search(T const &e, int n, ListNodePosi<T> p) const
{
    while (n-- >= 0) // n-0
    {
        if ((p = p->pred)->data <= e)
            break;
    }
    return p;
}

/*  */
template <typename T>
void List<T>::sort(ListNodePosi<T> p, int n)
{
    switch (rand() % 3)
    {
    case 1:
        insertionSort();
        break;
    case 2:
        selectionSort();
        break;
    default:
        mergeSort();
        break;
    }
}

/* #M 对起始于位置p的n个元素排序。

注意——T(n)最好情况下O(n)，最坏情况下O(n^2)，取决于search的运气。
#N 我突然发现我忽略了一件事，很多排序算法其实内核都是依靠查找，而有些查找其实又依赖排序事先创造的有序性，比如二分查找等。或者说低级的查找贡献给排序，排序又贡献给高级查找？似乎排序从来不是目的，查找才是。
出于不明原因，排序比查找对于同一个数组完全相同的数组来说时间抖动要小很多，除了第一个热身之外其他都非常稳定。然后数据增多之后抖动反而更大。 */
template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n)
{
    if (n < 1)
        return;

    // 最开始，有序range只有1，说明具备有序性的元素只有1个。每调整一个元素的位置，有序范围+1，因此很好理解当range=n时，说明已经有包括p在内n个元素有序了。
    for (int range = 0; range < n; range++) // && q != trailer
    {
        insertA(search(p->data, range, p), p->data); // #N 太细了……好像是p->data会在调用search之前先被临时保存，因此不需要再创建一个e。心好累，这是什么极限怪啊。好像不是这个原因，而是p不会被改变指针吗？因为我确实保险起见把q赋值为新指针，然后忘记这件事了，确实是我没有先学C++基础的东西。
        // 但总而言之，我发现语法应该对效率没有什么影响，主要作用还是为了简洁与美观吧。
        p = p->succ;
        remove(p->pred); // 我好像又犯了低级错误，本来以为remove了，但是又insert了，size会持恒啊？结果结点的Succ是够不着_size的，我忘记了都有insertA这个东西，唉。
    }
}

/* #H 对起始于位置p的n个元素排序。

注意——T(n)=thita(n^2)，说明它最好和最坏情况下效率都是一致。它的效率测试时居然比insertionSort低下，是几乎2-3倍的差距。 */
template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n)
{
    if (n < 1)
        return;

    // 之所以要head，因为如果max恰巧就是p，那么p就会被remove，无法支持下一次selectMax作为参数，导致错误。
    // 本来我都失去信心了？？我以为自己逐渐增加那么多很复杂的变量，已经离真正高效简洁的代码十万八千里了，没想到真的是这样的？？太好了。而且我要说，明明之前用调换方式一下子就做出来了，会不会这个写法没有效率上的提高，而只是类似递归和迭代的关系？
    ListNodePosi<T> head = p->pred;

    // 特别是这个tail的制作要循环，我心里已经觉得它很不靠谱了，高效简洁的代码怎么可能容忍这种一看就很低效的东西，肯定是在开头用什么更聪明的方法实现插入的吧。唉，我误解了，不过至少我写出来了。
    ListNodePosi<T> tail = p;
    for (int i = 0; i < n; i++)
        tail = tail->succ;

    while (n > 1) // 1-n == n-1
    {
        ListNodePosi<T> max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--; // #Q 可能就是在一个代入n的问题上反复折磨。我觉得这些0-n-1；1-n的想象至今都没办法用一种通用的思路来构建，这是不应该的，应该仔细想一下这个问题。
    }
}

/* 从起始于位置p的n个元素中选出最大者。为什么不选最小者呢？*/
template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n)
{
    ListNodePosi<T> max = p;
    for (ListNodePosi<T> cur = p; 1 < n; n--) // #Q 所以到底会不会修改指针啊？好像这里的顺序也有问题，用while就不行，见书上P102.
        if ((cur = cur->succ)->data >= max->data)
            max = cur;
    return max;
}

/* #H 其实思路就是聪明版vector实现，原来vector用笨办法花三个数组才能做成，这里就巧妙地用两个数组互相勾兑的感觉？ */
template <typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, int n, List<T> &L, ListNodePosi<T> q, int m)
{
    ListNodePosi<T> pp = p->pred;

    while (0 < m) // 将this列表作为最终列表，因此原来的东西要是顺序一致都可以默认不动，
        if ((0 < n) && (p->data <= q->data))
        {
            if ((p = p->succ) == q) // p归入合并的列表，并替换为其直接后继，但这里的==是什么作用？哦，好像是如果q的第一个值居然那么巧地大于所有p的值，然后p一直替换为后继都越界了，来到了第一个q，因为p、q本质是一个列表里的东西，那么就break。但是这个break范围是哪里啊，按我的想法它不是就冲破while了吗？可能因为L是this列表后半段的指针，本质上还是一个列表之类的，默认它们就不需排序，也就放在那儿，可以直接结束while了。
                break;
            n--;
        }
        else
        {
            insertB(p, L.remove((q->succ)->pred));
            m--;
        }

    p = pp->succ;
    return p;
}

/* 对起始于位置p的n个元素排序。 */
template <typename T>
void List<T>::mergeSort(ListNodePosi<T> &p, int n)
{
    int m = n >> 1;

    ListNodePosi<T> q = p;
    for (int i = 0; i < m; i++)
        q = q->succ;

    mergeSort(p, m);
    mergeSort(q, n - m); 
    // #N 确实有道理啊，我这里只会用if来分开奇数、偶数n的情况，做成m和m-1，没想到可以写成n-m。
    merge(p, m, *this, q, n - m);
}