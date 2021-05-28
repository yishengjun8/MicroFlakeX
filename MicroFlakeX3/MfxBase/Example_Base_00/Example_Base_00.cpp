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

typedef long MfxMessage;

MfxMessage FLAKE_MSG_FlakeMessage = 1;

MfxMessage FLAKE_MSG_SetPaper = 2;
MfxMessage FLAKE_MSG_RemovePaper = 3;

MfxMessage FLAKE_MSG_PaintBack = 4;
MfxMessage FLAKE_MSG_PaintMask = 5;


MfxMessage UI_MSG_FlakeMessage = 1;

MfxMessage UI_MSG_SetPaper = 2;
MfxMessage UI_MSG_RemovePaper = 3;

MfxMessage UI_MSG_PaintBack = 4;
MfxMessage UI_MSG_PaintMask = 5;


int main()
{
    MfxParam myParam1, myParam2;

    myParam1.push_back(FLAKE_MSG_FlakeMessage);
    myParam1.push_back(myParam2);

    cout << GetParam_Safe(myParam1, MfxMessage, 0);


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
