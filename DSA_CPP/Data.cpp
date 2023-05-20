#include "include/Data.h"

#define DOCUMENTS "C:/Users/qazse/Documents/"
char Family::addr[] = "C:/Users/qazse/Documents/Snow/Family.md";
char Feature::addr[] = "C:/Users/qazse/Documents/Snow/Feature.md";
char GrowType::addr[] = "C:/Users/qazse/Documents/Snow/GrowType.md";

// static Table<Family> T_FAMILY("Family");
// static Table<Feature> T_FEATURE("Feature");
// static Table<GrowType> T_GROWTYPE("GrowType");
// static Table<Meat> T_MEAT("Meat");

void GrowType::list(char c)
{
    string s[5] = {"统率", "武勇", "知略", "", "政治"};
    int tId, tWeight;
    bool next;

    cout << name << '\n';
    for (int i = featureGrow_GrowType; i < element.size(); i++)
        if (element[i]->Name() != DEFNAME)
        {
            cout << element[i]->Name() << "(";

            // printf("\t(");
            for (int j = 8, tId = element[i]->Id(), tWeight = element[i]->Weight(); j > 0; j /= 2)
                if (tId >= j)
                {
                    printf("%s+%d", s[j / 2].c_str(), tWeight);
                    tId -= j;
                    if (tId > 0)
                        cout << ',';
                }
            printf(")\n");
        }

    cout << endl;
}

/* 惊了……我原来以为这个不重要的，因为想着能自动化的也就是print和初始化函数了，结果……没想到会那么。 */
void Family::print()
{
    Block::print();
    element->print();
}
void Feature::print()
{
    Block::print();
    element->print();
}
void GrowType::print()
{
    Block::print();
    for (int i = 0; i < element.size(); i++)
        element[i]->print();
}
void Data::print()
{
    for (int i = 0; i < Data_length; i++)
        element[i]->print();
}

void Feature::updateWeight()
{
    weight = 0;
    weight += (float)element->Id() / 100;
    if (element->Weight() != DEFWEIGHT)
        weight += element->Weight();
}
void GrowType::updateWeight()
{
    weight = 0;

    Block *p;
    for (int i = featureGrow_GrowType; i < element.size(); i++)
    {
        if (element[i]->Name() == DEFNAME)
            break;
        // p = T_FEATURE.search(element[i]->Name());
        if (p != NULL)
            weight += p->Weight();
    }
}
void Data::updateWeight()
{
    weight = 0;
    for (int i = 0; i < Data_length; i++)
        weight += element[i]->Weight();
}

string Data::Name()
{
    for (int i = 0; i < Data_length; i++)
        cout << element[i]->Id() << '\t';
    return "";
}
ostream &operator<<(ostream &out, Data &d)
{
    for (int i = 0; i < Data_length; i++)
        out << d.element[i]->Id() << '\t';
    return out;
}
