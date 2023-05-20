#pragma once

// #include <string>
#include "test.h"
#include "Graph.h"
#include "Graph.cpp"
#include "Vector.h"
#include <iomanip>

template <typename Tv>
struct Vertex
{
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    // dTime: 访问这个点的顺序，甚至是序号
    int dTime, fTime;
    int parent;
    int priority;

    Vertex() : data(Tv(0)), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
    Vertex(Tv const &d) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te>
struct Edge
{
    Te data;
    int weight;
    EType type;

    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
private:
    int DEFAULT_WEIGHT = 1;
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te> *>> E;

public:
    GraphMatrix() { this->n = this->e = 0; } // #Q 为什么我的要加this，这个编译器……早知道我应该先学习前面的。
    GraphMatrix(Vector<Tv> A, Vector<Vector<Te>> B, int size)
    {
        this->n = this->e = 0;

        for (int i = 0; i < size; i++)
            insert(A[i]);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (B[i][j])
                    insert(B[i][j], DEFAULT_WEIGHT, i, j);
    }

    ~GraphMatrix()
    {                                          //析构
        for (Rank j = 0; j < this->n; j++)     //所有动态创建的
            for (Rank k = 0; k < this->n; k++) //边记录
                delete E[j][k];                //逐条清除
    }

    virtual Tv &vertex(Rank i) { return V[i].data; }              //数据
    virtual int inDegree(Rank i) { return V[i].inDegree; }        //入度
    virtual int outDegree(Rank i) { return V[i].outDegree; }      //出度
    virtual Rank firstNbr(Rank i) { return nextNbr(i, this->n); } //首个邻接顶点
    virtual Rank nextNbr(Rank i, Rank j)                          //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }                                                       //逆向线性试探
    virtual VStatus &status(Rank i) { return V[i].status; } //状态n
    virtual int &dTime(Rank i) { return V[i].dTime; }       //时间标签dTime
    virtual int &fTime(Rank i) { return V[i].fTime; }       //时间标签fTime
    virtual Rank &parent(Rank i) { return V[i].parent; }    //在遍历树中的父亲
    virtual int &priority(Rank i) { return V[i].priority; } //在遍历树中的优先级数
                                                            // 顶点的动态操作
    virtual Rank insert(Tv const &vertex)                   //插入顶点，返回编号
    {
        for (Rank j = 0; j < this->n; j++)
            E[j].insert(NULL);
        this->n++;                                                        //各顶点预留一条潜在的关联边
        E.insert(Vector<Edge<Te> *>(this->n, this->n, (Edge<Te> *)NULL)); //创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex));                              //顶点向量增加一个顶点
    }
    virtual Tv remove(Rank i)
    {                                      //删除第i个顶点及其关联边（0 <= i < n）
        for (Rank j = 0; j < this->n; j++) //所有出边
            if (exists(i, j))
            {
                delete E[i][j];
                V[j].inDegree--;
                this->e--;
            } //逐条删除
        E.remove(i);
        this->n--; //删除第i行
        Tv vBak = vertex(i);
        V.remove(i);                       //删除顶点i
        for (Rank j = 0; j < this->n; j++) //所有入边
            if (Edge<Te> *x = E[j].remove(i))
            {
                delete x;
                V[j].outDegree--;
                this->e--;
            }        //逐条删除
        return vBak; //返回被删除顶点的信息
    }
    // 边的确认操作
    virtual bool exists(Rank i, Rank j) //边(i, j)是否存在
    {
        return (i < this->n) && (j < this->n) && E[i][j] != NULL;
        // return (i < this->n) && (j < this->n) && E[i][j] != NULL && type(i, j) != UNDETERMINED;
    }
    // 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
    virtual EType &type(Rank i, Rank j) { return E[i][j]->type; }   //边(i, j)的类型
    virtual Te &edge(Rank i, Rank j) { return E[i][j]->data; }      //边(i, j)的数据
    virtual int &weight(Rank i, Rank j) { return E[i][j]->weight; } //边(i, j)的权重
                                                                    // 边的动态操作
    virtual void insert(Te const &edge, int w, Rank i, Rank j)      //插入权重为w的边(i, j)
    {
        if (exists(i, j))
            return;                      //确保该边尚不存在
        E[i][j] = new Edge<Te>(edge, w); //创建新边
        this->e++;
        V[i].outDegree++;
        V[j].inDegree++; //更新边计数与关联顶点的度数
    }
    virtual Te remove(Rank i, Rank j)
    { //删除顶点i和j之间的联边（exists(i, j)）
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL; //备份后删除边记录
        this->e--;
        V[i].outDegree--;
        V[j].inDegree--; //更新边计数与关联顶点的度数
        return eBak;     //返回被删除边的信息
    }

