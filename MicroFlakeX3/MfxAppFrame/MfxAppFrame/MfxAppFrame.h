#pragma once

/**************************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*
*	MfxAppFrame.h	提供了	MicroFlakeX	的UI框架
*
*	包含了MfxApp、MfxUI、MfxFlake
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
	class MFX_PORT MfxApp;
	class MFX_PORT MfxUI;
	class MFX_PORT MfxFlake;


	typedef MfxApp* pMfxApp;
	typedef MfxUI* pMfxUI;
	typedef MfxFlake* pMfxFlake;

	typedef std::unordered_set<pMfxFlake> MfxFlake_Set;
	typedef std::deque<pMfxFlake> MfxFlake_Deque;
	typedef std::vector<pMfxFlake> MfxFlake_Vector;


	/**************************************************************
	*	MfxMessage	为Mfx框架使用的消息标识号，是一个UINT类型
	**************************************************************/
	typedef UINT MfxMessage;

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
		Paper_Infor(pMfxUI setUI, HWND setWnd, MfxCanvas* setCanvas)
		{
			myUI = setUI;
			myWnd = setWnd;
			myCanvas = setCanvas;
		}
		Paper_Infor()
		{
			myWnd = NULL;
			myUI = nullptr;
			myCanvas = nullptr;
		}

		HWND myWnd;
		pMfxUI myUI;
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

namespace MicroFlakeX
{
	/**************************************************************
	*	MFX_MSG定义了每个类型允许使用的消息范围
	***************************************************************/
	const MfxMessage UI_MSG_BEGIN = 0xBFFF;
	const MfxMessage UI_MSG_END = UI_MSG_BEGIN - 256;

	const MfxMessage FLAKE_MSG_BEGIN = UI_MSG_END;
	const MfxMessage FLAKE_MSG_END = FLAKE_MSG_BEGIN - 256;


	/**************************************************************
	*	UI_MSG定义了MfxUI类型所产生的消息
	***************************************************************/
	const int UI_MSG_COUNT = __COUNTER__;
#define UI_MSG_(MSG) const MfxMessage MSG = UI_MSG_BEGIN - MFX_COUNT(UI_MSG_COUNT)
	UI_MSG_(UI_MSG_PaintBack);
	UI_MSG_(UI_MSG_PaintMask);

	UI_MSG_(UI_MSG_FlakeInsert);
	UI_MSG_(UI_MSG_FlakeRemove);

	UI_MSG_(UI_MSG_RemoveFlakeEvent);
	UI_MSG_(UI_MSG_PushBackFlakeEvent);
	UI_MSG_(UI_MSG_PushFrontFlakeEvent);

	UI_MSG_(UI_MSG_RemoveWin32Timer);
	UI_MSG_(UI_MSG_InsertWin32Timer);

	UI_MSG_(UI_MSG_SetBackColor);
	UI_MSG_(UI_MSG_SetMaskColor);
	UI_MSG_(UI_MSG_SetBackImage);
	UI_MSG_(UI_MSG_SetMaskImage);

	UI_MSG_(UI_MSG_OpenPercentRect);
	UI_MSG_(UI_MSG_ClosePercentRect);

	UI_MSG_(MSG_FlakeEvent);

	UI_MSG_(UI_MSG_FlakeFloorChange);


	/**************************************************************
	*	FLAKE_MSG定义了MfxFlake类型所产生的消息
	***************************************************************/
	const int FLAKE_MSG_COUNT = __COUNTER__;
#define FLAKE_MSG_(MSG) const MfxMessage MSG = FLAKE_MSG_BEGIN - MFX_COUNT(FLAKE_MSG_COUNT)
	FLAKE_MSG_(FLAKE_MSG_RemoveFlakeEvent);
	FLAKE_MSG_(FLAKE_MSG_PushBackFlakeEvent);
	FLAKE_MSG_(FLAKE_MSG_PushFrontFlakeEvent);

	FLAKE_MSG_(FLAKE_MSG_SetPaper);
	FLAKE_MSG_(FLAKE_MSG_RemovePaper);

	FLAKE_MSG_(FLAKE_MSG_PaintBack);
	FLAKE_MSG_(FLAKE_MSG_PaintMask);

	FLAKE_MSG_(FLAKE_MSG_Rect);
	FLAKE_MSG_(FLAKE_MSG_PercentRect);

	FLAKE_MSG_(FLAKE_MSG_ResetRect);
	FLAKE_MSG_(FLAKE_MSG_ResetPercentRect);

	FLAKE_MSG_(FLAKE_MSG_OpenPercentRect);
	FLAKE_MSG_(FLAKE_MSG_ClosePercentRect);

	FLAKE_MSG_(FLAKE_MSG_LButtonClick);
	FLAKE_MSG_(FLAKE_MSG_RButtonClick);

	FLAKE_MSG_(FLAKE_MSG_SetFloor);
	FLAKE_MSG_(FLAKE_MSG_SetTitle);

	FLAKE_MSG_(FLAKE_MSG_SetBackColor);
	FLAKE_MSG_(FLAKE_MSG_SetMaskColor);
	FLAKE_MSG_(FLAKE_MSG_SetBackImage);
	FLAKE_MSG_(FLAKE_MSG_SetMaskImage);

	FLAKE_MSG_(FLAKE_MSG_SetWords);
	FLAKE_MSG_(FLAKE_MSG_SetTitleSize);
	FLAKE_MSG_(FLAKE_MSG_SetTitleColor);
		
	FLAKE_MSG_(FLAKE_MSG_GetTitleSize);


