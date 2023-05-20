#include "Fib.h"
#include "test.h"

void Fib::fibonacci(Rank k)
{
    // // version A
    // if (k == 0)
    //     return 0;
    // if (k == 1)
    //     return 1;
    // // return fib(k - 1) + fib(k - 2);

    // // version B
    f = 1;
    g = 0;
    while (k-- > 0)
    {
        g += f;    // fib(k) = fib(k-1)->k3 + fib(k-2)->k2
        f = g - f; // fib(k-1) = fib(k)->k3 - fib(k-2)->k2
    }
}

/* #H 构造斐波那契数列的递归版本。Rank 0 -> 0。
DP，什么记忆备忘录法。 */
int Fib::fibonacci(Rank k, int &prev)
{
    // version B recursion
    // 但是这好像和A是一样的，只不过A先计算k-1，这里先计算k-2，而因为k-2不需要用到k-1，它的值反而变成了k-1的完美下一个参数……？
    if (k == 0)
    {
        prev = 1;
        return 0;
    }
    int prevPrev; // = fib(k-2, prevprev)。其实应该先这样直观想，然后观察代码，发现它可以合并到prev里，自然而然得出正确的。我明明最后都想这么写了，还是差了那么一点，这都是无可奈何了吧。
    prev = fibonacci(k - 1, prevPrev);
    return prev + prevPrev;
}

/* 好吧，这个算法是更简洁的，但勉强要挑错的话，它需要O(2n)的附加空间，而前者只需要O(n)。 */
int Fib::fibonacci(Rank k, int a, int b)
{
    if (k == 0)
        return b;
    return fibonacci(k - 1, b, a + b);
}

/*  */
void Fib::print(int r)
{
    printf("fib(0): %d\n", g);
    for (int i = 1; i < r; i++)
        printf("fib(%d): %d\n", i, next());
}