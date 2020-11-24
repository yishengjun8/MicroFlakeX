#include "pch.h"
#include "MfxMedPart.h"

/*
#include "cstdio"
using namespace std;
FILE* gFileOut;
/**/

void MicroFlakeX::MfxUI::MfxUIRegDef()
{
	MfxRegDefMessage(MFXUIEVENT_DRAWBUFFDC, (MFXUI_FUNC)&MfxUI::MfxDefOnDrawBuffDC);
	MfxRegDefMessage(MFXUIEVENT_DRAWMAINDC, (MFXUI_FUNC)&MfxUI::MfxDefOnDrawMainDC);

	MfxRegDefMessage(MFXCONTROLEVENT_CONTROLCREATE, (MFXUI_FUNC)&MfxUI::MfxDefOnControlCreate);
	MfxRegDefMessage(MFXCONTROLEVENT_CONTROLDELETE, (MFXUI_FUNC)&MfxUI::MfxDefOnControlDelete);

	MfxRegDefMessage(MFXCONTROLEVENT_FLOORCHANGE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIFloorChange);
	MfxRegDefMessage(WM_PAINT, (MFXUI_FUNC)&MfxUI::MfxDefOnUIPaint);

	MfxRegDefMessage(WM_TIMER, (MFXUI_FUNC)&MfxUI::MfxDefOnUITimer);

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

	MfxRegDefMessage(MFXUIEVENT_FATHERSIZE, (MFXUI_FUNC)&MfxUI::MfxDefOnUIFatherSize);
}

void MicroFlakeX::MfxUI::MfxUIInitData(Gdiplus::Rect value)
{
	myWndCreateSuccess = true; //窗口是否创建成功

	myUserFocusFlag = false; //表示可以更改焦点
	myUserFocusLock = nullptr; //表示锁定焦点，不允许更改
	myUserFocus = nullptr;

	myWnd = nullptr;
	myShowDc = nullptr;

	myMainDc = nullptr; //主画板 - 需要释放
	myBuffDc = nullptr; //双缓冲 - 需要释放
	myMainGraphics = nullptr; //主绘图 - 需要释放
	myBuffGraphics = nullptr; //双缓冲 - 需要释放

	myBackImage = nullptr;	//背景
	myMaskImage = nullptr;	//蒙版

	myRect = value; //窗口显示区域
}

void MicroFlakeX::MfxUI::MfxUICreateWindowEx(
	DWORD exStyle, DWORD dwStyle, MfxUI* father, 
	std::wstring title, std::wstring wndClass)
{
	MfxFunc_GetApp()->LoadBindingUI(this);

	CreateWindowEx(exStyle, wndClass.c_str(), title.c_str(), dwStyle,
		myRect.X, myRect.Y, myRect.Width, myRect.Height,
		father ? father->GetWnd() : NULL,
		NULL, MfxFunc_GetApp()->GetInstance(), NULL
	);
}

