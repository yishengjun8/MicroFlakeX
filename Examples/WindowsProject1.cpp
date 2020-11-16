#include "MfxMedPart.h"
#include "MfxButton.h"
#pragma comment(lib,"MfxMedPart.lib")
using namespace MicroFlakeX;
using namespace Gdiplus;
#include "MyUI.h"

MfxApplication app;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	MyUI a1(Rect(100, 100, 500, 309), MFXWINDTYPE_NORMAL, L"My Name is a1");
	MyUI a2(Rect(180, 180, 500, 309), MFXWINDTYPE_NORMAL, L"My Name is a2");

	MfxImage a1_Back(a1.GetBuffGraphics(), (WCHAR*)L"blackwall.jpg");
	MfxImage a2_Back(a2.GetBuffGraphics(), (WCHAR*)L"blacksmoke.jpg");
	MfxImage a1_Mask(a1.GetBuffGraphics(), Color(40, 255, 255, 255), Rect(0, 0, 600, 600));
	
	a1.UISetBack(&a1_Back);
	a2.UISetBack(&a2_Back);
	a1.UISetMask(&a1_Mask);
	
	MfxButton a1_Button(&a1), a2_Button(&a2);

	MfxImage a2_Button_Back(a2.GetBuffGraphics(), (WCHAR*)L"whitepaper.jpg");
	a2_Button.SetBackImage(&a2_Button_Back);

	a1.RegControlEvent(&a1_Button, MFXCONTROLEVENT_LBUTTONCLICK, (MFXUI_FUNC)&MyUI::OnButton01Click);

	return app.AppRun();
}

