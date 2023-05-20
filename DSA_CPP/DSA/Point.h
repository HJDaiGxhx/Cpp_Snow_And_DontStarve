#pragma once
#include <iostream>
using namespace std;
#include <iomanip>
#include <cmath>

class Point
{
    static int num;
    float x, y;

public:
    Point();
    Point(int, int);
    Point(Point &);

    void setX(int);
    void setY(int);
    void setXY(int, int);
    int getX();
    int getY();

    void print();

    friend class Tri;
    friend double getLine(const Point *, const Point *);
};

int getLine(Point, Point);

class Tri
{
    Point *a, *b, *c;
    float ab, ac, bc;

public:
    Tri();
    Tri(int, int, int, int, int, int);

    void forTri(Point *, Point *, Point *);
    bool isTri();
    void print();
};
