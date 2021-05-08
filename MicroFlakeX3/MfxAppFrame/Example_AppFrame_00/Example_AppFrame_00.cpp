#include <iostream>
#include "MfxAppFrame.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    cout << "Hello MicroFlakeX!\n";

    MfxUI* myUI = nullptr;
    MfxFlake* myFlake_00 = nullptr;
    MfxFlake* myFlake_01 = nullptr;

    //利用Mfx工厂创建一个对象 - 当然你也可以直接new对象
    MfxBaseFactory(MfxText("MfxUI"), (MfxBase**)&myUI);
    MfxBaseFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_00);
    MfxBaseFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_01);

    myUI->SetBackColor(MfxColor(255, 0, 255, 0));

    myFlake_00->SetRect(MfxRect(19, 18, 360, 120));
    myFlake_01->SetRect(MfxRect(19, 18 * 2 + 120, 360, 120));

    myUI->AddFlake(myFlake_00);
    myUI->AddFlake(myFlake_01);

    myFlake_00->SetTitle(L"Hello MicroFlakeX!");
    myFlake_01->SetTitle(L"Welcome to MFX based on D2D");

    myFlake_00->OpenLButtonMove();
    myFlake_00->OpenRButtonMove();

    MfxApp::theApp->Run();

    return MfxApp::theApp->overParam;
}