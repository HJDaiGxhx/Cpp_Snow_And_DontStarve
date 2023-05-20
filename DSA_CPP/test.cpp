#include "include/test.h"

// digit<=1，则统一返回0~9；digit>1，比如=5则返回10000+0~89999，即10000~99999。
long long random(int digit = 1)
{
    if (digit > 1)
        return rand() % (long long)(9 * pow(10, digit - 1)) + pow(10, digit - 1);
    else
        return rand() % 10;
}

/* 创建一个Vector对象：Vector<int> t('r', size, hi); t2.sort; print;
创建一个大小为size、每个数随机0~hi-1的向量，print，复制一个t2向量，绝对正确地排序后print作为参考答案。

效果：
<1> 3, 4, 1, 2... <---print array1
<2> **array[size] created, range = 0 ~ hi.**
<3> 1, 2, 3, 4... <---print array2, sorted
<4> **xxxSort: xxxns**\n
*/
Vector<int> test_sort(int size, int hi)
{
    Vector<int> t('r', size, hi);
    printf("array[%d] created, range = 0 ~ %d.\n", size, hi);
    t.print();

    Vector<int> t2 = t;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    string s = t2.sort(0, t2.size());
    endNPrintTime(start, s);
    t2.print();

    return t;
}

// #Q 使得随机数真的随机的一步，现在用的是c上面学到的srand，好像C++还有<random>什么，留意一下
void setRand()
{
    time_t t;
    srand((unsigned)time(&t));
}

/* type countStart()
{
    //定义毫秒级别的时钟类型
    // typedef chrono::time_point<chrono::system_clock, chrono::milliseconds> microClock_type;
    // time_point<clock_type, config> mstp;
    clock_type::time_point start = clock_type::now();

    //获取当前时间点，windows system_clock是100纳秒级别的(不同系统不一样，自己按照介绍的方法测试)，所以要转换
    // microClock_type tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    // mstp = time_point_cast<config>(clock_type::now();
    // type start = clock_type::to_time_t(mstp);

    return start;
}
 */

/* #Q 据测试，该函数本体执行要1000ns，仅供参考。

nanoseconds的尾数两位实际显示都是0，如何解决？ */
void endNPrintTime(std::chrono::steady_clock::time_point start, string s = "")
{
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "**";
    if (s != "")
        std::cout << s << ": ";
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
         << "ns.**\n";
}

/* 创建无序int数组，大小为size，即里面的全部size个数都会被初始化为一个随机数。每个数值的范围在0~hi-1之间。*/
// int *create(int size, int hi)
// {
//     int A[size];

//     for (int r = 0; r < size; r++)
//         A[r] = rand() % hi;

//     return A;
// }

/* 创建无序int数组，大小为size，即里面的全部size个数都会被初始化为一个随机数。每个数值的范围在0~hi-1之间。*/
int *create(int *A, int size, int hi)
{
    for (int r = 0; r < size; r++)
        A[r] = rand() % hi;

    return A;
}

/* 创建有序int数组，大小为size，从0开始根据count的大小随机生成0~count-1个，直到填满数组大小为止。

注意——比如从0开始，count随机为3，就生成0,0,0,然后机会结束，现在轮到1，count随机为0，那就不生成，然后轮到2…… */
int *createSorted(int *A, int size, int count)
{
    for (int r = 0, num = 0; r < size;) // rank = 0; number = 0; count = 0;
    {
        for (int c = rand() % count; c > 0; c--) // 0~hi-1
            A[r++] = num;
        num++;
    }

    return A;
}

/* 创建有序int数组，大小为size，从lo的数值开始以随机次数生成到数组中，出现次数为随机的countLo-countHi-1之间，然后下一个数与lo的数值差在1-diff之间。

注意——比如lo=1，diff=5，countLo=1，countHi=10，则最开始出现数为1，出现次数为1-9次，下一个数可能是1+1~5=2~5中的某一个。

特殊情况（未完善）——
每个数只出现1次: A, size, x, x, 1, 2;
无重复的0,1,2,3,4...的数组: A, size, 0, 1, 1, 1;
每个数只出现0次或1次：A, size, x, x, 0, 1 */
int *createSorted(int *A, int size, int lo, int diff, int countLo, int countHi)
{
    int num = lo;
    int count;
    count = countHi - countLo;

    for (int r = 0; r < size;) // rank = 0; number = 0; count = 0;
    {
        for (int c = rand() % count + countLo; c > 0; c--) // 0~hi-1
            A[r++] = num;
        num = num + rand() % diff + 1;
    }

    return A;
}

