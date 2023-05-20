#pragma once
#ifndef _Foods_H
#define _Foods_H

#include <stack>
using std::stack;
#include "ExcelTable.h"

const char *INADDR = "C:/Users/qazse/Documents/GitHub/scripts/preparedfoods.lua";
const char *OUTNAME = "Recipes";

enum BUFF_enum
{
    name_BUFF,
    healing_BUFF,
    calories_BUFF,
    sanity_BUFF,
    perish_time_BUFF,
    tags_BUFF,
    end_BUFF,
};
enum RAW_enum
{
    id_RAW = -3,
    healing_RAW = 0,
    calories_RAW,
    sanity_RAW,
    perish_time_RAW,
    tags_RAW,
    end_RAW,
};
enum RECIPE_enum
{
    name_RECIPE, // 原来的代码写成的样子
    must_RECIPE, // Table, names_MUST, tags_MUST
    not_RECIPE,  // Block或Entry就行，tags_NOT
};
enum MUSTORNOT
{
    default_FLAGS,
    consinlayer_FLAGS,
    or_FLAGS,
    not_FLAGS = 4,
};

static Table<Entry> BUFF("Buff");

class Meat : public Entry
{
public:
    Meat(vector<Block> *e_p) : Entry((*e_p)[0])
    {
        Block *p, *target;
        for (int i = healing_BUFF, size = e_p->size(); i < end_BUFF && i < size; i++)
        {
            target = &(*e_p)[i];

            p = BUFF.search(target->Id()); // 先ID
            if (p != NULL)
                Insert(p);
            else
            {
                string name = target->Name();
                if (name[0] == '-')
                    Insert(*target);
                else if ((p = BUFF.search(name)) != NULL)
                    Insert(p);
                else
                    Insert(Block(DEFID, name, target->Weight()));
            }
        }
    }

    void excel();
    void updateWeight();
};
void Meat::excel()
{
    Block::print();
    for (int i = 0, s = size(); i < perish_time_BUFF && i < s; i++)
        printf("\t%.2f", elem(i)->Weight());
}
void Meat::updateWeight()
{
    weight = 0;
    for (int i = 0, s = size(); i < sanity_BUFF && i < s; i++)
        weight += elem(i)->Weight();
}

class Foods
{
};

static Table<Meat> MEATS("Meats");
static Table<Entry> RAWFOODS("Rawfoods");
// static Table VEGGIES("Meat");
// static Table DIARIES("Meat");
// static Table PREPAREDFOOD("Meat");

// static Table *tables[] = {&MEATS, &VEGGIES, &DIARIES, &PREPAREDFOOD};
// static ExcelTable FOODS("Foods", tables);

int _less = 0, _less_equal = 0, _more = 0, _more_equal = 0;
Block getBlock(string substr, string optr, string i, int &k)
{
    double num = atof(i.c_str());
    double min = DEFID;
    double max = DEFWEIGHT;

    if (optr == ">")
    {
        max = num + .01;
        // _more++;
    }
    else if (optr == "<")
    {
        max = num;
        // _less++;
    }
    else if (optr == ">=")
    {
        max = num;
        // _more_equal++;
    }
    else if (optr == "<=")
    {
        max = num;
        // _less_equal++;
    }
    else
        return Block(substr);

    k += 2;
    return Block(min, substr, max); // [min, max]
    // printf("%d, %d, %d, %d", _less, _less_equal, _more, _more_equal); 1, 8, 11, 42
}
double getWeight(string substr, string optr, string i, int &k)
{
    double num = atof(i.c_str());
    double min = DEFID;
    double max = DEFWEIGHT;

    if (optr == ">")
    {
        max = num + .01;
        // _more++;
    }
    else if (optr == "<")
    {
        max = num;
        // _less++;
    }
    else if (optr == ">=")
    {
        max = num;
        // _more_equal++;
    }
    else if (optr == "<=")
    {
        max = num;
        // _less_equal++;
    }
    else
        return 1;

    k += 2;
    return max; // [min, max]
}

