#include "Graph.h"
#include "Queue.h"

/*

注意——T(n)=O(n+e) */
template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(Rank s)
{
    reset();
    int clock = 0; // #Q 这个clock的作用是什么啊，目的应该是赋值dTime，目前还看不懂。
    int v = s;
    do
    {
        if (status(v) == UNDISCOVERED)
            BFS(v, clock);
    } while (s != (n = (++v % n)));
}

/* 层次遍历，越早被访问到的节点，其邻居越优先被选用，感觉这个也不太好理解，还是二叉树的横向、或者动画模式，把一个点的子都摘了然后排到它身后更形象吧。
 */
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(Rank v, int &clock)
{
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);

    while (!Q.empty())
    {
        Rank v = Q.dequeue(); // ? why new v.
        dTime(v) = ++clock;
        // visit(V[v].data); // #N 原来它的遍历是通过TREE进行标识的
        for (Rank u = firstNbr(v); u > -1; u = nextNbr(v, u))
            if (status(u) == UNDISCOVERED)
            {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u) = TREE;
                parent(u) = v;
            }
            else
                type(v, u) = CROSS;
        status(v) = VISITED;
    }
}

/*

注意——T(n)=O(n+e) */
template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(Rank s)
{
    reset();
    int clock = 0;
    Rank v = s;
    do
    {
        if (status(v) == UNDISCOVERED)
            DFS(v, clock);
    } while (s != (v = (++v % n)));
}

