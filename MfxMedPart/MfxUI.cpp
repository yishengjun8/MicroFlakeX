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
	MFXWINDTYPE_ENUM dwStyle,
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
	//this->MfxRegDefMessage(WM_TIMER, (MFXUI_FUNC)&MfxUI::OnUIUpdateBasedTimer);MfxDefOnUIRButtonDown
	this->MfxRegDefMessage(WM_DESTROY, (MFXUI_FUNC)&MfxUI::MfxDefOnUIDestroy);
	this->MfxRegDefMessage(WM_SIZE, (MFXUI_FUNC)&MfxUI::MfxDefOnUISize);
	this->MfxRegDefMessage(WM_SIZING, (MFXUI_FUNC)&MfxUI::MfxDefOnUISizing);
	this->MfxRegDefMessage(WM_PAINT, (MFXUI_FUNC)&MfxUI::MfxDefOnUIPaint);
	this->MfxRegDefMessage(WM_MOVE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIMove);
	this->MfxRegDefMessage(WM_SYSCOMMAND, (MFXUI_FUNC)&MfxUI::MfxDefOnUISysCommand);
	this->MfxRegDefMessage(WM_ERASEBKGND, (MFXUI_FUNC)&MfxUI::MfxDefOnUIEraseBkGnd);
	this->MfxRegDefMessage(WM_CHILDACTIVATE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIChildActivate);
	this->MfxRegDefMessage(WM_LBUTTONDOWN, (MFXUI_FUNC)&MfxUI::MfxDefOnUILButtonDown);
	this->MfxRegDefMessage(WM_RBUTTONDOWN, (MFXUI_FUNC)&MfxUI::MfxDefOnUIRButtonDown);

	this->MfxRegDefMessage(MFXUIEVENT_SIZE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIMSGSize);


	myWnd = nullptr;
	myMainDc = nullptr; //UI的主画板 - 需要释放
	myBufferDc = nullptr; //用于双缓冲 - 需要释放
	myBufferGraphics = nullptr; //UI绘画类，指向UI的缓冲区 - 需要释放
	myMessageServer = nullptr; //UI窗口消息服务器 - 需要释放
	myWndCreateSuccess = true;
	myUIPaintEnumChild = false;
	myBackBitmap = nullptr;
	myBackImage = nullptr; 
	myMaskImage = nullptr;

	myPaintFrame = 30;
	myPaintFlag = PAINTFLAG_TSLEEP; //默认关闭
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

	new std::thread(std::bind(&MfxUI::UIThreadPaint, this));
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
		myWndCreateSuccess = false;
		PostMessage(myWnd, WM_CLOSE, 0, 0);
		/* 释放控件 */
		for (int i = 0; i < myControlList.size(); i++)
		{
			delete myControlList[i];
		}
		MfxFunc_GetApp()->DelRegisterUI(this);  // 解除注册，从现在开始没法接收消息了

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

bool MicroFlakeX::MfxUI::UIDrawToMainDc()
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

unsigned char MicroFlakeX::MfxUI::UIAutomation(unsigned char frame)
{
	unsigned char retFrame = myPaintFrame;
	myPaintFrame = frame;
	return retFrame;
}

