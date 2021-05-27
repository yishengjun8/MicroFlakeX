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


	typedef std::unordered_set<MfxFlake*> MfxFlake_Set;
	typedef std::deque<MfxFlake*> MfxFlake_Deque;
	typedef std::vector<MfxFlake*> MfxFlake_Vector;


	/**************************************************************
	*	MfxMessage	为Mfx框架使用的消息标识号，是一个UINT类型
	**************************************************************/
	typedef UINT MfxMessage;


	/**************************************************************
	*	MfxDataFlag_bool 为框架所使用的可以记录更改次数的变量，利
		用它可以知道某个bool变量是否更改过，更改过几次
	**************************************************************/
	//typedef MfxDataFlag<bool> MfxDataFlag_bool;


	/**************************************************************
	*	App_UI_Info 映射了从win32的hwnd句柄到MfxUI指针
	**************************************************************/
	class App_UI_Info
	{
	public:
		App_UI_Info(HWND hWnd, MfxUI* pUI, DWORD threadID)
		{
			myUI = pUI;
			myWnd = hWnd;
			myUIThreadID = threadID;
		}
		HWND myWnd;
		MfxUI* myUI;
		DWORD myUIThreadID;
	};


	typedef std::unordered_map<HWND, App_UI_Info*> App_UI_Info_Map;
	typedef App_UI_Info_Map::value_type App_UI_Info_Map_Elem;


	/**************************************************************
	*	pUIRecvFunc 是一个标准的接收消息的函数指针，为了兼容 win32 
		原本的消息，所以与win32参数保持统一
	***************************************************************/
	typedef MfxReturn(MfxUI::* pUIRecvFunc)(WPARAM, LPARAM);


	/**************************************************************
	*	UI_UIRecvFunc_Info 这里面存储了 "消息映射" 的具体信息
		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数
		处于消息接收链的第几层
	***************************************************************/
	class UI_UIRecvFunc_Info
	{
	public:
		UI_UIRecvFunc_Info(pUIRecvFunc pFunc, MfxString funcName)
		{
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxString myRecvFuncName;
		pUIRecvFunc recvFunc;
	};


	typedef std::deque<UI_UIRecvFunc_Info*> UI_UIRecvFunc_Infor_Deque;

	typedef std::unordered_map<MfxMessage, UI_UIRecvFunc_Infor_Deque> UI_UIMessage_Map;
	typedef UI_UIMessage_Map::value_type UI_UIMessage_Map_Elem;


	/**************************************************************
	*	UI_FlakeEvent_Info 标识了来自哪个MfxFlake控件，以及MfxFlake
		控件发出了什么消息同时MfxUI_FlakeMsg_Key重载了operator< 使
		其可以进行排序算法
	***************************************************************/
	class UI_FlakeEvent_Info
	{
	public:
		UI_FlakeEvent_Info()
		{
			myFlake = nullptr;
			myEvent = 0;
		}
		UI_FlakeEvent_Info(MfxFlake* setFlake, MfxMessage setEvent)
		{
			myFlake = setFlake;
			myEvent = setEvent;
		}
		MfxFlake* myFlake;
		MfxMessage myEvent;
		MfxString recvFuncName;

		bool operator< (const UI_FlakeEvent_Info& rhs) const
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
		bool operator==(const UI_FlakeEvent_Info& rhs) const
		{
			return (myFlake != rhs.myFlake) && (myEvent != rhs.myEvent);
		}

		std::size_t operator()(const UI_FlakeEvent_Info& key) const
		{
			return std::hash<int>()((int)key.myFlake);
		}
	};


	/**************************************************************
	*	Win32Msg_Value 标识了win32的具体消息，采用
		wParam和lParam两个消息,in32兼容
	***************************************************************/
	struct Win32Msg_Value
	{
		Win32Msg_Value(WPARAM wPara, LPARAM lPara)
		{
			wParam = wPara;
			lParam = lPara;
		}
		WPARAM wParam;
		LPARAM lParam;
	};


	typedef std::unordered_map<UI_FlakeEvent_Info, UI_UIRecvFunc_Infor_Deque, UI_FlakeEvent_Info> UI_FlakeEvent_Map;
	typedef UI_FlakeEvent_Map::value_type UI_FlakeMsg_Map_Elem;


	/**************************************************************
	*	UI_UITimer_Info 标识了定时器ID以及其接收函数
	***************************************************************/
	class UI_UITimer_Info
	{
	public:
		UI_UITimer_Info(ULONG id, ULONG delay, pUIRecvFunc pRecvFunc)
		{
			myID = id;
			delayTime = delay;
			recvFunc = pRecvFunc;
		}
		ULONG myID;
		ULONG delayTime;
		pUIRecvFunc recvFunc;
	};


	typedef std::unordered_map<MfxMessage, UI_UITimer_Info*> UI_UITimer_Map;
	typedef UI_UITimer_Map::value_type UI_UITimer_Map_Elem;


	/**************************************************************
	*
	*	Paper_Infor 标识了当前UI的状态
	*		MfxFlake添加到MfxUI的时候，发送一次
	*		MfxFlake从MfxUI移除的时候，发送一次
	*
	***************************************************************/
	class Paper_Infor
	{
	public:
		Paper_Infor(MfxUI* setUI, HWND setWnd, MfxCanvas* setCanvas, DWORD setThreadID)
		{
			myUI = setUI;
			myWnd = setWnd;
			myCanvas = setCanvas;
			myUIThreadID = setThreadID;
		}
		Paper_Infor()
		{
			myWnd = NULL;
			myUI = nullptr;
			myCanvas = nullptr;
			myUIThreadID = NULL;

		}

		HWND myWnd;
		MfxUI* myUI;
		DWORD myUIThreadID;
		MfxCanvas* myCanvas;

	};


	/**************************************************************
	*	pFlakeRecvFunc 是一个标准的接收消息的函数指针，为了兼容win32
	*	原本的消息，所以与win32参数保持统一
	***************************************************************/
	typedef MfxReturn(MfxFlake::* pFlakeRecvFunc)(WPARAM, LPARAM);


	/**************************************************************
	*	Flake_RecvFunc_Infor 这里面存储了 "消息映射" 的具体信息例如
		消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消
		息接收链的第几层
	***************************************************************/
	class Flake_RecvFunc_Infor
	{
	public:
		Flake_RecvFunc_Infor(pFlakeRecvFunc pFunc, MfxString funcName)
		{
			recvFunc = pFunc;
			myFuncName = funcName;
		}
		pFlakeRecvFunc recvFunc;
		MfxString myFuncName;
	};


	typedef std::deque<Flake_RecvFunc_Infor*> Flake_RecvFunc_Infor_Deque;

	typedef std::unordered_map<MfxMessage, Flake_RecvFunc_Infor_Deque> Flake_FlakeMessage_Map;
	typedef Flake_FlakeMessage_Map::value_type Flake_FlakeMessage_Map_Elem;
}

