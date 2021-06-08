#include "MyUI.h"

MfxObject_Init(MyUI)
MfxObject_EndInit(MyUI, MfxUI);

MyUI::MyUI()
{
	MfxRect tRect(0, 0, 60, 60);

	myFlake.SetRect(&tRect); 

	this->InsertFlake(&myFlake);

	//myFlake.SetRect(&tRect);

	myFlake.OpenLButtonMove();

	//InsertWin32Timer(Win32_Timer_Info(10, 2000, (pUIRecvFunc)&MyUI::Test__00));

	UI_ADDRECV_FLAKEMSG(&myFlake, FLAKE_EVENT_LButtonClick, MyUI, Test__01);


	
}

MfxReturn MyUI::MfxCallBack(Test__00)
{
	MessageBox(myWnd, MfxText("Win32Timer"), MfxText("Test__000"), 0);

	return MfxReturn();
}

MfxReturn MyUI::MfxCallBack(Test__01)
{
	MessageBox(NULL, MfxText("FLAKE_MSG_LButtonClick"), MfxText("Test__01"), 0);
	return MfxReturn();
}
