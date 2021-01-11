#include "pch.h"
#include "MfxMedPart.h"

/*
#include "cstdio"
using namespace std;
FILE* gFileOut;
/**/

MicroFlakeX::MfxApplication::MfxApplication()
{
	/**/
	//fopen_s(&gFileOut, "D:\\out.txt", "wb");
	MfxGlobleApplication(this); //注册全局唯一
	appInstance = GetModuleHandleW(NULL); //获取程序实例句柄

	WNDCLASSEX tempWC{0};

	tempWC.cbSize = sizeof(WNDCLASSEX);
	tempWC.style = CS_HREDRAW | CS_VREDRAW;

	tempWC.lpfnWndProc = MfxWndProc;
	tempWC.cbClsExtra = 0;               // no extra class memory 
	tempWC.cbWndExtra = 0;                // no extra window memory
	tempWC.hInstance = appInstance;		//获取程序实例句柄

	tempWC.hIcon = LoadIcon(NULL,IDI_APPLICATION);             // predefined app. icon 
	tempWC.hCursor = LoadCursor(NULL,IDC_ARROW);                // predefined arrow 
	tempWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	//tempWC.lpszMenuName = L"MainMenu";    // name of menu resource
	tempWC.lpszClassName = L"MfxNormal";  // name of window class
	tempWC.hIconSm = LoadIconW(NULL, IDI_APPLICATION);  // small class icon 

	if (!RegisterClassEx(&tempWC)) 
	{
		MessageBox(NULL, L"MfxBasicsWindowClass Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
	}

	//appWndClass.insert(WNDCLASSEXW_MAP_ELEM(L"MfxNormal", L"MfxNormal"));
	/**/

	myBindingUI = nullptr;
}

MicroFlakeX::MfxApplication::~MfxApplication()
{
	/**/
	for (MFXUI_MAPITERA itUI = myUIMap.begin(); itUI != myUIMap.end(); itUI++)
	{
		delete (itUI->second);
	}
	myUIMap.clear();
	/**/
}

int MicroFlakeX::MfxApplication::AppRun()
{
	/**/
	MSG appMsg; //消息
	while (GetMessageW(&appMsg, NULL, 0, 0) > 0) {
		TranslateMessage(&appMsg);
		DispatchMessageW(&appMsg);
		//MessageBoxW(NULL, L"GetMessageW!", L"GetMessageW!", MB_OK);
	}
	return appMsg.wParam;
	/**/
	return 0;
}

HINSTANCE MicroFlakeX::MfxApplication::GetInstance()
{
	return appInstance;
}

void MicroFlakeX::MfxApplication::LoadBindingUI(MfxUI* bind)
{
	myBindingUI = bind;
}

void MicroFlakeX::MfxApplication::BindUIWithWnd(HWND uiWnd)
{
	if (myBindingUI)
	{
		myBindingUI->SetWnd(uiWnd);
		myBindingUI = nullptr;
	}
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxApplication::RegUI(MfxUI* regUI)
{
	/**/
	MFXUI_MAPPAIR retPair = myUIMap.insert(MFXUI_MAPELEM(regUI->GetWnd(), regUI));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxApplication::DelUI(MfxUI* regUI)
{
	/**/
	MFXUI_MAPITERA tUIIt = myUIMap.find(regUI->GetWnd());
	if (tUIIt != myUIMap.end())
	{
		myUIMap.erase(tUIIt);
		return MFXRETURE_OK;
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxApplication::ForwardMessageByWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//return DefWindowProc(hWnd, message, wParam, lParam);
	/**/
	MFXUI_MAPITERA handleIter = myUIMap.find(hWnd);
	if (handleIter == myUIMap.end())
	{
		this->BindUIWithWnd(hWnd);/* 绑定UI到Wnd */

		handleIter = myUIMap.find(hWnd);/* 注册完毕后重新寻址 */
		if (handleIter != myUIMap.end())
		{
			/* UI接收消息 */
			return (handleIter->second)->RecvUIMessage(message, wParam, lParam);
		}
	}
	else
	{
		/* UI接收消息 */
		return (handleIter->second)->RecvUIMessage(message, wParam, lParam);
	}
	/**/
	return DefWindowProc(hWnd, message, wParam, lParam);
}