namespace MicroFlakeX
{
	/**************************************************************
	* 
	*	MFX_MSG定义了每个类型允许使用的消息范围
	* 
	***************************************************************/
	enum MFX_MSG
	{
		UI_MSG_BEGIN = 0xBFFF,
		UI_MSG_END = UI_MSG_BEGIN - 256,

		FLAKE_MSG_BEGIN = UI_MSG_END,
		FLAKE_MSG_END = FLAKE_MSG_BEGIN - 256,
	};


	/**************************************************************
	* 
	*	UI_MSG定义了MfxUI类型所产生的消息
	*
	***************************************************************/
	const int UI_MSG_COUNT = __COUNTER__;
#define UI_MSG_(MSG) MSG = UI_MSG_BEGIN - MFX_COUNT(UI_MSG_COUNT),
	enum UI_MSG
	{
		UI_MSG_(UI_MSG_PaintBack)
		UI_MSG_(UI_MSG_PaintMask)

		UI_MSG_(UI_MSG_FlakeInsert)
		UI_MSG_(UI_MSG_FlakeRemove)

		UI_MSG_(UI_MSG_RemoveFlakeMessage)
		UI_MSG_(UI_MSG_PushBackFlakeMessage)
		UI_MSG_(UI_MSG_PushFrontFlakeMessage)

