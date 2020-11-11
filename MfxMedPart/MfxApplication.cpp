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

	myUICreatNow = nullptr;
}

MicroFlakeX::MfxApplication::~MfxApplication()
{
	/**/
	for (int i = 0; i < myUIList.size(); i++)
	{
		delete myUIList[i];
	}
	myUIList.clear();
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

void MicroFlakeX::MfxApplication::SetCreatUI(MfxUI* add)
{
	//if (!myUICreatNow)
		//throw L"Only one UI can be created at the same time";
	myUICreatNow = add;
}

void MicroFlakeX::MfxApplication::GetCreatUI(HWND uiWnd)
{
	if (myUICreatNow)
	{
		myUICreatNow->SetWnd(uiWnd);
		myUICreatNow = nullptr;
	}
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxApplication::RegUI(MfxUI* regUI)
{
	/**/
	if (regUI != nullptr)
	{
		myUIList.push_back(regUI);
		myServerMap.insert(MFXCONTROL_SERVER_MAP_ELEM(regUI->GetWnd(), regUI->GetMessageServer()));
		return MFXRETURE_OK;
	}
	return MFXRETURE_ERROR;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxApplication::DelUI(MfxUI* regUI)
{
	/**/
	MFXUI_LIST_ITERA tUIIt = myUIList.begin();
	for (; tUIIt != myUIList.end(); tUIIt++)
	{
		if (*tUIIt == regUI)
		{
			MFXCONTROL_SERVER_MAP_ITERA delIter = myServerMap.find(regUI->GetWnd());
			if (delIter != myServerMap.end())
			{
				myServerMap.erase(delIter);
			}
			myUIList.erase(tUIIt);
			return MFXRETURE_OK;
		}
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxApplication::ForwardMessageInWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//return DefWindowProc(hWnd, message, wParam, lParam);
	/**/
	MFXCONTROL_SERVER_MAP_ITERA handleIter = myServerMap.find(hWnd);
	if (handleIter == myServerMap.end())
	{
		this->GetCreatUI(hWnd);/* 注册当前 */
		//fprintf(gFileOut, "hWnd:%d, message:%d, wParam:%d, lParam:%d \n", (long)hWnd, (long)message, (long)wParam, (long)lParam);
		handleIter = myServerMap.find(hWnd);/* 注册完毕后重新寻址 */
		if (handleIter != myServerMap.end())
		{
			/* 优先给控件发消息 */
			(handleIter->second)->ForwardMessageToControl(message, wParam, lParam);
			/* 然后是UI接收消息 */
			return (handleIter->second)->GetMyUI()->RecUIMessage(message, wParam, lParam);
		}
	}
	else
	{
		/* 优先给控件发消息 */
		(handleIter->second)->ForwardMessageToControl(message, wParam, lParam);
		/* 然后是UI接收消息 */
		return (handleIter->second)->GetMyUI()->RecUIMessage(message, wParam, lParam);
	}
	/**/
	return DefWindowProc(hWnd, message, wParam, lParam);
}