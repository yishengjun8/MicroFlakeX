# MicroFlakeX
一个运行在Windows上的简单的DirectUI库。

/* 目前比较简陋，是模仿Mfc制作的 */
/* 使用下面的代码测试是否正确运行 */
#include "MfxMedPart.h"
#pragma comment(lib,"MfxMedPart.lib")
using namespace MicroFlakeX;

MfxApplication app;

int main()
{
	MfxUI* a1 = new MfxUI(Gdiplus::Rect(50, 50, 400, 400), MFXWINDTYPE_NORMAL, nullptr,
		L"a1");
	MfxUI* a2 = new MfxUI(Gdiplus::Rect(100, 100, 400, 400), MFXWINDTYPE_NORMAL | MFXWINDTYPE_CHILD, a1,
		L"a2");

	MfxUI* a3 = new MfxUI(Gdiplus::Rect(150, 150, 400, 400));
	delete a3;

	return app.AppRun();
}
