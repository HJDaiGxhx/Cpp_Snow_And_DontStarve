#pragma once
#ifndef _Table_H
#define _Table_H

#include <fstream>
#include <vector>
#include <string_view>
#include <cstring>
#include "../DSA/vector.h"
#include "Entry.h"
#include "Data.h"

#define vector std::vector
#define s_v std::string_view
string ADDR = "C:/Users/qazse/Documents/Snow/";
string UNDEF = "undefined";
// s_v UNDEF = "undefined";

template <typename T>
class Table;

const char *cpy(int size, char **array)
{
    char *c = new char[50];
    int c_size = 0;

    for (int i = 0; i < size; i++)
        for (int j = 0; array[i][j] != '\0'; j++)
            c[c_size++] = array[i][j];
    c[c_size] = '\0';

    return c;
}

template <typename T>
class Table
{
protected:
    string addr;
    string name;
    fstream inFile;
    vector<Entry *> *entry_p;

public:
    Table() : name(UNDEF)
    {
        // addr = strcpy(strcpy(ADDR, UNDEF), ".md");
        addr = ADDR + UNDEF + ".md";
        entry_p = new vector<Entry *>();
        read();
    }
    Table(char *c = UNDEF) : name(c)
    {
        // addr = strcpy(strcpy(c, ADDR), ".md");
        addr = ADDR + c + ".md";
        entry_p = new vector<Entry *>();
        read();
    }
    virtual ~Table()
    {
        write();
        for (int i = 0; i < entry_p->size(); i++)
            delete (*entry_p)[i];
        delete entry_p; // ?指针不需要吗？
        inFile.close();
    }

    void read();
    void write(const char *addr);
    void write() { write(addr.c_str()); }
    void save();

    int size() { return entry_p->size(); }

    void sortUp(int low, int high) {} // entry_p->sort();
    void sortUp() { sortUp(0, size()); }
    void sortDown(int low, int high);
    void sortDown() { sortDown(0, size()); }

    Block *search(int id);
    Block *search(char *c);
    Block *search(string name);
    Block *search(Block &b);
    int search(int index, string name, int low = 0);
    void remove(const Block &b);
    void remove(int id) { remove(search(id)); }
    void remove(string name) { remove(search(name)); }

    void updateWeight() { updateWeight(0, entry_p->size()); }
    void fun();
    void fun_Meat();

    Entry *operator[](int i) { return entry(i); }
    Entry *entry(int i) { return (*entry_p)[i]; }
    void print();
    void excel();

private:
    // 其实对于这种下标问题就是不知道到底要不要设置检测，其实我是……所以一种巧径是这样设置，无法直接调用，只能在其他函数体内部调用，减少了很多（假如）被别人用做库的可能性。
    void updateWeight(int low, int high);
    void updateWeight(int id) { entry(id)->updateWeight(); }
};
/*  */
template <typename T>
void Table<T>::fun()
{
    Block *p;
    int oldId, temp;
    for (int i = 0; i < entry_p->size(); i++)
        for (int j = 1; j < entry(i)->element.size(); j++)
        {
            p = entry(i)->element[j];
            if (p->Name() != DEFNAME)
            {
                oldId = p->Id();
                temp = oldId / 1000 * 8;
                oldId %= 1000;
                temp += oldId / 100 * 4;
                oldId %= 100;
                temp += oldId / 10 * 2;
                oldId %= 10;
                temp += oldId * 1;
                p->setId(temp);
            }
        }
}
/*  */
template <typename T>
void Table<T>::read()
{
    int id;
    string name;
    float weight;
    vector<Block> elem;

    inFile.open(addr, ios::in);
    for (; !inFile.eof(); id = -1, elem = vector<Block>())
    {
        do
        {
            inFile >> id >> name >> weight;
            if (name == "-1")
                name = DEFNAME;
            elem.emplace_back(Block(id, name, weight));
        } while (!inFile.eof() && inFile.get() != '\n');
        if (elem[0].Id() >= 0)
            entry_p->emplace_back(new Entry(&elem));
    }
}
/*  */
template <typename T>
void Table<T>::write(const char *addr)
{
    inFile.open(addr, ios::out | ios::trunc);
    freopen(addr, "w", stdout);
    print();
    fclose(stdout);
}
/*  */
template <typename T>
void Table<T>::save()
{
    string addr = ADDR + "Save/" + name + "/" + name + "_";
    addr += Log::setTime('.', '.') + ".md";
    // char *array[8] = {ADDR, "Save/", name, "/", name, "_", Log::setTime('.', '.').c_str(), ".md"};
    // const char *addr = cpy(8, array);
    char *c = new char[addr.length() + 1];
    strcpy(c, addr.c_str());
    write(c);
}
/*  */
template <typename T>
void Table<T>::excel()
{
    for (int i = 0; i < size(); i++)
        entry(i)->excel();
}
/*  */
template <typename T>
void Table<T>::updateWeight(int low, int high)
{
    for (int i = low; i < high; i++)
        entry(i)->updateWeight();
}
/*  */
template <typename T>
void Table<T>::print()
{
    for (int i = 0; i < size(); i++, printf("\n"))
        entry(i)->print();
}
/*
    if (p != NULL)
        for (int i = 0; i < p->size(); i++)
            p->Element(i)->disCount();
 */
