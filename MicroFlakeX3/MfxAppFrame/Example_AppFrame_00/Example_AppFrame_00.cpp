#include <iostream>
#include "MfxAppFrame.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    cout << "Hello MicroFlakeX!\n";

    MfxUI* myUI_00 = nullptr;
    MfxFlake* myFlake_01 = nullptr;

    MfxFactory(MfxText("MfxUI"), (MfxBase**)&myUI_00);
    MfxFactory(MfxText("MfxFlake"), (MfxBase**)&myFlake_01);

    MfxSize uiSize(400, 400);
    myUI_00->SetSize(&uiSize);
    myUI_00->InsertFlake(myFlake_01);

    MfxColor uiColor(255, 0, 255, 255);
    myUI_00->SetBackColor(&uiColor);

    MfxColor flakeColor(255, 255, 0, 0);
    myFlake_01->SetBackColor(&flakeColor);

    flakeColor.Reset(255, 0, 0, 255);
    myFlake_01->SetTitleColor(&flakeColor);

    MfxRect flakeRect(0, 0, 100, 100);
    myFlake_01->SetRect(&flakeRect);

    myFlake_01->SetTitle(L"Welcome to MFX based on D2D");

    myFlake_01->OpenRButtonMove();

    MfxGlide myGlide;
    
    myGlide.SetFPS(90);
    myGlide.BindObject(myFlake_01);

    myGlide.BindObjectName(MfxText("group_1"),
        MfxGulid_WidelyType(MfxText("MfxSize"), MfxText("MfxSize"), MfxText("GetSize"), MfxText("SetSize")));

    myGlide.BindObjectName(MfxText("group_2"),
        MfxGulid_WidelyType(MfxText("MfxPoint"), MfxText("MfxPoint"), MfxText("GetPoint"), MfxText("SetPoint")));

    myGlide.BindObjectName(MfxText("group_3"),
        MfxGulid_WidelyType(MfxText("MfxColor"), MfxText("MfxColor"), MfxText("GetTitleColor"), MfxText("SetTitleColor")));

    myGlide.BindObjectName(MfxText("group_4"),
        MfxGulid_WidelyType(MfxText("MfxColor"), MfxText("MfxColor"), MfxText("GetBackColor"), MfxText("SetBackColor")));

    myGlide.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetWidth"), MfxText("SetWidth"));
    myGlide.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetHeight"), MfxText("SetHeight"));

    myGlide.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetX"), MfxText("SetX")); //MfxEaseOutBack
    myGlide.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetY"), MfxText("SetY")); //MfxEaseOutElastic

    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetA"), MfxText("SetA"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetR"), MfxText("SetR"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetG"), MfxText("SetG"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetB"), MfxText("SetB"));

    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetA"), MfxText("SetA"));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetR"), MfxText("SetR"));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetG"), MfxText("SetG"));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetB"), MfxText("SetB"));

    MfxPoint tpPoint(300, 0);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &tpPoint, 1500);
    tpPoint.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &tpPoint, 1500);
    tpPoint.Reset(0, 300);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &tpPoint, 1500);
    tpPoint.Reset(0, 0);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &tpPoint, 1500);


    MfxColor tpColor(255, 0, 255, 0);
    myGlide.MfxAddKeyframe(MfxText("group_3"), &tpColor, 3000);
    tpColor.Reset(255, 255, 0, 255);
    myGlide.MfxAddKeyframe(MfxText("group_4"), &tpColor, 3000);

    tpColor.Reset(255, 255, 0, 255);
    myGlide.MfxAddKeyframe(MfxText("group_3"), &tpColor, 3000);
    tpColor.Reset(255, 0, 255, 0);
    myGlide.MfxAddKeyframe(MfxText("group_4"), &tpColor, 3000);

    myGlide.Begin();

    return MFXAPP->Run();
}