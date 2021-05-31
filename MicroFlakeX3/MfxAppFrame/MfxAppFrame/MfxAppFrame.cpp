#include "pch.h"
#include "MfxAppFrame.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;


const auto g_Handle = GetModuleHandle(NULL);

App_UI_Info_Map myUIMap;

pMfxUI myBindingUI;

WPARAM MicroFlakeX::MfxAppRun()
{
	MSG tMsg;
	while (GetMessage(&tMsg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&tMsg);
		DispatchMessage(&tMsg);
	}

	return tMsg.wParam;
}

HWND __MicroFlakeX::MfxCreateWindowsEx(pMfxUI ui, pMfxUI father, MfxRect rect,
	DWORD dwStyle, DWORD dwExStyle, MfxString className, MfxString windowsName)
{
	while (myBindingUI);

	myBindingUI = ui;

	HWND f_hWnd = NULL;
	father ? father->GetWnd(&f_hWnd) : 0;

	return CreateWindowEx(dwExStyle, className.c_str(), windowsName.c_str(), dwStyle,
		rect.myX, rect.myY, rect.myWidth, rect.myHeight, f_hWnd, NULL, g_Handle, NULL
	);
}

LRESULT CALLBACK __MicroFlakeX::MfxAppFrameProc(HWND hWnd, MfxMessage message, WPARAM wParam, LPARAM lParam)
{
ForwardMessageBegin:
	auto t_Itera = myUIMap.find(hWnd);
	if (t_Itera == myUIMap.end())
	{
		if (myBindingUI)
		{
			myUIMap.insert(App_UI_Info_Map_Elem(hWnd, App_UI_Info(hWnd, myBindingUI)));
			myBindingUI = nullptr;

			goto ForwardMessageBegin;
		}
	}
	else
	{
		MAKE_WIN32_PARAM(win32, message, hWnd, wParam, lParam);

		auto ret = t_Itera->second.myUI->Send_Message(win32);
		if (message == WM_DESTROY)
		{
			myUIMap.erase(t_Itera);
		}
		return ret;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}