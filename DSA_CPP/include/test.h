#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <math.h>
#include "../DSA/vector.h"
// #include "DSA/BinTree.h"
// #include "DSA/GraphMatrix.h"

#include "Print.h"

using namespace std;

#ifndef Rank
#define Rank int
#endif

void setRand();
void endNPrintTime(std::chrono::steady_clock::time_point start, string s);

// 构造测试用数组
// [int array]

int *create(int *A, int size, int hi);
int *create(int *A, int size, int lo, int hi);
int *createSorted(int *A, int size, int count);
int *createSorted(int *A, int size, int lo, int diff, int countLo, int countHi);

// [char array]

char *create(char *A, int size, int hi);
char *createSymbols(char *A, int size);
char *createWithSymbols(char *A, int size);
char *createFormula(char *A, int size, int hi);

// [vector to tree]

// 打印数组。
// 虽然说c也有类似的printf函数，但是多少不够方便，因为每次都要手打\n。

void p(string s);
void print(int);
void print(double);
void print(char);
void print(string);
template <typename T>
void print(T *A, int size);
void print(char *A, int size);

void pause();

// 检测错误
int test_IfNaturalNum(int r);
Rank *test_RangeValid(Rank lo, Rank hi);
int test_RankValid(Rank r, Rank lo, Rank hi);
void test_find();
int printErrorNRetry(string s);
void printError(string s);