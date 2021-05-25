#include "pch.h"
#include "MfxAppFrame.h"

using namespace MicroFlakeX;


MfxApp* const MfxApp::g_pApp = new MfxApp;
HINSTANCE const MfxApp::g_hInstance = GetModuleHandle(NULL);

MicroFlakeX::MfxApp::MfxApp()
{
	if (g_pApp)
	{
		throw MfxText("MfxApp Object Exceeds One");
	}

	myBindingUI = nullptr;

	WNDCLASSEX tempWC{ 0 };

	tempWC.cbSize = sizeof(WNDCLASSEX);
	tempWC.style = CS_HREDRAW | CS_VREDRAW;

	tempWC.lpfnWndProc = AppProc;
	tempWC.cbClsExtra = 0;               // no extra class memory 
	tempWC.cbWndExtra = 0;                // no extra window memory
	tempWC.hInstance = g_hInstance;		//获取程序实例句柄

	tempWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // predefined app. icon 
	tempWC.hCursor = LoadCursor(NULL, IDC_ARROW);                // predefined arrow 
	tempWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

	tempWC.lpszMenuName = 0;     // name of menu resource
	tempWC.lpszClassName = MfxText("MfxNormalUI");  // name of window class
	tempWC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // small class icon 

	if (!RegisterClassEx(&tempWC))
	{
		MessageBox(NULL, MfxText("MfxNormalUI Registration Failed!"), MfxText("Error!"), MB_ICONEXCLAMATION | MB_OK);
	}
}

MicroFlakeX::MfxApp::~MfxApp()
{
	//删除全部UI - 并不需要
}

WPARAM MicroFlakeX::MfxApp::Run()
{
	MSG tMsg;
	while (GetMessage(&tMsg, NULL, 0, 0) > 0) 
	{
		TranslateMessage(&tMsg);
		DispatchMessage(&tMsg);
	}

	return tMsg.wParam;
}

HWND MicroFlakeX::MfxApp::MfxCreateUIEx(MfxUI* ui, MfxRect rect,
	DWORD dwExStyle, DWORD dwStyle, MfxString className, MfxString windowsName)
{
	while (myBindingUI);

	myBindingUI = ui;

	return CreateWindowEx(dwExStyle, className.c_str(), windowsName.c_str(), dwStyle,
		rect.myX, rect.myY, rect.myWidth, rect.myHeight, NULL, NULL, g_hInstance, NULL
	);
}


MfxReturn MicroFlakeX::MfxApp::ForwardMessage(HWND hWnd, MfxMessage message, WPARAM wParam, LPARAM lParam)
{
ForwardMessageBegin:
	auto t_Itera = myUIMap.find(hWnd);
	if (t_Itera == myUIMap.end())
	{
		if (myBindingUI)
		{
			MfxBeginNewThread(myBindingUI, MfxText("UIThread"), NULL, NULL);

			myUIMap.insert(App_UI_Info_Map_Elem(hWnd, new App_UI_Info(hWnd, myBindingUI, 0)));
			myBindingUI->myWnd = hWnd;
			myBindingUI = nullptr;

			goto ForwardMessageBegin;
		}
	}
	else
	{
		auto ret = t_Itera->second->myUI->ProcMessage(message,wParam, lParam);
		if (message == WM_DESTROY)
		{
			delete t_Itera->second;
			myUIMap.erase(t_Itera);
		}
		return ret;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT MicroFlakeX::MfxApp::AppProc(HWND hWnd, MfxMessage msg, WPARAM wParam, LPARAM lParam)
{
	return g_pApp->ForwardMessage(hWnd, msg, wParam, lParam);
}