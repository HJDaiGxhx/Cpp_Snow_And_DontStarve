#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using std::cout;
using std::printf;
using std::string;

#include "include/Log.h" /* 代码测试用日志模块。 */
#include "test.cpp"      /* 打印、测试类工具模块。 */

/* <映雪>的C++文件，目的是制作一个命令行界面，从而在游戏中新获得一批武将的时候，通过数据输入查询到该培养哪些对象。 */
#include "Maiden.cpp"
/* <饥荒>的C++文件，目的是通过分析游戏内的食物制作配方，逆向得到制作哪些食物最优，制作了一个模拟表的类Table，以在多种模糊配方中生成一个最优配方。但中期转到了Lua(AllMods/Mods_DST/food_helper)进行制作，后期发现通过数据筛选事先排除大部分食物后剩下十几种食物，手动计算反而更加便利，模块失败。 */
#include "include/Foods.h"

/* 供<映雪>数据查询的命令行界面。 */
/* void serve()
{
    string s2[5];
    while (true)
    {
        cout << "> ";

        for (int i = 0; cin >> s2[i]; i++)
            if (cin.get() == '\n')
                break;
        if (s2[0] == "growtype")
        {
            // #NQ 施工中，中文字符无法正常被查询，显示为NULL，数字编号可以。
            Block *p = T_GROWTYPE.search(stoi(s2[1]));
            if (p != NULL)
                p->list();
        }
        else if (!strcmp(s2[0].c_str(), "quit"))
            break;

        cout << endl;
    }
}
 */

/* 尝试自动打印数组。 */
void traverse(
    auto &array, auto fun = [](auto x) {})
{
    for (auto x : array)
        fun(x);
}

// ----------- 代码实际运行区（fun()中写实际运行代码） -----------
string tag = "Snow"; // 日志文件中记录的标签
int cycle = 1;       // fun()运行次数
void fun()
{
    // serve();

    // Recipe r("RecipesRaw", "RecipesNew");
    // Recipe r("RecipesNew", "RecipesNew3");
    // Recipe r("RecipesNew2", "RecipesNew3");
    // // r.funRaw();
    // r.funNew();
    // r.save(Recipe::funNew);
    // cout << "hello\n";
    // int A[10] = {0};
    // traverse(A, [](auto x)
    //          { cout << x << endl; });
}

int main()
{
    setRand();

    // #NQ 还需要解决freopen("CON") 无法适配插件Code Runner中命令的问题
    // 第一遍运行，将运行结果和运行总时间打印在命令行界面中
    std::chrono::steady_clock::time_point start;
    for (int i = 0; i < cycle; i++)
    {
        cout << endl;
        start = std::chrono::steady_clock::now();
        fun();
        endNPrintTime(start, tag);
    }

    // 第二遍运行，将相同数据输入到Markdown格式的日志文件中
    Log2 log(tag);
    for (int i = 0; i < cycle; i++)
    {
        cout << "```" << endl;
        start = std::chrono::steady_clock::now();
        fun();
        cout << "```" << endl;
        endNPrintTime(start, tag);
    }

    return 0;
}