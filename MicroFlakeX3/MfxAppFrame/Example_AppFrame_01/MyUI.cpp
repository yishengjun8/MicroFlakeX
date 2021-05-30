#include "MyUI.h"

MfxObject_Init_0(MyUI)
MfxObject_Init_1(MyUI, END)
MfxObject_Init_2(MyUI, MfxUI);

MyUI::MyUI()
{
	this->InsertFlake(&myFlake);


	myFlake.OpenLButtonMove();

	//UI_ADDRECV_TIMER(10, 2000, MyUI::Test__000);
	InsertWin32Timer(Win32_Timer_Info(10, 5000, (pUIRecvFunc)&MyUI::Test__00));

	UI_ADDRECV_FLAKEMSG(&myFlake, FLAKE_MSG_LButtonClick, MyUI, Test__01);
}

MfxReturn MyUI::MfxCallBack(Test__00)
{
	MessageBox(NULL, MfxText("Hello"), MfxText("Test__000"), 0);

	//MyUI myUI;


	return MfxReturn();
}

MfxReturn MyUI::MfxCallBack(Test__01)
{
	MessageBox(NULL, MfxText("Test__01"), MfxText("Test__01"), 0);
	return MfxReturn();
}
