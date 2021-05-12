#include <iostream>
#include "MfxAppFrame.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    cout << "Hello MicroFlakeX!\n";

    {
        MfxUI myUI_02(MfxRect(10, 10, 600, 600), MfxText("myUI_02"));
    }

    MfxUI* myUI_01 = new MfxUI(MfxRect(10,10,600,600), MfxText("myUI_01"));

    MfxUI* myUI_00 = nullptr;
    MfxFlake* myFlake_00 = nullptr;
    MfxFlake* myFlake_01 = nullptr;

    //利用Mfx工厂创建一个对象 - 当然你也可以直接new对象
    //MfxFlake在MfxUIUI结束的时候会被delete，所以MfxFlake不能是局部变量
    MfxFactory(MfxText("MfxUI"), (MfxBase**)&myUI_00);
    MfxFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_00);
    MfxFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_01);

    myUI_00->SetBackColor(MfxColor(255, 0, 255, 0));

    myFlake_00->SetRect(MfxRect(19, 18, 360, 120));
    myFlake_01->SetRect(MfxRect(19, 18 * 2 + 120, 360, 120));

    myUI_00->AddFlake(myFlake_00);
    myUI_00->AddFlake(myFlake_01);

    myFlake_00->SetBackColor(MfxColor(255, 0, 0, 255));
    myFlake_00->SetTitle(L"Hello MicroFlakeX!");
    myFlake_01->SetTitle(L"Welcome to MFX based on D2D");

    myFlake_00->OpenLButtonMove();

    myFlake_01->OpenRButtonMove();

    myFlake_00->OpenPercentRect();

    return MFXAPP->Run();
}