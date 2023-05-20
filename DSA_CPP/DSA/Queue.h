#pragma once

#include "List.h"
#include "List.cpp"

template <typename T>
class Queue : public List<T>
{                                                       //队列模板类
public:                                                 //原有接口一概沿用
    void enqueue(T const &e) { this->insertAsLast(e); } //入队：尾部插入
    T dequeue() { return this->remove(this->first()); } //出队：首部删除
    T &front() { return this->first()->data; }          //队首
};