	/**************************************************************
	*	UI_STYLE定义了MfxUI可以创建的窗口类型
	*	UI_WINDOWS_STYLE_AntiFlicker - 防止闪烁 - 原理：在移动子窗口的时候，不刷新
	*	UI_WINDOWS_STYLE_Normal - 正常的窗口
	***************************************************************/
	enum UI_WINDOWS_STYLE
	{
		UI_WINDOWS_STYLE_AntiFlicker = WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		UI_WINDOWS_STYLE_Normal = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_VISIBLE
	};
}

namespace MicroFlakeX
{

	/**************************************************************
	*	MfxApp - 单例模式
	*		这个类型在每个程序中，仅允许同时存在1个实例化的对象。
	*	这个对象会在程序开始执行之前自动创建，若要使用这个对象，
	*	请使用 MfxApp::g_pApp 或者 MFXAPP 宏
	*	使用 MFXAPP->Run(); 才能开始整个程序。
	*	当 MFXAPP->Run(); 返回时，程序结束，返回值为结束标志。
	***************************************************************/
	class MfxApp
	{
	private:
		MfxApp();
		virtual ~MfxApp();

	public:
		WPARAM Run();
	public:	
		static MfxApp* const g_pApp;
		static HINSTANCE const g_hInstance;

	private:
		pMfxUI myBindingUI;
	public:
		HWND MfxCreateUIEx(pMfxUI ui, MfxRect rect, DWORD dwExStyle, DWORD dwStyle,
			MfxString className, MfxString windowsName);

	private:
		App_UI_Info_Map myUIMap;
	public:
		MfxReturn ForwardMessage(HWND hWnd, MfxMessage message, WPARAM wParam, LPARAM lParam);

	private:
		static LRESULT CALLBACK AppProc(HWND hWnd, MfxMessage msg, WPARAM wParam, LPARAM lParam);
	};

#define MFXAPP MicroFlakeX::MfxApp::g_pApp
}

namespace MicroFlakeX
{
	class MfxUI :
		public MfxBase
	{
		MfxObject;
		friend class MfxApp;
	private:
		void MfxUIInitData();
		void MfxRegMessages();
	public:
		MfxUI();
		MfxUI(MfxRect set, MfxString title);
		MfxUI(MfxRect set, DWORD myStyle_EN, MfxString title);
		MfxUI(MfxRect set, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxString myClass, MfxString title);
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
		MfxReturn UnionInvalidateRect(MfxRect* set);

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

		MfxImage* myBackImage;
		MfxImage* myMaskImage;
	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);

		MfxReturn GetBackColor(MfxColor* ret);
		MfxReturn GetMaskColor(MfxColor* ret);

		MfxReturn GetBackImage(MfxImage** ret);
		MfxReturn GetMaskImage(MfxImage** ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);

		MfxReturn SetBackColor(MfxColor* set);
		MfxReturn SetMaskColor(MfxColor* set);

		MfxReturn SetBackImage(MfxImage* set);
		MfxReturn SetMaskImage(MfxImage* set);

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

		MfxReturn __OnTimer(MfxParam param);

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
		MfxReturn __OnSetBackImage(MfxParam param);
		MfxReturn __OnSetMaskImage(MfxParam param);



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


/********************************************************************************
* Mfx消息回调函数
*********************************************************************************/
#define MfxCallBack(funcName) funcName(MfxParam param)



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

		friend class MfxApp;
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
		pMfxUI myUI;
		MfxFloor myFloor;
		MfxCanvas* myCanvas;
	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetUI(pMfxUI* ret);
		MfxReturn GetFloor(MfxFloor* ret);
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
	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);
		MfxReturn GetEdgeRect(MfxRect* ret);

		MfxReturn GetTitle(MfxString* ret);
		MfxReturn GetTitleSize(DOUBLE* ret);

		MfxReturn GetBackColor(MfxColor* ret);
		MfxReturn GetMaskColor(MfxColor* ret);
		MfxReturn GetTitleColor(MfxColor* ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);
		MfxReturn SetEdgeRect(MfxRect* set);

		MfxReturn SetTitle(MfxString set);

		MfxReturn SetTitleSize(DOUBLE set);

		MfxReturn SetBackColor(MfxColor* set);
		MfxReturn SetMaskColor(MfxColor* set);
		MfxReturn SetTitleColor(MfxColor* set);


		/********************************************************************************
		*
		*
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
		*
		*
		*********************************************************************************/
	private:
		MfxWords* myWords;
		MfxImage* myBackImage;
		MfxImage* myMaskImage;
	public:
		MfxReturn GetWords(MfxWords** ret);
		MfxReturn GetBackImage(MfxImage** ret);
		MfxReturn GetMaskImage(MfxImage** ret);

		MfxReturn SetWords(MfxWords * set);
		MfxReturn SetBackImage(MfxImage* set);
		MfxReturn SetMaskImage(MfxImage* set);


		/********************************************************************************
		*
		*
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

		MfxReturn __OnSetWords(MfxParam param);
		MfxReturn __OnSetBackImage(MfxParam param);
		MfxReturn __OnSetMaskImage(MfxParam param);

		MfxReturn __OnFlakeEvent(MfxParam param);

		MfxReturn __OnRemoveFlakeEvent(MfxParam param);
		MfxReturn __OnPushBackFlakeEvent(MfxParam param);
		MfxReturn __OnPushFrontFlakeEvent(MfxParam param);
	};

/********************************************************************************
* 为Flake添加一个来自Flake的消息映射
*********************************************************************************/
#define FLAKE_ADDRECV_FLAKEMSG(Msg, myClass, recvFunc) \
	PushBackFlakeMessage(Msg, Flake_RecvFunc_Infor(\
		(pFlakeRecvFunc)&myClass::recvFunc, MfxText(#myClass#recvFunc))\
		);

}