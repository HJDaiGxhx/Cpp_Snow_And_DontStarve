#pragma once
#include <string>
#include <iostream>
#include <vector>
using std::printf;
using std::string;
using std::vector;

#ifndef DEFAULT
#define DEFID -1
#define DEFWEIGHT -1
#define DEFNAME "N"
#define s_v std::string_view
#endif

/* 基础Block类，模拟一个原子属性，用以组成更高级的属性。 */
enum Block_enum
{
    id_BLOCK = -3,
    name_BLOCK,
    weight_BLOCK,
    end_BLOCK,
};
class Block
{
protected:
    double id;
    string name;
    double weight;
    bool changed;

public:
    Block(double i = DEFID, s_v n = DEFNAME, double w = DEFWEIGHT) : id(i), name(string(n)), weight(w), changed(0) {}
    Block(string n, double w = DEFWEIGHT) : id(DEFID), name(n), weight(w), changed(0) {}

    virtual double Id() const { return id; }
    virtual string Name() { return name; }
    virtual double Weight() { return weight; }
    virtual double Weight(int i) { return DEFWEIGHT; }
    virtual bool Changed() { return changed; }

    virtual Block *elem(int i) { return NULL; }
    virtual Block *entry(int i) { return NULL; }
    virtual vector<Block *> *Element() { return NULL; }
    virtual int size() { return 0; }

    virtual void setId(double i) { id = i; }
    virtual void setName(string n) { name = n; }
    virtual void setWeight(double w) { weight = w; }
    void operator=(int weight) { setWeight(weight); }
    virtual void setChanged(bool b) { changed = b; }

    bool operator>(const Block &m) { return id > m.Id(); }
    bool operator<(const Block &m) { return id < m.Id(); }
    // operator int() { return id; }
    friend ostream &operator<<(ostream &out, Block &b)
    {
        out << '\t' << b.id << '\t' << b.name.c_str() << b.weight << '\t';
        return out;
    }
    virtual void list(char c = ' ') {}
    virtual void print() { printf("\t%.2f\t%s\t%.2f", id, name.c_str(), weight); }
    virtual void excel() { printf("\t%s", name.c_str()); }
    virtual void luatable(string s = "", bool b = true, s_v idname = "atleast", s_v weightname = "atmost") { printf("%s{ %s = %.2f, name = \"%s\", %s = %.2f },\n", s.c_str(), idname.data(), id, name.c_str(), weightname.data(), weight); }

    virtual void updateWeight() {}
    virtual void disCount() {}
    virtual void Insert() {}
    virtual void Insert(Block *b) {}
    virtual void Insert(const Block &b) {}
    virtual void Clear() {}
};