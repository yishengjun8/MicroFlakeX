#include "pch.h"
#include "MfxAppFrame.h"

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

HWND __MicroFlakeX::MfxCreateWindowsEx(MfxUI* ui, MfxUI* father, MfxRect rect,
	DWORD dwStyle, DWORD dwExStyle, MfxString className, MfxString windowsName)
{
	HWND f_hWnd = NULL;

	//Ê¼ÖÕºöÂÔfather²ÎÊı
	//father ? father->GetWnd(&f_hWnd) : 0;

	return CreateWindowEx(dwExStyle, className.c_str(), windowsName.c_str(), dwStyle,
		rect.myX, rect.myY, rect.myWidth, rect.myHeight, f_hWnd, NULL, GetModuleHandle(NULL), ui
	);
}

LRESULT CALLBACK __MicroFlakeX::MfxAppFrameProc(HWND hWnd, MfxMessage message, WPARAM wParam, LPARAM lParam)
{
	static App_UI_Info_Map myUIMap;

	auto t_Itera = myUIMap.find(hWnd);
	if (t_Itera == myUIMap.end())
	{
		if (message != WM_CREATE)
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		else
		{
			MfxUI* myBind = (MfxUI*)((LPCREATESTRUCTA)lParam)->lpCreateParams;
			myUIMap.insert(App_UI_Info_Map_Elem(hWnd, App_UI_Info(hWnd, myBind)));

			MAKE_WIN32_PARAM(win32, message, hWnd, wParam, lParam);
			return myBind->Send_Message(win32);
		}
	}
	else
	{
		MAKE_WIN32_PARAM(win32, message, hWnd, wParam, lParam);
		MfxReturn ret = t_Itera->second.myUI->Send_Message(win32);

		message == WM_DESTROY ? myUIMap.erase(t_Itera)->first : 0;

		return ret;
	}
}