#pragma once

/**************************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*
*	MfxAppFrame.h	提供了	MicroFlakeX	的UI框架
*
*	包含了MfxUI、MfxFlake
*
**************************************************************/

#ifdef MFXDLL_BUILDING
#define MFX_PORT __declspec(dllexport)
#else
#define MFX_PORT __declspec(dllimport)
#pragma comment(lib, "MfxAppFrame.lib")
#include "MfxGraph.h"

#include <set>
#include <thread>

#include <deque>
#include <windowsx.h>
#endif

namespace MicroFlakeX
{
	class MFX_PORT MfxUI;
	class MFX_PORT MfxFlake;

	typedef MfxUI* pMfxUI;
	typedef MfxFlake* pMfxFlake;

	typedef std::unordered_set<pMfxFlake> MfxFlake_Set;
	typedef std::deque<pMfxFlake> MfxFlake_Deque;
	typedef std::vector<pMfxFlake> MfxFlake_Vector;

	/**************************************************************
	*	App_UI_Info 映射了从win32的hwnd句柄到MfxUI指针
	**************************************************************/
	struct App_UI_Info
	{
		App_UI_Info(HWND hWnd, pMfxUI pUI)
		{
			myUI = pUI;
			myWnd = hWnd;
		}
		HWND myWnd;
		pMfxUI myUI;
	};

	typedef std::unordered_map<HWND, App_UI_Info> App_UI_Info_Map;
	typedef App_UI_Info_Map::value_type App_UI_Info_Map_Elem;


	/**************************************************************
	*	pUIRecvFunc 是一个标准的接收消息的函数指针
	***************************************************************/
	typedef MfxReturn(MfxUI::* pUIRecvFunc)(MfxParam);

	/**************************************************************
	*	UI_UIRecvFunc_Info 这里面存储了 "消息映射" 的具体信息
		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数
		处于消息接收链的第几层
	***************************************************************/
	struct UI_UIRecvFunc_Info
	{
		UI_UIRecvFunc_Info()
		{
			recvFunc = 0;
		}
		UI_UIRecvFunc_Info(pUIRecvFunc pFunc, MfxString funcName)
		{
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxString myRecvFuncName;
		pUIRecvFunc recvFunc;
	};
	typedef std::deque<UI_UIRecvFunc_Info> UI_UIRecvFunc_Infor_Deque;

	typedef std::unordered_map<MfxMessage, UI_UIRecvFunc_Infor_Deque> UI_UIMessage_Map;
	typedef UI_UIMessage_Map::value_type UI_UIMessage_Map_Elem;


	/**************************************************************
	*	FlakeEvent_Info 标识了来自哪个MfxFlake控件，以及MfxFlake
		控件发出了什么消息同时MfxUI_FlakeMsg_Key重载了operator< 使
		其可以进行排序算法
	***************************************************************/
	struct FlakeEvent_Info
	{
		FlakeEvent_Info()
		{
			myFlake = nullptr;
			myEvent = 0;
		}
		FlakeEvent_Info(pMfxFlake setFlake, MfxMessage setEvent)
		{
			myFlake = setFlake;
			myEvent = setEvent;
		}
		pMfxFlake myFlake;
		MfxMessage myEvent;
		MfxString recvFuncName;

		bool operator< (const FlakeEvent_Info& rhs) const
		{
			if (myFlake != rhs.myFlake)
			{
				return (myFlake < rhs.myFlake);
			}
			else
			{
				return (myFlake < rhs.myFlake) || (myEvent < rhs.myEvent);
			}
		}
		bool operator==(const FlakeEvent_Info& rhs) const
		{
			return (myFlake == rhs.myFlake) && (myEvent == rhs.myEvent);
		}

		std::size_t operator()(const FlakeEvent_Info& key) const
		{
			return std::hash<int>()((int)key.myFlake);
		}
	};
	typedef FlakeEvent_Info* pFlakeEvent_Info;

