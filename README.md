# MicroFlakeX

* 一个运行在`Windows`上的简单`DirectUI`库。
* `MicroFlakeX`可以让你远离复杂的框架，极其简单且快速的开发一些轻量级的`Win桌面应用`

## 请使用下面的代码测试是否正确运行
```cpp
#include "MfxMedPart.h"
#include "MfxButton.h"
#pragma comment(lib,"MfxMedPart.lib")
using namespace MicroFlakeX;

MfxApplication app;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
){
	MfxUI a1(Gdiplus::Rect(100, 100, 250, 250), MFXWINDTYPE_NORMAL, L"My Name is a1");
	MfxUI a2(Gdiplus::Rect(180, 180, 250, 250), MFXWINDTYPE_NORMAL, L"My Name is a2");

	MfxImage a1_Back(a1.GetBuffGraphics(), (WCHAR*)L"D:\\image\\blackwall.jpg");
	MfxImage a2_Back(a2.GetBuffGraphics(), (WCHAR*)L"D:\\image\\blacksmoke.jpg");
	MfxImage a1_Mask(a1.GetBuffGraphics(), Gdiplus::Color(40, 184, 61, 186), Gdiplus::Rect(0, 0, 600, 600));

	a1.UISetBack(&a1_Back);
	a2.UISetBack(&a2_Back);
	a1.UISetMask(&a1_Mask);
	
	MfxButton a1_Button(&a1);
	MfxButton a2_Button(&a2);

	MfxImage a2_Button_Back(a2.GetBuffGraphics(), (WCHAR*)L"D:\\image\\whitepaper.jpg");

	a2_Button.SetBackImage(&a2_Button_Back);

	return app.AppRun();
}
```

## 未来的控件计划：
  MfxButton.h、MfxMenu.h、MfxForm、MfxEdit.h、MfxRadioButton、MfxCheckButton.h

## 注意事项：
  当你注册消息或事件的时候，请注意添加`MfxRecDefMessage`或者`DefWindowProc`来确保缺省的消息也正常响应！  
  目前的`MicroFlakeX不是多线程`，也就是说可能会存在界面卡死的问题！请注意！