template <typename T>
void Table<T>::remove(const Block &p)
{
    if (p != NULL)
        for (int i = 0; i < p->size(); i++)
            p->Element(i)->disCount();
}
/*  */
template <typename T>
Block *Table<T>::search(int id)
{
    if (id >= 0 && id < size())
        return entry(id);
    return NULL;
}
/*  */
template <typename T>
Block *Table<T>::search(string name)
{
    for (int i = 0; i < size(); i++)
        if (entry(i)->Name() == name)
            return entry(i);
    return NULL;
}
/*  */
template <typename T>
int Table<T>::search(int index, string name, int low)
{
    for (int i = low; i < size(); i++)
        if (0 <= index < entry(i)->size())
            if (entry(i)->elem(index)->Name() == name)
                return i;
    return -1;
}
/*  */
template <typename T>
Block *Table<T>::search(char *c)
{
    string name = c;
    return search(name);
}
/*  */
template <typename T>
Block *Table<T>::search(Block &b)
{
    Block *p = search(b.Id());
    if (p == NULL)
        p = search(b.Name());
    else
        return p;
    if (p == NULL)
        p = &b;
    return p;
}
/*  */
template <typename T>
void Table<T>::sortDown(int low, int high)
{
    int j;
    T temp;

    for (int i = 1; i < size(); i++)
    {
        for (j = i - 1, temp = entry(i); j >= 0 && temp > entry(j); j--)
            (*entry_p)[j + 1] = (*entry_p)[j];
        (*entry_p)[j + 1] = temp;
    }
}
/*  */
/* template <typename T>
void Table<T>::fun_Meat()
{
    int target = 0;
    int follower = 1;
    T *p;
    T *pf;
    int size = size();

    string cutter = "localfunction";
    string params[] = {"HEALING", "CALORIES", "SANITY", "PERISH"};

    for (p = entry[target]; target < size && follower < size;)
    {
        pf = entry[follower];
        for (; follower < size && pf->Name().find(cutter) == string::npos; pf = entry[++follower])
            for (int i = 0; i < 4; i++)
            {
                if (pf->Name().find(params[i]) != string::npos)
                {
                    for (int j = 0; j < i; j++)
                        p->element.insert(new Block(-1, "TUNING." + params[j], 0));

                    p->element.insert(pf);

                    for (int j = i + 1; j < 4 && follower + 1 < size; j++)
                    {
                        pf = entry[++follower];

                        if (pf->Name().find(params[j]) != string::npos)
                            p->element.insert(pf);
                        else
                            p->element.insert(new Block(-1, "TUNING." + params[j], 0));
                    }

                    break;
                }
            }

        if (follower < size)
        {
            target = pf->Id();
            p = entry[target];
            follower = target + 1;
        }
    }
}
 */
#endif