	typedef std::unordered_map<FlakeEvent_Info, UI_UIRecvFunc_Infor_Deque, FlakeEvent_Info> UI_FlakeEvent_Map;
	typedef UI_FlakeEvent_Map::value_type UI_FlakeMsg_Map_Elem;

	/**************************************************************
	*	Win32_Timer_Info 标识了定时器ID以及其接收函数
	***************************************************************/
	struct Win32_Timer_Info
	{
		Win32_Timer_Info()
		{
			myID = 0;
			delayTime = 0;
			recvFunc = nullptr;
		}

		Win32_Timer_Info(ULONG id, ULONG delay, pUIRecvFunc pRecvFunc)
		{
			myID = id;
			delayTime = delay;
			recvFunc = pRecvFunc;
		}
		ULONG myID;
		ULONG delayTime;
		pUIRecvFunc recvFunc;
	};


	typedef std::unordered_map<MfxMessage, Win32_Timer_Info> Win32_Timer_Info_Map;
	typedef Win32_Timer_Info_Map::value_type Win32_Timer_Info_Map_Elem;


	/**************************************************************
	*	Paper_Infor 标识了当前UI的状态当 MfxFlake 添加到 MfxUI 的时候，发送一次
	***************************************************************/
	struct Paper_Infor
	{
		Paper_Infor(pMfxBase father, HWND setWnd, MfxCanvas* setCanvas)
		{
			myFather = father;
			myWnd = setWnd;
			myCanvas = setCanvas;
		}
		Paper_Infor()
		{
			myWnd = NULL;
			myFather = nullptr;
			myCanvas = nullptr;
		}

		HWND myWnd;
		pMfxBase myFather;
		MfxCanvas* myCanvas;

	};


	/**************************************************************
	*	pFlakeRecvFunc 是一个标准的接收消息的函数指针
	***************************************************************/
	typedef MfxReturn(MfxFlake::* pFlakeRecvFunc)(MfxParam);

	/**************************************************************
	*	Flake_RecvFunc_Infor 这里面存储了 "消息映射" 的具体信息例如
		消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消
		息接收链的第几层
	***************************************************************/
	struct Flake_RecvFunc_Infor
	{
		Flake_RecvFunc_Infor()
		{
			recvFunc = 0;
		}
		Flake_RecvFunc_Infor(pFlakeRecvFunc pFunc, MfxString funcName)
		{
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxString myRecvFuncName;
		pFlakeRecvFunc recvFunc;
	};

	typedef std::deque<Flake_RecvFunc_Infor> Flake_RecvFunc_Infor_Deque;

	typedef std::unordered_map<MfxMessage, Flake_RecvFunc_Infor_Deque> Flake_FlakeMessage_Map;
	typedef Flake_FlakeMessage_Map::value_type Flake_FlakeMessage_Map_Elem;

	typedef std::unordered_map<FlakeEvent_Info, Flake_RecvFunc_Infor_Deque, FlakeEvent_Info> Flake_FlakeEvent_Map;
	typedef Flake_FlakeEvent_Map::value_type Flake_FlakeEvent_Map_Elem;
}

namespace __MicroFlakeX
{
	using namespace MicroFlakeX;

	MFX_PORT constexpr MfxMessage MSG_COUNT();
	MFX_PORT constexpr MfxMessage MSG_COUNT_RESET(MfxMessage num = 0xBFFF);
}

namespace MicroFlakeX
{
	const MfxMessage MFX_MSG_RESET = __MicroFlakeX::MSG_COUNT_RESET();
#define MFX_MSG(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
#define UI_MSG(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
#define FLAKE_MSG(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()

#define MFX_EVENT(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
#define UI_EVENT(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()
#define FLAKE_EVENT(MSG) const MfxMessage MSG = __MicroFlakeX::MSG_COUNT()

	/**************************************************************
	*	MFX消息
	***************************************************************/
	MFX_MSG(MSG_FlakeInsert);
	MFX_MSG(MSG_FlakeRemove);

