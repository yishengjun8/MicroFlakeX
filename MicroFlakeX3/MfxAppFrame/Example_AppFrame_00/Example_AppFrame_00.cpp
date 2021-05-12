#include <iostream>
#include "MfxAppFrame.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    cout << "Hello MicroFlakeX!\n";


    {
        MfxUI myUI3(MfxRect(10, 10, 600, 600), MfxText("myUI3"));
    }

    //{
    MfxUI* myUI2 = new MfxUI(MfxRect(10,10,600,600), MfxText("myUI2"));
    //}
    //delete myUI2;
    MfxUI* myUI = nullptr;
    MfxFlake* myFlake_00 = nullptr;
    MfxFlake* myFlake_01 = nullptr;

    //利用Mfx工厂创建一个对象 - 当然你也可以直接new对象
    MfxFactory(MfxText("MfxUI"), (MfxBase**)&myUI);
    MfxFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_00);
    MfxFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_01);

    myUI->SetBackColor(MfxColor(255, 0, 255, 0));

    myFlake_00->SetRect(MfxRect(19, 18, 360, 120));
    myFlake_01->SetRect(MfxRect(19, 18 * 2 + 120, 360, 120));

    myUI->AddFlake(myFlake_00);
    myUI->AddFlake(myFlake_01);

    myFlake_00->SetBackColor(MfxColor(255, 0, 0, 255));
    myFlake_00->SetTitle(L"Hello MicroFlakeX!");
    myFlake_01->SetTitle(L"Welcome to MFX based on D2D");

    myFlake_00->OpenLButtonMove();
    myFlake_00->OpenRButtonMove();

    myUI->OpenPercentRect();
    myFlake_00->OpenPercentRect();
    MfxApp::theApp->Run();
    return 0;
    //return MfxApp::theApp->overParam;
}