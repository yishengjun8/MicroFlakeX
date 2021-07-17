// Example_MicroFlakeX_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <functional>
#include "MfxTest.h"

using namespace std;
using namespace MicroFlakeX;
using namespace __MicroFlakeX;



void FuncTest0(int a) {};
void FuncTest1(int a, char b) {};
void FuncTest2(int a, char b, double c) {};

class GetFuncArgType
{
public:
    GetFuncArgType() {};
    ~GetFuncArgType() {};


    template <class T, class R, class... Args>
    MfxReturn Ex_Reflection(pMfxBase pThis, T pFunc, va_list argc, R(*)(Args...) )
    {
        return (pThis->*pFunc)(std::move(va_arg(argc, typename std::decay<decltype(Args)>::type))...);
    };

    //template<typename A1, typename ... Args, typename ... RetArgs>
    //auto GetArg(const int begin, const int over, A1, Args...)
    //{
    //}

};




int main()
{
    MyClass set; MfxTest myTest; MfxSignal mySignal; MfxClient myClient;
    myClient.PushBackReceiver(&myTest);
    mySignal.PushBackReceiver(&myTest, L"test002");

    mySignal.SendSignal(MyClass());
    mySignal.PostSignal(set);

    Sleep(10);
    std::cout << "MfxSignal OVER" << endl << endl;


    myClient.SendClient(L"test002", set);
    myClient.PostClient(L"test002", set);

    Sleep(10);
    std::cout << "MfxClient OVER" << endl << endl;


    myTest.Reflection(L"test002", set);

    return 0;
}


int ccccc()
{
    MfxBase* tes = new MfxRect;

    MfxStringW name;

    tes->GetObjectName(&name);

    //auto fun = &(tes->Reflection);

    std::wcout << name;

    return 0;
}


int ccout(int a)
{
    std::cout << "ccout" << a << endl;
    return a;
}

int cccout(int a, int b)
{
    std::cout << "ccout" << a << " " << b << endl;
    return a;
}

int ccccout(int a, int b, int c)
{
    std::cout << "cccout" << a << " " << b << " " << c << endl;
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

    //for (int i = 0; i < Mfx_GetFuncArgc(ccout); i++)
    {
        //auto myBind = new BIND(ccout, 100);
    }

    //BINDFOR(ccout, 1, 200);

    BIND myBind(ccout, 100);
    std::cout << myBind() << endl;

    BIND myBind2(cccout, 100);
    BIND myBind2_(&myBind2, 200);
    std::cout << myBind2_() << endl;


    BIND myBind3(ccccout, 100);
    BIND myBind3_(&myBind3, 200);
    BIND myBind3__(&myBind3_, 300);
    std::cout << myBind3__() << endl;

    return 66;

}


int mainsssssssssssssssssssss()
{

    /**/
    int a = clock();
    MfxTest myTest;


    MfxSignal mySignal;
    MfxClient myClient;
    
    mySignal.PushBackReceiver(&myTest, L"test001");
    myClient.PushBackReceiver(&myTest);

    long long times = 20000000;
    int begin, out, fo = 0;


    mySignal.PostSignal(10);
    myClient.PostClient(L"test001", 10);

    while (fo < 4)
    {
        std::cout << "————————————————————\ntimes = " << times << std::endl;
        begin = clock();
        for (int i = 0; i < times; i++)
        {
            myTest.test001(10);
        }
        out = clock() - begin;
        std::cout << "Direct:" << out << std::endl;

        begin = clock();
        for (int i = 0; i < times; i++)
        {
            mySignal.SendSignal(10);
        }
        out = clock() - begin;
        std::cout << "MfxSignal:" << out << std::endl;

        begin = clock();
        for (int i = 0; i < times; i++)
        {
            myClient.SendClient(L"test001", 10);
        }
        out = clock() - begin;
        std::cout << "MfxClient:" << out << std::endl;

        fo++;
        times *= 2;
    }
    int tta;
    std::cin >> tta;
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
