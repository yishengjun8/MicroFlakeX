#include "pch.h"
#include "MfxAppFrame.h"

MicroFlakeX::MfxApp* __theApp = nullptr;
HINSTANCE __theInstance = nullptr;

MfxObject_Init_0(MfxApp)
{
	__theApp = new MfxApp;
	__theInstance = GetModuleHandle(NULL);
}
MfxObject_Init_1(MfxApp, END)
MfxObject_Init_2(MfxApp, MfxBase);

MfxApp*& MfxApp::theApp = __theApp;
const HINSTANCE& MfxApp::theInstance = __theInstance;

MicroFlakeX::MfxApp::MfxApp()
{
	if (__theApp)
	{
		throw MfxText("MfxApp Object Exceeds One");
	}

	overParam = 0;
	myBindingUI = nullptr;

	WNDCLASSEX tempWC{ 0 };

	tempWC.cbSize = sizeof(WNDCLASSEX);
	tempWC.style = CS_HREDRAW | CS_VREDRAW;

	tempWC.lpfnWndProc = AppProc;
	tempWC.cbClsExtra = 0;               // no extra class memory 
	tempWC.cbWndExtra = 0;                // no extra window memory
	tempWC.hInstance = __theInstance;		//获取程序实例句柄

	tempWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // predefined app. icon 
	tempWC.hCursor = LoadCursor(NULL, IDC_ARROW);                // predefined arrow 
	tempWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

	//tempWC.lpszMenuName = MfxTextMainMenu";    // name of menu resource
	tempWC.lpszClassName = MfxText("MfxNormalUI");  // name of window class
	tempWC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // small class icon 

	if (!RegisterClassEx(&tempWC))
	{
		MessageBox(NULL, MfxText("MfxNormalUI Registration Failed!"), MfxText("Error!"), MB_ICONEXCLAMATION | MB_OK);
	}
}

MicroFlakeX::MfxApp::~MfxApp()
{
	//删除全部UI-并不需要
}

WPARAM MicroFlakeX::MfxApp::Run()
{
	MSG tMsg;
	while (GetMessage(&tMsg, NULL, 0, 0) > 0) {
		TranslateMessage(&tMsg);
		DispatchMessage(&tMsg);
	}
	overParam = tMsg.wParam;
	return tMsg.wParam;
}

HWND MicroFlakeX::MfxApp::MfxCreateUIEx(MfxUI* ui, MfxRect rect,
	DWORD dwExStyle, DWORD dwStyle,
	MfxString className, MfxString windowsName)
{
	while (myBindingUI);
	myBindingUI = ui; 
	return CreateWindowEx(
		dwExStyle, className.c_str(), windowsName.c_str(), dwStyle,
		rect.myX, rect.myY, rect.myWidth, rect.myHeight, NULL, NULL, __theInstance, NULL
	);
}


MfxReturn MicroFlakeX::MfxApp::ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam)
{
	auto t_Itera = myUIMap.find(hWnd);
	if (t_Itera == myUIMap.end())
	{
		if (myBindingUI)
		{
			myUIMap.insert(MfxUI_Map_elem(hWnd, myBindingUI));
			myBindingUI->myWnd = hWnd;
			myBindingUI = nullptr;

			t_Itera = myUIMap.find(hWnd);
			if (t_Itera != myUIMap.end())
			{
				auto ret = (t_Itera->second)->ProcMessage(message, wParam, lParam);
				if (message == WM_DESTROY)
				{
					myUIMap.erase(t_Itera);
				}
				return ret;
			}
		}
	}
	else
	{
		auto ret = (t_Itera->second)->ProcMessage(message, wParam, lParam);
		if (message == WM_DESTROY)
		{
			myUIMap.erase(t_Itera);
		}
		return ret;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT MicroFlakeX::MfxApp::AppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam)
{
	return __theApp->ForwardMessage(hWnd, msg, wParam, lParam);
}