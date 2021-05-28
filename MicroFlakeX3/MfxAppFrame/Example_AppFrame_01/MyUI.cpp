#include "MyUI.h"

MfxObject_Init_0(MyUI)
MfxObject_Init_1(MyUI, END)
MfxObject_Init_2(MyUI, MfxUI);

MyUI::MyUI()
{
	this->InsertFlake(&myFlake);


	myFlake.OpenLButtonMove();

	//UI_ADDRECV_TIMER(10, 2000, MyUI::Test__000);

	InsertTimer(UI_UITimer_Info(10, 2000, (pUIRecvFunc)&MyUI::Test__000));

	//InsertFlakeMessage(UI_FLAKEMSG_Infor(myFlake, FLAKE_MSG_LButtonClick), UIMSG_RecvFunc_Infor((pUIRecvFunc)&MyUI::Test__000, 1, MfxText("Test__000")));
	//UI_ADDRECV_FLAKEMSG(&myFlake, FLAKE_MSG_LButtonClick, MyUI, Test__000, 10);
}

MfxReturn MyUI::MfxCallBack(Test__000)
{
	MessageBox(NULL, MfxText("Hello"), MfxText("Test__000"), 0);

	//MyUI myUI;


	return MfxReturn();
}
