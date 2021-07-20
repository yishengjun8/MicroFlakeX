#include "MyUI.h"

//MFXOBJ_REFLECTION_INIT(MyUI)
//MFXOBJ_REFLECTION_ENDINIT(MyUI, MfxUI);

MyUI::MyUI()
{
	UI_ADDFLAKE(&myFlake);

	MfxRect tRect(0, 0, 60, 60);

	myFlake.SetRect(&tRect); 
	myFlake.OpenLButtonMove();

	//UI_ADDRECV_TIMER(100, 1000, MyUI, Test__00);
	UI_ADDRECV_FLAKEEVENT(&myFlake, FLAKE_EVENT_LButtonClick, MyUI, LButtonClick);
    UI_ADDRECV_FLAKEEVENT(&myFlake, FLAKE_EVENT_RButtonClick, MyUI, RButtonClick);

    myGlide.SetFPS(60);
    myGlide.BindObject(&myFlake);

    myGlide.BindObjectName(MFX_TXT_W("group_1"),
        MfxGulid_GroupDetails(MFX_TXT_W("MfxSize"), MFX_TXT_W("MfxSize"), MFX_TXT_W("GetSize"), MFX_TXT_W("SetSize")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_1"), MFX_TXT_W("GetWidth"), MFX_TXT_W("SetWidth"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_1"), MFX_TXT_W("GetHeight"), MFX_TXT_W("SetHeight"));

    myGlide.BindObjectName(MFX_TXT_W("group_2"),
        MfxGulid_GroupDetails(MFX_TXT_W("MfxPoint"), MFX_TXT_W("MfxPoint"), MFX_TXT_W("GetPoint"), MFX_TXT_W("SetPoint")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_2"), MFX_TXT_W("GetX"), MFX_TXT_W("SetX"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_2"), MFX_TXT_W("GetY"), MFX_TXT_W("SetY"));

    myGlide.BindObjectName(MFX_TXT_W("group_3"),
        MfxGulid_GroupDetails(MFX_TXT_W("MfxColor"), MFX_TXT_W("MfxColor"), MFX_TXT_W("GetBackColor"), MFX_TXT_W("SetBackColor")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetA"), MFX_TXT_W("SetA"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetR"), MFX_TXT_W("SetR"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetG"), MFX_TXT_W("SetG"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_3"), MFX_TXT_W("GetB"), MFX_TXT_W("SetB"));

    myGlide.BindObjectName(MFX_TXT_W("group_4"),
        MfxGulid_GroupDetails(MFX_TXT_W("MfxColor"), MFX_TXT_W("MfxColor"), MFX_TXT_W("GetTitleColor"), MFX_TXT_W("SetTitleColor")));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetA"), MFX_TXT_W("SetA"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetR"), MFX_TXT_W("SetR"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetG"), MFX_TXT_W("SetG"));
    myGlide.Add_GetSetFuncName(MFX_TXT_W("group_4"), MFX_TXT_W("GetB"), MFX_TXT_W("SetB"));

    MfxSize keySize(300, 300);
    myGlide.AddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);
    keySize.Reset(100, 100);
    myGlide.AddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);
    keySize.Reset(300, 300);
    myGlide.AddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);
    keySize.Reset(100, 100);
    myGlide.AddKeyframe(MFX_TXT_W("group_1"), &keySize, 1500);


    MfxPoint keyPoint(300, 0);
    myGlide.AddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);
    keyPoint.Reset(300, 300);
    myGlide.AddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 300);
    myGlide.AddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);
    keyPoint.Reset(0, 0);
    myGlide.AddKeyframe(MFX_TXT_W("group_2"), &keyPoint, 1500);

    MfxColor keyColor(255, 0, 255, 255);
    myGlide.AddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 0, 0, 255);
    myGlide.AddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 50, 50, 50);
    myGlide.AddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);
    keyColor.Reset(255, 255, 0, 0);
    myGlide.AddKeyframe(MFX_TXT_W("group_3"), &keyColor, 1500);

    keyColor.Reset(255, 0, 0, 255);
    myGlide.AddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 0, 255, 255);
    myGlide.AddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 255);
    myGlide.AddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);
    keyColor.Reset(255, 255, 255, 0);
    myGlide.AddKeyframe(MFX_TXT_W("group_4"), &keyColor, 1500);

    myGlide.Begin();
    /**/
}

MfxReturn MyUI::MFX_CALLBACK(Test__00)
{
	UI_DELRECV_TIMER(100);

	MessageBox(myWnd, MFX_TXT_W("Win32Timer"), MFX_TXT_W("Test__000"), 0);

	//Test__02(MFX_MAKE_PARAM(100, 90, MfxPoint(100, 100), 70, 60));

	return MFX_RET_SECCESS;
}

MfxReturn MyUI::MFX_CALLBACK(LButtonClick)
{
	//MessageBox(NULL, MFX_TXT_W("FLAKE_MSG_LButtonClick"), MFX_TXT_W("Test__01"), 0);

    MfxRect tRect;
    myFlake.GetRect(&tRect);
    std::cout <<"MFX_CALLBACK(LButtonClick)" << tRect.myX << "  " << tRect.myY << std::endl;

    myGlide.Begin();

	return MFX_RET_SECCESS;
}

MfxReturn MyUI::MFX_CALLBACK(RButtonClick)
{
    myGlide.Stop();

    return MFX_RET_SECCESS;
}

MfxReturn MyUI::MFX_CALLBACK(Test__02)
{
	std::cout << MFXPARAM_GET_0(int) << std::endl;
	std::cout << MFXPARAM_GET_1(int) << std::endl;

	MfxPoint a = MFXPARAM_GET_2(MfxPoint);

	std::cout << a.myX << a.myY << std::endl;

	return MFX_RET_SECCESS;
}
