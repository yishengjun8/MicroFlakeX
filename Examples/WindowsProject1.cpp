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
	//MyUI a2(Rect(180, 180, 500, 309), MFXWINDTYPE_NORMAL, L"My Name is a2");

	MfxImage a1_Back(a1.GetDefGraphics(), (WCHAR*)L"blackwall.jpg");
	//MfxImage a2_Back(a2.GetDefGraphics(), (WCHAR*)L"blacksmoke.jpg");

	MfxImage a1_Mask(a1.GetDefGraphics(), Color(40, 255, 255, 255));
	
	a1.UISetBack(&a1_Back);
	//a2.UISetBack(&a2_Back);

	a1.UISetMask(&a1_Mask);

	return app.AppRun();
}