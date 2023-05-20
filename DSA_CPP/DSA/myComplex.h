#pragma once
#include <iostream>
using namespace std;

class myComplex
{
    int rp, vp;

public:
    myComplex();
    myComplex(int rp, int vp) : rp(rp), vp(vp) {}
    myComplex(myComplex &x) : rp(x.rp), vp(x.vp) {}
    myComplex operator*(myComplex);
    void print();
};

myComplex::myComplex()
{
    char c;
    scanf("%lf%c%lf", rp, c, vp);
    if (c == '-')
        vp *= -1;
}

myComplex myComplex::operator*(myComplex y)
{
    return myComplex((rp * y.rp - vp * y.vp), (vp * y.rp + rp * y.vp));
}

void myComplex::print()
{
    printf("%d%di\n", rp, vp);
}