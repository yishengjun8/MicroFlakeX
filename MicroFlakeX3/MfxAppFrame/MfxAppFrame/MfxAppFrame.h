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


	typedef std::set<MfxFlake*> MfxFlake_Set;
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
	typedef MfxDataFlag<bool> MfxDataFlag_bool;


	/**************************************************************
	*	App_UI_Info 映射了从win32的hwnd句柄到MfxUI指针
	**************************************************************/
	struct App_UI_Info
	{
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


	typedef std::map<HWND, App_UI_Info*> App_UI_Info_Map;
	typedef App_UI_Info_Map::value_type App_UI_Info_Map_Elem;


	/**************************************************************
	*	pUIRecvFunc 是一个标准的接收消息的函数指针，为了兼容 win32 
		原本的消息，所以与win32参数保持统一
	***************************************************************/
	typedef MfxReturn(MfxUI::* pUIRecvFunc)(WPARAM, LPARAM);


	/**************************************************************
	*	UI_UIMsg_RecvFunc_Infor 这里面存储了 "消息映射" 的具体信息
		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数
		处于消息接收链的第几层
	***************************************************************/
	struct UI_UIMsg_RecvFunc_Infor
	{
		UI_UIMsg_RecvFunc_Infor(pUIRecvFunc pFunc, MfxString funcName)
		{
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxString myRecvFuncName;
		pUIRecvFunc recvFunc;
	};


	typedef std::deque<UI_UIMsg_RecvFunc_Infor*> UI_UIMsg_RecvFunc_Infor_Deque;

	typedef std::map<MfxMessage, UI_UIMsg_RecvFunc_Infor_Deque> UI_UIMsg_Map;
	typedef UI_UIMsg_Map::value_type UI_UIMsg_Map_Elem;


	/**************************************************************
	*	UI_FlakeMsg_Infor 标识了来自哪个MfxFlake控件，以及MfxFlake
		控件发出了什么消息同时MfxUI_FlakeMsg_Key重载了operator< 使
		其可以进行排序算法
	***************************************************************/
	struct UI_FlakeMsg_Infor
	{
		UI_FlakeMsg_Infor(MfxFlake* set, MfxMessage msg)
		{
			Flake = set;
			message = msg;
		}
		MfxMessage message;
		MfxFlake* Flake;

		bool operator< (const UI_FlakeMsg_Infor& rhs) const
		{
			if (Flake != rhs.Flake)
			{
				return (Flake < rhs.Flake);
			}
			else
			{
				return (Flake < rhs.Flake) || (message < rhs.message);
			}
		}
	};


	/**************************************************************
	*	UI_FlakeMsg_Value 标识了MfxFlake控件发出的具体消息，采用
		wParam和lParam两个消息，保持跟win32兼容
	***************************************************************/
	struct UI_FlakeMsg_Value
	{
		UI_FlakeMsg_Value(WPARAM wPara, LPARAM lPara)
		{
			wParam = wPara;
			lParam = lPara;
		}
		bool operator < (const UI_FlakeMsg_Value& get) const
		{
			return true;
		}
		WPARAM wParam;
		LPARAM lParam;
	};


	typedef std::map<UI_FlakeMsg_Infor, UI_UIMsg_RecvFunc_Infor_Deque> UI_FlakeMsg_Map;
	typedef UI_FlakeMsg_Map::value_type UI_FlakeMsg_Map_Elem;


	/**************************************************************
	*	UI_UITimer_Infor 标识了定时器ID以及其接收函数
	***************************************************************/
	struct UI_UITimer_Infor
	{
		UI_UITimer_Infor(DWORD id, clock_t delay, pUIRecvFunc pRecvFunc)
		{
			myID = id;
			delayTime = delay;
			recvFunc = pRecvFunc;
		}
		DWORD myID;
		clock_t delayTime;
		pUIRecvFunc recvFunc;
	};


	typedef std::map<MfxMessage, UI_UITimer_Infor*> UI_UITimer_Infor_Map;
	typedef UI_UITimer_Infor_Map::value_type UI_UITimer_Infor_Map_Elem;


	/**************************************************************
	*
	*	Paper_Infor 标识了当前UI的状态
	*		MfxFlake添加到MfxUI的时候，发送一次
	*		MfxFlake从MfxUI移除的时候，发送一次
	*
	***************************************************************/
	struct Paper_Infor
	{
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
	*	Flake_FlakeMsg_Infor 这里面存储了 "消息映射" 的具体信息例如
		消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消
		息接收链的第几层
	***************************************************************/
	struct Flake_FlakeMsg_Infor
	{
		Flake_FlakeMsg_Infor(pFlakeRecvFunc pFunc, MfxString funcName)
		{
			recvFunc = pFunc;
			myFuncName = funcName;
		}
		pFlakeRecvFunc recvFunc;
		MfxString myFuncName;
	};


	typedef std::deque<Flake_FlakeMsg_Infor*> Flake_FlakeMsg_Infor_Vector;

	typedef std::map<MfxMessage, Flake_FlakeMsg_Infor_Vector> Flake_FlakeMsg_Map;
	typedef Flake_FlakeMsg_Map::value_type Flake_FlakeMsg_Map_Elem;
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

		UI_MSG_(UI_MSG_FlakeMessage)

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
		FLAKE_MSG_(FLAKE_MSG_SetPaper)

		FLAKE_MSG_(FLAKE_MSG_PaintBack)
		FLAKE_MSG_(FLAKE_MSG_PaintMask)

		FLAKE_MSG_(FLAKE_MSG_Size)
		FLAKE_MSG_(FLAKE_MSG_Point)

		FLAKE_MSG_(FLAKE_MSG_PercentSize)
		FLAKE_MSG_(FLAKE_MSG_PercentPoint)

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
		UI_WINDOWS_STYLE_Normal = WS_OVERLAPPEDWINDOW | WS_VISIBLE | UI_WINDOWS_STYLE_AntiFlicker,
		UI_WINDOWS_STYLE_Pop = WS_POPUP | WS_VISIBLE | UI_WINDOWS_STYLE_AntiFlicker,
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
		MfxReturn UIThread(WPARAM wParam, LPARAM lParam);
	public:
		MfxUI();
		MfxUI(MfxRect set, MfxString title);
		MfxUI(MfxRect set, DWORD myStyle_EN, MfxString title);
		MfxUI(MfxRect set, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxString myClass, MfxString title);
		virtual ~MfxUI();
		MfxReturn CreateSuccess();

		MfxReturn ProcMessage(MfxMessage message, WPARAM wParam, LPARAM lParam);
		MfxReturn SendMessageToFlakes(MfxMessage message, WPARAM wParam, LPARAM lParam, bool sort = false);


		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		UI_UIMsg_Map myMessageMap;
	public:
		MfxReturn RemoveUIMessage(MfxMessage message, MfxString recvFuncName);
		MfxReturn PushBackUIMessage(MfxMessage message, UI_UIMsg_RecvFunc_Infor* msgValue);
		MfxReturn PushFrontUIMessage(MfxMessage message, UI_UIMsg_RecvFunc_Infor* msgValue);
		

		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		bool myPercentRectFlag;
	public:
		MfxReturn OpenPercentRect();
		MfxReturn ClosePercentRect();
		MfxReturn ChickPercentRect();


		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		MfxFlake_Set myFlakeSet;
		MfxFlake_Deque myFlakeDeque;

		UI_FlakeMsg_Map myFlakeMessageMap;

	public:
		MfxReturn RemoveFlake(MfxFlake* set);
		MfxReturn InsertFlake(MfxFlake* set);

		MfxReturn RemoveFlakeMessage(UI_FlakeMsg_Infor message, MfxString recvFuncName);
		MfxReturn PushBackFlakeMessage(UI_FlakeMsg_Infor message, UI_UIMsg_RecvFunc_Infor* msgValue);
		MfxReturn PushFrontFlakeMessage(UI_FlakeMsg_Infor message, UI_UIMsg_RecvFunc_Infor* msgValue);


		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		UI_UITimer_Infor_Map myTimerMap;
	public:
		MfxReturn RemoveTimer(WPARAM setID);
		MfxReturn InsertTimer(WPARAM setID, clock_t delay, pUIRecvFunc recv);


		/********************************************************************************
		*
		*
		*
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
		*
		*
		*
		*********************************************************************************/
	private:
		HWND myWnd;
		DWORD myUIThreadID;
		MfxCanvas myCanvas;
		PTP_TIMER myPTP_TIME;

	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetUIThreadID(DWORD* ret);
		MfxReturn GetCanvas(MfxCanvas** ret);


		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		MfxRect myRect;
		MfxImage* myBackImage, * myMaskImage;
	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);
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

		//MfxReturn SetBigIcon(MfxImage* set);
		//MfxReturn SetSmallIcon(MfxImage* set);

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

		MfxReturn __OnFlakeMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPushBackFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPushFrontFlakeMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnOpenPercentRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnClosePercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
	};

/********************************************************************************
* 为UI添加一个来自控件的消息映射
*********************************************************************************/
#define UI_ADDRECV_FLAKEMSG(Flake, Msg, myClass, recvFunc) PushBackFlakeMessage(UI_FlakeMsg_Infor(Flake, Msg), new UI_UIMsg_RecvFunc_Infor((pUIRecvFunc)&myClass::recvFunc, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自窗口的消息映射
*********************************************************************************/
#define UI_ADDRECV_UIMSG(Msg, myClass, recvFunc) PushBackUIMessage(Msg, new UI_UIMsg_RecvFunc_Infor((pUIRecvFunc)&myClass::recvFunc, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自定时器的消息映射
*********************************************************************************/
#define UI_ADDRECV_TIMER(timerID, delay, recvFunc) InsertTimer(timerID, delay, (pUIRecvFunc)&recvFunc)


/********************************************************************************
* Mfx消息回调函数
*********************************************************************************/
#define MfxCallBack(funcName) funcName(WPARAM wParam, LPARAM lParam)

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

		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		Flake_FlakeMsg_Map myMessageMap;
	public:
		MfxReturn RemoveFlakeMessage(MfxMessage message, MfxString name);
		MfxReturn PushBackFlakeMessage(MfxMessage message, Flake_FlakeMsg_Infor* msgValue);
		MfxReturn PushFrontFlakeMessage(MfxMessage message, Flake_FlakeMsg_Infor* msgValue);


		/********************************************************************************
		*
		*
		*
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
		MfxRect myPercentRect;

		MfxString myTitle;

		MfxColor myBackColor;
		MfxColor myMaskColor;
		MfxColor myTitleColor;
	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);

		MfxReturn GetTitle(MfxString* ret);
		MfxReturn GetTitleSize(FLOAT* ret);

		MfxReturn GetBackColor(MfxColor* ret);
		MfxReturn GetMaskColor(MfxColor* ret);
		MfxReturn GetTitleColor(MfxColor* ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);

		MfxReturn SetTitle(MfxString set);

		MfxReturn SetTitleSize(FLOAT set);

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
		MfxDataFlag_bool myMouseFloat;
		MfxDataFlag_bool myLButtonPress;
		MfxDataFlag_bool myLButtonClickFlag;
		MfxDataFlag_bool myRButtonPress;
		MfxDataFlag_bool myRButtonClickFlag;
		MfxDataFlag_bool myLButtonMoveFlag, myRButtonMoveFlag;

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
	private:
		MfxReturn __OnSetPaper(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetFloor(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnUISize(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPoint(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPercentSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPercentPoint(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnResetRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnResetPercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnOpenPercentRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnClosePercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnMouseMove(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnLButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnLButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRButtonDown(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetTitle(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetWords(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
	};

/********************************************************************************
* 为Flake添加一个来自Flake的消息映射
*********************************************************************************/
#define FLAKE_ADDRECV_FLAKEMSG(Msg, myClass, recvFunc) \
	PushBackFlakeMessage(Msg, new Flake_FlakeMsg_Infor(\
		(pFlakeRecvFunc)&myClass::recvFunc, MfxText(#myClass#recvFunc))\
		);


/********************************************************************************
* Post一个Flake消息到主线程消息队列中
*********************************************************************************/
#define FLAKE_POSTMSG_MAIN(Msg, wPara, lPara)\
	myUI ? \
		PostMessage(myWnd, UI_MSG_FlakeMessage, \
			(WPARAM)(new UI_FlakeMsg_Infor(this, Msg)), \
			(LPARAM)(new UI_FlakeMsg_Value(wPara, lPara))) : Mfx_Return_Fail;


/********************************************************************************
* Send一个Flake消息到主线程消息队列中
*********************************************************************************/
#define FLAKE_SENDMSG_MAIN(Msg, wPara, lPara)\
	myUI ? \
		SendMessage(myWnd, UI_MSG_FlakeMessage, \
			(WPARAM)(new UI_FlakeMsg_Infor(this, Msg)), \
			(LPARAM)(new UI_FlakeMsg_Value(wPara, lPara))) : Mfx_Return_Fail;


/********************************************************************************
* Post一个Flake消息到UI线程消息队列中
*********************************************************************************/
#define FLAKE_POSTMSG_UITHREAD(Msg, wPara, lPara)\
	myUI ? \
		PostThreadMessage(myUIThreadID, UI_MSG_FlakeMessage, \
			(WPARAM)(new UI_FlakeMsg_Infor(this, Msg)), \
			(LPARAM)(new UI_FlakeMsg_Value(wPara, lPara))) : Mfx_Return_Fail;


}