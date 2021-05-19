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
	/**************************************************************
	*	MfxApp、MfxUI、MfxFlake	的前置声明和导出标识
	*
	*
	**************************************************************/
	class MFX_PORT MfxApp;
	class MFX_PORT MfxUI;
	class MFX_PORT MfxFlake;

	typedef std::set<MfxFlake*> MfxFlake_Set;
	typedef std::deque<MfxFlake*> MfxFlake_Deque;
	typedef std::vector<MfxFlake*> MfxFlake_Vector;
	/**************************************************************
	* 
	*	MfxMsg	为Mfx框架使用的消息标识号，是一个无符号int整形
	*
	*	MfxFloor 为Mfx框架使用的标识层级的变量，消息传递按照层级顺序传递
	*		传递顺序默认为从小打大，允许负数层级
	*
	*	MfxDataFlag_bool 为框架所使用的可以记录更改次数的变量，利用它可以知道某个
	*		变量是否更改过，更改过几次
	* 
	*	pFloorCompare 是排序模板，如果要在类里面使用这个排序，
	*		请使用MFX_FloorCompare_Enable宏
	**************************************************************/
	typedef unsigned int MfxMsg;
	typedef long long MfxFloor;
	typedef MfxDataFlag<bool> MfxDataFlag_bool;

	template<class lhsT, class rhsT = lhsT>
	bool pFloorCompare(lhsT* lhs, rhsT* rhs)
	{
		return lhs->myFloor < rhs->myFloor;
	}

	template<class lhsT, class rhsT = lhsT>
	bool FloorCompare(lhsT& lhs, rhsT& rhs)
	{
		return lhs.myFloor < rhs.myFloor;
	}

