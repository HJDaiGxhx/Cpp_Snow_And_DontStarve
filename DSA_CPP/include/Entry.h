#pragma once
#ifndef _Entry_H
#define _Entry_H

#include "Block.h"

/* Entry是由不定个Block指针组成的vector。
由于一些原因并没有将它做成vector，而是包装成了一个元素是vector的类，可能之后要进行修改。 */
class Entry : public Block
{
public: // 其实我真的应该尽快更新一下这个结构，因为感觉Entry还是做成模板比较好，而Table做成Entry<Entry>之类的形式，因为总是Entry装Entry装Entry然后就无法打印，这个问题非常难受，而应该通过模板中Insert<T>解决吧。
    vector<Block *> *elem_p;

    Entry() : Block("Entry") { Init_ElemP(); }
    Entry(string name) : Block(name) { Init_ElemP(); }
    Entry(const Block &b) : Block(b) { Init_ElemP(); }
    Entry(Entry &e) : Block(e)
    {
        Init_ElemP();
        for (int i = 0; i < e.size(); i++)
            Insert(*(e.elem(i)));
    }
    Entry(vector<Block> *e_p) : Block((*e_p)[0])
    {
        Init_ElemP();

        for (int i = 1; i < e_p->size(); i++)
            Insert((*e_p)[i]);

        if (weight == DEFWEIGHT)
            updateWeight();
    }
    virtual ~Entry()
    {
        for (int i = 0; i < size(); i++)
            delete (*elem_p)[i];
        vector<Block *>().swap(*elem_p);
        // delete elem_p;
    }

    double Weight(int i)
    {
        if (0 <= i < size())
            return elem(i)->Weight();
        return DEFWEIGHT;
    }
    int size() { return elem_p->size(); }
    void traverse(auto fun = [](auto x) {});

    virtual void updateWeight();
    virtual void updateWeightALL();
    void clearWeight() { setWeight(DEFWEIGHT); }
    void clearWeightALL();

    void print();
    void excel();
    void luatable(string s, bool b = true, s_v idname = "atleast", s_v weightname = "atmost");

    Block *operator[](int i) { return elem(i); }
    vector<Block *> &elem() { return (*elem_p); }
    Block *elem(int i) { return (*elem_p)[i]; }
    vector<Block *> *Element() { return elem_p; }

    void Init_ElemP() { elem_p = new vector<Block *>(); }
    void Init_ElemP(int i) { elem_p = new vector<Block *>(i); }

    void Insert() { elem_p->emplace_back(new Block()); }
    void Insert(Block *b) { elem_p->emplace_back(b); }
    // void Insert(auto p) { elem_p->emplace_back(p); }
    void Insert(const Block &b) { elem_p->emplace_back(new Block(b)); }
    void Insert(string s) { elem_p->emplace_back(new Block(s)); }
    void Insert(Entry &e) { elem_p->emplace_back(new Entry(e)); }

    void Clear();
};

void Entry::print()
{
    Block::print();
    for (int i = 0; i < size(); i++)
        elem(i)->print();
}
void Entry::excel()
{
    Block::print();
    for (int i = 0; i < size(); i++)
        elem(i)->excel();
}
void Entry::luatable(string s, bool b, s_v idname, s_v weightname)
{
    if (b && name != "")
        printf("%s%s = {\n", s.c_str(), name.c_str());
    else
        printf("%s{\n", s.c_str());

    for (int i = 0; i < size(); i++)
        elem(i)->luatable(s + "\t", b);
    // if (!b)
    //     Block::luatable();

    printf("%s},\n", s.c_str());
}
void Entry::clearWeightALL()
{
    setWeight(DEFWEIGHT);
    for (int i = 0; i < size(); i++)
        elem(i)->setWeight(DEFWEIGHT);
}
void Entry::updateWeight()
{
    weight = 0;
    for (int i = 0; i < size(); i++)
        weight += elem(i)->Weight();
}
void Entry::updateWeightALL()
{
    weight = 0;
    for (int i = 0; i < size(); i++)
    {
        elem(i)->updateWeight();
        weight += elem(i)->Weight();
    }
}
// template <typename T>
// void Entry::Insert(const T &b) { elem_p->emplace_back(new T(b)); }
void Entry::Clear()
{
    for (int i = 0, s = elem_p->size(); i < s; i++)
        delete (*elem_p)[i];
    elem_p->clear();
}
void Entry::traverse(auto fun)
{
    for (auto x : *elem_p)
        fun(x);
}

#endif