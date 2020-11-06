#include "pch.h"
#include "MfxMedPart.h"

MicroFlakeX::MfxUI::MfxUI(
	Gdiplus::Rect theRect,
	DWORD dwStyle,
	std::wstring titleName,
	MfxUI* father,
	std::wstring wndClassName
	)
{
	myWnd = NULL;
	myMainDc = NULL; //UI的主画板 - 需要释放
	myBufferDc = NULL; //用于双缓冲 - 需要释放
	myGraphics = NULL; //UI绘画类，指向UI的缓冲区 - 需要释放
	myMessageServer = NULL; //UI窗口消息服务器 - 需要释放
	myWndCreateSuccess = true;
	
	myWnd = CreateWindow(wndClassName.c_str(), NULL, dwStyle | WS_MINIMIZE,
		theRect.X, theRect.Y,
		theRect.Width, theRect.Height,
		father ? father->GetWnd() : NULL, 
		NULL, MfxFunc_GetApp()->GetInstance(), NULL);

	if (myWnd == NULL)
	{
		std::wstring tOut = L"Window Creation Failed!\n  >>wndClassName: ";
		tOut += wndClassName;
		tOut += L"  >>titleName: \n";
		tOut += titleName.c_str();
		MessageBox(NULL, tOut.c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
		myWndCreateSuccess = false;
	}
	else
	{
		myMainDc = GetDC(myWnd); //UI的主画板
		myBufferDc = MfxFunc_GetComhDC(myMainDc, Gdiplus::Size(theRect.Width, theRect.Height)); //UI缓冲区-用于双缓冲
		myRect = theRect; //UI的大小 - 会随窗口大小而自动调整
		myGraphics = MfxFunc_GetGraphics(myBufferDc); //UI绘画类，指向UI的缓冲区
		myMessageServer = new MfxControlMessageServer(this); //UI窗口消息服务器
		MfxFunc_GetApp()->RegisterUI(this); //注册UI界面

		SetWindowText(myWnd, titleName.c_str());
		ShowWindow(myWnd, SW_NORMAL);
	}
}

MicroFlakeX::MfxUI::~MfxUI()
{
	if (myWndCreateSuccess)
	{
		SendMessage(myWnd, WM_CLOSE, 0, 0);
		/* 释放控件 */
		for (int i = 0; i < myControlList.size(); i++)
		{
			delete myControlList[i];
		}
		MfxFunc_GetApp()->DelRegisterUI(this);

		ReleaseDC(myWnd, myBufferDc);
		ReleaseDC(myWnd, myMainDc);
		delete myGraphics;

		delete myMessageServer;
	}
}

bool MicroFlakeX::MfxUI::CheckWndCreateSuccess()
{
	return myWndCreateSuccess;
}

bool MicroFlakeX::MfxUI::RegisterControl(MfxControl* con)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	myControlList.push_back(con);
	/**/
	return false;
}

bool MicroFlakeX::MfxUI::DelRegisterControl(MfxControl* con)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	for (MFXCONTROL_LIST_ITERA delIt = myControlList.begin(); delIt != myControlList.end(); delIt++)
	{
		if (*delIt == con)
		{
			myControlList.erase(delIt);
		}
	}
	/**/
	return false;
}

bool MicroFlakeX::MfxUI::UIUpdate()
{
	if (!myWndCreateSuccess) return 0;
	return BitBlt(myMainDc, 0, 0, myRect.Width, myRect.Height, myBufferDc, 0, 0, SRCCOPY);
}

bool MicroFlakeX::MfxUI::UIClean(bool type)
{
	if (!myWndCreateSuccess) return 0;
	return BitBlt(myBufferDc, 0, 0, myRect.Width, myRect.Height, 0, 0, 0, type ? BLACKNESS : WHITENESS);
}

HWND MicroFlakeX::MfxUI::GetWnd()
{
	return myWnd;
}

Gdiplus::Size MicroFlakeX::MfxUI::GetSize()
{
	return Gdiplus::Size(myRect.Width,myRect.Height);
}

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetGraphics()
{
	return myGraphics;
}

MicroFlakeX::MfxControlMessageServer* MicroFlakeX::MfxUI::GetMessageServer()
{
	return myMessageServer;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RegisterControlMessage(MfxControl* con, UINT message, MFXUI_FUNC valFunc)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	CONCTROLMSG temp{ con, message };
	MFXUI_CONCTROL_FUNC_MAP_PAIR retPair = myControlMessageMap.insert(MFXUI_CONCTROL_FUNC_MAP_ELEM(temp, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::ReceiveControlMessage(MfxControl* con, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	CONCTROLMSG temp{ con, message };
	MFXUI_CONCTROL_FUNC_MAP_ITERA callIter = myControlMessageMap.find(temp);
	if (callIter != myControlMessageMap.end())
	{
		return (this->*callIter->second)(wParam, lParam);
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}



MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RegisterUIMessage(UINT message, MFXUI_FUNC valFunc)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_MESSAGE_FUNC_MAP_PAIR retPair = myUIMessageMap.insert(MFXUI_MESSAGE_FUNC_MAP_ELEM(message, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::ReceiveUIMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	/*
	switch (message) 
	{
	case WM_LBUTTONDOWN:
	{
		MessageBox(myWnd, L"<Now In ReceiveUIMessage>", L"<WM_LBUTTONDOWN>", 0);
	}
	case WM_CREATE:
	{
		break;
	}
	case WM_DESTROY: 
	{
		//PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(myWnd, message, wParam, lParam);
	}
	/**/
	MFXUI_MESSAGE_FUNC_MAP_ITERA callIter = myUIMessageMap.find(message);
	if (callIter != myUIMessageMap.end())
	{
		return (this->*callIter->second)(wParam, lParam);
	}
	return DefWindowProc(myWnd, message, wParam, lParam);
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::DelUIMessage(UINT message)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_MESSAGE_FUNC_MAP_ITERA delIter = myUIMessageMap.find(message);
	if (delIter != myUIMessageMap.end())
	{
		myUIMessageMap.erase(delIter);
		return MFXRETURE_OK;
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::DelControlMessage(MfxControl* con, UINT message)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	CONCTROLMSG temp{ con, message };
	MFXUI_CONCTROL_FUNC_MAP_ITERA delIter = myControlMessageMap.find(temp);
	if (delIter != myControlMessageMap.end())
	{
		myControlMessageMap.erase(delIter);
		return MFXRETURE_OK;
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}