    /*     Vector<Vector<Edge<Te> *>> Edge(Tv e1, Tv e2)
        {
            Rank r1 = E.search(e1, 0, E.size());
            if (r1 > -1)
            {
                Rank r2 = E[r1].search(e2, 0, E.size());
                if (r2 > -1)
                    return E[r1][r2];
            }

            Test::p("r1 = -1 and r2 = -1.");
            return E[0][0];
        }
     */

    void print2()
    {
        cout << "  ";
        for (int i = 0; i < this->n; i++)
            cout << vertex(i) << ' ';
        printf("\n");

        for (int i = 0; i < this->n; i++)
        {
            cout << vertex(i) << ' ';
            for (int j = 0; j < this->n; j++)
                if (E[i][j])
                    cout << edge(i, j) << ' ';
                else
                    cout << 0 << ' ';
            printf("\n");
        }
        printf("\n");
    }

    virtual void print()
    {
        int inD = 0;
        for (int i = 0; i < this->n; i++)
            inD += this->inDegree(i); // 总入度
        int outD = 0;
        for (int i = 0; i < this->n; i++)
            outD += this->outDegree(i); // 总出度
        // printf("%s[%d]*(%d, %d):\n", typeid(this).name(), this, this->n, this->e); //基本信息
        // 标题行
        printf("%d", this->n);
        printf(" ");
        printf("%d", inD);
        printf("   |"); // 修改
        for (int i = 0; i < this->n; i++)
        {
            printf("%c", this->vertex(i));
            printf("[");
            printf("%d", this->status(i));
            printf("]  "); // 修改
        }
        printf("\n");
        // 标题行（续）
        printf("%d", outD);
        printf(" ");
        printf("%d", this->e);
        printf("   |"); // 修改
        for (int i = 0; i < this->n; i++)
        {
            printf("%d", this->inDegree(i));
            printf("     "); // 修改
        }
        printf("| dTime fTime Parent Weight\n");
        // 水平分隔线
        printf("------+"); // 修改
        for (int i = 0; i < this->n; i++)
            printf("------");
        printf("+----------------------------\n");
        // 逐行输出各顶点
        for (int i = 0; i < this->n; i++)
        {
            printf("%c", this->vertex(i));
            printf("[");
            printf("%d", this->status(i));
            printf("] ");
            printf("%d", this->outDegree(i));
            printf("|");
            for (int j = 0; j < this->n; j++)
                if (this->exists(i, j))
                {
                    printf("%d", this->edge(i, j));
                    printf("%d", this->type(i, j));
                    printf("   ."); // 修改
                }
                else
                    printf("     .");
            printf("| ");
            // printf("%d   ", this->dTime(i)); // 修改
            // cout.setf(ios::showpos);
            cout << showpos << this->dTime(i) << "    ";    // 修改
            cout << showpos << this->dTime(i) << noshowpos; // 修改
            printf("    ");                                 // 修改
            if (0 > this->parent(i))
                printf("^"); // 修改
            else
                printf("%c", this->vertex(this->parent(i)));
            printf("      ");
            if (INT_MAX > this->priority(i))
                printf("%d", this->priority(i));
            else
                printf("INF");
            printf("\n");
        }
        printf("\n");
    }
};