void MicroFlakeX::MfxUI::SetWnd(HWND get)
{
	if (myWnd) return;
	myWnd = get;
	myShowDc = GetDC(myWnd); //展示DC

	myMainDc = CreateCompatibleDC(myShowDc); //主画板 - 需要释放
	myBuffDc = CreateCompatibleDC(myShowDc); //双缓冲 - 需要释放

	int cx = GetSystemMetrics(SM_CXFULLSCREEN);//默认为屏幕最大大小 <-待优化
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	SelectObject(myMainDc, CreateCompatibleBitmap(myShowDc, cx, cy)); //主画板背景，默认为黑色
	SelectObject(myBuffDc, CreateCompatibleBitmap(myShowDc, cx, cy)); //缓冲区背景，默认为黑色

	myMainGraphics = MfxFunc_GetGraphics(myMainDc); //主绘图 - 需要释放
	myBuffGraphics = MfxFunc_GetGraphics(myBuffDc); //双缓冲 - 需要释放

	myBackImage = new MfxImage(myBuffGraphics, Gdiplus::Color::DarkBlue, Gdiplus::Rect(0, 0, myRect.Width, myRect.Height));
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
		{
			delete myControlList[i];
		}

		MfxFunc_GetApp()->DelUI(this);  //断开消息接收

		ReleaseDC(myWnd, myShowDc);
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

bool MicroFlakeX::MfxUI::UICopyMainDCToShowDC()
{
	return BitBlt(myShowDc, 0, 0, myRect.Width, myRect.Height, myMainDc, 0, 0, SRCCOPY);
}

bool MicroFlakeX::MfxUI::UICopyBufferDCToMainDC()
{
	return BitBlt(myMainDc, 0, 0, myRect.Width, myRect.Height, myBuffDc, 0, 0, SRCCOPY);
}

bool MicroFlakeX::MfxUI::UIDrawBufferDCBack()
{
	if (myBackImage)
	{
		myBackImage->Draw(); //刷新背景
	}
	
	return true;
}

bool MicroFlakeX::MfxUI::UIDrawMainDCMask()
{
	if (myMaskImage)
	{
		myMaskImage->Draw(); //添加主界面蒙版
	}

	return true;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::UISetBack(MfxImage* uiBack)
{
	/**/
	MfxImage* retImage = myBackImage;
	myBackImage = uiBack;
	myBackImage->SetRect(Gdiplus::Rect(0, 0, myRect.Width, myRect.Height));
	/**/
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxUI::UISetMask(MfxImage* uiMask)
{
	/**/
	MfxImage* retImage = myMaskImage;
	myMaskImage = uiMask;
	myMaskImage->SetGraphics(myMainGraphics);
	myMaskImage->SetRect(Gdiplus::Rect(0, 0, myRect.Width, myRect.Height));
	/**/
	return retImage;
}

void MicroFlakeX::MfxUI::UIAddClock(MFXUI_CLOCK set)
{
	set.count = 0;
	if(myClockList.insert(MFXUI_CLOCK_MAPELEM(set.message, set)).second)
	SetTimer(myWnd, set.message, set.delay, (TIMERPROC)NULL);
}

void MicroFlakeX::MfxUI::UIDelClock(UINT message)
{
	MFXUI_CLOCK_MAPITERA delIter = myClockList.find(message);
	if (delIter != myClockList.end())
	{
		KillTimer(myWnd, message);
		myClockList.erase(delIter);
	}
}

void MicroFlakeX::MfxUI::UIModifyClock(MFXUI_CLOCK set)
{
	UIDelClock(set.message);
	UIAddClock(set);
}

MicroFlakeX::MfxControl* MicroFlakeX::MfxUI::SetUserFocus(MfxControl* con)
{
	if (myUserFocusFlag || myUserFocusLock)
	{
		return nullptr;
	}

	myUserFocusFlag = true;
	MfxControl* retControl = myUserFocus;
	myUserFocus = con;
	return retControl ? retControl : myUserFocus;
}

void MicroFlakeX::MfxUI::LockUserFocus(MfxControl* con)
{
	if (!myUserFocusLock)
	{
		myUserFocusLock = con;
	}
}

void MicroFlakeX::MfxUI::FreeUserFocus(MfxControl* con)
{
	if (myUserFocusLock == con)
	{
		myUserFocusLock = nullptr;
	}
}

MicroFlakeX::MfxControl* MicroFlakeX::MfxUI::GetUserFocus()
{
	return myUserFocus;
}

bool MicroFlakeX::MfxUI::RegControl(MfxControl* con)
{
	/**/
	myControlList.push_back(con);
	/**/
	return false;
}

bool MicroFlakeX::MfxUI::DelControl(MfxControl* con)
{
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
	/**/
	MFXUI_CONTROLEVENT temp{ con, eventID };
	MFXUI_CONTROLEVENT_MAPPAIR retPair = myControlEventMap.insert(MFXUI_CONTROLEVENT_MAPELEM(temp, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RecvControlEvent(MfxControl* con, UINT eventID, WPARAM wParam, LPARAM lParam)
{
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
	/**/
	MFXUI_MESSAGE_MAPPAIR retPair = myUIMessageMap.insert(MFXUI_MESSAGE_MAPELEM(message, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::RecvUIMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	/**/
	//将焦点设为可更改的
	myUserFocusFlag = false;

	//先给控件发消息，同时如果控件获取了焦点，那么其余控件无法重新获取焦点
	for (int i = myControlList.size() - 1; i > -1; i--)
	{
		myControlList[i]->RecvMessage(message, wParam, lParam);
	}

	//将焦点设为可更改的
	myUserFocusFlag = false;

	//自我消息映射
	MFXUI_MESSAGE_MAPITERA callIter = myUIMessageMap.find(message);
	if (callIter != myUIMessageMap.end())
	{
		return (this->*callIter->second)(wParam, lParam);
	}
	return MfxRecvDefMessage(message, wParam, lParam);
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::DelUIMessage(UINT message)
{
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
	/**/
	MFXUI_MESSAGE_MAPPAIR retPair = myMfxDefUIMessageMap.insert(MFXUI_MESSAGE_MAPELEM(message, valFunc));
	return retPair.second;
	/**/
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxRecvDefMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
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

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetDefGraphics()
{
	return myBuffGraphics;
}

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetMainGraphics()
{
	return myMainGraphics;
}

Gdiplus::Graphics* MicroFlakeX::MfxUI::GetBuffGraphics()
{
	return myBuffGraphics;
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
	SetWindowPos(myWnd, NULL, set.X, set.Y, set.Width, set.Height, SWP_NOZORDER);
}

void MicroFlakeX::MfxUI::SetSize(Gdiplus::Size set)
{
	SetWindowPos(myWnd, NULL, 0, 0, set.Width, set.Height, SWP_NOMOVE | SWP_NOZORDER);
}

void MicroFlakeX::MfxUI::SetPoint(Gdiplus::Point set)
{
	SetWindowPos(myWnd, NULL, set.X, set.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

/* ———————————————————————————————————————————— */
/* ——————————————下面的代码是默认响应———————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnDrawBuffDC(WPARAM wParam, LPARAM lParam)
{

	UIDrawBufferDCBack(); //重置缓冲区背景

	for (int i = 0; i < myControlList.size(); i++) //通知控件BUFFDC
	{
		myControlList[i]->RecvMessage(MFXUIEVENT_DRAWBUFFDC, wParam, lParam);
	}

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnDrawMainDC(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < myControlList.size(); i++) //通知控件MAINDC
	{
		myControlList[i]->RecvMessage(MFXUIEVENT_DRAWMAINDC, wParam, lParam);
	}

	UIDrawMainDCMask(); //添加主画板蒙版

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnControlCreate(WPARAM wParam, LPARAM lParam)
{
	if(!lParam)
		this-RegControl((MicroFlakeX::MfxControl*)wParam);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnControlDelete(WPARAM wParam, LPARAM lParam)
{
	this->DelControl((MicroFlakeX::MfxControl*)wParam);
	return 0;
}

bool comp(MicroFlakeX::MfxControl* a, MicroFlakeX::MfxControl* b)
{
	return a->GetFloor() < b->GetFloor();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIFloorChange(WPARAM wParam, LPARAM lParam)
{
	if(!lParam)
		std::sort(myControlList.begin(), myControlList.end(), comp);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIPaint(WPARAM wParam, LPARAM lParam)
{
	BeginDrawBufferDC:
		PAINTSTRUCT ps;

		HDC hDc = BeginPaint(myWnd, &ps); //开始绘画

		//需不需要重绘缓冲界面 - 也就是重绘底层图片
		if (wParam == MFXUIPAINTTYPE_PAINTALL || wParam & MFXUIPAINTTYPE_DRAWBUFFDC) 
		{
			MfxDefOnDrawBuffDC((WPARAM)&ps, (LPARAM)hDc); //绘制缓冲区
		}

		//需不需要把缓冲界面拷贝到主界面中
		if (wParam == MFXUIPAINTTYPE_PAINTALL || wParam & MFXUIPAINTTYPE_COPYBUFFDCTOMAINDC)
		{
			UICopyBufferDCToMainDC(); //拷贝缓冲区到主界面
		}
		
	EndDrawBufferDC:
		//需不需要绘制主界面 - 也就是需不需要添加蒙版
		if (wParam == MFXUIPAINTTYPE_PAINTALL || wParam & MFXUIPAINTTYPE_DRAWMAINDC) 
		{
			MfxDefOnDrawMainDC((WPARAM)&ps, (LPARAM)hDc); //绘制主界面
		}
		
		//需不需要将主界面显示到用户界面
		if (wParam == MFXUIPAINTTYPE_PAINTALL || wParam & MFXUIPAINTTYPE_COPYMAINDCTOSHOWDC)
		{
			UICopyMainDCToShowDC(); //拷贝主画板到显示界面
		}

		EndPaint(myWnd, &ps); //结束绘画

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUITimer(WPARAM wParam, LPARAM lParam)
{
	MFXUI_CLOCK_MAPITERA delIter = myClockList.find(wParam);
	if (delIter != myClockList.end())
	{
		SendMessage(myWnd, (*delIter).second.message, (*delIter).second.wParam, (*delIter).second.lParam);
	}
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
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEraseBack(WPARAM wParam, LPARAM lParam)
{
	/* 什么也不做，因为我是DirectUI库，而且双缓冲绘图，所以不需要擦除主画板的背景 */
	return 0;
}


MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUISize(WPARAM wParam, LPARAM lParam)
{
	// 当大小正在发生改变
	MFXUI_CHANGESIZE tSize;
	tSize.bRect = myRect;
	tSize.aRect = Gdiplus::Rect(myRect.X, myRect.Y, LOWORD(lParam), HIWORD(lParam));

	// 通知控件们，大小发生改变 
	for (int i = 0; i < myControlList.size(); i++)
	{
		myControlList[i]->RecvMessage(MFXUIEVENT_FATHERSIZE, 0, (LPARAM)&tSize);
	}

	// 通知子窗口们，大小发生改变
	EnumChildWindows(myWnd, MfxEnumFatherSize, (LPARAM)&tSize); 

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
		myBackImage->SetSize(Gdiplus::Size(myRect.Width, myRect.Height));
	}

	if (myMaskImage)
	{
		myMaskImage->SetSize(Gdiplus::Size(myRect.Width, myRect.Height));
	}
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUISizing(WPARAM wParam, LPARAM lParam)
{
	/* 大小改变之后才会发送一次这个消息 */
	return DefWindowProc(myWnd, WM_SIZING, wParam, lParam);
}


MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIMove(WPARAM wParam, LPARAM lParam)
{
	/* 还没想好要做啥，可是移动的时候确实没事可做啊，或许加个物理特效吗？ */
	myRect.X = LOWORD(lParam);
	myRect.Y = HIWORD(lParam);
	return DefWindowProc(myWnd, WM_MOVE, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIMoving(WPARAM wParam, LPARAM lParam)
{
	/* 好家伙，移动结束后才会接收一次 */
	return DefWindowProc(myWnd, WM_MOVING, wParam, lParam);
}


MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILButtonDown(WPARAM wParam, LPARAM lParam)
{
	BringWindowToTop(myWnd);
	//PostMessage(myWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	return DefWindowProc(myWnd, WM_LBUTTONDOWN, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(myWnd, WM_LBUTTONUP, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUILDoubleClick(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(myWnd, WM_LBUTTONDBLCLK, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRButtonDown(WPARAM wParam, LPARAM lParam)
{
	BringWindowToTop(myWnd);
	return DefWindowProc(myWnd, WM_RBUTTONDOWN, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(myWnd, WM_RBUTTONUP, wParam, lParam);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIRDoubleClick(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(myWnd, WM_RBUTTONDBLCLK, wParam, lParam);
}

/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */
/* ———————————————————————————————————————————— */

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIFatherSize(WPARAM wParam, LPARAM lParam)
{
	MFXUI_CHANGESIZE* getSize = (MFXUI_CHANGESIZE*)lParam;
	/* 算吧，这里给出了前后坐标，怎么搞就是你的事情了 */
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxUI::MfxDefOnUIEventSizing(WPARAM wParam, LPARAM lParam)
{
	return 0;
}