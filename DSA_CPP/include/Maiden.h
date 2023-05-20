#pragma once

#ifndef _MAIDEN_H_
#define _MAIDEN_H_

#include <string>
#include "../Data.cpp" // 啊啊啊……人生都浪费在debug上了，真的烦死了。
#include "../DSA/vector.h"

enum MAIDEN
{
    family_Maiden,
    growType_Maiden,
    skill_Maiden,
    data_Maiden,
    length_Maiden
};
class Maiden : public Block
{
protected:
public:
    static int sample[];
    static char addr[];
    vector<Block *> element;

    Maiden(Block *element);
    Maiden(vector<Block> *element);
    Maiden(int id = -1, string name = DEFNAME, float weight = DEFWEIGHT, Block family = Block(), GrowType growType = GrowType(), Skill skill = Skill(), Data data = Data());
    virtual ~Maiden()
    {
        // for (int i = 0; i < element.size(); i++)
        //     delete element[i];
    }

    virtual int size() { return element.size(); }
    virtual Block *Element(int i) { return element[i]; }
    void updateWeight();
    void print();
    friend ostream &operator<<(ostream &out, Maiden &m);
};

#endif
