#include "MyUI.h"

//MFXOBJ_REFLECTION_INIT(MyUI)
//MFXOBJ_REFLECTION_ENDINIT(MyUI, MfxUI);

MyUI::MyUI()
{
	UI_ADDFLAKE(&myFlake);

	MfxRect tRect(0, 0, 60, 60);

	myFlake.SetRect(&tRect); 
	myFlake.OpenLButtonMove();


	UI_ADDRECV_TIMER(100, 1000, MyUI, Test__00);
	UI_ADDRECV_FLAKEEVENT(&myFlake, FLAKE_EVENT_LButtonClick, MyUI, Test__01);
}

MfxReturn MyUI::MFX_CALLBACK(Test__00)
{
	UI_DELRECV_TIMER(100);

	MessageBox(myWnd, MfxText("Win32Timer"), MfxText("Test__000"), 0);

	MfxParam tParam = MFX_MAKE_PARAM(NULL, 100, 90, MfxPoint(100, 100), 70, 60);

	Test__02(tParam);

	return MfxReturn_Seccess;
}

MfxReturn MyUI::MFX_CALLBACK(Test__01)
{
	MessageBox(NULL, MfxText("FLAKE_MSG_LButtonClick"), MfxText("Test__01"), 0);

	return MfxReturn_Seccess;
}

MfxReturn MyUI::MFX_CALLBACK(Test__02)
{
	std::cout << getParam_0(int) << std::endl;
	std::cout << getParam_1(int) << std::endl;

	MfxPoint a = getParam_2(MfxPoint);

	std::cout << a.myX << a.myY << std::endl;

	return MfxReturn_Seccess;
}
