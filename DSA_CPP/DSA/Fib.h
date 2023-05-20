#pragma once

#ifndef Rank
#define Rank int
#endif

class Fib
{
private:
    long long f;
    long long g; // f = fib(k - 1), g = fib(k)。均为int型，很快就会数值溢出
public:
    // #H Rank 0 -> 0。构造斐波那契数列的递归版本。初始化为不小于n的最小Fibonacci项。
    Fib(int n)
    {
        // version B upgrade
        // 震撼，再一次错了，明明是那么简单的函数思路，都能这么极限，太打击信心了。感觉好像又好一点了，因为我发现写出B之后，只要稍微仔细观察一下，就能发现能省略一个参数，所以这肯定不是我的错。
        f = 1; // fib(k-1)
        g = 0; // 这里g = fib(1)之所以设置为了0，是考虑到k=0时直接跳过循环返回g了，所以g必须是0，而对应的f = fib(-1)不该是1，但因为g是0，所以它需要充当fib1的功能。最终得到的fib2还是1，因此只是直觉上会有点奇怪。
        while (n > g)
        {
            g += f;
            f = g - f;
        }
    }
    int next()
    {
        g += f;
        f = g - f;
        return g;
    }
    int prev()
    {
        f = g - f;
        g -= f;
        return g;
    }
    int get()
    {
        return g;
    }

    void fibonacci(Rank k);
    int fibonacci(Rank k, int &prev);
    int fibonacci(Rank k, int a, int b);

    /* 测试各种fib函数的函数。 */
    void fib(Rank k)
    {
        switch (rand() % 3)
        {
        case 0:
        {
            int i = 0;
            int &prev = i;
            cout << fibonacci(k, prev) << endl;
            break;
        }
        case 1:
        {
            fibonacci(k);
            cout << g << endl;
            break;
        }

        default:
            cout << fibonacci(k, 1, 0) << endl;
            break;
        }
    }

    void print(int r);
};