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

    MfxColor tColor(255, 0, 255, 0);
    myUI_00->SetBackColor(&tColor);

    MfxRect tRect(19, 18, 360, 120);
    myFlake_00->SetRect(&tRect);
    tRect.Reset(19, 18 * 2 + 120, 360, 120);
    myFlake_01->SetRect(&tRect);

    myUI_00->AddFlake(myFlake_00);
    myUI_00->AddFlake(myFlake_01);

    tColor.Reset(255, 0, 0, 255);
    myFlake_00->SetBackColor(&tColor);
    myFlake_00->SetTitle(L"Hello MicroFlakeX!");
    myFlake_01->SetTitle(L"Welcome to MFX based on D2D");

    myFlake_00->OpenLButtonMove();

    myFlake_01->OpenRButtonMove();

    myFlake_00->OpenPercentRect();


    MfxGlide myGlide;
    myGlide.SetFPS(60);
    myGlide.BindObject(myFlake_01);

    myGlide.BindObjectName(MfxText("group_1"),
        MfxGulid_WidelyType(MfxText("MfxSize"), MfxText("MfxSize"), MfxText("GetSize"), MfxText("SetSize")));

    myGlide.BindObjectName(MfxText("group_2"),
        MfxGulid_WidelyType(MfxText("MfxPoint"), MfxText("MfxPoint"), MfxText("GetPoint"), MfxText("SetPoint")));

    myGlide.BindObjectName(MfxText("group_3"),
        MfxGulid_WidelyType(MfxText("MfxColor"), MfxText("MfxColor"), MfxText("GetBackColor"), MfxText("SetBackColor")));

    myGlide.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetWidth"), MfxText("SetWidth"));
    myGlide.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetHeight"), MfxText("SetHeight"));

    myGlide.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetX"), MfxText("SetX"));
    myGlide.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetY"), MfxText("SetY"));

    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetA"), MfxText("SetA"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetR"), MfxText("SetR"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetG"), MfxText("SetG"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetB"), MfxText("SetB"));

    MfxSize* tpSize = new MfxSize(200, 200);
    myGlide.MfxAddKeyframe(MfxText("group_1"), tpSize, 5000);

    tpSize = new MfxSize(100, 100);
    myGlide.MfxAddKeyframe(MfxText("group_1"), tpSize, 5000);

    MfxPoint* tpPoint = new MfxPoint(100, 200);
    myGlide.MfxAddKeyframe(MfxText("group_2"), tpPoint, 5000);

    tpPoint = new MfxPoint(0, 0);
    myGlide.MfxAddKeyframe(MfxText("group_2"), tpPoint, 5000);

    MfxColor* tpColor = new MfxColor(0, 255, 0, 0);
    myGlide.MfxAddKeyframe(MfxText("group_3"), tpColor, 5000);

    tpColor = new MfxColor(255, 255, 0, 0);
    myGlide.MfxAddKeyframe(MfxText("group_3"), tpColor, 5000);

    myGlide.Begin();
    return MFXAPP->Run();
}