#define MFX_FloorCompare_Enable\
	template<class lhsT, class rhsT>\
	friend bool pFloorCompare(lhsT* lhs, rhsT* rhs);\
	template<class lhsT, class rhsT>\
	friend bool FloorCompare(lhsT& lhs, rhsT& rhs);

	/**************************************************************
	*
	*	MfxUI_Info_Map 映射了从win32的hwnd句柄到MfxUI指针
	*
	**************************************************************/
	struct MfxUI_Info
	{
		MfxUI_Info(HWND hWnd, MfxUI* pUI, DWORD threadID)
		{
			myUI = pUI;
			myWnd = hWnd;
			myUIThreadID = threadID;
		}
		HWND myWnd;
		MfxUI* myUI;
		DWORD myUIThreadID;
	};

	typedef std::map<HWND, MfxUI_Info> MfxUI_Info_Map;
	typedef MfxUI_Info_Map::value_type MfxUI_Info_Map_elem;


	/**************************************************************
	*
	*	pUIRecvFunc 是一个标准的接收消息的函数指针，为了兼容win32
	*		原本的消息，所以与win32参数保持统一
	*
	*	UI_UIMsg_RecvFunc_Infor 这里面存储了 "消息映射" 的具体信息
	*		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消息接收链的第几层
	*
	*	UI_UIMsg_RecvFunc_Infor_Vector 消息队列
	*		这里存储着对应消息的 "MfxFlake_MsgMap_Infor队列" ，内部按照层级顺序排序
	*
	*	UI_UIMsg_Map 消息映射
	*		这里负责存储 "消息 - 消息队列" 的映射，派送函数将按照消息队列的层级顺序，
	*		依次发送消息给指定的函数。
	*
	***************************************************************/
	typedef MfxReturn(MfxUI::* pUIRecvFunc)(WPARAM, LPARAM);
	struct UI_UIMsg_RecvFunc_Infor
	{
		UI_UIMsg_RecvFunc_Infor(pUIRecvFunc pFunc, MfxFloor floor, MfxString funcName)
		{
			myFloor = floor;
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxFloor myFloor;
		MfxString myRecvFuncName;
		pUIRecvFunc recvFunc;

		bool operator< (const UI_UIMsg_RecvFunc_Infor& rhs) const
		{
			return myFloor < rhs.myFloor;
		}

		bool operator==(UI_UIMsg_RecvFunc_Infor& rhs)
		{
			return myFloor == rhs.myFloor &&
				recvFunc == rhs.recvFunc &&
				myRecvFuncName == rhs.myRecvFuncName;
		}
	};
	typedef std::vector<UI_UIMsg_RecvFunc_Infor> UI_UIMsg_RecvFunc_Infor_Vector;

	typedef std::map<MfxMsg, UI_UIMsg_RecvFunc_Infor_Vector> UI_UIMsg_Map;
	typedef UI_UIMsg_Map::value_type UI_UIMsg_Map_Elem;


	/**************************************************************
	* 
	*	UI_MSG_FlakeMessage 
	*		这个消息的wParam为 UI_FlakeMsg_Infor
	*		这个消息的lParam为 UI_FlakeMsg_Value
	* 
	*	UI_FlakeMsg_Infor 标识了来自哪个MfxFlake控件，以及MfxFlake控件发出了什么消息
	*		同时MfxUI_FlakeMsg_Key重载了operator< 使其可以进行排序算法
	* 
	*	UI_FlakeMsg_Value 标识了MfxFlake控件发出的具体消息，采用wParam和lParam两个消息，
	*		保持跟win32兼容
	* 
	* 
	*	UI_FlakeMsg_Map 映射了从 UI_FlakeMsg_Infor 到 pUIRecvFunc 
	*		在 MfxUI 处理消息的时候，就可以直接调用对应的 pUIRecvFunc
	* 
	***************************************************************/
	struct UI_FlakeMsg_Infor
	{
		UI_FlakeMsg_Infor(MfxFlake* set, MfxMsg msg)
		{
			Flake = set;
			message = msg;
		}
		MfxFlake* Flake;
		MfxMsg message;
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

	typedef std::map<UI_FlakeMsg_Infor, UI_UIMsg_RecvFunc_Infor_Vector> UI_FlakeMsg_Map;
	typedef UI_FlakeMsg_Map::value_type UI_FlakeMsg_Map_Elem;


	/**************************************************************
	* 
	*	MfxUI_Timer_Infor 标识了 定时器以及其接收函数的具体消息
	*
	*	MfxUI_Timer_Map 维护一个映射 - 定时器id到MfxUI_Timer_Value*
	*		通过这个映射，在OnTimer事件中，可以准确定位到对应的接收函数
	*
	*
	***************************************************************/
	struct MfxUI_Timer_Infor
	{
		MfxUI_Timer_Infor(clock_t delay, clock_t pass, pUIRecvFunc pFunc)
		{
			delayTime = delay;
			passTime = pass;
			recvFunc = pFunc;
		}
		pUIRecvFunc recvFunc;
		clock_t delayTime;
		clock_t passTime;
	};

	typedef std::map<MfxMsg, MfxUI_Timer_Infor*> MfxUI_Timer_Map;
	typedef MfxUI_Timer_Map::value_type MfxUI_Timer_Map_elem;


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
	* 
	*	pFlakeRecvFunc 是一个标准的接收消息的函数指针，为了兼容win32
	*		原本的消息，所以与win32参数保持统一
	* 
	*	Flake_FlakeMsg_Infor 这里面存储了 "消息映射" 的具体信息
	*		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消息接收链的第几层
	*
	*	Flake_FlakeMsg_Infor_Vector 消息队列
	*		这里存储着对应消息的 "MfxFlake_MsgMap_Infor队列" ，内部按照层级顺序排序
	*
	*	Flake_FlakeMsg_Map 消息映射
	*		这里负责存储 "消息 - 消息队列" 的映射，派送函数将按照消息队列的层级顺序，
	*		依次发送消息给指定的函数。
	* 
	***************************************************************/
	typedef MfxReturn(MfxFlake::* pFlakeRecvFunc)(WPARAM, LPARAM);
	struct Flake_FlakeMsg_Infor
	{
		Flake_FlakeMsg_Infor(pFlakeRecvFunc pFunc, MfxFloor floor, MfxString funcName)
		{
			recvFunc = pFunc;
			myFloor = floor;
			myFuncName = funcName;
		}
		pFlakeRecvFunc recvFunc;
		MfxFloor myFloor;
		MfxString myFuncName;
	};
	typedef std::vector< Flake_FlakeMsg_Infor> Flake_FlakeMsg_Infor_Vector;

	typedef std::map<MfxMsg, Flake_FlakeMsg_Infor_Vector> Flake_FlakeMsg_Map;
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

		UI_MSG_(UI_MSG_InsertFlakeMessage)
		UI_MSG_(UI_MSG_RemoveFlakeMessage)

		UI_MSG_(UI_MSG_AddTimer)
		UI_MSG_(UI_MSG_RemoveTimer)

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
	*	请使用 MfxApp::theApp 或者 MFXAPP 宏
	*	
	*	使用 MFXAPP->Run(); 才能开始整个程序。
	*	当 MFXAPP->Run(); 返回时，程序结束，返回值为结束标志。
	* 
	***************************************************************/
	class MfxApp
		: public MfxBase
	{
		MfxObject;
#define MFXAPP MicroFlakeX::MfxApp::theApp

	public:
		MfxApp();
		virtual ~MfxApp();

	public:	
		WPARAM Run();
		static MfxApp*& theApp;
		const static HINSTANCE& theInstance;

	private:
		WPARAM overParam;
		MfxUI* myBindingUI;
	public:
		HWND MfxCreateUIEx(MfxUI* ui, MfxRect rect, 
			DWORD dwExStyle, DWORD dwStyle,
			MfxString className, MfxString windowsName);

	private:
		MfxUI_Info_Map myUIMap;
	public:
		MfxReturn ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam);

	private:
		static LRESULT CALLBACK AppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam);
	};
}

