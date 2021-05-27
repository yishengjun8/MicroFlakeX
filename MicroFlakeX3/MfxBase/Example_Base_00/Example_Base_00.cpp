#include <iostream>
#include "MfxBase.h"
#include "MfxBaseExample_00.h"
using namespace MicroFlakeX;
using namespace std;

/*********************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*   这个示例展示了如何使用MfxBase及其组件
*********************************************************/

int main()
{
    MfxBase* test;

    MfxFactory(L"MfxBaseExample_00", &test);

    MfxSignal mySignal;

    mySignal.PushBackReceiver(test, MfxText("SayHello"));

    mySignal.SendSignal(MfxString(L"SendSignal"));

    MfxString str = MfxText("PostSignal");

    mySignal.PostSignal(str);

    Sleep(1000);

    mySignal.SendSignal(MfxString(L"SendSignal"));
    return 0;
}
