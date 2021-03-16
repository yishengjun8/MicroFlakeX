// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "MfxAppFrame.h"
using namespace std;
using namespace MicroFlakeX;

int main()
{
    std::cout << "Hello World!\n";
    MfxUI myUI;


    myUI.SetBackColor(MfxColor(255, 0, 255, 0));

    MfxApp::theApp->Run();

    return 6;
}