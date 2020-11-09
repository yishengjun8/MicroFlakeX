# MicroFlakeX
一个运行在Windows上的简单的DirectUI库。

/* 目前比较简陋，是模仿Mfc制作的 */
/* 使用下面的代码测试是否正确运行 */

#include "MfxMedPart.h"

#pragma comment(lib,"MfxMedPart.lib")

using namespace MicroFlakeX;

MfxApplication app;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
)
{

	MfxUI* a1 = new MfxUI(Gdiplus::Rect(0, 0, 500, 500), MFXWINDTYPE_NORMAL,
		L"a1");
		
	MfxUI* a2 = new MfxUI(Gdiplus::Rect(100, 100, 200, 200), MFXWINDTYPE_NORMAL | MFXWINDTYPE_CHILD,
		L"a2", a1);
		
	MfxUI* a3 = new MfxUI(Gdiplus::Rect(10, 10, 200, 200), MFXWINDTYPE_NORMAL | MFXWINDTYPE_CHILD,
		L"a3", a1);

	MfxImage mytest(a1->GetBufferGraphics());
	
	mytest.LoadFromFile((WCHAR*)L"D:\\testt.png");

	a3->SetUIBack(&mytest);
	
	a1->SetUIBack(&mytest);

	return app.AppRun();
}
