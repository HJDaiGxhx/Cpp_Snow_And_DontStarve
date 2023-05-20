#pragma once

#include "Stack.h"
#include "test.h"
// #include "GraphMatrix.h"

using Rank = int;
using VStatus = enum { UNDISCOVERED,
                       DISCOVERED,
                       VISITED }; //顶点状态

// C:\Users\qazse\Pictures\图.png
using EType = enum { UNDETERMINED,
                     TREE,       // 可以被识别为二叉树树干的边，或者是最小生成树的边，而最小生成树根据遍历选择的优先级的规则进行生成。
                     CROSS,      // 横跨边，有点像兄弟，又可以认为是一个“跨”，负责连接两子图的边
                     FORWARD,    // 祖先接上了孙子的情况，这明显不是树的结构，因为祖先只能接父，由父接孙
                     BACKWARD }; // 孙子接上了祖先的情况

template <typename Tv, typename Te> //顶点类型、边类型
class Graph
{ //图Graph模板类
private:
    void reset()
    { //所有顶点、边的辅助信息复位
        for (Rank i = 0; i < n; i++)
        { //所有顶点的
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1; //状态，时间标签
            parent(i) = -1;
            priority(i) = INT_MAX;       //（在遍历树中的）父节点，优先级数
            for (Rank j = 0; j < n; j++) //所有边的
                if (exists(i, j))
                    type(i, j) = UNDETERMINED; //类型
        }
    }
    void BFS(Rank, int &);                //（连通域）广度优先搜索算法
    void DFS(Rank, int &);                //（连通域）深度优先搜索算法
    void BCC(Rank, int &, Stack<Rank> &); //（连通域）基于DFS的双连通分量分解算法
    bool TSort(Rank, int &, Stack<Tv> *); //（连通域）基于DFS的拓扑排序算法
    template <typename PU>                //（连通域）优先级搜索框架
    void PFS(Rank, PU);

public:
    Graph() { n = e = 0; }

    // 顶点
    int n; //顶点总数
    VStatus vs;
    EType et;
    virtual Rank insert(Tv const &) = 0;  //插入顶点，返回编号
    virtual Tv remove(Rank) = 0;          //删除顶点及其关联边，返回该顶点信息
    virtual Tv &vertex(Rank) = 0;         //顶点的数据（该顶点的确存在）
    virtual int inDegree(Rank) = 0;       //顶点的入度（该顶点的确存在）
    virtual int outDegree(Rank) = 0;      //顶点的出度（该顶点的确存在）
    virtual Rank firstNbr(Rank) = 0;      //顶点的首个邻接顶点
    virtual Rank nextNbr(Rank, Rank) = 0; //顶点（相对当前邻居的）下一邻居
    /* #Q
    很奇怪的是，其他纯虚函数没问题，但是碰到有enum作为返回的就会挂，显示is defined but never used，使得我最后给它搞了一个实现，多添加了vs和et的变量。
    #N 所以我觉得debug真的能学到什么东西吗？我今天因为debug搞了半天，一头雾水，最后是都解决了，但我的内心却没有多少愉悦，因为觉得这根本是“智力游戏”，而不是经验，玩再多次游戏都不能让我进步。
    所以我从中想到的大概唯一一个东西，就是基础真的应该在之前学的，太后悔了，所以我觉得明天开始应该先中断数据结构，先把C++和那本CSAPP书看完，否则真的耗费掉很多无效时间。

    现在C++那本书看完了，居然连enum之类的关键字都没说全，然后也不能解释我为什么会遇到这些bug。
    所以我感觉大概是编译的问题，就只能看一下CSAPP吧，说实话这本书是很长，每天看30页要30天左右才能看完，恐怖。 */
    virtual VStatus &status(Rank)
    {
        vs = UNDISCOVERED;
        return vs;
    }                                //顶点的状态
    virtual int &dTime(Rank) = 0;    //顶点的时间标签dTime
    virtual int &fTime(Rank) = 0;    //顶点的时间标签fTime
    virtual Rank &parent(Rank) = 0;  //顶点在遍历树中的父亲
    virtual int &priority(Rank) = 0; //顶点在遍历树中的优先级数

    // 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e;                                                //边总数
    virtual bool exists(Rank, Rank) = 0;                  //边(v, u)是否存在
    virtual void insert(Te const &, int, Rank, Rank) = 0; //在两个顶点之间插入指定权重的边
    virtual Te remove(Rank, Rank) = 0;                    //删除一对顶点之间的边，返回该边信息
    virtual EType &type(Rank, Rank)
    {
        et = UNDETERMINED;
        return et;
    }                                    //边的类型
    virtual Te &edge(Rank, Rank) = 0;    //边的数据（该边的确存在）
    virtual int &weight(Rank, Rank) = 0; //边(v, u)的权重
                                         // 算法
    void bfs(int);                       //广度优先搜索算法
    void dfs(Rank);                      //深度优先搜索算法
    void bcc(Rank);                      //基于DFS的双连通分量分解算法
    Stack<Tv> *tSort(Rank);              //基于DFS的拓扑排序算法
    void prim(Rank);                     //最小支撑树Prim算法
    void dijkstra(Rank);                 //最短路径Dijkstra算法
    template <typename PU>
    void pfs(Rank, PU); //优先级搜索框架

    virtual void print() = 0;
};
