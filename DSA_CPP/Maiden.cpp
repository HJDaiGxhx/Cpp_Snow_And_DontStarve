#include "include/Maiden.h"

#ifndef _MAIDEN_CPP_
#define _MAIDEN_CPP_

char Maiden::addr[] = "C:/Users/qazse/Documents/Snow/Maiden.md";
int Maiden::sample[] = {0, 1, 1, 1};
// static Table<Maiden> T_MAIDEN("Maiden");

Maiden::Maiden(int id, string name, float weight, Block family, GrowType growType, Skill skill, Data data) : Block(id, name, weight)
{
    // element.insert(new Block(family));
    // element.insert(new GrowType(growType));
    // element.insert(new Skill(skill));
    // element.insert(new Data(data));
    if (weight == DEFWEIGHT)
        updateWeight();
}
Maiden::Maiden(Block *element) : Block(element[0])
{
    int A[4] = {element[4].Id(), element[5].Id(), element[6].Id(), element[7].Id()};
    // this->element.insert(T_FAMILY.search(element[1]));
    // this->element.insert(T_GROWTYPE.search(element[2]));
    // this->element.insert(new Skill(element[3]));
    // this->element.insert(new Data(A));
    if (weight == DEFWEIGHT)
        updateWeight();
}
Maiden::Maiden(vector<Block> *element) : Block((*element)[0])
{
    int A[4] = {(*element)[4].Id(), (*element)[5].Id(), (*element)[6].Id(), (*element)[7].Id()};
    // this->element.insert(T_FAMILY.search((*element)[1]));
    // this->element.insert(T_GROWTYPE.search((*element)[2]));
    // this->element.insert(new Skill((*element)[3]));
    // this->element.insert(new Data(A));
    if (weight == DEFWEIGHT)
        updateWeight();
}

ostream &operator<<(ostream &out, Maiden &m)
{
    m.Block::print();
    for (int i = 0; i < m.element.size(); i++)
        m.element[i]->print();
    return out;
}
void Maiden::print()
{
    Block::print();
    element[family_Maiden]->Block::print();
    element[growType_Maiden]->Block::print();
    for (int i = growType_Maiden + 1; i < element.size(); i++)
        element[i]->print();
}

void Family::updateWeight()
{
    weight = 0;
    int searched = -1;
    for (int i = Count(); i > 0; i--)
    {
        // searched = T_MAIDEN.search(family_Maiden, name, searched + 1);
        if (searched >= 0)
            // weight += T_MAIDEN[searched]->Weight()
            ;
    }
}
void Maiden::updateWeight()
{
    weight = 0;
    for (int i = 0; i < element.size(); i++)
        weight += sample[i] * element[i]->Weight();
}

#endif