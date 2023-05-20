#pragma once

#ifndef _PRINT_H_
#define _PRINT_H_

#include <iomanip>

void p() { cout << '\n'; }
void p(bool b, char c) { cout << boolalpha << b << endl; }
void p(string s) { cout << s << '\n'; }
void p(int e) { cout << e << '\n'; }
void p(float e, int i = 1, char c = '\n') { cout << fixed << setprecision(i) << e << c; }
void p(double e) { cout << e << '\n'; }
void p(char e) { cout << e << '\n'; }

/* 打印数组char，格式为abcdef...\n */
void p(char *A, int size)
{
    for (int i = 0; i < size; i++)
        cout << A[i];
    cout << "\n";
}

/* 打印数组T，格式为1, 2, 3, ...\n */
template <typename T>
void p(T *A, int size)
{
    for (int i = 0; i < size - 1; i++)
        cout << A[i] << ", ";
    cout << A[size - 1] << "\n";
}

template <typename T>
void p(T *A, int i, int j)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%d ", A[i][j]);
        p();
    }
}

#endif