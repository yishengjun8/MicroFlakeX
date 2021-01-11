#include "MyUI.h"

MyUI::MyUI(Gdiplus::Rect theRect, DWORD dwStyle, std::wstring title, MfxUI* father)
	: MfxUI(theRect,  dwStyle, title, father)
{
	MfxButton* myButton = new MfxButton(this);
	myButton->SetTitle(L"这是第一个创建的");
	MfxButton* myButton2 = new MfxButton(this);
	myButton2->SetTitle(L"这是第二个，按理来说后创建的应该压住前面的");

	myButton->SetFloor(30);
	//myButton2->SetFloor(2);
	this->RegControlEvent(myButton, MFXCONTROLEVENT_LBUTTONCLICK, (MFXUI_FUNC)&MyUI::OnButton01Click);
}

MFXRETURE MyUI::OnButton01Click(WPARAM wParam, LPARAM lParam)
{
	MessageBox(myWnd, L"！我被点击了！", L"MFXCONTROLEVENT_LBUTTONCLICK", 0);
	return 0;
}