	MFX_MSG(MSG_UIEvent);
	MFX_MSG(MSG_FlakeEvent);

	MFX_MSG(MSG_FlakeFloorChange);
	/**************************************************************
	*	UI消息
	***************************************************************/
	UI_MSG(UI_MSG_PaintBack);
	UI_MSG(UI_MSG_PaintMask);

	UI_MSG(UI_MSG_RemoveFlakeEvent);
	UI_MSG(UI_MSG_PushBackFlakeEvent);
	UI_MSG(UI_MSG_PushFrontFlakeEvent);

	UI_MSG(UI_MSG_RemoveWin32Timer);
	UI_MSG(UI_MSG_InsertWin32Timer);

	UI_MSG(UI_MSG_OpenPercentRect);
	UI_MSG(UI_MSG_ClosePercentRect);

	UI_MSG(UI_MSG_SetBackColor);
	UI_MSG(UI_MSG_SetMaskColor);

	/**************************************************************
	*	Flake消息
	***************************************************************/
	FLAKE_MSG(FLAKE_MSG_PaintBack);
	FLAKE_MSG(FLAKE_MSG_PaintMask);

	FLAKE_MSG(FLAKE_MSG_RemoveFlakeEvent);
	FLAKE_MSG(FLAKE_MSG_PushBackFlakeEvent);
	FLAKE_MSG(FLAKE_MSG_PushFrontFlakeEvent);

	FLAKE_MSG(FLAKE_MSG_SetPaper);
	FLAKE_MSG(FLAKE_MSG_RemovePaper);

	FLAKE_MSG(FLAKE_MSG_OpenPercentRect);
	FLAKE_MSG(FLAKE_MSG_ClosePercentRect);

	FLAKE_MSG(FLAKE_MSG_Rect);
	FLAKE_MSG(FLAKE_MSG_PercentRect);

	FLAKE_MSG(FLAKE_MSG_ResetRect);
	FLAKE_MSG(FLAKE_MSG_ResetPercentRect);

	FLAKE_MSG(FLAKE_MSG_SetFloor);

	FLAKE_MSG(FLAKE_MSG_SetWords);
	FLAKE_MSG(FLAKE_MSG_SetTitle);
	FLAKE_MSG(FLAKE_MSG_SetTitleSize);
	FLAKE_MSG(FLAKE_MSG_SetTitleColor);

	FLAKE_MSG(FLAKE_MSG_SetBackColor);
	FLAKE_MSG(FLAKE_MSG_SetMaskColor);
	FLAKE_MSG(FLAKE_MSG_SetBackFrameSize);
	FLAKE_MSG(FLAKE_MSG_SetMaskFrameSize);

	/**************************************************************
	*	MFX事件
	***************************************************************/
	FLAKE_MSG(FLAKE_EVENT_MouseMove);

	FLAKE_MSG(FLAKE_EVENT_LButtonClick);
	FLAKE_MSG(FLAKE_EVENT_RButtonClick);

	/**************************************************************
	*	UI事件
	***************************************************************/

	/**************************************************************
	*	Flake事件
	***************************************************************/


	/**************************************************************
	*	UI_STYLE定义了MfxUI可以创建的窗口类型
	*	UI_WINDOWS_STYLE_AntiFlicker - 防止闪烁 - 原理：在移动子窗口的时候，不刷新
	*	UI_WINDOWS_STYLE_Normal - 正常的窗口
	***************************************************************/
	enum UI_WINDOWS_STYLE
	{
		UI_WINDOWS_STYLE_AntiFlicker = WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		UI_WINDOWS_STYLE_Normal = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME
	};
}

namespace MicroFlakeX
{
#define MAKE_WIN32_PARAM(name, msg, hwnd, wParam, lParam) \
	MfxParam name(msg);\
	name.push_back(hwnd);\
	name.push_back(wParam);\
	name.push_back(lParam);\

#define GetMSG(param) param.NowMessage()
#define GetHWND(param) GetParam_Safe(param, HWND, 0)
#define GetWPARAM(param) GetParam_Safe(param, WPARAM, 1)
#define GetLPARAM(param) GetParam_Safe(param, LPARAM, 2)

