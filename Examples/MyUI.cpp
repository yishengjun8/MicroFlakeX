#include "MyUI.h"

MyUI::MyUI(Gdiplus::Rect theRect, DWORD dwStyle, std::wstring title, MfxUI* father)
	: MfxUI(theRect,  dwStyle, title, father)
{
	
}

MFXRETURE MyUI::OnButton01Click(WPARAM wParam, LPARAM lParam)
{
	MessageBox(myWnd, L"MFXCONTROLEVENT_LBUTTONCLICK", L"MFXCONTROLEVENT_LBUTTONCLICK", 0);
	return 0;
}
