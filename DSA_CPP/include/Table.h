#pragma once
#ifndef _Table_H
#define _Table_H

#include <fstream>
using std::fstream;
using std::ios;
#include <string_view>
#include <cstring>
#include "Entry.h"

string ADDR = "C:/Users/qazse/Documents/Snow/";
string UNDEF = "Undefined";
string suffix = ".md";

template <typename T>
class Table : public Block
{
protected:
    string foldername;
    string addrIn, addrOut, filename;
    fstream inFile;
    vector<Block *> *entry_p;

public:
    Table(string c = UNDEF)
    {
        string addr = ADDR + c + suffix;
        init(addr, addr, c, c);
    }
    Table(string inname, string outname, s_v foldername = UNDEF)
    {
        string inaddr = ADDR + inname + suffix;
        string outaddr = ADDR + outname + suffix;
        init(inaddr, outaddr, outname, foldername);
    }
    Table(s_v inaddr, s_v outaddr, s_v filename = UNDEF, s_v foldername = UNDEF)
    {
        init(inaddr, outaddr, filename, foldername);
    }
    virtual ~Table()
    {
        write();

        for (int i = 0; i < size(); i++)
            delete (*entry_p)[i];
        vector<Block *>().swap(*entry_p);
        // delete entry_p;
        inFile.close();
    }

    void init(s_v inaddr, s_v outaddr, s_v filename, s_v foldername)
    {
        addrIn = string(inaddr);
        addrOut = string(outaddr);
        this->filename = string(filename);
        this->foldername = string(foldername);

        entry_p = new vector<Block *>();
        read();
    }
    void read();
    void write(const char *addr);
    void write() { write(addrOut.c_str()); }
    void save();
    void save(void (Table<T>::*fun_p)());

    int size() { return entry_p->size(); }
    bool empty() { return entry_p->empty(); }

    void sortUp(int low, int high) {} // entry_p->sort();
    void sortUp() { sortUp(0, size()); }
    void sortDown(int low, int high);
    void sortDown() { sortDown(0, size()); }

    Block *search(int id);
    Block *search(char *c);
    Block *search(string name);
    Block *search(s_v name)
    {
        string s = string(name);
        return search(s);
    }
    Block *search(Block &b);
    int search(int index, string name, int low = 0);

    void remove(const Block &b);
    void remove(Block *b) {}
    void remove(int id) { remove(search(id)); }
    void remove(string name) { remove(search(name)); }

    void updateWeight() { updateWeight(0, size()); }
    void fun();

    Block *operator[](int i) { return entry(i); }
    Block *entry(int i) { return (*entry_p)[i]; }
    void print();
    void excel();
    void luatable();

private:
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
        for (int j = 1; j < entry(i)->size(); j++)
        {
            p = entry(i)->elem(j);
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
    double id;
    string name;
    double weight;
    vector<Block> elem;

    inFile.open(addrIn, ios::in);
    for (; !inFile.eof(); id = -1, elem = vector<Block>())
    {
        do
        {
            inFile >> id;
            inFile.get();

            getline(inFile, name, '\t');
            inFile >> weight;

            elem.emplace_back(Block(id, name, weight));
        } while (!inFile.eof() && inFile.get() != '\n');
        if (elem[0].Id() >= 0)
            entry_p->emplace_back(new T(&elem));
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
    string addr = ADDR + "Save/" + filename + "/" + filename + "_";
    addr += Log::setTime('.', '.') + ".md";
    // char *array[8] = {ADDR, "Save/", name, "/", name, "_", Log::setTime('.', '.').c_str(), ".md"};
    // const char *addr = cpy(8, array);
    char *c = new char[addr.length() + 1];
    strcpy(c, addr.c_str());

    write(c);
}
/*  */
template <typename T>
void Table<T>::save(void (Table<T>::*fun_p)())
{
    string s = ADDR + "Save/" + foldername + "/" + "excel_";
    s += Log::setTime('.', '.') + ".md";
    char *addr = new char[s.length() + 1];
    strcpy(addr, s.c_str());

    inFile.open(addr, ios::out | ios::trunc);
    freopen(addr, "w", stdout);

    (this->*fun_p)();

    fclose(stdout);
}
/*  */
template <typename T>
void Table<T>::excel()
{
    for (int i = 0; i < size(); i++, printf("\n"))
        entry(i)->excel();
}
/*  */
template <typename T>
void Table<T>::luatable()
{
    printf("Table = {\n", name.c_str());
    for (int i = 0; i < size(); i++)
        entry(i)->luatable(1, false);
    Block::luatable();
    printf("}");
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
    // if (p != NULL)
    //     for (int i = 0; i < p->size(); i++)
    //         p->Element(i)->disCount();
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
    if (p != NULL)
        return p;
    p = search(b.Name());
    return p;
}
/*  */
template <typename T>
void Table<T>::sortDown(int low, int high)
{
    int j;
    Entry *temp;

    for (int i = 1; i < size(); i++)
    {
        for (j = i - 1, temp = entry(i); j >= 0 && temp > entry(j); j--)
            (*entry_p)[j + 1] = (*entry_p)[j];
        (*entry_p)[j + 1] = temp;
    }
}
/*  */
/*
void Table::fun_Meat()
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
