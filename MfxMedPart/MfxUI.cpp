#include "pch.h"
#include "MfxMedPart.h"

/*
#include "cstdio"
using namespace std;
FILE* gFileOut;
/**/

void MicroFlakeX::MfxUI::MfxUIRegDef()
{
	MfxRegDefMessage(WM_PAINT, (MFXUI_FUNC)&MfxUI::MfxDefOnUIPaint);
	MfxRegDefMessage(WM_DESTROY, (MFXUI_FUNC)&MfxUI::MfxDefOnUIDestroy);

	MfxRegDefMessage(WM_SYSCOMMAND, (MFXUI_FUNC)&MfxUI::MfxDefOnUISysCommand);
	MfxRegDefMessage(WM_ERASEBKGND, (MFXUI_FUNC)&MfxUI::MfxDefOnUIEraseBack);

	MfxRegDefMessage(WM_SIZE, (MFXUI_FUNC)&MfxUI::MfxDefOnUISize);
	MfxRegDefMessage(WM_SIZING, (MFXUI_FUNC)&MfxUI::MfxDefOnUISizing);

	MfxRegDefMessage(WM_MOVE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIMove);
	MfxRegDefMessage(WM_MOVING, (MFXUI_FUNC)&MfxUI::MfxDefOnUIMoving);

	MfxRegDefMessage(WM_LBUTTONDOWN, (MFXUI_FUNC)&MfxUI::MfxDefOnUILButtonDown);
	MfxRegDefMessage(WM_LBUTTONUP, (MFXUI_FUNC)&MfxUI::MfxDefOnUILButtonUp);
	MfxRegDefMessage(WM_LBUTTONDBLCLK, (MFXUI_FUNC)&MfxUI::MfxDefOnUILDoubleClick);

	MfxRegDefMessage(WM_RBUTTONDOWN, (MFXUI_FUNC)&MfxUI::MfxDefOnUIRButtonDown);
	MfxRegDefMessage(WM_RBUTTONUP, (MFXUI_FUNC)&MfxUI::MfxDefOnUIRButtonUp);
	MfxRegDefMessage(WM_RBUTTONDBLCLK, (MFXUI_FUNC)&MfxUI::MfxDefOnUIRDoubleClick);

	MfxRegDefMessage(MFXUIEVENT_SIZE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIEventSize);
}

void MicroFlakeX::MfxUI::MfxUIInitData(Gdiplus::Rect value)
{
	myWndCreateSuccess = true; //窗口是否创建成功

	myWnd = nullptr;

	myMainDc = nullptr; //主画板 - 需要释放
	myBuffDc = nullptr; //双缓冲 - 需要释放
	myMainGraphics = nullptr; //主绘图 - 需要释放
	myBuffGraphics = nullptr; //双缓冲 - 需要释放
	myMessageServer = nullptr;//消息服务器 - 需要释放

	myBackBitmap = nullptr;	//背景 - 需要释放
	myBackImage = nullptr;	//背景
	myMaskImage = nullptr;	//蒙版
	myUIPaintEnumChild = false; //重绘是否刷新子窗口

	myPaintFlag = PAINTFLAG_TSLEEP; 
	myPaintDelay = 40; //每次刷新延迟多少毫秒

	myRect = value; //窗口显示区域
}

void MicroFlakeX::MfxUI::MfxUICreateWindowEx(
	DWORD exStyle, DWORD dwStyle, MfxUI* father, 
	std::wstring title, std::wstring wndClass)
{
	MfxFunc_GetApp()->SetCreatUI(this);

	CreateWindowEx(exStyle, wndClass.c_str(), title.c_str(), dwStyle,
		myRect.X, myRect.Y, myRect.Width, myRect.Height,
		father ? father->GetWnd() : NULL,
		NULL, MfxFunc_GetApp()->GetInstance(), NULL
	);
	//myPaintThread = std::thread(std::bind(&MfxUI::UIPaintThread, this));//高刷
	//myPaintThread.detach();
	//myClockThread = std::thread(std::bind(&MfxUI::UIClockThread, this));//定时器
	//myClockThread.detach();
}

