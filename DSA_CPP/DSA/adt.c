#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// typedef & #define----------------------------------------------------------------

typedef int DataType;
typedef int Rank;
#define vSize 100
#define test_num -1

// function declarations------------------------------------------------------------
void printError(char *s);
int printErrorNRetry(char *s);
int test_position_invalid(Rank r, int i);

void printArray(int array[], int n);
void createRandArray(int array[], int array_length, int low_range, int high_range);

#pragma region // Vector

typedef struct v
{
    DataType elem[vSize];
    int length;
} Vector;

void createByUserTyping(Vector *v);
void createByCopyArray(Vector *v, DataType a[], int n);
void createByRandom(Vector *v, int high_range);
void print(Vector *v);
void insert(Vector *v, DataType e);
void insertAt(Vector *v, Rank r, DataType e); // 在Vector v中下标r处插入一个值e
DataType delete (Vector *v, Rank r);          // 删除Vector v中下标r处的数据，将之后的数据全部前移，然后返回该数据
void convert(Vector *v);

void test_insert(Vector *v, Rank r);
void test_delete(Vector *v, Rank r);
void test_insert_delete(Vector *v, Rank r);
void testNPrint();
void countTime();
#pragma endregion
#pragma region // LinkList

typedef struct node
{
    char data;
    struct node *next;
} LinkNode;
typedef LinkNode *LinkList;

LinkList linkListCreateByArrayF();
LinkList linkListCreateByArrayR();
LinkList linkListCreateByUserTypingF();
LinkList linkListCreateByUserTypingR1();
LinkList linkListCreateByUserTypingR2();
void printLinkListF(LinkList head);
void printLinkListR(LinkList head);
LinkNode *searchRank(LinkList head, Rank r);
LinkNode *searchValue(LinkList head, char c);
void linkListInsertEnd(LinkList head, LinkNode *p);
void linkListInsertEndChar(LinkList head, char c);
void linkListInsertAt(LinkList head, Rank r, char e);
char linkListRemoveAt(LinkList head, Rank r);
void split(LinkList a, LinkList b);
#pragma endregion
#pragma region // LinkList functions
LinkList linkListCreateByArrayF()
{
    char array[] = {'a', 'b', 'c', 'd', 'e'};
    int n = 5;

    LinkList head = NULL;
    LinkNode *p;
    for (int i = n - 1; i >= 0; i--)
    {
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = array[i];
        p->next = head;
        head = p;
    }

    return p;
}

LinkList linkListCreateByArrayR()
{
    LinkList head, rear;
    LinkNode *p;
    head = (LinkList)malloc(sizeof(LinkList));
    rear = head;

    char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};
    int n = 13;
    // char array[] = {'a', 'b', 'c', 'd', 'e'};
    // int n = 5;
    int i = 0;

    while (i < n)
    {
        p = (LinkNode *)malloc(sizeof(LinkNode)); //(LinkList)malloc(sizeof(LinkList))
        p->data = array[i++];
        if (head == NULL)
            head->next = p;
        rear->next = p;
        rear = p;
    }
    if (rear != NULL)
        rear->next = NULL;

    return head;
}

LinkList linkListCreateByUserTypingF()
{
    LinkList head = NULL;
    LinkNode *p;
    char ch = getchar();
    while (ch != '\n')
    {
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = ch;
        p->next = head;
        head = p;
        ch = getchar();
    }

    return head;
}

LinkList linkListCreateByUserTypingR1()
{
    LinkList head, rear;
    LinkNode *p;
    head = rear = NULL;
    char ch = getchar();

    while (ch != '\n')
    {
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = ch;
        if (head == NULL)
            head = p;
        else
            rear->next = p;
        rear = p;
        ch = getchar();
    }
    if (rear != NULL)
        rear->next = NULL;

    return head;
}

LinkList linkListCreateByUserTypingR2()
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode));
    LinkNode *p, *rear;
    rear = head;
    char ch;

    while ((ch = getchar()) != '\n')
    {
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = ch;
        rear->next = p; // rear之前等于head，因此第一次就相当于为头结点连接开始结点，P52
        rear = p;
    }
    rear->next = NULL;

    return head;
}

void printLinkListF(LinkList head)
{
    LinkNode *p = head;
    char array[100];
    int i = 0;

    while (p != NULL)
    {
        array[i++] = p->data;
        p = p->next;
    }

    while (i >= 0)
        printf("%c ", array[i--]);
    printf("\n");
}

