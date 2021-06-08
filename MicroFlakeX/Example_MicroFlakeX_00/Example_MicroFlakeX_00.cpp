#include <iostream>
#include "MicroFlakeX.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    MfxBase* myUI_00 = nullptr;
    MfxBase* myColor = nullptr;
    MfxBase* myFlake_01 = nullptr;

    MfxFactory(MfxText("MfxUI"), &myUI_00);
    MfxFactory(MfxText("MfxFlake"), &myFlake_01);

    MfxFactory(MfxText("MfxColor"), &myColor);


    MfxSignal mySignal;
    mySignal.PushBackReceiver(myUI_00, MfxText("SetSize"));

    MfxSize uiSize(600, 600);
    mySignal.SendSignal(&uiSize);

    myColor->AutoFunc(MfxText("Reset"), 255, 0, 255, 0);
    myUI_00->AutoFunc(MfxText("SetBackColor"), myColor);

    myColor->AutoFunc(MfxText("Reset"), 255, 255, 255, 255);
    myFlake_01->AutoFunc(MfxText("SetBackColor"), myColor);

    myColor->AutoFunc(MfxText("Reset"), 255, 0, 0, 0);
    myFlake_01->AutoFunc(MfxText("SetTitleColor"), myColor);

    MfxRect flakeRect(0, 0, 100, 100);
    myFlake_01->AutoFunc(MfxText("SetRect"), &flakeRect);

    myFlake_01->AutoFunc(MfxText("SetTitle"), MfxString(MfxText("MFX")));
    myFlake_01->AutoFunc(MfxText("OpenRButtonMove"));
    myFlake_01->AutoFunc(MfxText("OpenLButtonMove"));

    myUI_00->AutoFunc(MfxText("InsertFlake"), myFlake_01);

    MfxGlide myGlide;

    myGlide.SetFPS(90);
    myGlide.BindObject(myFlake_01);

    myGlide.BindObjectName(MfxText("group_1"),
        MfxGulid_WidelyType(MfxText("MfxSize"), MfxText("MfxSize"), MfxText("GetSize"), MfxText("SetSize")));
    myGlide.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetWidth"), MfxText("SetWidth"));
    myGlide.Add_GetSetFuncName(MfxText("group_1"), MfxText("GetHeight"), MfxText("SetHeight"));

    myGlide.BindObjectName(MfxText("group_2"),
        MfxGulid_WidelyType(MfxText("MfxPoint"), MfxText("MfxPoint"), MfxText("GetPoint"), MfxText("SetPoint")));
    myGlide.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetX"), MfxText("SetX"));
    myGlide.Add_GetSetFuncName(MfxText("group_2"), MfxText("GetY"), MfxText("SetY"));

    myGlide.BindObjectName(MfxText("group_3"),
        MfxGulid_WidelyType(MfxText("MfxColor"), MfxText("MfxColor"), MfxText("GetBackColor"), MfxText("SetBackColor")));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetA"), MfxText("SetA"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetR"), MfxText("SetR"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetG"), MfxText("SetG"));
    myGlide.Add_GetSetFuncName(MfxText("group_3"), MfxText("GetB"), MfxText("SetB"));

    myGlide.BindObjectName(MfxText("group_4"),
        MfxGulid_WidelyType(MfxText("MfxColor"), MfxText("MfxColor"), MfxText("GetTitleColor"), MfxText("SetTitleColor")));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetA"), MfxText("SetA"));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetR"), MfxText("SetR"));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetG"), MfxText("SetG"));
    myGlide.Add_GetSetFuncName(MfxText("group_4"), MfxText("GetB"), MfxText("SetB"));

    MfxSize keySize(300, 300);
    myGlide.MfxAddKeyframe(MfxText("group_1"), &keySize, 1500);
    keySize.Reset(100, 100);
    myGlide.MfxAddKeyframe(MfxText("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxText("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxText("group_1"), &keySize, 1500);


    MfxPoint keyPoint(300, 0);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &keyPoint, 1500);
    keyPoint.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 300);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 0);
    myGlide.MfxAddKeyframe(MfxText("group_2"), &keyPoint, 1500);

    MfxColor keyColor(255, 0, 255, 255);
    myGlide.MfxAddKeyframe(MfxText("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 0, 0, 255);
    myGlide.MfxAddKeyframe(MfxText("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 50, 50, 50);
    myGlide.MfxAddKeyframe(MfxText("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 255, 0, 0);
    myGlide.MfxAddKeyframe(MfxText("group_3"), &keyColor, 1500);

    keyColor.Reset(255, 0, 0, 255);
    myGlide.MfxAddKeyframe(MfxText("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 0, 255, 255);
    myGlide.MfxAddKeyframe(MfxText("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 255);
    myGlide.MfxAddKeyframe(MfxText("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 0);
    myGlide.MfxAddKeyframe(MfxText("group_4"), &keyColor, 1500);

    myGlide.Begin();

    myUI_00->AutoFunc(MfxText("SetUI_Show"));
    return MfxAppRun();
}