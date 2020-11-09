#include "pch.h"
#include "MfxMedPart.h"

/*
#include "cstdio"
using namespace std;
FILE* gFileOut;
/**/

MicroFlakeX::MfxUI::MfxUI(
	Gdiplus::Rect theRect,
	DWORD exStyle,
	DWORD dwStyle,
	std::wstring titleName,
	MfxUI* father,
	std::wstring wndClassName
	)
{
	/*
	static bool a = true;
	if (a)
	{
		fopen_s(&gFileOut, "D:\\MfxUI001.txt", "wb");
		a = false;
	}
	/**/
	/* 注册消息 */
	//this->RegisterUIMessage(WM_TIMER, (MFXUI_FUNC)&MfxUI::OnUIUpdateBasedTimer);
	this->RegisterUIMessage(WM_DESTROY, (MFXUI_FUNC)&MfxUI::OnUIDestroy);
	this->RegisterUIMessage(WM_SIZE, (MFXUI_FUNC)&MfxUI::OnUISize);
	this->RegisterUIMessage(WM_SIZING, (MFXUI_FUNC)&MfxUI::OnUISizing);
	this->RegisterUIMessage(WM_PAINT, (MFXUI_FUNC)&MfxUI::OnUIPaint); 
	this->RegisterUIMessage(WM_MOVE, (MFXUI_FUNC)&MfxUI::OnUIMove); 
	this->RegisterUIMessage(WM_SYSCOMMAND, (MFXUI_FUNC)&MfxUI::OnUISysCommand);
	this->RegisterUIMessage(WM_ERASEBKGND, (MFXUI_FUNC)&MfxUI::OnUIEraseBkGnd);
	this->RegisterUIMessage(WM_CHILDACTIVATE, (MFXUI_FUNC)&MfxUI::OnUIChildActivate);
	
	this->RegisterUIMessage(MFXUIMSG_SIZE, (MFXUI_FUNC)&MfxUI::OnUIMSGSize);


	myWnd = nullptr;
	myMainDc = nullptr; //UI的主画板 - 需要释放
	myBufferDc = nullptr; //用于双缓冲 - 需要释放
	myBufferGraphics = nullptr; //UI绘画类，指向UI的缓冲区 - 需要释放
	myMessageServer = nullptr; //UI窗口消息服务器 - 需要释放
	myWndCreateSuccess = true;
	myUIPaintEnum = false;
	myBackBitmap = nullptr;
	myBackImage = nullptr; 
	myMaskImage = nullptr;
	myRect = theRect; //UI的大小 - 会随窗口大小而自动调整

	MfxFunc_GetApp()->SetCreatUI(this);

	CreateWindowEx(exStyle, wndClassName.c_str(), titleName.c_str(), dwStyle// | WS_MINIMIZE,
		,theRect.X, theRect.Y,
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
}

void MicroFlakeX::MfxUI::SetWnd(HWND hWnd)
{
	if (myWnd) return;
	myWnd = hWnd;

	myMainDc = GetDC(myWnd); //UI的主画板

	myBackBitmap = CreateCompatibleBitmap(myMainDc, myRect.Width, myRect.Height);
	myBufferDc = CreateCompatibleDC(myMainDc); //UI缓冲区-用于双缓冲

	DeleteObject(SelectObject(myBufferDc, myBackBitmap)); //给予缓冲区大小和背景

	myBufferGraphics = MfxFunc_GetGraphics(myBufferDc); //UI绘画类，指向UI的缓冲区

	myMessageServer = new MfxControlMessageServer(this); //UI窗口消息服务器
	MfxFunc_GetApp()->RegisterUI(this); //注册UI界面
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
		//delete myBackImage;
		//delete myMaskImage;
		delete myBufferGraphics;
		delete myMessageServer;
	}
}

bool MicroFlakeX::MfxUI::CheckWndCreateSuccess()
{
	return myWndCreateSuccess;
}

bool MicroFlakeX::MfxUI::UIUpdateMainDc()
{
	if (!myWndCreateSuccess) return 0;
	return BitBlt(myMainDc, 0, 0, myRect.Width, myRect.Height, myBufferDc, 0, 0, SRCCOPY);
}

bool MicroFlakeX::MfxUI::UICleanBufferDc()
{
	if (!myWndCreateSuccess) return 0;
	SelectObject(myBufferDc, myBackBitmap); //刷新缓冲区
	return true;
}