		UI_MSG_(UI_MSG_RemoveTimer)
		UI_MSG_(UI_MSG_InsertTimer)

		UI_MSG_(UI_MSG_SetBackColor)
		UI_MSG_(UI_MSG_SetMaskColor)
		UI_MSG_(UI_MSG_SetBackImage)
		UI_MSG_(UI_MSG_SetMaskImage)

		UI_MSG_(UI_MSG_OpenPercentRect)
		UI_MSG_(UI_MSG_ClosePercentRect)

		UI_MSG_(UI_MSG_FlakeEvent)

		UI_MSG_(UI_MSG_FlakeFloorChange)
	};


	/**************************************************************
	*
	*	FLAKE_MSG定义了MfxFlake类型所产生的消息
	*
	***************************************************************/
	const int FLAKE_MSG_COUNT = __COUNTER__;
#define FLAKE_MSG_(MSG) MSG = FLAKE_MSG_BEGIN - MFX_COUNT(FLAKE_MSG_COUNT),
	enum FLAKE_MSG
	{
		FLAKE_MSG_(FLAKE_MSG_FlakeMessage)

		FLAKE_MSG_(FLAKE_MSG_SetPaper)
		FLAKE_MSG_(FLAKE_MSG_RemovePaper)

		FLAKE_MSG_(FLAKE_MSG_PaintBack)
		FLAKE_MSG_(FLAKE_MSG_PaintMask)

		FLAKE_MSG_(FLAKE_MSG_Rect)
		FLAKE_MSG_(FLAKE_MSG_PercentRect)

		FLAKE_MSG_(FLAKE_MSG_ResetRect)
		FLAKE_MSG_(FLAKE_MSG_ResetPercentRect)

		FLAKE_MSG_(FLAKE_MSG_OpenPercentRect)
		FLAKE_MSG_(FLAKE_MSG_ClosePercentRect)

		FLAKE_MSG_(FLAKE_MSG_LButtonClick)
		FLAKE_MSG_(FLAKE_MSG_RButtonClick)

		FLAKE_MSG_(FLAKE_MSG_SetFloor)
		FLAKE_MSG_(FLAKE_MSG_SetTitle)

		FLAKE_MSG_(FLAKE_MSG_SetBackColor)
		FLAKE_MSG_(FLAKE_MSG_SetMaskColor)
		FLAKE_MSG_(FLAKE_MSG_SetBackImage)
		FLAKE_MSG_(FLAKE_MSG_SetMaskImage)

		FLAKE_MSG_(FLAKE_MSG_SetWords)
		FLAKE_MSG_(FLAKE_MSG_SetTitleSize)
		FLAKE_MSG_(FLAKE_MSG_SetTitleColor)
		
		FLAKE_MSG_(FLAKE_MSG_GetTitleSize)
	};


