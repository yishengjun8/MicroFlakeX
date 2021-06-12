// Example_MicroFlakeX_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <functional>
#include "MfxTest.h"

using namespace std;
using namespace MicroFlakeX;
using namespace __MicroFlakeX;



int main()
{
    MfxBase* tes = new MfxRect;

    MfxString name;

    tes->GetObjectName(&name);

    //auto fun = &(tes->Reflection);

    wcout << name;

    return 0;
}


int ccout(int a)
{
    cout << "ccout" << a << endl;
    return a;
}

int cccout(int a, int b)
{
    cout << "ccout" << a << " " << b << endl;
    return a;
}

int ccccout(int a, int b, int c)
{
    cout << "cccout" << a << " " << b << " " << c << endl;
    return a;
}

template<typename T, typename TT>
class BIND
{
public:
    BIND(T func, TT arg)
    {
        myFunc = func;
        argc = arg;
        is = 0;
    }

    ~BIND()
    {
        if (is)
        {
        //    (*this)();
        }
    }

    T myFunc;
    TT argc;
    int is;

    template<typename T1, typename T2>
    int operator()(T1 t1, T2 t2)
    {
        return (*myFunc)(argc, t1, t2);
    }

    template<typename T1>
    int operator()(T1 t1)
    {
        return (*myFunc)(argc, t1);
    }

    int operator()()
    {
        return (*myFunc)(argc);
    }

    //operator

};
template<typename T>
void RUNIT(T set)
{
    (*set)();
}

template<typename T>
void BINDFOR(T set, int num, int arg)
{
    if (num == 1)
    {
        BIND myBind(set, arg);
        RUNIT(&myBind);
    }
    else
    {
        BIND myBind(set, arg);
        BINDFOR(&myBind, num - 1, arg * 100);
    }
}


int test2()
{
    using namespace std::placeholders;
    cout << Mfx_GetFuncArgc(ccout) << endl;

    //for (int i = 0; i < Mfx_GetFuncArgc(ccout); i++)
    {
        //auto myBind = new BIND(ccout, 100);
    }

    //BINDFOR(ccout, 1, 200);

    BIND myBind(ccout, 100);
    cout << myBind() << endl;

    BIND myBind2(cccout, 100);
    BIND myBind2_(&myBind2, 200);
    cout << myBind2_() << endl;


    BIND myBind3(ccccout, 100);
    BIND myBind3_(&myBind3, 200);
    BIND myBind3__(&myBind3_, 300);
    cout << myBind3__() << endl;

    return 66;

}


int test1()
{
    int a = clock();
    MfxTest myTest;


    MfxSignal_Link mySignal;
    MfxSignal_UnLink mySignalEx;
    
    mySignal.PushBackReceiver(&myTest, L"test001");
    mySignalEx.PushBackReceiver(&myTest);

    long long times = 20000000;
    int begin, out, fo = 0;



    while (fo < 4)
    {
        cout << "————————————————————\ntimes = " << times << endl;
        begin = clock();
        for (int i = 0; i < times; i++)
        {
            myTest.test001(10);
        }
        out = clock() - begin;
        cout << "Direct:" << out << endl;

        begin = clock();
        for (int i = 0; i < times; i++)
        {
            mySignal.SendSignal(10);
        }
        out = clock() - begin;
        cout << "MfxSignal_Link:" << out << endl;

        begin = clock();
        for (int i = 0; i < times; i++)
        {
            mySignalEx.SendSignal(L"test001", 10);
        }
        out = clock() - begin;
        cout << "MfxSignal_UnLink:" << out << endl;

        fo++;
        times *= 2;
    }
    int tta;
    cin >> tta;
    return clock() - a;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
