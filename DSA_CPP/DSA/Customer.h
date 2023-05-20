#pragma once

#include "Vector.h"
#include "Queue.h"
#include "test.h"

struct Customer;

struct Customer
{
    int window;
    unsigned int time;
};

class Bank
{
private:
    int nowTime = 0;
    int customer = 0;
    int winSize = 0;          // 可能主要目的是为了print保持干净，不要带参数，print怎么能带参数呢？真是异端……（个人浅见）
    Queue<Customer> *windows; // 感觉还是治标不治本，nWin也要变内部变量，还是向量香啊，就是一个小小的size在折磨。
    int properWin(Queue<Customer> windows[], int nWin);

public:
    void start(int nWin, int servTime);
    void print();
};

/* 如果能做一个功能，使得四个队列人数都一致时随机选择一个队列就好了，因为顺时针时间片的话，其实就是很无聊。 */
int Bank::properWin(Queue<Customer> windows[], int nWin)
{
    int min = 0;
    int minSize = windows[0].size();

    for (int i = 1; i < nWin; i++)
        if (windows[i].size() < minSize)
        {
            min = i;
            minSize = windows[i].size();
        }

    return min;
}

/* 做是做好了，总怀疑有优化的余地，但是真的兴致不高，想要做下一个项目了。 */
void Bank::start(int nWin, int servTime)
{
    int timeStamp = 1 + nWin;
    winSize = nWin;
    windows = new Queue<Customer>[nWin]; // Capacity = nWin

    while (true)
    {
        bool empty = true;

        for (int i = 0; i < nWin; i++)
            if (!windows[i].empty())
            {
                if (--windows[i].front().time <= 0)
                    windows[i].dequeue();
                empty = false;
            }

        if (empty && (nowTime >= servTime))
            break;

        if (nowTime < servTime)
            if (rand() % timeStamp)
            {
                // int pWin = properWin(windows.size());
                customer++;
                Customer c;
                c.window = properWin(windows, nWin);
                c.time = 1 + rand() % 9;
                windows[c.window].enqueue(c);
            }
        nowTime++;
        print();
    }

    Test::p("The bank is closed! Come tomorrow.");
}

/* 有个问题，如果按这种写法，时间为两位数或者三位数就会乱，可能可以用printf的标准格式来改，但是懒得改了。 */
void Bank::print()
{
    pause();

    printf("current time is: %ds\n", nowTime);
    printf("current customer is: %dp\n", customer);
    for (int i = 0; i < winSize; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < windows[i].size(); j++)
            printf("██%ds ", windows[i][j].time);
        p();
    }
    p();
}
