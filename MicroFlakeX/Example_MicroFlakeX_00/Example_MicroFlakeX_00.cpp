#include <iostream>
#include "MicroFlakeX.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    MfxBase* myUI_00 = nullptr;
    MfxBase* myColor = nullptr;
    MfxBase* myFlake_01 = nullptr;

    MfxFactory(MfxTextW("MfxUI"), &myUI_00);
    MfxFactory(MfxTextW("MfxFlake"), &myFlake_01);
    MfxFactory(MfxTextW("MfxColor"), &myColor);

    /**/
    MfxSignal mySignal;
    MfxClient myClient;

    mySignal.PushBackReceiver(myUI_00, MfxTextW("SetBackColor"));
    myClient.PushBackReceiver(myUI_00);

    MfxSize uiSize(600, 600);
    myClient.PostClient(MfxTextW("SetSize"), &uiSize);

    myColor->Reflection(MfxTextW("Reset"), 255, 0, 255, 0);
    mySignal.SendSignal(myColor);

    myColor->Reflection(MfxTextW("Reset"), 255, 255, 255, 255);
    myFlake_01->Reflection(MfxTextW("SetBackColor"), myColor);

    myColor->Reflection(MfxTextW("Reset"), 255, 0, 0, 0);
    myFlake_01->Reflection(MfxTextW("SetTitleColor"), myColor);

    MfxRect flakeRect(0, 0, 100, 100);
    myFlake_01->Reflection(MfxTextW("SetRect"), &flakeRect);

    myFlake_01->Reflection(MfxTextW("SetTitle"), MfxStringW(MfxTextW("MFX")));
    myFlake_01->Reflection(MfxTextW("OpenRButtonMove"));
    myFlake_01->Reflection(MfxTextW("OpenLButtonMove"));

    myUI_00->Reflection(MfxTextW("InsertFlake"), myFlake_01);

    MfxGlide myGlide;

    myGlide.SetFPS(90);
    myGlide.BindObject(myFlake_01);

    myGlide.BindObjectName(MfxTextW("group_1"),
        MfxGulid_WidelyType(MfxTextW("MfxSize"), MfxTextW("MfxSize"), MfxTextW("GetSize"), MfxTextW("SetSize")));
    myGlide.Add_GetSetFuncName(MfxTextW("group_1"), MfxTextW("GetWidth"), MfxTextW("SetWidth"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_1"), MfxTextW("GetHeight"), MfxTextW("SetHeight"));

    myGlide.BindObjectName(MfxTextW("group_2"),
        MfxGulid_WidelyType(MfxTextW("MfxPoint"), MfxTextW("MfxPoint"), MfxTextW("GetPoint"), MfxTextW("SetPoint")));
    myGlide.Add_GetSetFuncName(MfxTextW("group_2"), MfxTextW("GetX"), MfxTextW("SetX"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_2"), MfxTextW("GetY"), MfxTextW("SetY"));

    myGlide.BindObjectName(MfxTextW("group_3"),
        MfxGulid_WidelyType(MfxTextW("MfxColor"), MfxTextW("MfxColor"), MfxTextW("GetBackColor"), MfxTextW("SetBackColor")));
    myGlide.Add_GetSetFuncName(MfxTextW("group_3"), MfxTextW("GetA"), MfxTextW("SetA"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_3"), MfxTextW("GetR"), MfxTextW("SetR"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_3"), MfxTextW("GetG"), MfxTextW("SetG"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_3"), MfxTextW("GetB"), MfxTextW("SetB"));

    myGlide.BindObjectName(MfxTextW("group_4"),
        MfxGulid_WidelyType(MfxTextW("MfxColor"), MfxTextW("MfxColor"), MfxTextW("GetTitleColor"), MfxTextW("SetTitleColor")));
    myGlide.Add_GetSetFuncName(MfxTextW("group_4"), MfxTextW("GetA"), MfxTextW("SetA"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_4"), MfxTextW("GetR"), MfxTextW("SetR"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_4"), MfxTextW("GetG"), MfxTextW("SetG"));
    myGlide.Add_GetSetFuncName(MfxTextW("group_4"), MfxTextW("GetB"), MfxTextW("SetB"));

    MfxSize keySize(300, 300);
    myGlide.MfxAddKeyframe(MfxTextW("group_1"), &keySize, 1500);
    keySize.Reset(100, 100);
    myGlide.MfxAddKeyframe(MfxTextW("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxTextW("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxTextW("group_1"), &keySize, 1500);


    MfxPoint keyPoint(300, 0);
    myGlide.MfxAddKeyframe(MfxTextW("group_2"), &keyPoint, 1500);
    keyPoint.Reset(300, 300);
    myGlide.MfxAddKeyframe(MfxTextW("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 300);
    myGlide.MfxAddKeyframe(MfxTextW("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 0);
    myGlide.MfxAddKeyframe(MfxTextW("group_2"), &keyPoint, 1500);

    MfxColor keyColor(255, 0, 255, 255);
    myGlide.MfxAddKeyframe(MfxTextW("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 0, 0, 255);
    myGlide.MfxAddKeyframe(MfxTextW("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 50, 50, 50);
    myGlide.MfxAddKeyframe(MfxTextW("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 255, 0, 0);
    myGlide.MfxAddKeyframe(MfxTextW("group_3"), &keyColor, 1500);

    keyColor.Reset(255, 0, 0, 255);
    myGlide.MfxAddKeyframe(MfxTextW("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 0, 255, 255);
    myGlide.MfxAddKeyframe(MfxTextW("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 255);
    myGlide.MfxAddKeyframe(MfxTextW("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 0);
    myGlide.MfxAddKeyframe(MfxTextW("group_4"), &keyColor, 1500);

    myGlide.Begin();

    /**/
    myUI_00->Reflection(MfxTextW("WND_SHOW"));
    return MfxAppRun();
}