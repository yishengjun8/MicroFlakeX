#include "MyUI.h"

MfxObject_Init(MyUI)
MfxObject_EndInit(MyUI, MfxUI);

MyUI::MyUI()
{
	this->InsertFlake(&myFlake);


	myFlake.OpenLButtonMove();

	InsertWin32Timer(Win32_Timer_Info(10, 5000, (pUIRecvFunc)&MyUI::Test__00));

	UI_ADDRECV_FLAKEMSG(&myFlake, FLAKE_MSG_LButtonClick, MyUI, Test__01);
}

MfxReturn MyUI::MfxCallBack(Test__00)
{
	MessageBox(NULL, MfxText("Hello"), MfxText("Test__000"), 0);

	return MfxReturn();
}

MfxReturn MyUI::MfxCallBack(Test__01)
{
	MessageBox(NULL, MfxText("Test__01"), MfxText("Test__01"), 0);
	return MfxReturn();
}