	MFX_PORT WPARAM MfxAppRun();
}

namespace __MicroFlakeX
{
	MFX_PORT HWND MfxCreateWindowsEx(pMfxUI ui, pMfxUI father, MfxRect rect, DWORD dwStyle, DWORD dwExStyle,
		MfxString className, MfxString windowsName);

	MFX_PORT LRESULT CALLBACK MfxAppFrameProc(HWND hWnd, MfxMessage msg, WPARAM wParam, LPARAM lParam);
}

namespace MicroFlakeX
{
	/* 延迟初始化MfxUI - 暂时还没想好怎么做 */
	class MfxUI :
		public MfxBase
	{
		MfxObject;
	private:
		void MfxUIInitData();
		void MfxRegMessages();
	public:
		MfxUI(MfxRect set = MfxRect(60, 60, 400, 400), MfxString title = MfxText("MfxNormalUI"), DWORD myStyle = UI_WINDOWS_STYLE_Normal, DWORD myStyleEx = WS_EX_LAYERED, MfxUI* father = nullptr);
		virtual ~MfxUI();

		MfxReturn CreateSuccess();
	private:
		MfxReturn ProcMessage(MfxParam param);
		MfxReturn ProcFlakesMessage(MfxParam param);
		MfxReturn RProcFlakesMessage(MfxParam param);
	
	public:
		MfxReturn Send_Message(MfxParam param);
		MfxReturn Post_Message(MfxParam param);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		MfxFlake_Set myFlakeSet;
		MfxFlake_Deque myFlakeDeque;
	public:
		MfxReturn RemoveFlake(pMfxFlake set);
		MfxReturn InsertFlake(pMfxFlake set);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		Win32_Timer_Info_Map myTimerMap;
	public:
		MfxReturn RemoveWin32Timer(ULONG setID);
		MfxReturn InsertWin32Timer(Win32_Timer_Info timer);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		UI_UIMessage_Map myMessageMap;
	public:
		MfxReturn RemoveUIMessage(MfxMessage message, MfxString recvFuncName);
		MfxReturn PushBackUIMessage(MfxMessage message, UI_UIRecvFunc_Info msgValue);
		MfxReturn PushFrontUIMessage(MfxMessage message, UI_UIRecvFunc_Info msgValue);
		
		/********************************************************************************
		*
		*********************************************************************************/
	private:
		UI_FlakeEvent_Map myFlakeEventMap;
	public:
		MfxReturn RemoveFlakeEvent(FlakeEvent_Info message, MfxString recvFuncName);
		MfxReturn PushBackFlakeEvent(FlakeEvent_Info message, UI_UIRecvFunc_Info msgValue);
		MfxReturn PushFrontFlakeEvent(FlakeEvent_Info message, UI_UIRecvFunc_Info msgValue);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		bool myPercentRectFlag;
	public:
		MfxReturn OpenPercentRect();
		MfxReturn ClosePercentRect();
		MfxReturn ChickPercentRect(bool* ret);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		pMfxFlake myMutexFocus;
		MfxFlake *myKeyboardFocus;

		bool myMutexFocusLockFlag;
		bool myKeyboardFocusLockFlag;
	public:
		MfxReturn LockMutexFocus(pMfxFlake set);
		MfxReturn UnLockMutexFocus();

		MfxReturn SetMutexFocus(pMfxFlake set);
		MfxReturn GetMutexFocus(pMfxFlake* ret);

		MfxReturn SetKeyboardFocus(pMfxFlake set);
		MfxReturn GetKeyboardFocus(pMfxFlake* ret);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		MfxRect myInvalidateRect;
	public:
		MfxReturn UnionInvalidateRect(MfxRect set, double inflate = 1);

		/********************************************************************************
		*
		*********************************************************************************/
	protected:
		HWND myWnd;
		MfxCanvas myCanvas;

	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetCanvas(MfxCanvas** ret);

		MfxReturn GetWorldRect(MfxRect* ret);
		MfxReturn GetLocalMousePos(MfxPoint* ret);
		MfxReturn TransWorldRectToLocalRect(MfxRect* world, MfxRect* local);
		MfxReturn TransWorldPointToLocalPoint(MfxPoint* world, MfxPoint* local);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		MfxRect myRect;

		MfxColor myBackColor;
		MfxColor myMaskColor;

		MfxRectangle myBackRectangle;
		MfxRectangle myMaskRectangle;
	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);

