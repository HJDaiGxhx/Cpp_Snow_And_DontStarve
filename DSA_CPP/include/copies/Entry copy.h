#pragma once
#ifndef _Entry_H
#define _Entry_H

#include <vector>
// using namespace std;
#include "Block.h"

#define vector std::vector
#define DEF_ELEM_SIZE 0

class Entry : public Block
{
public:
    vector<Block *> *elem_p;

    Entry() {}
    Entry(vector<Block> *e_p)
    {
        Init();

        if (e_p->size() > 0)
            for (int i = 1; i < e_p->size(); i++)
                elem_p->emplace_back(new Block((*e_p)[i]));
        else
            elem_p->emplace_back(new Block()); // 确保element[0]是存在的，虽然上游函数可能确保导致这里冗余。

        if (elem(0)->Weight() == DEFWEIGHT)
            updateWeight();
    }
    ~Entry()
    {
        for (int i = 0; i < size(); i++)
            delete (*elem_p)[i];
        delete elem_p;
    }

    int Count() { return elem(0)->Id(); }
    int Id() { return elem(0)->Id(); }
    string Name() { return elem(0)->Name(); }
    float Weight() { return elem(0)->Weight(); }

    int size() { return elem_p->size(); }

    virtual void updateWeight() {}
    virtual void updateWeightALL() {}
    void clearWeight() { elem(0)->setWeight(DEFWEIGHT); }
    void clearWeightALL()
    {
        for (int i = 0; i < size(); i++)
            elem(i)->setWeight(DEFWEIGHT);
    }

    virtual void excel() {}
    void print()
    {
        for (int i = 0; i < size(); i++)
            elem(i)->print();
    }

    Block *operator[](int i) { return elem(i); }
    Block *elem(int i) { return (*elem_p)[i]; }
    vector<Block *> *Element() { return elem_p; }

    void Init() { elem_p = new vector<Block *>(); }
    void Init(int i) { elem_p = new vector<Block *>(i); }

    void Insert() { elem_p->emplace_back(new Block()); }
    void Insert(const Block *b) { elem_p->emplace_back(b); }
    void Insert(const Block &b) { elem_p->emplace_back(new Block(b)); }
};

#endif