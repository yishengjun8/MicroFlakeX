#include <iostream>
#include "MicroFlakeX.h"

using namespace std;
using namespace MicroFlakeX;

int main()
{
    MfxBase* myUI_00 = nullptr;
    MfxBase* myColor = nullptr;
    MfxBase* myFlake_01 = nullptr;

    MfxFactory(MFX_TXT_W("MfxUI"), &myUI_00);
    MfxFactory(MFX_TXT_W("MfxFlake"), &myFlake_01);
    MfxFactory(MFX_TXT_W("MfxColor"), &myColor);

    /**/
    MfxSignal mySignal, myTestSignal;
    MfxClient myClient;

    myTestSignal.PushBackReceiver(myColor, MFX_TXT_W("Reset"));

    mySignal.PushBackReceiver(myUI_00, MFX_TXT_W("SetBackColor"));
    myClient.PushBackReceiver(myUI_00);

    MfxSize uiSize(600, 600);
    myClient.PostClient(MFX_TXT_W("SetSize"), &uiSize);

    myColor->Reflection(MFX_TXT_W("Reset"), 255, 255, 0, 0);
    //myTestSignal.PostSignal(255, 255, 0, 0);
    Sleep(10);
    mySignal.SendSignal(myColor);


    myColor->Reflection(MFX_TXT_W("Reset"), 255, 255, 255, 255);
    myFlake_01->Reflection(MFX_TXT_W("SetBackColor"), myColor);

    myColor->Reflection(MFX_TXT_W("Reset"), 255, 0, 0, 0);
    myFlake_01->Reflection(MFX_TXT_W("SetTitleColor"), myColor);

    MfxRect flakeRect(0, 0, 100, 100);
    myFlake_01->Reflection(MFX_TXT_W("SetRect"), &flakeRect);

    myFlake_01->Reflection(MFX_TXT_W("SetTitle"), MfxStringW(MFX_TXT_W("MFX")));
    myFlake_01->Reflection(MFX_TXT_W("OpenRButtonMove"));
    myFlake_01->Reflection(MFX_TXT_W("OpenLButtonMove"));

    myUI_00->Reflection(MFX_TXT_W("InsertFlake"), myFlake_01);

    MfxGlide myGlide;

    myGlide.SetFPS(90);
    myGlide.BindObject(myFlake_01);

    myGlide.BindObjectName(MFX_TXT_W("group_1"),
        MfxGulid_WidelyType(MFX_TXT_W("MfxSize"), MFX_TXT_W("MfxSize"), MFX_TXT_W("GetSize"), MFX_TXT_W("SetSize")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_1"), MFX_TXT_W("GetWidth"), MFX_TXT_W("SetWidth"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_1"), MFX_TXT_W("GetHeight"), MFX_TXT_W("SetHeight"));

    myGlide.BindObjectName(MFX_TXT_W("group_2"),
        MfxGulid_WidelyType(MFX_TXT_W("MfxPoint"), MFX_TXT_W("MfxPoint"), MFX_TXT_W("GetPoint"), MFX_TXT_W("SetPoint")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_2"), MFX_TXT_W("GetX"), MFX_TXT_W("SetX"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_2"), MFX_TXT_W("GetY"), MFX_TXT_W("SetY"));

    myGlide.BindObjectName(MFX_TXT_W("group_3"),
        MfxGulid_WidelyType(MFX_TXT_W("MfxColor"), MFX_TXT_W("MfxColor"), MFX_TXT_W("GetBackColor"), MFX_TXT_W("SetBackColor")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetA"), MFX_TXT_W("SetA"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetR"), MFX_TXT_W("SetR"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetG"), MFX_TXT_W("SetG"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetB"), MFX_TXT_W("SetB"));

    myGlide.BindObjectName(MFX_TXT_W("group_4"),
        MfxGulid_WidelyType(MFX_TXT_W("MfxColor"), MFX_TXT_W("MfxColor"), MFX_TXT_W("GetTitleColor"), MFX_TXT_W("SetTitleColor")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetA"), MFX_TXT_W("SetA"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetR"), MFX_TXT_W("SetR"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetG"), MFX_TXT_W("SetG"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetB"), MFX_TXT_W("SetB"));

    MfxSize keySize(300, 300);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);
    keySize.Reset(100, 100);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);


    MfxPoint keyPoint(300, 0);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);
    keyPoint.Reset(300, 300);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 300);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 0);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);

    MfxColor keyColor(255, 0, 255, 255);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 0, 0, 255);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 50, 50, 50);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 255, 0, 0);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);

    keyColor.Reset(255, 0, 0, 255);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 0, 255, 255);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 255);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 0);
    myGlide.MfxAddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);

    myGlide.Begin();

    /**/


    myUI_00->Reflection(MFX_TXT_W("WND_SHOW"));
    return MfxAppRun();
}