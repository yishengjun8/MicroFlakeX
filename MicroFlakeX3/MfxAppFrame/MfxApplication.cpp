#include "pch.h"
#include "MfxAppFramework.h"

MicroFlakeX::MfxApplication::MfxApplication()
{
	MfxCodeLock t_CodeLock(this);
	__MicroFlakeX::MfxRegApp(this);

	myUIMap_Value = nullptr;
	myInstance = GetModuleHandleW(NULL);

	WNDCLASSEX tempWC{ 0 };

	tempWC.cbSize = sizeof(WNDCLASSEX);
	tempWC.style = CS_HREDRAW | CS_VREDRAW;

	tempWC.lpfnWndProc = __MicroFlakeX::MfxAppProc;
	tempWC.cbClsExtra = 0;               // no extra class memory 
	tempWC.cbWndExtra = 0;                // no extra window memory
	tempWC.hInstance = myInstance;		//获取程序实例句柄

	tempWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // predefined app. icon 
	tempWC.hCursor = LoadCursor(NULL, IDC_ARROW);                // predefined arrow 
	tempWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

	//tempWC.lpszMenuName = L"MainMenu";    // name of menu resource
	tempWC.lpszClassName = L"MfxNormalUI";  // name of window class
	tempWC.hIconSm = LoadIconW(NULL, IDI_APPLICATION);  // small class icon 

	if (!RegisterClassEx(&tempWC))
	{
		MessageBox(NULL, L"MfxBasicsWindowClass Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
	}
}

MicroFlakeX::MfxApplication::~MfxApplication()
{
	MfxCodeLock t_CodeLock(this);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxApplication::Run()
{
	MSG appMsg;
	while (GetMessageW(&appMsg, NULL, 0, 0) > 0) {
		TranslateMessage(&appMsg);
		DispatchMessageW(&appMsg);
	}
	return appMsg.wParam;
}

HWND MicroFlakeX::MfxApplication::MfxCreateWindowExW(
	MfxUI* value, GdipRect gdiRect,
	DWORD dwExStyle, DWORD dwStyle,
	MfxStrW lpClassName, MfxStrW lpWindowName)
{
	MfxCodeLock t_CodeLock(this);

	myUIMap_Value = value;
	return CreateWindowExW(
		dwExStyle, lpClassName.c_str(), lpWindowName.c_str(), dwStyle,
		gdiRect.X, gdiRect.Y, gdiRect.Width, gdiRect.Height,
		NULL, NULL, myInstance, NULL
	);
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxApplication::ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);

	MfxUI_Map_iterator t_Itera = myUIMap.find(hWnd);
	if (t_Itera == myUIMap.end())
	{
		if (myUIMap_Value)
		{
			myUIMap.insert(MfxUI_Map_elem(hWnd, myUIMap_Value));
			myUIMap_Value->myWnd = hWnd;
			myUIMap_Value = nullptr;

			t_Itera = myUIMap.find(hWnd);
			if (t_Itera != myUIMap.end())
			{
				return (t_Itera->second)->ProcMessage(message, wParam, lParam);
			}
		}
	}
	else
	{
		if (message == WM_DESTROY)
		{
			MfxReturn ret = (t_Itera->second)->ProcMessage(message, wParam, lParam);
			myUIMap.erase(t_Itera);
			return ret;
		}
		else
		{
			return (t_Itera->second)->ProcMessage(message, wParam, lParam);
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxApplication::GetInstance(HINSTANCE* ret)
{
	*ret = myInstance;
	return MfxFine;
}