void printLinkListR(LinkList head)
{
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p = head->next; // 头结点的情况
    while (p != NULL)
    {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

LinkNode *searchRank(LinkList head, Rank r)
{
    // LinkNode *temp = head;
    LinkNode *p = head->next; // 有头结点，突然发现头结点就像数组、顺序表中下标0的哨兵啊
    int i = 1;

    while ((p != NULL) && i < r)
    {
        p = p->next;
        i++;
    }

    if (i == r)
        return p;
    else
    {
        printf("没有找到下标r， 返回了链表中最后一个结点！\n");
        return NULL; // temp = p->prev
    }
}

LinkNode *searchValue(LinkList head, char c)
{
    LinkNode *p = head->next->next;
    while (p && p->data != c)
        p = p->next;
    return p;
}

void linkListInsertEnd(LinkList head, LinkNode *p)
{
    LinkNode *rear = searchRank(head, 1000);
    rear->next = p;
    p->next = NULL;
}

void linkListInsertEndChar(LinkList head, char c)
{
    LinkNode *rear = searchRank(head, 1000);
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = c;
    rear->next = p;
}

void linkListInsertAt(LinkList head, Rank r, char e)
{
    LinkNode *prev = searchRank(head, r - 1); // NULL or correct
    if (prev == NULL)
        return;

    LinkNode *target = (LinkNode *)malloc(sizeof(LinkNode));
    target->data = e;
    target->next = prev->next;
    prev->next = target;
}

char linkListRemoveAt(LinkList head, Rank r)
{
    LinkNode *prev;
    prev = searchRank(head, r - 1);

    if (prev == NULL || prev->next == NULL) // head头结点怎么解决？
    {
        printError("position invalid");
        exit(0);
    }

    LinkNode *target = prev->next;
    prev->next = prev->next->next;

    char c = target->data;
    free(target);
    return c;
}

void split(LinkList a, LinkList b)
{
    int i = 2;
    LinkNode *p = searchRank(a, i);
    char c;
    LinkNode *tempB = b;

    while (p != NULL)
    {
        c = linkListRemoveAt(a, i);
        LinkNode *target = (LinkNode *)malloc(sizeof(LinkNode));
        target->data = c;
        target->next = NULL;
        tempB->next = target;
        tempB = target;

        i++;
        p = searchRank(a, i);
    }
}
#pragma endregion

#pragma region // CycleList functions

// error treatments-----------------------------------------------------------------

void printError(char *s)
{
    printf("Error: %s\n", s);
}
int printErrorNRetry(char *s) // private，大概率给其他的test_error函数使用
{
    int i = -1;

    while (i == -1) // 感觉0作为哨兵真的很方便C里面if(0)表示FALSE的机制的啊……
    {
        printError(s);
        printf("Please resend: ");
        scanf("%d", &i);
    }
    return i;
}
int test_position_invalid(Rank r, int i) // 数组下标越界
{
    int newR = r;
    while (newR < 0 || newR > i)
    {
        newR = printErrorNRetry("position invalid");
        // 感觉还可以再简单一点，比如编号，下标越界就是第p+i号（position和invalid的首字母），这样既方便记忆，又书写更简单一些。
    }

    return newR;
}

// Vector functions-----------------------------------------------------------------

void createRandArray(int array[], int array_length, int low_range, int high_range)
{
    printf("array length: %d, low range: %d, high range: %d\n", array_length, low_range, high_range);

    for (Rank i = 0; i < array_length; i++)
    {
        // if (rand() % 2)
        array[i] = rand() % high_range;
        // else
        // array[i] = -(rand() % low_range);
    }

    printArray(array, array_length);
}

void printArray(int array[], int n)
{
    printf("array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void createByUserTyping(Vector *v)
{
    printf("Please type a line of numbers to form the vector,\n");
    printf("(Like this: 1, 2, 3, 4, 5):\n");

    // int i;
    // do
    // {
    //     scanf("%d", i);
    //     v->elem[j] = i;
    // } while (i != NULL);
}

void createByCopyArray(Vector *v, DataType a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v->elem[i] = a[i];
    }
    v->length = n;
}

void createByRandom(Vector *v, int high_range)
{
    int length = v->length = rand() % 10 + 10;
    for (int i = 0; i < length; i++)
    {
        v->elem[i] = rand() % high_range;
    }
}

void print(Vector *v)
{
    printf("Vector: ");
    for (int i = 0; i < v->length; i++)
    {
        int j = v->elem[i];
        printf("%d ", j);
    }
    printf("\n");
}

void insert(Vector *v, DataType e)
{
    v->elem[v->length] = e;
    v->length++;
}

void insertAt(Vector *v, Rank r, DataType e) // 在Vector v中下标r处插入一个值e
{
    if (v->length >= vSize)
    {
        printf("Error: 存放过多数据，已经超过限制了");
        return;
    }

    Rank newR = test_position_invalid(r, vSize - 2);
    // if (newR == -1) // 如果不需要newR（但是如果newR = 0，0又是一个合法下标。所以如果让0的位置作为哨兵很方便，但是不符合使用正常逻辑啊？
    //     newR = r;

    // 这个函数要求至少下标r在连续的已存放段落之间，如果存放数据在0-10，r为47，则调整为存放到11位置。
    if (newR < v->length)
    {
        for (int i = v->length - 1; i >= newR; i--)
            v->elem[i + 1] = v->elem[i];
        v->elem[newR] = e;
    }
    else // if (newR < v->length)
        v->elem[v->length] = e;

    v->length++;
}

DataType delete (Vector *v, Rank r) // 删除Vector v中下标r处的数据，将之后的数据全部前移，然后返回该数据
{
    Rank newR = test_position_invalid(r, v->length - 1);

    // if (newR == -1) // 如果test得到的下标newR不是0，是其他数，if为TRUE，因此使用newR作为下标。否则用r替换newR。
    //     newR = r;

    DataType x = v->elem[newR];
    for (int i = newR + 1; i < v->length; i++) // Q：这里到底是<还是<=length，P47
    {
        v->elem[i - 1] = v->elem[i];
    }

    // v->elem[v->length - 1] = NULL;
    // 因为更新length，所以不用设置NULL，因为不会发生越界
    v->length--;
    return x;
}

void convert(Vector *v)
{
    int len = v->length;
    for (int i = 0; i < v->length / 2; i++)
    {
        DataType temp = v->elem[i];
        v->elem[i] = v->elem[--len];
        v->elem[len] = temp;
    }
}

void minNMax(Vector *v, int *min, int *minR, int *max, int *maxR)
{
    *min = v->elem[0];
    *max = v->elem[0];
    *minR = 0;
    *maxR = 0;

    for (Rank i = 1; i < v->length; i++)
    {
        int currentNum = v->elem[i];
        if (currentNum < *min)
        {
            *min = currentNum;
            *minR = i;
        }
        else if (currentNum > *max)
        {
            *max = currentNum;
            *maxR = i;
        }
    }
}

// Vector test---------------------------------------------------------------------

void test_insert(Vector *v, Rank r)
{
    printf("insert to index: %d\n", r);
    insertAt(v, r, test_num);
    print(v);
    printf("\n");
}

void test_delete(Vector *v, Rank r)
{
    printf("delete %d at index %d\n", test_num, r);
    delete (v, r);
    print(v);
    printf("\n");
}

void test_insert_delete(Vector *v, Rank r)
{
    test_insert(v, r);
    test_delete(v, r);
}

void testNPrint()
{
}

void countTime()
{
    // count time
    // 执行函数
    // end count time
    // printf t; // "总计花费x时间。"
}
#pragma endregion

#pragma region // Single LinkList

#pragma endregion

// Single Cycle LinkList

int main(void)
{
    /* 初始化随机数发生器 */
    time_t t;
    srand((unsigned)time(&t));

    LinkList a = (LinkList)malloc(sizeof(LinkList));
    a = linkListCreateByArrayR();
    printLinkListR(a);

    LinkNode *b = (LinkList)malloc(sizeof(LinkList));
    split(a, b);
    printLinkListR(a);
    printLinkListR(b);
}

// 我突然发现可以用log的方式，把实验后的结果和一些标志存放到一个.markdown或者什么文件里，然后用软件进行查看，比如Obsidian，这样可以更系统地管理实验数据。
// 而且如果屏幕够大的话，可以分屏左边显示软件，如果Obsidian能够瞬间刷新的话，就完美地输出了结果。或者有的IDE是可以记录控制台输出的文字吧。

// 我只知道，在使用C的过程中真的深深的感受到C++与其他语言的便捷，面向对象的强大，首先每个函数都不能重名，然后每次新创建一个结构变量，总是要写一长串malloc的东西，然后函数不能作为类的成员函数，使得每次要将类作为参数代入进去，然后类的成员变量都要写成指针引用xx->yy的形式，而不能直接写yy。
// 当然这些都有一些迂回的解法吧，我就是觉得ucore的时候好像也没有不能重名，然后malloc设置一个代码片段，其实也不是不能接受。

// 难道学习C的目的是为了更加了解这些吗？因为单纯觉得太巧合了。