void MicroFlakeX::MfxUI::UIThreadPaint()
{
	//线程标志 线程使用0x01，主程序使用0x02  
	//暂停线程使用0x10，暂停主程序使用0x20
	clock_t t_myBeginTime, t_myOverTime;
	while (myWndCreateSuccess)
	{
		t_myBeginTime = clock();
		while (1)
		{
			t_myOverTime = clock();
			if ((t_myOverTime - t_myBeginTime) >= myPaintFrame && !(myPaintFlag & 0x10))
				break;
		}

		if (!(myPaintFlag & 0x02) && !(myPaintFlag & 0x10))
		{
			myPaintFlag |= 0x01; //开始

			PAINTSTRUCT ps;
			if (!myWndCreateSuccess)return;
			HDC hDc = BeginPaint(myWnd, &ps);
			if (!myWndCreateSuccess)return;
			UICleanBufferDc(); //刷新缓冲区背景
			if (!myWndCreateSuccess)return;
			for (int i = 0; i < myControlList.size(); i++)
			{
				myControlList[i]->ThreadPaint();
				if (!myWndCreateSuccess)return;
			}
			if (myMaskImage)
				myMaskImage->Draw(); //绘制最前面的Mask
			if (!myWndCreateSuccess)return;
			UIDrawToMainDc(); //绘制到主界面
			if (!myWndCreateSuccess)return;
			//主界面绘制完毕，开始通知子窗口绘制，防止被遮挡 
			if (myUIPaintEnumChild)
				EnumChildWindows(myWnd, MfxEnumRedrawWindow, 0);
			if (!myWndCreateSuccess)return;
			EndPaint(myWnd, &ps);

			myPaintFlag &= ~0x01; //结束
		}
	}
}

void MicroFlakeX::MfxUI::UIAddPainFlag(PAINTFLAG set)
{
	myPaintFlag |= set;
}