bool MicroFlakeX::MfxUI::UIAutomation(bool runType)
{
	return false;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::SetUIBack(MfxImage* uiBack)
{
	/**/
	MfxImage* retImage = myBackImage;
	DeleteObject(myBackBitmap);
	myBackImage = uiBack;

	myBackImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	myBackImage->GetBitmap()->GetHBITMAP(NULL, &myBackBitmap);
	/**/
	OnUIPaint(0, 0);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::SetUIMask(MfxImage* uiMask)
{
	/**/
	MfxImage* retImage = myMaskImage;
	myMaskImage = uiMask;
	myMaskImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	/**/
	OnUIPaint(0, 0);
	return retImage;
}

void MicroFlakeX::MfxUI::SetUIPaintEnum(bool enumType)
{
	myUIPaintEnum = enumType;
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
			return true;
		}
	}
	/**/
	return false;
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

MicroFlakeX::MFXRETURE CALLBACK MicroFlakeX::MfxUI::ReceiveUIMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	/*
	return DefWindowProc(hWnd, message, wParam, lParam);
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
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(myWnd, message, wParam, lParam);
	}
	return 0;
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


HWND MicroFlakeX::MfxUI::GetWnd()
{
	return myWnd;
}


MicroFlakeX::MfxControlMessageServer* MicroFlakeX::MfxUI::GetMessageServer()
{
	return myMessageServer;
}

Gdiplus::Rect MicroFlakeX::MfxUI::GetRect()
{
	return myRect;
}

Gdiplus::Point MicroFlakeX::MfxUI::GetPoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}

Gdiplus::Size MicroFlakeX::MfxUI::GetSize()
{
	return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetBufferGraphics()
{
	return myBufferGraphics;
}

void MicroFlakeX::MfxUI::SetX(int set)
{
}

void MicroFlakeX::MfxUI::SetY(int set)
{
}

void MicroFlakeX::MfxUI::SetWidth(int set)
{
}

void MicroFlakeX::MfxUI::SetHeight(int set)
{
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIDestroy(WPARAM wParam, LPARAM lParam)
{
	/* 结束消息循环 */
	PostQuitMessage(0);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIEachFrame(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIPaint(WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;;
	HDC hDc = BeginPaint(myWnd, &ps);
	//fprintf(gFileOut, "hWnd:%d, message:WM_PAINT, wParam:%d, lParam:%d \n", (long)myWnd, (long)wParam, (long)lParam);
	UICleanBufferDc(); //刷新缓冲区背景

	for (int i = 0; i < myControlList.size(); i++)
	{
		myControlList[i]->ReceiveMessage(WM_PAINT, (WPARAM)&ps, 0);
	}
	if(myMaskImage)
		myMaskImage->Draw(); //绘制最前面的Mask
	UIUpdateMainDc(); //绘制到主界面
	
	/* 主界面绘制完毕，开始通知子窗口绘制，防止被遮挡 */
	if(myUIPaintEnum)
		EnumChildWindows(myWnd, MfxEnumRedrawWindow, 0);

	EndPaint(myWnd, &ps);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUISize(WPARAM wParam, LPARAM lParam)
{
	// 当大小发生改变
	UICHANGESIZE tSize;
	tSize.bRect = myRect;
	tSize.aRect = Gdiplus::Rect(myRect.X, myRect.Y, LOWORD(lParam), HIWORD(lParam));

	// 通知控件们，大小发生改变 
	for (int i = 0; i < myControlList.size(); i++)
		myControlList[i]->ReceiveMessage(MFXUIMSG_SIZE, 0, (LPARAM)&tSize);
	EnumChildWindows(myWnd, MfxEnumFatherSize, (LPARAM)&tSize); // 通知子窗口们，大小发生改变。

	//重设主窗口大小
	myRect.Width = tSize.aRect.Width;
	myRect.Height = tSize.aRect.Height;


	/*
		HBRUSH brush;
		brush = CreatePatternBrush(myBackBitmap);
		SetClassLong(hWnd,GCL_HBRBACKGROUND,(long)brush);
	*/
	if (myBackImage != NULL)
	{
		myBackImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
		DeleteObject(myBackBitmap);
		myBackImage->GetBitmap()->GetHBITMAP(NULL, &myBackBitmap);
	}
	else
	{
		DeleteObject(myBackBitmap);
		myBackBitmap = CreateCompatibleBitmap(myMainDc, myRect.Width, myRect.Height);
	}
	//PostMessage(myWnd, WM_PAINT, 0, 0);
	//OnUIPaint(0, 0);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUISizing(WPARAM wParam, LPARAM lParam)
{
	/* 交给系统自己处理 */
	return DefWindowProc(myWnd, WM_SIZING, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIMove(WPARAM wParam, LPARAM lParam)
{
	/* 还没想好要做啥，可是移动的时候确实没事可做啊，或许加个物理特效吗？ */
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUISysCommand(WPARAM wParam, LPARAM lParam)
{
	/* 在收到命令的时候，置顶窗口 */
	BringWindowToTop(myWnd);
	return DefWindowProc(myWnd, WM_SYSCOMMAND, wParam, lParam);
	//fprintf(gFileOut, "hWnd:%d, message:WM_SYSCOMMAND, wParam:%d, lParam:%d \n", (long)myWnd, (long)wParam, (long)lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIEraseBkGnd(WPARAM wParam, LPARAM lParam)
{
	/* 什么也不做，因为我是DirectUI库，而且双缓冲绘图，所以不需要擦除主画板的背景 */
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIChildActivate(WPARAM wParam, LPARAM lParam)
{
	/* 我在活动？ */
	//BringWindowToTop(myWnd);
	return DefWindowProc(myWnd, WM_SYSCOMMAND, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::OnUIMSGSize(WPARAM wParam, LPARAM lParam)
{
	UICHANGESIZE* getSize = (UICHANGESIZE*)lParam;
	/* 算吧，这里给出了前后坐标，怎么搞就是你的事情了 */
	return 0;
}