		MfxReturn GetBackColor(MfxColor* ret);
		MfxReturn GetMaskColor(MfxColor* ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);

		MfxReturn SetBackColor(MfxColor* set);
		MfxReturn SetMaskColor(MfxColor* set);

	public:
		MfxReturn SetBigIcon(MfxImage* set);
		MfxReturn SetSmallIcon(MfxImage* set);


		//LWA_COLORKEY
		//LWA_ALPHA
	private:
		MfxColor myGlobeAlpha;
		UINT myGlobeAlphaMode;
	public:
		MfxReturn GetGlobeAlpha(MfxColor* set);
		MfxReturn GetGlobeAlphaMode(UINT set);
	public:
		MfxReturn SetGlobeAlpha(MfxColor* set);
		MfxReturn SetGlobeAlphaMode(UINT set);

	public:
		MfxReturn SetUI_Max();
		MfxReturn SetUI_Min();
		MfxReturn SetUI_Show();
		MfxReturn SetUI_Hide();
		MfxReturn SetUI_Normal();

		/********************************************************************************
		*
		*
		*
		*********************************************************************************/
	public:
		MfxReturn __OnTest00(MfxParam param);
		MfxReturn __OnTest01(MfxParam param);
	private:
		MfxReturn __OnCreate(MfxParam param);
		MfxReturn __OnDestroy(MfxParam param);

		MfxReturn __OnSize(MfxParam param);
		MfxReturn __OnMove(MfxParam param);

		MfxReturn __OnPaint(MfxParam param);
		MfxReturn __OnEraseBackGrand(MfxParam param);

		MfxReturn __OnPaintBackDC(MfxParam param);
		MfxReturn __OnPaintMaskDC(MfxParam param);

		MfxReturn __OnFlakeInsert(MfxParam param);
		MfxReturn __OnFlakeRemove(MfxParam param);
		MfxReturn __OnFlakeFloorChange(MfxParam param);

		MfxReturn __OnWin32Timer(MfxParam param);

		MfxReturn __OnInsertWin32Timer(MfxParam param);
		MfxReturn __OnRemoveWin32Timer(MfxParam param);

		MfxReturn __OnFlakeEvent(MfxParam param);

		MfxReturn __OnRemoveFlakeEvent(MfxParam param);
		MfxReturn __OnPushBackFlakeEvent(MfxParam param);
		MfxReturn __OnPushFrontFlakeEvent(MfxParam param);

		MfxReturn __OnOpenPercentRect(MfxParam param);
		MfxReturn __OnClosePercentRect(MfxParam param);

		MfxReturn __OnSetBackColor(MfxParam param);
		MfxReturn __OnSetMaskColor(MfxParam param);



		MfxReturn __OnNCPaint(MfxParam param);
		MfxReturn __OnNCHitTest(MfxParam param);
		MfxReturn __OnNCActivate(MfxParam param);

		MfxReturn __OnNCMouseMove(MfxParam param);
		MfxReturn __OnNCMouseHover(MfxParam param);

		MfxReturn __OnNCLButtonUp(MfxParam param);
		MfxReturn __OnNCLButtonDown(MfxParam param);
		MfxReturn __OnNCLButtonDouble(MfxParam param);