void MicroFlakeX::MfxUI::UIDelPainFlag(PAINTFLAG set)
{
	myPaintFlag &= ~set;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::UISetBack(MfxImage* uiBack)
{
	/**/
	MfxImage* retImage = myBackImage;
	DeleteObject(myBackBitmap);
	myBackImage = uiBack;

	myBackImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	myBackImage->GetBitmap()->GetHBITMAP(NULL, &myBackBitmap);
	/**/
	//ReceiveUIMessage(WM_PAINT, 0, 0);

	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::UISetMask(MfxImage* uiMask)
{
	/**/
	MfxImage* retImage = myMaskImage;
	myMaskImage = uiMask;
	myMaskImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	/**/
	//ReceiveUIMessage(WM_PAINT, 0, 0);
	return retImage;
}

void MicroFlakeX::MfxUI::UISetPaintEnumChild(bool enumType)
{
	myUIPaintEnumChild = enumType;
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
	MFXUI_MESSAGE_FUNC_MAP_ITERA callIter = myUIMessageMap.find(message);
	if (callIter != myUIMessageMap.end())
	{
		return (this->*callIter->second)(wParam, lParam);
	}
	return MfxRecDefMessage(message, wParam, lParam);
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

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxRegDefMessage(UINT message, MFXUI_FUNC valFunc)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_MESSAGE_FUNC_MAP_PAIR retPair = myMfxDefUIMessageMap.insert(MFXUI_MESSAGE_FUNC_MAP_ELEM(message, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE CALLBACK MicroFlakeX::MfxUI::MfxRecDefMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	MFXUI_MESSAGE_FUNC_MAP_ITERA callIter = myMfxDefUIMessageMap.find(message);
	if (callIter != myMfxDefUIMessageMap.end())
	{
		return (this->*callIter->second)(wParam, lParam);
	}
	return DefWindowProc(myWnd, message, wParam, lParam);
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDelDefMessage(UINT message)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_MESSAGE_FUNC_MAP_ITERA delIter = myMfxDefUIMessageMap.find(message);
	if (delIter != myMfxDefUIMessageMap.end())
	{
		myMfxDefUIMessageMap.erase(delIter);
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

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetBufferGraphics()
{
	return myBufferGraphics;
}

MicroFlakeX::MfxControlMessageServer* MicroFlakeX::MfxUI::GetMessageServer()
{
	return myMessageServer;
}

Gdiplus::Rect MicroFlakeX::MfxUI::GetRect()
{
	return myRect;
}
Gdiplus::Size MicroFlakeX::MfxUI::GetSize()
{
	return Gdiplus::Size(myRect.Width, myRect.Height);
}

Gdiplus::Point MicroFlakeX::MfxUI::GetPoint()
{
	return Gdiplus::Point(myRect.X, myRect.Y);
}

void MicroFlakeX::MfxUI::SetRect(Gdiplus::Rect set)
{
}

void MicroFlakeX::MfxUI::SetSize(Gdiplus::Size set)
{
}

void MicroFlakeX::MfxUI::SetPoint(Gdiplus::Point set)
{
}





MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIDestroy(WPARAM wParam, LPARAM lParam)
{
	/* 结束消息循环 */
	PostQuitMessage(0);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEachFrame(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIPaint(WPARAM wParam, LPARAM lParam)
{
	//线程标志 线程使用0x01，主程序使用0x02  
	//暂停线程使用0x10，暂停主程序使用0x20
	if (!(myPaintFlag & 0x01) && !(myPaintFlag & 0x20))
	{
		myPaintFlag |= 0x02;//开始

		PAINTSTRUCT ps;
		HDC hDc = BeginPaint(myWnd, &ps);
		//fprintf(gFileOut, "hWnd:%d, message:WM_PAINT, wParam:%d, lParam:%d \n", (long)myWnd, (long)wParam, (long)lParam);

		UICleanBufferDc(); //刷新缓冲区背景

		this->myMessageServer->ForwardMessageToControl(WM_PAINT, (WPARAM)&ps, 0);

		if (myMaskImage)
			myMaskImage->Draw(); //绘制最前面的Mask

		UIDrawToMainDc(); //绘制到主界面

		/* 主界面绘制完毕，开始通知子窗口绘制，防止被遮挡 */
		if (myUIPaintEnumChild)
			EnumChildWindows(myWnd, MfxEnumRedrawWindow, 0);

		EndPaint(myWnd, &ps);

		myPaintFlag &= ~0x02; //结束
	}
	
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUISize(WPARAM wParam, LPARAM lParam)
{
	// 当大小发生改变
	UICHANGESIZE tSize;
	tSize.bRect = myRect;
	tSize.aRect = Gdiplus::Rect(myRect.X, myRect.Y, LOWORD(lParam), HIWORD(lParam));

	// 通知控件们，大小发生改变 
	this->myMessageServer->ForwardMessageToControl(MFXUIEVENT_SIZE, 0, (LPARAM)&tSize);
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
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUISizing(WPARAM wParam, LPARAM lParam)
{
	/* 交给系统自己处理 */
	return DefWindowProc(myWnd, WM_SIZING, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIMove(WPARAM wParam, LPARAM lParam)
{
	/* 还没想好要做啥，可是移动的时候确实没事可做啊，或许加个物理特效吗？ */
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUISysCommand(WPARAM wParam, LPARAM lParam)
{
	/* 在收到命令的时候，置顶窗口 */
	BringWindowToTop(myWnd);
	return DefWindowProc(myWnd, WM_SYSCOMMAND, wParam, lParam);
	//fprintf(gFileOut, "hWnd:%d, message:WM_SYSCOMMAND, wParam:%d, lParam:%d \n", (long)myWnd, (long)wParam, (long)lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEraseBkGnd(WPARAM wParam, LPARAM lParam)
{
	/* 什么也不做，因为我是DirectUI库，而且双缓冲绘图，所以不需要擦除主画板的背景 */
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIChildActivate(WPARAM wParam, LPARAM lParam)
{
	/* 我在活动？ */
	//BringWindowToTop(myWnd);
	return DefWindowProc(myWnd, WM_SYSCOMMAND, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILButtonDown(WPARAM wParam, LPARAM lParam)
{
	BringWindowToTop(myWnd);
	//PostMessage(myWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRButtonDown(WPARAM wParam, LPARAM lParam)
{
	BringWindowToTop(myWnd);
	//PostMessage(myWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIMSGSize(WPARAM wParam, LPARAM lParam)
{
	UICHANGESIZE* getSize = (UICHANGESIZE*)lParam;
	/* 算吧，这里给出了前后坐标，怎么搞就是你的事情了 */
	return 0;
}