namespace MicroFlakeX
{		
	/********************************************************************************
	*
	* 
	* 
	*
	*********************************************************************************/
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

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);
		MfxReturn SendMessageToFlakes(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort = false);


		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	protected:
		MfxFloor myUnderFloor;
		MfxFloor myCoverFloor;
	private:
		UI_UIMsg_Map myMessageMap;
	public:
		MfxReturn RemoveUIMessage(MfxMsg message, MfxString recvFuncName);
		MfxReturn InsertUIMessage(MfxMsg message, UI_UIMsg_RecvFunc_Infor msgValue);
		

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
		MfxReturn InsertFlakeMessage(UI_FlakeMsg_Infor message, UI_UIMsg_RecvFunc_Infor msgValue);


		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		MfxUI_Timer_Map myTimerMap;
	public:
		MfxReturn RemoveTimer(WPARAM cid);
		MfxReturn InsertTimer(WPARAM timerID, clock_t delay, pUIRecvFunc recv);


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

		MfxReturn __OnAddTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnInsertFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam);

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
#define UI_ADDRECV_FLAKEMSG(Flake, Msg, myClass, recvFunc, Floor) InsertFlakeMessage(UI_FlakeMsg_Infor(Flake, Msg), UI_UIMsg_RecvFunc_Infor((pUIRecvFunc)&myClass::recvFunc, Floor, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自窗口的消息映射
*********************************************************************************/
#define UI_ADDRECV_UIMSG(Msg, myClass, recvFunc, Floor) InsertUIMessage(Msg, UI_UIMsg_RecvFunc_Infor((pUIRecvFunc)&myClass::recvFunc, Floor, MfxText(#recvFunc)));


/********************************************************************************
* 为UI添加一个来自定时器的消息映射
*********************************************************************************/
#define UI_ADDRECV_TIMER(timerID, delay, recvFunc) InsertTimer(timerID, delay, (pUIRecvFunc)&recvFunc)


/********************************************************************************
* 为UI添加一个消息阶梯等级
*********************************************************************************/
#define UI_ADD_FLOOR myUnderFloor--; myCoverFloor++;


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

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);

		/********************************************************************************
		*
		*
		*
		*
		*********************************************************************************/
	private:
		MfxFloor myUnderFloor;
		MfxFloor myCoverFloor;
		Flake_FlakeMsg_Map myMessageMap;
	public:
		MfxReturn RemoveUIMessage(MfxMsg message, MfxString name);
		MfxReturn InsertUIMessage(MfxMsg message, Flake_FlakeMsg_Infor msgValue);


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
#define FLAKE_ADDRECV_FLAKEMSG(Msg, myClass, recvFunc, Floor)\
	InsertUIMessage(Msg, Flake_FlakeMsg_Infor(\
		(pFlakeRecvFunc)&myClass::recvFunc, Floor, MfxText(#myClass#recvFunc))\
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