	/**************************************************************
	*
	*	UI_STYLE定义了MfxUI可以创建的窗口类型
	* 
	*	UI_WINDOWS_STYLE_AntiFlicker - 防止闪烁 - 原理：在移动子窗口的时候，不刷新
	* 
	*	UI_WINDOWS_STYLE_Normal - 正常的窗口
	* 
	*	UI_WINDOWS_STYLE_Pop - 无边框的弹出窗口
	*
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
	*
	*	MfxApp - 单例模式
	*		这个类型在每个程序中，仅允许同时存在1个实例化的对象。
	*	这个对象会在程序开始执行之前自动创建，若要使用这个对象，
	*	请使用 MfxApp::g_pApp 或者 MFXAPP 宏
	*	
	*	使用 MFXAPP->Run(); 才能开始整个程序。
	*	当 MFXAPP->Run(); 返回时，程序结束，返回值为结束标志。
	* 
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
		MfxUI* myBindingUI;
	public:
		HWND MfxCreateUIEx(MfxUI* ui, MfxRect rect, DWORD dwExStyle, DWORD dwStyle,
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
	class MfxUI
		: public MfxBase 
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

		MfxReturn ProcMessage(MfxMessage message, WPARAM wParam, LPARAM lParam);
		MfxReturn SendMessageToFlakes(MfxMessage message, WPARAM wParam, LPARAM lParam, bool sort = false);
	
	public:
		MfxReturn UI_PostMessage(MfxMessage message, MfxParam param);
	private:
		std::queue<MfxParam> myTreadQueue;
		MfxReturn UIThread(WPARAM wParam, LPARAM lParam);
	protected:
		MfxReturn myUIMessageReturnKeep;
		MfxReturn myFlakeEventReturnKeep;


		/********************************************************************************
		*
		*********************************************************************************/
	private:
		MfxFlake_Set myFlakeSet;
		MfxFlake_Deque myFlakeDeque;
	public:
		MfxReturn RemoveFlake(MfxFlake* set);
		MfxReturn InsertFlake(MfxFlake* set);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		UI_UITimer_Map myTimerMap;
	public:
		MfxReturn RemoveTimer(ULONG setID);
		MfxReturn InsertTimer(UI_UITimer_Info timer);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		UI_UIMessage_Map myMessageMap;
	public:
		MfxReturn RemoveUIMessage(MfxMessage message, MfxString recvFuncName);
		MfxReturn PushBackUIMessage(MfxMessage message, UI_UIRecvFunc_Info* msgValue);
		MfxReturn PushFrontUIMessage(MfxMessage message, UI_UIRecvFunc_Info* msgValue);
		
		/********************************************************************************
		*
		*********************************************************************************/
	private:
		UI_FlakeEvent_Map myFlakeEventMap;
	public:
		MfxReturn RemoveFlakeEvent(UI_FlakeEvent_Info message);
		MfxReturn PushBackFlakeEvent(UI_FlakeEvent_Info message, UI_UIRecvFunc_Info msgValue);
		MfxReturn PushFrontFlakeEvent(UI_FlakeEvent_Info message, UI_UIRecvFunc_Info msgValue);

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
		MfxFlake* myMutexFocus;
		MfxFlake *myKeyboardFocus;

		bool myMutexFocusLockFlag;
		bool myKeyboardFocusLockFlag;
	public:
		MfxReturn LockMutexFocus(MfxFlake* set);
		MfxReturn UnLockMutexFocus();

		MfxReturn SetMutexFocus(MfxFlake* set);
		MfxReturn GetMutexFocus(MfxFlake** ret);