/* 先序遍历，然而访问完毕次序又是后序排序。先push右，再push左，实际上是从最后一个节点开始push，再pop最开始的子节点。
这里没有像之前用数据结构，比如堆栈，可能是因为它主要功能是判断图是否连通，是否有环，而不是单纯的遍历……？好像不是的，入栈也是一样能判断，只是这里用了递归前序遍历的形式吧。

#N 我怎么感觉图的遍历反而比二叉树在逻辑上好理解很多呢？

是真的，可能因为二叉树的子太少了，没有凸显它每到一个点，都按照某种优先级选取自己的某个子，本质上都是层次遍历，**把所有的结点都放进数据结构中，无一放过**。只不过一个真层次遍历是从左往右、从上往下地把结点塞进队列里，然后优先考查更早被发现的顶点；DFS则是每放进一批，就优先选择最后发现的结点。
反而被LDR、LRD这些口号洗脑了。所以说，把子的个数添加到3、4个，马上立竿见影地看出逻辑的效果。

而且可能是当时迭代遍历给的各种1234个解法导致阴影太深了，各种push右左、父右，还是只父，都让人有点混乱，其实明明二叉树递归遍历是超级简单的啊，但我却突然很自大地觉得图的遍历反而如此简单，比二叉树简单啊，留下了错误的印象。 */
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(Rank s, int &clock)
{
    dTime(s) = ++clock;
    status(s) = DISCOVERED; // #Q why first DIS if last VISITED?
    for (Rank u = firstNbr(s); u > -1; u = nextNbr(s, u))
    {
        switch (status(u))
        {
        case UNDISCOVERED:
            type(s, u) = TREE;
            parent(u) = s;
            DFS(u, clock);
            break;
        case DISCOVERED:
            type(s, u) = BACKWARD;
            break;
        default:
            type(s, u) = (dTime(s) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(s) = VISITED;
    fTime(s) = ++clock;
}

/* vertex(Rank s) */
template <typename Tv, typename Te>
Stack<Tv> *Graph<Tv, Te>::tSort(Rank s)
{
    reset();
    int clock = 0;
    Rank v = s;
    Stack<Tv> *S = new Stack<Tv>;

    do
    {
        if (status(v) == UNDISCOVERED)
            if (!TSort(v, clock, S))
            { // 这里这么写，是因为这是失败选项，为了表示失败，下面必须return空白S，所以要pop的步骤
                while (!S->empty())
                    S->pop();
                break;
            }
    } while (s != (v = (++v % n)));

    return S;
}

/* 隐式先序遍历，显式……拓扑排序。

实现——在只有出度的极大元素会是第一个入队的同时，只有入度的极小元素会是最后一个，虽然可以用检查的方式检测它的所有边是否都没有出，也就是UNDETERMINED，但也可以换种思考方式，认为最先完成VISITED的项就是极小元素。抖M，唉，一直高压做这种题目就是发现自己一无是处，答案是绝对的正确，而你的力量太过于渺小，你不可能比它强。

注意——必须返回bool是因为一旦非DAG，后面是不能算的，而且外函数还是个while，所以无奈地必须每次都检测其true。
#Q 一个问题是，在实验P185的拓扑排序时得到的结果为H, B, P, S, V, L，实际上和预设答案在等同权值上都相反了，这是为什么？ */
template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(Rank v, int &clock, Stack<Tv> *S)
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED; // #Q why first DIS if last VISITED?
    for (Rank u = firstNbr(v); u > -1; u = nextNbr(v, u))
    {
        switch (status(u))
        {
        case UNDISCOVERED:
            parent(u) = v;
            type(v, u) = TREE;
            if (!TSort(u, clock, S))
                return false;
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD;
            printf("not DAG!\n");
            return false;
        default:
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break; // 主要是我觉得这里的type改了也没意义啊？
        }
        print();
    }
    status(v) = VISITED;
    S->push(vertex(v));
    return true;
}

#define hca(u) (fTime(u))

/* #H 我也不知道是真的难，还是昨天我在大脑极度疲惫的状态下做这个，产生了心理阴影，就很不服，很不快。 叫你在这里写，为什么在这里写啊，真的是debug要到什么时候，我TM的，我真的无语，我真的累了。*/
template <typename Tv, typename Te>
void Graph<Tv, Te>::bcc(Rank s)
{
    reset();
    int clock = 0;
    Rank v = s;
    Stack<Rank> S;

    do
    {
        if (status(v) == UNDISCOVERED)
        {
            BCC(v, clock, S);
            // printf("%c is a joint point.\n", vertex(S.pop()));
            S.pop();
        }
    } while (s != (v = (++v % n)));
    // 最后所有关节点入栈？
}

/* #Q
为什么P185的图，V、P、S、V是显示出的关节点？？怎么看以人类的视角来理解，只有S是关节点，总之先搁置吧。

好起来了，原来我只是用了迭代版，所以看起来错了很多，其实还好吧，有了点信心。又坏了。

还是不行啊，我漏了一点，对于DFS的描述是访问次序是前序，但访问完毕是后序，也就相当于递归DFS的话会按前序访问延伸，然后又像电影倒放一样依次回来（怪不得叫忒休斯的线绳！！）而堆栈能保证前序次序已经是极限，不能收放自如，只能二叉树……？ */
template <typename Tv, typename Te>
void Graph<Tv, Te>::BCC(Rank v, int &clock, Stack<Rank> &S)
{
    hca(v) = dTime(v) = ++clock;
    status(v) = DISCOVERED; // #Q why first DIS if last VISITED?
    S.push(v);
    for (Rank u = firstNbr(v); u > -1; u = nextNbr(v, u))
    {
        switch (status(u))
        {
        case UNDISCOVERED:
            parent(u) = v;
            type(v, u) = TREE;
            BCC(u, clock, S);

            if (hca(u) < dTime(v))
                hca(v) = min(hca(v), hca(u));
            else // 是关节点，那其他的子也不用比了，重新入栈v
            {
                while (v != S.pop())
                    ;
                S.push(v);
                printf("%c is a joint point.\n", vertex(v));
            }
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD;
            if (u != parent(v))
                hca(v) = min(hca(v), dTime(u));
            break;
        default:
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
        print();
    }
    status(v) = VISITED;
}

/* #H

注意——T(n)=O(n^2) */
template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(Rank s, PU prioUpdater)
{
    reset();
    Rank v = s; // #Q Rank到底和int有什么区别？虽然它好像是所谓的秩，但也没必要特地抽象封装吧？
    do
    {
        if (status(v) == UNDISCOVERED)
            PFS(v, prioUpdater);
    } while (s != (v = (++v % n)));
}

/*  */
template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(Rank s, PU prioUpdater)
{
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;

    while (1)
    {
        for (Rank w = firstNbr(s); w > -1; w = nextNbr(s))
            prioUpdater(this, s, w); // 我怎么感觉这更像之前的迭代Stack的BCC

        // !!这是全局检查，所以都怀疑是为了Prim之类的算法量身打造的，毕竟T(n)太大了
        for (int shortest = INT_MAX, w = 0; w < n; w++)
        {
            if (status(w) == UNDISCOVERED) // 这里其实就只有UNDIS和VIS两种区别
                if (shortest > priority(w))
                {
                    shortest = priority(w);
                    s = w;
                }
        }
        if (status(s) == VISITED) // 如果s所有的边都VISITED了，s还是s
            break;
        status(s) = VISITED; // !!每次遍历后其实是有个visit函数的，就是为所有的子prioUpdater，它其实是做了事的，只不过折叠到上面去了
        type(parent(s), s) = TREE;
    }
}

/*  */
template <typename Tv, typename Te>
struct PrimPU
{
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED)
            if (g->priority(v) > g->weight(uk, v))
            {
                g->priority(v) = g->weight(uk, v);
                g->parent(v) = uk;
            }
    }
};

/* #M 其他边虽然逻辑抽象上来看是类似P196那样还没有够到、没有被初始化，然而实际上它们的实现是：大小为INT_MAX，因此永远不会被选到，而被初始化的更新了优先级。
所以这个prim算法真的跟PFS太贴合逻辑实现得太好了啊，显得像关系户……？ */
template <typename Tv, typename Te>
void Graph<Tv, Te>::prim(Rank s)
{
    pfs(s, PrimPU<Tv, Te>());
}

/*  */
template <typename Tv, typename Te>
struct dijkstraPU
{
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED)
            if (g->priority(v) > g->weight(uk, v) + g->priority(uk)) // !!INT_MAX??
            {
                g->priority(v) = g->weight(uk, v) + g->priority(uk);
                g->parent(v) = uk;
            }
    }
};

/* #M */
template <typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(Rank s)
{
    pfs(s, dijkstraPU<Tv, Te>());
}