Block b_bestNames;
Block *bestNames(string substr)
{
    Block *temp, *p;

    if (p != NULL) // p = RAWFOODS.search(substr)
        return p;
    else
    {
        const string ADDR = "C:/Users/qazse/Documents/GitHub/scripts/prefabs/";
        fstream inFile(ADDR + substr + ".lua", ios::in);

        const string CUTTER = "inst.components.edible.hungervalue = ";
        string line, tuning;
        int pos, hungervalue = 0;

        for (; !inFile.eof();)
        {
            getline(inFile, line, '\n'); // TODO: 反方向指针，因为通常写在最下面。
            pos = line.find(CUTTER);
            if (pos != std::string::npos)
            {
                tuning = line.substr(pos + CUTTER.size());
                if (temp = BUFF.search(tuning))
                    hungervalue = temp->Weight();
                break;
            }
        }

        // RAWFOODS.Insert(Block(RAWFOODS.size(), substr, hungervalue));
        // return RAWFOODS.Element()->back();
        return NULL;
    }
}
Block *bestAll(int prior, int lo, int hi)
{
    // RAWFOODS.sort(lo, hi, prior);
    // i = RAWFOODS.elem(lo)->Id();
    // RAWFOODS.sort(lo, hi, id_RAW);

    // return RAWFOODS.search(i);
    return NULL;
}
Block *bestTags(string str = "")
{
    /*
      RAWFOODS.sort(tags_RAW); // 默认从小到大。这个应该做在subtable函数里。

      int limit[2] = {0, RAWFOODS.size()}, i = DEFID;
      if (str != "")
           limit = RAWFOODS.sub(tags_RAW, str);

      Block *p = bestAll(hunger_RAW, limit[0], limit[1]);
      RAWFOODS.sort(id_RAW, 0, limit[0]);
      RAWFOODS.sort(id_RAW, limit[1], RAWFOODS.size());
      return p;
    */
    return NULL;
}
void bestInsert(Block *Best, Block *p, int min, int &slot)
{
    if (min == DEFID)
        min = 1;

    if (p != NULL)
        for (int num = 0; num < min && slot < 4; num++, slot++)
            Best->Insert(p); // 这里有问题啊……如果不注册就，怎么办。
}

class Recipe : public Table<Entry>
{
public:
    s_v addrRaw;
    Recipe(string name) : Table<Entry>(name), addrRaw(INADDR) {}
    Recipe(s_v inname, s_v outname, s_v foldername = "Recipes") : Table<Entry>(string(inname), string(outname), foldername), addrRaw(INADDR) {}

    void readRaw();
    void funRaw();
    void funNew();
    Entry &funBest(Entry &Must, Entry &Or, Entry &Not);
    void cutIngreStrNew();

    bool found(int pos) { return pos != std::string::npos; }
};
void Recipe::readRaw()
{
    s_v target = "test =";

    string line;
    vector<Block> elem;
    int pos = -1;
    int space = 0;

    fstream inFile(string(addrRaw), ios::in);
    freopen(addrRaw.data(), "r", stdin);

    for (int id = 0; !inFile.eof();)
    {
        getline(inFile, line, '\n');
        pos = line.find(target);

        if (pos != string::npos)
        {
            string lines = line;
            for (int p = lines.find("end"); p == string::npos;)
            {
                getline(inFile, lines, '\n');

                space = 0;
                for (int size = lines.size(); space < size && (lines[space] == ' ' or lines[space] == '\t'); space++)
                    ;
                lines = ' ' + lines.substr(space);

                line += lines;
                p = lines.find("end");
            }

            pos = line.find("return") + 7;
            elem.emplace_back(Block(id++, line.substr(pos), DEFWEIGHT));
        }
    }

    fstream outFile(addrOut, ios::out | ios::trunc);
    freopen(addrOut.c_str(), "w", stdout);

    for (int i = 0; i < elem.size(); i++, printf("\n"))
        elem[i].print();
}
void Recipe::funRaw()
{
    string recipeRaw;
    string substr;
    Entry recipeNew("RecipeNew");
    int pos;

    for (int i = 0; i < size(); i++)
    {
        recipeRaw = entry(i)->Name();
        for (pos = recipeRaw.find("and"); found(pos); pos = recipeRaw.find("and"))
        {
            substr = recipeRaw.substr(0, pos - 1); // 正常情况下不可能and在最开头或最结尾……
            recipeNew.Insert(Block(0, substr, 0));
            recipeRaw = recipeRaw.substr(pos + 4);
        }
        if (found(pos = recipeRaw.find("end")))
            recipeNew.Insert(Block(0, recipeRaw.substr(0, pos - 1), 0));

        entry(i)->Element()->emplace_back(new Entry(recipeNew));

        vector<Block *> *p = recipeNew.Element();
        recipeNew.Init_ElemP();
        delete p;
    }
}

string notchar = "()";
int notcharsize = notchar.size();
void cutIngreStr(vector<string> *substrs, string ingreStr)
{
    int i = -1;
    string substr = "";
    substrs->clear();

    for (int s = ingreStr.size(); i < s; substr = "")
    {
        while (i < s && ingreStr[++i] != ' ')
            switch (ingreStr[i])
            {
            case '(':
                substrs->emplace_back("(");
                break;
            case ')':
                substrs->emplace_back(substr);
                substrs->emplace_back(")");
                substr = "";
                i++;
                break;
            default:
                substr += ingreStr[i];
                break;
            }
        if (substr == "and")
            substrs->emplace_back("A");
        else if (substr == "not")
            substrs->emplace_back("N");
        else if (substr == "or")
            substrs->emplace_back("O");
        else if (substr.find("end") == string::npos)
            substrs->emplace_back(substr);
    }
}

