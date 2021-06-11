// Example_MicroFlakeX_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>

#include "MfxTest.h"

using namespace std;


int main()
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
        cout << "\n————————————————————\ntimes = " << times << endl;
        begin = clock();
        for (int i = 0; i < times; i++)
        {
            myTest.test001(10);
        }
        out = clock() - begin;
        cout << out << endl;

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