		MfxReturn SetKeyboardFocus(MfxFlake* set);
		MfxReturn GetKeyboardFocus(MfxFlake** ret);

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
		DWORD myUIThreadID;
		MfxCanvas myCanvas;

	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetUIThreadID(DWORD* ret);
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
		MfxReturn __OnTest00(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnTest01(WPARAM wParam, LPARAM lParam);
	private:
		MfxReturn __OnCreate(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnDestroy(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnMove(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaint(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnEraseBackGrand(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFlakeInsert(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFlakeRemove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFlakeFloorChange(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnInsertTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFlakeEvent(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPushBackFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPushFrontFlakeMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnOpenPercentRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnClosePercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);



		MfxReturn __OnNCPaint(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCHitTest(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCActivate(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnNCMouseMove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCMouseHover(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnNCLButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCLButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCLButtonDouble(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnNCRButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCRButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCRButtonDouble(WPARAM wParam, LPARAM lParam);
	};

/********************************************************************************
* 为UI添加一个来自控件的消息映射
*********************************************************************************/
#define UI_ADDRECV_FLAKEMSG(Flake, Event, myClass, recvFunc) PushBackFlakeEvent(UI_FlakeEvent_Info(Flake, Event), new UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自窗口的消息映射
*********************************************************************************/
#define UI_ADDRECV_UIMSG(Msg, myClass, recvFunc) PushBackUIMessage(Msg, new UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自定时器的消息映射
*********************************************************************************/
#define UI_ADDRECV_TIMER(timerID, delay, recvFunc) InsertTimer(timerID, delay, (pUIRecvFunc)&recvFunc)


/********************************************************************************
* Mfx消息回调函数
*********************************************************************************/
#define MfxCallBack(funcName) funcName(WPARAM wParam, LPARAM lParam)


/********************************************************************************
* Post一个消息到线程消息队列中
*********************************************************************************/
#define POSTMSG_UITHREAD(Msg, wPara, lPara)\
	PostThreadMessage(myUIThreadID, Msg, wPara, lPara);


}

namespace MicroFlakeX
{
	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
	class MfxFlake
		: public MfxBase
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

		MfxReturn ProcMessage(MfxMessage message, WPARAM wParam, LPARAM lParam);

	protected:
		MfxReturn myFlakeReturnKeep;
		/********************************************************************************
		*
		*********************************************************************************/
	private:
		Flake_FlakeMessage_Map myMessageMap;
	public:
		MfxReturn RemoveFlakeEvent(MfxMessage message, MfxString name);
		MfxReturn PushBackFlakeEvent(MfxMessage message, Flake_RecvFunc_Infor* msgValue);
		MfxReturn PushFrontFlakeEvent(MfxMessage message, Flake_RecvFunc_Infor* msgValue);

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
		MfxUI* myUI;
		MfxFloor myFloor;
		DWORD myUIThreadID;
		MfxCanvas* myCanvas;
	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetUI(MfxUI** ret);
		MfxReturn GetFloor(MfxFloor* ret);
		MfxReturn GetCanvas(MfxCanvas** ret);

		MfxReturn SetFloor(MfxFloor floor);
		

		/********************************************************************************
		*
		*
		*
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
		MfxReturn __OnTest001(WPARAM wParam, LPARAM lParam);
private:
		MfxReturn __OnSetPaper(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemovePaper(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetFloor(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnUISize(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnResetRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnResetPercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnOpenPercentRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnClosePercentRect(WPARAM wParam, LPARAM lParam);

		//
		MfxReturn __OnNCMouseMove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCMouseHover(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnNCLButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCLButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCLButtonDouble(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnNCRButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCRButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnNCRButtonDouble(WPARAM wParam, LPARAM lParam);
		//

		MfxReturn __OnMouseMove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnMouseHover(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnLButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnLButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnLButtonDouble(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnRButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRButtonDouble(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetTitle(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetTitleColor(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetWords(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
	};

/********************************************************************************
* 为Flake添加一个来自Flake的消息映射
*********************************************************************************/
#define FLAKE_ADDRECV_FLAKEMSG(Msg, myClass, recvFunc) \
	PushBackFlakeEvent(Msg, new Flake_RecvFunc_Infor(\
		(pFlakeRecvFunc)&myClass::recvFunc, MfxText(#myClass#recvFunc))\
		);


/********************************************************************************
* Post一个Flake消息到主线程消息队列中
*********************************************************************************/
#define FLAKE_POSTMSG_MAIN(Event, wPara, lPara)\
	myUI ? \
		PostMessage(myWnd, UI_MSG_FlakeEvent, \
			(WPARAM)(new UI_FlakeEvent_Info(this, Event)), \
			(LPARAM)(new Win32Msg_Value(wPara, lPara))) : Mfx_Return_Fail;


/********************************************************************************
* Send一个Flake消息到主线程消息队列中
*********************************************************************************/
#define FLAKE_SENDMSG_MAIN(Event, wPara, lPara)\
	myUI ? \
		SendMessage(myWnd, UI_MSG_FlakeEvent, \
			(WPARAM)(new UI_FlakeEvent_Info(this, Event)), \
			(LPARAM)(new Win32Msg_Value(wPara, lPara))) : Mfx_Return_Fail;


/********************************************************************************
* Post一个Flake消息到UI线程消息队列中
*********************************************************************************/
#define FLAKE_POSTMSG_UITHREAD(Event, wPara, lPara)\
	myUI ? \
		PostThreadMessage(myUIThreadID, UI_MSG_FlakeEvent, \
			(WPARAM)(new UI_FlakeEvent_Info(this, Event)), \
			(LPARAM)(new Win32Msg_Value(wPara, lPara))) : Mfx_Return_Fail;


}