Entry Best("Best");
void Recipe::funNew()
{
    // Entry recipeNew("recipeNew");
    Entry Must("must_needs");
    Entry Not("not_needs");
    Entry Or("or_needs");
    stack<Block> Stack;

    string ingreStr;
    vector<string> substrs;
    string substr;
    char initial;

    for (int i = 0; i < size(); i++)
    {
        for (int j = 1; j < entry(i)->size(); j++)
        {
            ingreStr = entry(i)->Name();
            cutIngreStr(&substrs, ingreStr);

            int flag = default_FLAGS;
            for (int k = 0, s = substrs.size(); k < s; k++)
            {
                initial = substrs[k][0];
                switch (initial)
                {
                case 'A':
                    break;
                case 'N':
                    break;
                case 'O':
                    break;
                case '(':
                    break;
                case ')':
                    break;
                default:
                    break;
                }

                substr = substrs[k];

                if (substr == "not")
                    flag = not_FLAGS;
                else if (substr == "or")
                    flag = or_FLAGS;
                else
                {
                    if (flag == not_FLAGS)
                        Not.Insert(substr);
                    else if (flag == or_FLAGS)
                    {
                        if (!Stack.empty())
                        {
                            Or.Insert(Stack.top());
                            Stack.pop();
                        }
                        if (!(found(substr.find("_cooked")) || found(substr.find("_ripe"))))
                            if (k + 2 < s)
                                Or.Insert(getBlock(substr, substrs[k + 1], substrs[k + 2], k));
                            else
                                Or.Insert(Block(substr, 1));
                    }
                    else if (k + 2 < s)
                        Stack.push(getBlock(substr, substrs[k + 1], substrs[k + 2], k));
                    else
                        Stack.push(Block(substr, 1));
                }
            }
            for (; !Stack.empty(); Stack.pop())
                Must.Insert(Stack.top());
        }

        entry(i)->Clear();
        // entry(i)->Element()->emplace_back(new Entry(recipeNew));
        entry(i)->Element()->emplace_back(new Entry(Must));
        entry(i)->Element()->emplace_back(new Entry(Or));
        entry(i)->Element()->emplace_back(new Entry(Not));

        // entry(i)->Element()->emplace_back(new Entry(funBest(Must, Or, Not)));
        // Best.Clear();

        Must.Clear();
        Or.Clear();
        Not.Clear();
    }
}
Entry &Recipe::funBest(Entry &Must, Entry &Or, Entry &Not)
{
    int pos, slot = 0, min, max, cals, min_cals, best_min;
    string str, substr;
    vector<string> not_tags;
    Block *p, *temp;

    for (int i = 0; i < Must.size() && slot < 4; i++)
    {
        min = Must.elem(i)->Id();
        str = Must.elem(i)->Name();

        if (found(pos = str.find("names.")))
        {
            p = bestNames(str.substr(pos + 6));
            bestInsert(&Best, p, min, slot);
        }
        else if (found(str.find("tags.")))
            bestInsert(&Best, bestTags(str), min, slot);
    }

    for (int i = 0, min_cals = 1000; i < Or.size() && slot < 4; i++)
    {
        min = Or.elem(i)->Id();
        str = Or.elem(i)->Name();

        if (found(pos = str.find("names.")))
            temp = bestNames(str.substr(pos + 6));
        else if (found(str.find("tags.")))
            temp = bestTags(str);

        if (temp != NULL)
        {
            cals = min * temp->Weight(calories_RAW);
            if (p == NULL || cals < min_cals)
            {
                p = temp;
                min_cals = cals;
                best_min = min;
            }
        }
    }
    if (p != NULL)
        bestInsert(&Best, p, best_min, slot);

    if (slot < 4)
    {
        for (auto *x : Not.elem())
        {
            str = x->Name();
            if (found(pos = str.find("names.")))
                str = str.substr(pos + 6);
            not_tags.emplace_back(str);
        }

        /*
        int limit[2] = RAWFOODS.sort(calories_RAW, not_tags);
        p = RAWFOODS.entry(0);
        bestInsert(&Best, p, 4, slot);
        RAWFOODS.sort(id_RAW);
        */
    }

    Best.updateWeight();
    return Best;
}
void Recipe::cutIngreStrNew()
{
    Entry Must("must_needs");
    Entry Not("not_needs");
    Entry Or("or_needs");
    stack<Block> Stack;

    string ingreStr, s;
    stack<string> substrs;
    stack<Block> blocks;
    int flag;

    for (int entryId = 0; entryId < size(); entryId++)
    {
        for (int j = 1; j < entry(entryId)->size(); j++)
        {
            ingreStr = entry(entryId)->Name();

            string substr = "";
            stack<string>().swap(substrs);

            for (int i = -1, size = ingreStr.size(); i < size; substr = "")
            {
                while (i < size && ingreStr[++i] != ' ')
                    switch (ingreStr[i])
                    {
                    case '(':
                        substrs.push("(");
                        break;
                    case ')':
                        substrs.push(")");
                        while ((s = substrs.top()) != "(")
                            ;
                        break;
                    default:
                        substr += ingreStr[i];
                        break;
                    }
                if (substr == "and")
                {
                    flag = consinlayer_FLAGS;
                }
                else if (substr == "or")
                    substrs.push("O");
                else if (substr == "not")
                    substrs.push("N");
                else
                {
                    substr += " ";
                }
            }
        }
    }
}

#endif