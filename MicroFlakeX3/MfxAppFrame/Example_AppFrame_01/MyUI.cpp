#include "MyUI.h"

MfxObject_Init_0(MyUI)
MfxObject_Init_1(MyUI, END)
MfxObject_Init_2(MyUI, MfxUI);

MyUI::MyUI()
{
	UI_ADDRECV_TIMER(10, 2000, MyUI::Test__000);
}

MfxReturn MyUI::MfxCallBack(Test__000)
{
	MessageBox(NULL, MfxText("Hello"), 0, 0);
	return MfxReturn();
}