/* 创建一个只有(){}[]符号的数组测试堆栈应用。
#Q 如果要更加极限地去做调试的话，完全可以把这些数组放在一起做全局变量，然后达到最舒服的只要调整数组就行了，size什么都不用调的地步。像在玩经营类游戏的感觉。 */
char *createSymbols(char *A, int size)
{
    char table[] = {'(', ')'}; //, '{', '}', '[', ']'};
    int tableSize = 2;

    for (int r = 0; r < size; r++)
    {
        A[r] = table[rand() % tableSize];
    }

    return A;
}

/*  */
char *createWithSymbols(char *A, int size)
{
    char table[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', ')', '{', '}', '[', ']', '+', '-', '/', '*'};
    int tableSize = 36;

    for (int r = 0; r < size; r++)
    {
        A[r] = table[rand() % tableSize];
    }

    return A;
}

/* 为RPN和衍生函数制造一个供计算的数学算式，比如1+2*3 */
char *createFormula(char *A, int size, int hi = 15)
{
    if (size % 2 == 1)
    {
        // print("数组数量是奇数，暂时没有此技术。\n");
        return A;
    }

    // 这里是不是可以改进为ASCII之类的表？
    // 然后括号是否可以用之前的paren来检查，我其实觉得随机生成数组然后最后用paren工厂验收质量的感觉很帅，就是像以前曾经介绍过计算机的算力可以蛮力解决一些东西。
    char table[] = {'+', '-', '/', '*', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int tableSize = 14;
    for (int i = 0; i < size - 1; i++)
    {
        if (i % 2 == 0)
            A[i] = table[rand() % 10 + 4];
        else
            A[i] = table[rand() % 4];
    }
    A[size - 1] = '\0';
    return A;
}

/* 让计算机计算一些东西，使得出现1s的停顿，用来打造动画效果。 */
void pause()
{
    for (int i = 0; i < 4196; i++)
    {
        int size = 4196;
        int a[size];
        Vector<int> v(a, size);
        createSorted(v.array(), v.size(), 5);
        v.deduplicate();
    }
}

// #Q 老是出现似乎cin把程序里的参数输入到自己那边去了的情况，导致控制台一直滚动信息。
// #未完成
Rank *test_RangeValid(Rank lo, Rank hi)
{
    /*     Rank newLo = test_IfNaturalNum(lo);
        Rank newHi = test_IfNaturalNum(hi);
        while (newLo > newHi)
        {
            cout << "Error: lo is larger than hi, cant form a range\n";
            newLo = test_IfNaturalNum(newLo);
            newHi = test_IfNaturalNum(newHi);
        }
        Rank array[2] = {newLo, newHi};
        return array;
         */
    return 0;
}

// 测试下标是否在[lo, hi]范围内。因为我不确定是不是大家都用[lo, hi)的标准，否则要修改一下。最后返回r或者用户新输入的newR。
int test_RankValid(Rank r, Rank lo, Rank hi)
{
    int newR = r;
    while (newR < lo || newR > hi)
        newR = printErrorNRetry("position invalid");
    return newR; // 如果测试的r没有问题，返回的还是r；如果有问题，返回用户最后输入的newR。
}

// 测试是否是自然数，如果不是，要求重新输入一个合法的数。主要用于数组下标是否负数、非数检查。
// 然而我还是不太懂怎么把字符和数混着查，所以只先做出了数判断负数的部分。
int test_IfNaturalNum(int r)
{
    int newR = r;
    while (newR < 0) // 如果是十进制数，检测是否是正的，否则进入Retry方案。
        newR = printErrorNRetry("not natural number (0~+...)");

    return newR;
}

void test_find()
{
    // ListNodePosi<T> p;
    int num = rand() % 100;
    cout << "\n"
         << num << " is the data to be find.\n";
}

// 根据给予的s写出Error：具体内容，然后返回用户新输入的一个int数。
// 这个函数大概率是不公开的，因为它本身不包含无限循环，循环必须要一个对于数的约束条件。
int printErrorNRetry(string s)
{
    printError(s);
    cout << "Please retry a rank: ";
    int i = 1;
    cin >> i;

    return i;
}

/* 一个endl */
void printError(string s = "")
{
    cout << "Error";
    if (s != "")
        cout << ": " << s << endl;
    else
        cout << '.' << endl;
}