		MfxReturn __OnNCRButtonUp(MfxParam param);
		MfxReturn __OnNCRButtonDown(MfxParam param);
		MfxReturn __OnNCRButtonDouble(MfxParam param);
	};

/********************************************************************************
* 为UI添加一个来自控件的消息映射
*********************************************************************************/
#define UI_ADDRECV_FLAKEMSG(Flake, Event, myClass, recvFunc) PushBackFlakeEvent(FlakeEvent_Info(Flake, Event), UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自窗口的消息映射
*********************************************************************************/
#define UI_ADDRECV_UIMSG(Msg, myClass, recvFunc) PushBackUIMessage(Msg, UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自定时器的消息映射
*********************************************************************************/
#define UI_ADDRECV_TIMER(timerID, delay, recvFunc) InsertWin32Timer(timerID, delay, (pUIRecvFunc)&recvFunc)

}

namespace MicroFlakeX
{
	/********************************************************************************
	*
	*********************************************************************************/
	class MfxFlake :
		public MfxBase
	{
		MfxObject;
		MFX_FloorCompare_Enable;
	private:
		void MfxRegMessages();
		void MfxFlakeInitData();
	public:
		MfxFlake();
		MfxFlake(MfxRect set);
		virtual ~MfxFlake();

	private:
		MfxReturn ProcMessage(MfxParam param);

	public:
		MfxReturn Send_Message(MfxParam param);
		MfxReturn Post_Message(MfxParam param);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		Flake_FlakeMessage_Map myMessageMap;
	public:
		MfxReturn RemoveFlakeMessage(MfxMessage message, MfxString name);
		MfxReturn PushBackFlakeMessage(MfxMessage message, Flake_RecvFunc_Infor msgValue);
		MfxReturn PushFrontFlakeMessage(MfxMessage message, Flake_RecvFunc_Infor msgValue);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		Flake_FlakeEvent_Map myFlakeEventMap;
	public:
		MfxReturn RemoveFlakeEvent(FlakeEvent_Info message, MfxString recvFuncName);
		MfxReturn PushBackFlakeEvent(FlakeEvent_Info message, Flake_RecvFunc_Infor msgValue);
		MfxReturn PushFrontFlakeEvent(FlakeEvent_Info message, Flake_RecvFunc_Infor msgValue);
		/********************************************************************************
		*
		*********************************************************************************/
	private:
		bool myPercentRectFlag;
	public:
		MfxReturn OpenPercentRect();
		MfxReturn ClosePercentRect();
		MfxReturn ChickPercentRect();

	private:
		HWND myWnd;
		pMfxBase myFather;
		MfxFloor myFloor;
		MfxCanvas* myCanvas;
	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetFloor(MfxFloor* ret);
		MfxReturn GetFather(pMfxBase* ret);
		MfxReturn GetCanvas(MfxCanvas** ret);

		MfxReturn SetFloor(MfxFloor floor);
		

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		MfxRect myRect;
		MfxRect myEdgeRect;
		MfxRect myPercentRect;

		MfxString myTitle;

		MfxColor myBackColor;
		MfxColor myMaskColor;
		MfxColor myTitleColor;
		double myBackFrameSize;
		double myMaskFrameSize;

		MfxWords* myWords;
		MfxRectangle myBackRectangle;
		MfxRectangle myMaskRectangle;

	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);
		MfxReturn GetEdgeRect(MfxRect* ret);

		MfxReturn GetTitle(MfxString* ret);
		MfxReturn GetTitleSize(DOUBLE* ret);

		MfxReturn GetWords(MfxWords** ret);
		MfxReturn GetBackColor(MfxColor* ret);
		MfxReturn GetMaskColor(MfxColor* ret);
		MfxReturn GetTitleColor(MfxColor* ret);

		MfxReturn GetBackFrameSize(double* ret);
		MfxReturn GetMaskFrameSize(double* ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);
		MfxReturn SetEdgeRect(MfxRect* set);

		MfxReturn SetTitle(MfxString set);
		MfxReturn SetTitleSize(DOUBLE set);