void MicroFlakeX::MfxUI::SetWnd(HWND get)
{
	if (myWnd) return;
	myWnd = get;

	myMainDc = GetDC(myWnd); //主画板 - 需要释放
	myBuffDc = CreateCompatibleDC(myMainDc); //双缓冲 - 需要释放

	int cx = GetSystemMetrics(SM_CXFULLSCREEN);//默认为屏幕最大大小 <-待优化
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	myBackBitmap = CreateCompatibleBitmap(myMainDc, cx, cy);
	SelectObject(myBuffDc, myBackBitmap); //缓冲区背景，默认为黑色

	myMainGraphics = MfxFunc_GetGraphics(myMainDc); //主绘图 - 需要释放
	myBuffGraphics = MfxFunc_GetGraphics(myBuffDc); //双缓冲 - 需要释放

	myBackImage = new MfxImage(myBuffGraphics, Gdiplus::Color::DarkBlue, myRect);
	myMessageServer = new MfxControlMessageServer(this); //创建消息服务器
	MfxFunc_GetApp()->RegUI(this); //注册UI
}

MicroFlakeX::MfxUI::MfxUI(
	Gdiplus::Rect theRect, DWORD exStyle, DWORD dwStyle,
	std::wstring title, MfxUI* father, std::wstring wndClass)
{
	MfxUIRegDef();
	MfxUIInitData(theRect);
	MfxUICreateWindowEx(exStyle, dwStyle, father, title, wndClass);
	
	if (myWnd == NULL)
	{
		std::wstring tOut = L"Window Creation Failed!\n  >>wndClassName: ";
		tOut += wndClass;
		tOut += L"\n  >>titleName: ";
		tOut += title.c_str();
		MessageBox(NULL, tOut.c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
		myWndCreateSuccess = false;
	}
}

MicroFlakeX::MfxUI::MfxUI(Gdiplus::Rect theRect, DWORD dwStyle, std::wstring title, MfxUI* father)
{
	MfxUIRegDef();
	MfxUIInitData(theRect);
	MfxUICreateWindowEx(NULL, dwStyle, father, title, L"MfxNormal");

	if (myWnd == NULL)
	{
		std::wstring tOut = L"Window Creation Failed!\n  >>wndClassName: ";
		tOut += L"MfxNormal\n  >>titleName: ";
		tOut += title.c_str();
		MessageBox(NULL, tOut.c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
		myWndCreateSuccess = false;
	}
}


MicroFlakeX::MfxUI::~MfxUI()
{
	if (myWndCreateSuccess)
	{
		myWndCreateSuccess = false;
		PostMessage(myWnd, WM_CLOSE, 0, 0); //发送窗口关闭消息 <-等待优化

		for (int i = 0; i < myControlList.size(); i++)
			delete myControlList[i];

		MfxFunc_GetApp()->DelUI(this);  //断开消息接收
		delete myMessageServer; //删除消息服务器

		ReleaseDC(myWnd, myBuffDc);
		ReleaseDC(myWnd, myMainDc);

		delete myMainGraphics;
		delete myBuffGraphics;
	}
}

bool MicroFlakeX::MfxUI::CheckWndCreateSuccess()
{
	return myWndCreateSuccess;
}

/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

bool MicroFlakeX::MfxUI::UIDrawToMainDc()
{
	if (!myWndCreateSuccess) return 0;
	return BitBlt(myMainDc, 0, 0, myRect.Width, myRect.Height, myBuffDc, 0, 0, SRCCOPY);
}

bool MicroFlakeX::MfxUI::UICleanBufferDc()
{
	if (!myWndCreateSuccess) return 0;
	myBackImage->Draw();
	return true;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::UISetBack(MfxImage* uiBack)
{
	/**/
	MfxImage* retImage = myBackImage;
	myBackImage = uiBack;
	myBackImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	/**/
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::UISetMask(MfxImage* uiMask)
{
	/**/
	MfxImage* retImage = myMaskImage;
	myMaskImage = uiMask;
	myMaskImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	/**/
	return retImage;
}

void MicroFlakeX::MfxUI::UISetPaintEnumChild(bool enumType)
{
	myUIPaintEnumChild = enumType;
}

void MicroFlakeX::MfxUI::UIPaintThread()
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
			if ((t_myOverTime - t_myBeginTime) >= myPaintDelay && !(myPaintFlag & PAINTFLAG_TSLEEP))
				break;
		}

		myPaintFlag |= PAINTFLAG_TDOING; //开始

		if (!(myPaintFlag & PAINTFLAG_MDOING) && !(myPaintFlag & PAINTFLAG_TSLEEP))
		{
			PAINTSTRUCT ps;
			HDC hDc = BeginPaint(myWnd, &ps);

			if (myBackImage)
				myBackImage->Draw(); //刷新背景

			for (int i = 0; i < myControlList.size(); i++)
				myControlList[i]->ThreadPaint();

			if (myMaskImage)
				myMaskImage->Draw(); //添加蒙版

			UIDrawToMainDc(); 

			EnumChildWindows(myWnd, MfxEnumRedrawWindow, 0);

			EndPaint(myWnd, &ps);
		}

		myPaintFlag &= ~PAINTFLAG_TDOING; //结束
	}
}

int MicroFlakeX::MfxUI::UISetPaintSleep(int set)
{
	unsigned char retFrame = myPaintDelay;
	myPaintDelay = set;
	return retFrame;
}

void MicroFlakeX::MfxUI::UIAddPainFlag(UINT set)
{
	myPaintFlag |= set;
}

void MicroFlakeX::MfxUI::UIDelPainFlag(UINT del)
{
	myPaintFlag &= ~del;
}

void MicroFlakeX::MfxUI::UIClockThread()
{
	//MessageBox(myWnd, L"??", L"ss", 0);
	clock_t t_myBeginTime, t_myOverTime;
	while (myWndCreateSuccess)
	{
		t_myBeginTime = clock();
		while (true)
		{
			t_myOverTime = clock();
			if ((t_myOverTime - t_myBeginTime) >= 1)
				break;
		}
		for (int i = 0; i < myClockList.size(); i++)
		{
			myClockList[i].count += 1;
			if (myClockList[i].count >= myClockList[i].delay)
			{
				PostMessage(myWnd, myClockList[i].message, myClockList[i].count, myClockList[i].delay);
				myClockList[i].count = 0;
			}
		}
	}
}

void MicroFlakeX::MfxUI::UIAddClock(MFXUI_CLOCK set)
{
	set.count = 0;
	myClockList.push_back(set);
}

void MicroFlakeX::MfxUI::UIDelClock(UINT message)
{
	for (MFXUI_CLOCK_LISTITERA it = myClockList.begin(); it != myClockList.end(); it++)
	{
		if ((*it).message == message)
		{
			myClockList.erase(it);
			return;
		}
	}
}

bool MicroFlakeX::MfxUI::RegControl(MfxControl* con)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	myControlList.push_back(con);
	/**/
	return false;
}

