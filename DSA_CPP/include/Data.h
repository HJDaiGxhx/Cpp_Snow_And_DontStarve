#pragma once
#include <string>
#include "Block.h"
#include "Table.h"

#ifndef _GROWTYPE_H_
#define _GROWTYPE_H_

float REQUIRE[][3] = {{89, 79, 65}, {89, 79, 65}, {89, 79, 65}, {89, 79, 65}};
float SAMPLE[][3] = {{10, 2.5, 0.5}, {10, 2.5, 0.5}, {10, 2.5, 0.5}, {1, 0, 0}};

class Family : public Block
{
protected:
    Block *element;

public:
    static char addr[];
    Family(const Block &b) : Block(b)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Family(Block *element) : Block(element[0])
    {
        this->element = new Block(element[1]);
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Family(vector<Block> *element) : Block((*element)[0])
    {
        this->element = new Block((*element)[1]);
    }
    Family(int i = -1, string n = DEFNAME, int w = DEFWEIGHT) : Block(i, n, w)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Family(string name, float weight = DEFWEIGHT) : Block(-1, name, weight)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }

    int Count() { return element->Id(); }
    void updateWeight();
    void print();
};
class Feature : public Block
{
protected:
    Block *element;

public:
    static char addr[];
    Feature(const Block &b) : Block(b)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Feature(vector<Block> *element) : Block((*element)[0]) { this->element = new Block((*element)[1]); }
    Feature(int i = -1, string n = DEFNAME, int w = DEFWEIGHT) : Block(i, n, w)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Feature(string name, float weight = DEFWEIGHT) : Block(-1, name, weight)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    void updateWeight();
    void print();
};

enum GROWTYPE
{
    count_GrowType,
    featureGrow_GrowType,
    length_Growtype
};
class GrowType : public Block
{
protected:
public:
    static char addr[];
    vector<Block *> element;
    GrowType(const Block &b) : Block(b)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    GrowType(vector<Block> *element) : Block((*element)[0])
    {
        for (int i = 1; i < (*element).size(); i++)
            this->element.emplace_back(new Block((*element)[i]));
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    GrowType(int i = -1, string n = DEFNAME, int w = DEFWEIGHT) : Block(i, n, w)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    GrowType(string name, float weight = DEFWEIGHT) : Block(-1, name, weight)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }

    int Count() { return element[0]->Id(); }

    void updateWeight();
    void list(char);
    void print();
};
class Skill : public Block
{
public:
    static char addr[];
    Skill(const Block &b) : Block(b)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Skill(int i = -1, string n = DEFNAME, int w = DEFWEIGHT) : Block(i, n, w)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Skill(string name, float weight = DEFWEIGHT) : Block(-1, name, weight)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    void updateWeight() { weight = 0; }
};

class BaseData : public Block
{
protected:
    float *require;
    float *sample;

public:
    BaseData(int i = -1, string n = "", int w = DEFWEIGHT, int sampleId = 0) : Block(i, n, w)
    {
        require = REQUIRE[sampleId];
        sample = SAMPLE[sampleId];
        if (weight == -1)
            updateWeight();
    }
    void updateWeight()
    {
        weight = 0;
        for (int i = 0; i < 3; i++)
            if (id >= require[i])
            {
                weight = id * sample[i] * 0.01;
                break;
            }
    }
};

enum DATA
{
    guard = 0,
    attack,
    wisdom,
    caring,
    Data_length
};
class Data : public Block
{
    Block *element[4];

public:
    Data(int i = -1, string n = "", float w = DEFWEIGHT) : Block(i, n, w)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Data(string name) : Block(-1, name, DEFWEIGHT)
    {
        if (weight == DEFWEIGHT)
            updateWeight();
    }
    Data(const int A[]) : Block()
    {
        for (int i = 0; i < Data_length; i++)
            element[i] = new BaseData(A[i], DEFNAME, DEFWEIGHT, i);
        updateWeight();
    }

    void set(int i, int weight) { *element[i] = weight; }
    void print();
    string Name();
    friend ostream &operator<<(ostream &out, Data &d);

    void updateWeight();
};

#endif