		MfxReturn SetWords(MfxWords* set);
		MfxReturn SetBackColor(MfxColor* set);
		MfxReturn SetMaskColor(MfxColor* set);
		MfxReturn SetTitleColor(MfxColor* set);

		MfxReturn SetBackFrameSize(double set);
		MfxReturn SetMaskFrameSize(double set);


		/********************************************************************************
		*
		*
		*********************************************************************************/
	protected:
		bool myMouseFloat;
		bool myMouseHover;

		bool myLButtonPress;
		bool myLButtonClickFlag;

		bool myRButtonPress;
		bool myRButtonClickFlag;

		bool myLButtonMoveFlag;
		bool myRButtonMoveFlag;
	protected:
		MfxPoint myButtonMoveBegin;
	public:
		MfxReturn OpenLButtonMove();
		MfxReturn CloseLButtonMove();

		MfxReturn OpenRButtonMove();
		MfxReturn CloseRButtonMove();

		/********************************************************************************
		*
		*
		*********************************************************************************/
		MfxReturn __OnTest001(MfxParam param);
private:
		MfxReturn __OnSetPaper(MfxParam param);
		MfxReturn __OnRemovePaper(MfxParam param);

		MfxReturn __OnSetFloor(MfxParam param);

		MfxReturn __OnPaintBackDC(MfxParam param);
		MfxReturn __OnPaintMaskDC(MfxParam param);

		MfxReturn __OnUISize(MfxParam param);

		MfxReturn __OnRect(MfxParam param);
		MfxReturn __OnPercentRect(MfxParam param);

		MfxReturn __OnResetRect(MfxParam param);
		MfxReturn __OnResetPercentRect(MfxParam param);

		MfxReturn __OnOpenPercentRect(MfxParam param);
		MfxReturn __OnClosePercentRect(MfxParam param);

		//
		MfxReturn __OnNCMouseMove(MfxParam param);
		MfxReturn __OnNCMouseHover(MfxParam param);

		MfxReturn __OnNCLButtonUp(MfxParam param);
		MfxReturn __OnNCLButtonDown(MfxParam param);
		MfxReturn __OnNCLButtonDouble(MfxParam param);

		MfxReturn __OnNCRButtonUp(MfxParam param);
		MfxReturn __OnNCRButtonDown(MfxParam param);
		MfxReturn __OnNCRButtonDouble(MfxParam param);
		//

		MfxReturn __OnMouseMove(MfxParam param);
		MfxReturn __OnMouseHover(MfxParam param);

		MfxReturn __OnLButtonUp(MfxParam param);
		MfxReturn __OnLButtonDown(MfxParam param);
		MfxReturn __OnLButtonDouble(MfxParam param);

		MfxReturn __OnRButtonUp(MfxParam param);
		MfxReturn __OnRButtonDown(MfxParam param);
		MfxReturn __OnRButtonDouble(MfxParam param);

		MfxReturn __OnSetTitle(MfxParam param);

		MfxReturn __OnSetBackColor(MfxParam param);
		MfxReturn __OnSetMaskColor(MfxParam param);
		MfxReturn __OnSetTitleColor(MfxParam param);

		MfxReturn __OnSetBackFrameSize(MfxParam param);
		MfxReturn __OnSetMaskFrameSize(MfxParam param);

		MfxReturn __OnSetWords(MfxParam param);

		MfxReturn __OnFlakeEvent(MfxParam param);

		MfxReturn __OnRemoveFlakeEvent(MfxParam param);
		MfxReturn __OnPushBackFlakeEvent(MfxParam param);
		MfxReturn __OnPushFrontFlakeEvent(MfxParam param);
	};

/********************************************************************************
* 为Flake添加一个来自Flake的消息映射
*********************************************************************************/
#define FLAKE_ADDRECV_FLAKEMSG(Msg, myClass, recvFunc) PushBackFlakeMessage(Msg, Flake_RecvFunc_Infor((pFlakeRecvFunc)&myClass::recvFunc, MfxText(#myClass#recvFunc)));

}