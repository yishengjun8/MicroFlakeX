#include "MyUI.h"



MFXOBJ_REFLECTION_INIT(MyUI)
MFXOBJ_REFLECTION_ENDINIT(MyUI, MfxUI);

MyUI::MyUI()
{
	MfxRect tRect(0, 0, 60, 60);

	myFlake.SetRect(&tRect); 

	this->InsertFlake(&myFlake);

	//myFlake.SetRect(&tRect);

	myFlake.OpenLButtonMove();


	UI_ADDRECV_TIMER(100, 1000, MyUI, Test__00);
	//InsertWin32Timer(Win32_Timer_Info(10, 2000, (pUIRecvFunc)&MyUI::Test__00));

	UI_ADDRECV_FLAKEEVENT(&myFlake, FLAKE_EVENT_LButtonClick, MyUI, Test__01);


	
}

MfxReturn MyUI::MFX_CALLBACK(Test__00)
{
	this->RemoveWin32Timer(100);

	MessageBox(myWnd, MfxText("Win32Timer"), MfxText("Test__000"), 0);

	return MfxReturn();
}

MfxReturn MyUI::MFX_CALLBACK(Test__01)
{
	MessageBox(NULL, MfxText("FLAKE_MSG_LButtonClick"), MfxText("Test__01"), 0);
	return MfxReturn();
}
