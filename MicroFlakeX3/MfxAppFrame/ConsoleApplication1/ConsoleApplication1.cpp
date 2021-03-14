// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//#include "MfxAppFrame.h"
using namespace std;
//using namespace MicroFlakeX;


int fun1(int a, int b, int c)
{
    cout << "fun1" << a << "-" << b << "-" << c << endl;
    return a;
}


class people
{
public:
    people()
    {
        cout << "people()" << endl;
    }
    people(int a)
    {
        cout << "people(int a)" << a << endl;
    }
    people(int a, int b)
    {
        cout << "people(int a, int b)" << a << "-" << b << endl;
    }
    people(int a, int b, int c)
    {
        cout << "people(int a, int b, int c)" << a << "-" << b << "-" << c << endl;
    }

};

class animal
{
public:
    animal()
    {
        cout << "animal()" << endl;
    }
    animal(int a)
    {
        cout << "animal(int a)" << a << endl;
    }
    animal(int a, int b)
    {
        cout << "animal(int a, int b)" << a << "-" << b << endl;
    }
    animal(int a, int b, int c)
    {
        cout << "animal(int a, int b, int c)" << a << "-" << b << "-" << c << endl;
    }

};

class MfxFactoryHand
{
public:
    MfxFactoryHand() {

    }
    template<typename... T>
    int Creat(people** ret, T... args) {
        *ret = new people(args...);
        return 10;
    }

    
};
class MfxFactoryHand1
    : public MfxFactoryHand
{
public:
    MfxFactoryHand1() {

    }
    template<typename... T>
    int Creat(animal** ret, T... args) {
        *ret = new animal(args...);
        return 10;
    }
};

int main()
{
    std::cout << "Hello World!\n";
    //MfxUI myUI;
    MfxFactoryHand* test = new MfxFactoryHand1;
    //MfxFactoryHand1 test;
    people* a = nullptr;

    test->Creat(&a, 60, 80, 90);
    test->Creat(&a, 66, 88);
    //MfxApp::theApp->Run();


    cout << typeid(*test).name() << endl;
    return 6;
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