bool MicroFlakeX::MfxUI::DelControl(MfxControl* con)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	for (MFXCONTROL_LISTITERA delIt = myControlList.begin(); delIt != myControlList.end(); delIt++)
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

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RegControlEvent(MfxControl* con, UINT eventID, MFXUI_FUNC valFunc)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_CONTROLEVENT temp{ con, eventID };
	MFXUI_CONTROLEVENT_MAPPAIR retPair = myControlEventMap.insert(MFXUI_CONTROLEVENT_MAPELEM(temp, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RecControlEvent(MfxControl* con, UINT eventID, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_CONTROLEVENT temp{ con, eventID };
	MFXUI_CONTROLEVENT_MAPITERA callIter = myControlEventMap.find(temp);
	if (callIter != myControlEventMap.end())
	{
		return (this->*callIter->second)(wParam, lParam);
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::DelControlEvent(MfxControl* con, UINT eventID)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_CONTROLEVENT temp{ con, eventID };
	MFXUI_CONTROLEVENT_MAPITERA delIter = myControlEventMap.find(temp);
	if (delIter != myControlEventMap.end())
	{
		myControlEventMap.erase(delIter);
		return MFXRETURE_OK;
	}
	return MFXRETURE_NOFIND;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RegUIMessage(UINT message, MFXUI_FUNC valFunc)
{
	if (!myWndCreateSuccess) return 0;
	/**/
	MFXUI_MESSAGE_MAPPAIR retPair = myUIMessageMap.insert(MFXUI_MESSAGE_MAPELEM(message, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RecUIMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	MFXUI_MESSAGE_MAPITERA callIter = myUIMessageMap.find(message);
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
	MFXUI_MESSAGE_MAPITERA delIter = myUIMessageMap.find(message);
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
	MFXUI_MESSAGE_MAPPAIR retPair = myMfxDefUIMessageMap.insert(MFXUI_MESSAGE_MAPELEM(message, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxRecDefMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!myWndCreateSuccess) return 0;
	MFXUI_MESSAGE_MAPITERA callIter = myMfxDefUIMessageMap.find(message);
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
	MFXUI_MESSAGE_MAPITERA delIter = myMfxDefUIMessageMap.find(message);
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

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetMainGraphics()
{
	return myMainGraphics;
}

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetBuffGraphics()
{
	return myBuffGraphics;
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

/* ———————————————————————————————————————————— */
/* ——————————————下面的代码是默认响应———————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIPaint(WPARAM wParam, LPARAM lParam)
{
	// 线程标志 线程使用0x01，主程序使用0x02  
	// 暂停线程使用0x10，暂停主程序使用0x20

	myPaintFlag |= PAINTFLAG_MDOING; //开始

	if (!(myPaintFlag & PAINTFLAG_TDOING) && !(myPaintFlag & PAINTFLAG_MSLEEP))
	{
		PAINTSTRUCT ps;
		HDC hDc = BeginPaint(myWnd, &ps);
		//fprintf(gFileOut, "hWnd:%d, message:WM_PAINT, wParam:%d, lParam:%d \n", (long)myWnd, (long)wParam, (long)lParam);

		if (myBackImage)
			myBackImage->Draw(); //刷新背景

		this->myMessageServer->ForwardMessageToControl(WM_PAINT, (WPARAM)&ps, 0);

		if (myMaskImage)
			myMaskImage->Draw(); //添加蒙版

		UIDrawToMainDc(); //绘制到主界面

		/* 主界面绘制完毕，开始通知子窗口绘制，防止被遮挡 */
		if (myUIPaintEnumChild)
			EnumChildWindows(myWnd, MfxEnumRedrawWindow, 0);

		EndPaint(myWnd, &ps);
	}

	myPaintFlag &= ~PAINTFLAG_MDOING; //结束
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIDestroy(WPARAM wParam, LPARAM lParam)
{
	/* 结束消息循环 */
	PostQuitMessage(0);
	return 0;
}


MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUISysCommand(WPARAM wParam, LPARAM lParam)
{
	/* 在收到命令的时候，置顶窗口 */
	BringWindowToTop(myWnd);
	return DefWindowProc(myWnd, WM_SYSCOMMAND, wParam, lParam);
	//fprintf(gFileOut, "hWnd:%d, message:WM_SYSCOMMAND, wParam:%d, lParam:%d \n", (long)myWnd, (long)wParam, (long)lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEraseBack(WPARAM wParam, LPARAM lParam)
{
	/* 什么也不做，因为我是DirectUI库，而且双缓冲绘图，所以不需要擦除主画板的背景 */
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

	if (myBackImage)
	{
		myBackImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	}

	if (myMaskImage)
	{
		myMaskImage->SetImageSize(Gdiplus::Size(myRect.Width, myRect.Height));
	}
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

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIMoving(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}


MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILButtonDown(WPARAM wParam, LPARAM lParam)
{
	BringWindowToTop(myWnd);
	//PostMessage(myWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILButtonUp(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILDoubleClick(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}


MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRButtonDown(WPARAM wParam, LPARAM lParam)
{
	BringWindowToTop(myWnd);
	//PostMessage(myWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRDoubleClick(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEventSize(WPARAM wParam, LPARAM lParam)
{
	UICHANGESIZE* getSize = (UICHANGESIZE*)lParam;
	/* 算吧，这里给出了前后坐标，怎么搞就是你的事情了 */
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEventSizing(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}
