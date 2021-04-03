#include "pch.h"
#include "MfxAppFrame.h"

MicroFlakeX::MfxApp* __theApp = nullptr;
HINSTANCE __theInstance = nullptr;

MfxObject_Init_0(MfxApp)
{
	__theApp = new MfxApp;
	__theInstance = GetModuleHandleW(NULL);
}
MfxObject_Init_1(MfxApp)
MfxObject_Init_2(MfxApp, MfxBase);

MfxApp*& MfxApp::theApp = __theApp;
const HINSTANCE& MfxApp::theInstance = __theInstance;

LRESULT MicroFlakeX::MfxApp::AppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam)
{
	return __theApp->ForwardMessage(hWnd, msg, wParam, lParam);
}

MicroFlakeX::MfxApp::MfxApp()
{
	if (__theApp)
	{
		throw L"MfxApp Object Exceeds One";
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

	//tempWC.lpszMenuName = L"MainMenu";    // name of menu resource
	tempWC.lpszClassName = L"MfxNormalUI";  // name of window class
	tempWC.hIconSm = LoadIconW(NULL, IDI_APPLICATION);  // small class icon 

	if (!RegisterClassExW(&tempWC))
	{
		MessageBoxW(NULL, L"MfxNormalUI Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
	}
}

MicroFlakeX::MfxApp::~MfxApp()
{
	//删除全部UI-并不需要
}

void MicroFlakeX::MfxApp::Run()
{
	MSG tMsg;
	while (GetMessageW(&tMsg, NULL, 0, 0) > 0) {
		TranslateMessage(&tMsg);
		DispatchMessageW(&tMsg);
	}
	overParam = tMsg.wParam;
}

HWND MicroFlakeX::MfxApp::MfxCreateUIExW(
	MfxUI* ui, MfxRect rect,
	DWORD dwExStyle, DWORD dwStyle,
	MfxStrW className, MfxStrW windowsName)
{
	while (myBindingUI);
	myBindingUI = ui; 
	return CreateWindowExW(
		dwExStyle, className.c_str(), windowsName.c_str(), dwStyle,
		rect.myX, rect.myY, rect.myWidth, rect.myHeight, NULL, NULL, __theInstance, NULL
	);
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxApp::ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam)
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
				return (t_Itera->second)->ProcMessage(message, wParam, lParam);
			}
		}
	}
	else
	{
		return (t_Itera->second)->ProcMessage(message, wParam, lParam);
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}