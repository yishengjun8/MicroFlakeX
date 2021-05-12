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
	*	FloorCompare 是排序模板，如果要在类里面使用这个排序，
	*		请使用MFX_FloorCompare_Enable宏
	**************************************************************/
	typedef unsigned int MfxMsg;
	typedef long long MfxFloor;
	typedef MfxDataFlag<bool> MfxDataFlag_bool;

	typedef std::set<MfxMsg> MfxMsg_Set;

	template<class lhsT, class rhsT = lhsT>
	bool FloorCompare(lhsT* lhs, rhsT* rhs)
	{
		return lhs->myFloor < rhs->myFloor;
	}
#define MFX_FloorCompare_Enable\
	template<class lhsT, class rhsT>\
	friend bool FloorCompare(lhsT* lhs, rhsT* rhs);
	/**************************************************************
	*
	*	MfxUI_Map 映射了从win32的hwnd句柄到MfxUI指针
	*
	**************************************************************/
	typedef std::map<HWND, MfxUI*> MfxUI_Map;
	typedef MfxUI_Map::value_type MfxUI_Map_elem;


	/**************************************************************
	*
	*	MfxUI_MsgFunc 是一个标准的接收消息的函数指针，为了兼容win32
	*		原本的消息，所以与win32参数保持统一
	*
	*	MfxUI_MsgMap_Infor 这里面存储了 "消息映射" 的具体信息
	*		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消息接收链的第几层
	*
	*	MfxUI_MsgMap_Vector 消息队列
	*		这里存储着对应消息的 "MfxFlake_MsgMap_Infor队列" ，内部按照层级顺序排序
	*
	*	MfxUI_MsgMap 消息映射
	*		这里负责存储 "消息 - 消息队列" 的映射，派送函数将按照消息队列的层级顺序，
	*		依次发送消息给指定的函数。
	*
	***************************************************************/
	typedef MfxReturn(MfxUI::* MfxUI_MsgFunc)(WPARAM, LPARAM);
	struct MfxUI_MsgMap_Infor
	{
		MfxUI_MsgMap_Infor(MfxUI_MsgFunc pFunc, MfxFloor floor, MfxString funcName)
		{
			recvFunc = pFunc;
			myFloor = floor;
			myFuncName = funcName;
		}
		MfxUI_MsgFunc recvFunc;
		MfxFloor myFloor;
		MfxString myFuncName;
	};
	typedef std::vector<MfxUI_MsgMap_Infor*> MfxUI_MsgMap_Vector;

	typedef std::map<MfxMsg, MfxUI_MsgMap_Vector*> MfxUI_MsgMap;
	typedef MfxUI_MsgMap::value_type MfxUI_MsgMap_elem;


	/**************************************************************
	* 
	*	UI_MSG_FlakeMessage 
	*		这个消息的wParam为 MfxUI_FlakeMsg_Infor
	*		这个消息的lParam为 MfxUI_FlakeMsg_Value
	* 
	*	MfxUI_FlakeMsg_Infor 标识了来自哪个MfxFlake控件，以及MfxFlake控件发出了什么消息
	*		同时MfxUI_FlakeMsg_Key重载了operator< 使其可以进行排序算法
	* 
	*	MfxUI_FlakeMsg_Value 标识了MfxFlake控件发出的具体消息，采用wParam和lParam两个消息，
	*		保持跟win32兼容
	* 
	* 
	*	MfxUI_FlakeMsg_Map 映射了从 MfxUI_FlakeMsg_Infor 到 MfxUI_MsgFunc 
	*		在 MfxUI 处理消息的时候，就可以直接调用对应的 MfxUI_MsgFunc
	* 
	***************************************************************/
	struct MfxUI_FlakeMsg_Infor
	{
		MfxUI_FlakeMsg_Infor(MfxFlake* set, MfxMsg msg)
		{
			Flake = set;
			message = msg;
		}
		MfxFlake* Flake;
		MfxMsg message;
		bool operator< (const MfxUI_FlakeMsg_Infor& get) const
		{
			if (Flake != get.Flake)
			{
				return (Flake < get.Flake);
			}
			else
			{
				return (Flake < get.Flake) || (message < get.message);
			}
		}
	};

	struct MfxUI_FlakeMsg_Value
	{
		MfxUI_FlakeMsg_Value(WPARAM wPara, LPARAM lPara)
		{
			wParam = wPara;
			lParam = lPara;
		}
		bool operator < (const MfxUI_FlakeMsg_Value& get) const
		{
			return true;
		}
		WPARAM wParam;
		LPARAM lParam;
	};

	typedef std::map<MfxUI_FlakeMsg_Infor, MfxUI_MsgFunc> MfxUI_FlakeMsg_Map;
	typedef MfxUI_FlakeMsg_Map::value_type MfxUI_FlakeMsg_Map_elem;


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
		MfxUI_Timer_Infor(clock_t delay, clock_t pass, MfxUI_MsgFunc pFunc)
		{
			delayTime = delay;
			passTime = pass;
			recvFunc = pFunc;
		}
		MfxUI_MsgFunc recvFunc;
		clock_t delayTime;
		clock_t passTime;
	};

	typedef std::map<MfxMsg, MfxUI_Timer_Infor*> MfxUI_Timer_Map;
	typedef MfxUI_Timer_Map::value_type MfxUI_Timer_Map_elem;


	/**************************************************************
	*
	*	MfxUI_Paper_Infor 标识了当前UI的状态
	*		MfxFlake添加到MfxUI的时候，发送一次
	*		MfxFlake从MfxUI移除的时候，发送一次
	*
	***************************************************************/
	struct MfxUI_Paper_Infor
	{
		MfxUI_Paper_Infor(MfxUI* setUI, HWND setWnd, MfxCanvas* setCanvas)
		{
			myUI = setUI;
			myWnd = setWnd;
			myCanvas = setCanvas;
		}
		MfxUI_Paper_Infor()
		{
			myUI = nullptr;
			myWnd = NULL;
			myCanvas = nullptr;
		}
		MfxUI* myUI;
		HWND myWnd;
		MfxCanvas* myCanvas;

	};


	/**************************************************************
	* 
	*	MfxFlake_MsgFunc 是一个标准的接收消息的函数指针，为了兼容win32
	*		原本的消息，所以与win32参数保持统一
	* 
	*	MfxFlake_MsgMap_Infor 这里面存储了 "消息映射" 的具体信息
	*		例如消息的接收函数，消息的接收函数的字符串编码，该接收函数处于消息接收链的第几层
	*
	*	MfxFlake_MsgMap_Vector 消息队列
	*		这里存储着对应消息的 "MfxFlake_MsgMap_Infor队列" ，内部按照层级顺序排序
	*
	*	MfxFlake_MsgMap 消息映射
	*		这里负责存储 "消息 - 消息队列" 的映射，派送函数将按照消息队列的层级顺序，
	*		依次发送消息给指定的函数。
	* 
	***************************************************************/
	typedef MfxReturn(MfxFlake::* MfxFlake_MsgFunc)(WPARAM, LPARAM);
	struct MfxFlake_MsgMap_Infor
	{
		MfxFlake_MsgMap_Infor(MfxFlake_MsgFunc pFunc, MfxFloor floor, MfxString funcName)
		{
			recvFunc = pFunc;
			myFloor = floor;
			myFuncName = funcName;
		}
		MfxFlake_MsgFunc recvFunc;
		MfxFloor myFloor;
		MfxString myFuncName;
	};
	typedef std::vector< MfxFlake_MsgMap_Infor*> MfxFlake_MsgMap_Vector;

	typedef std::map<MfxMsg, MfxFlake_MsgMap_Vector*> MfxFlake_MsgMap;
	typedef MfxFlake_MsgMap::value_type MfxFlake_MsgMap_elem;
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
#define UI_MSG(MSG) MSG = UI_MSG_BEGIN - MFX_COUNT(UI_MSG_COUNT),
	enum UI_MSG
	{
		UI_MSG(UI_MSG_PaintBack)
		UI_MSG(UI_MSG_PaintMask)

		UI_MSG(UI_MSG_FlakeInsert)
		UI_MSG(UI_MSG_FlakeRemove)

		UI_MSG(UI_MSG_SetPaper)

		UI_MSG(UI_MSG_AddFlakeMessage)
		UI_MSG(UI_MSG_RemoveFlakeMessage)

		UI_MSG(UI_MSG_AddTimer)
		UI_MSG(UI_MSG_RemoveTimer)

		UI_MSG(UI_MSG_SetBackColor)
		UI_MSG(UI_MSG_SetMaskColor)
		UI_MSG(UI_MSG_SetBackImage)
		UI_MSG(UI_MSG_SetMaskImage)

		UI_MSG(UI_MSG_OpenPercentRect)
		UI_MSG(UI_MSG_ClosePercentRect)

		UI_MSG(UI_MSG_FlakeMessage)
	};


	/**************************************************************
	*
	*	FLAKE_MSG定义了MfxFlake类型所产生的消息
	*
	***************************************************************/
	const int FLAKE_MSG_COUNT = __COUNTER__;
#define FLAKE_MSG(MSG) MSG = FLAKE_MSG_BEGIN - MFX_COUNT(FLAKE_MSG_COUNT),
	enum FLAKE_MSG
	{
		FLAKE_MSG(FLAKE_MSG_Size)
		FLAKE_MSG(FLAKE_MSG_Point)

		FLAKE_MSG(FLAKE_MSG_PercentSize)
		FLAKE_MSG(FLAKE_MSG_PercentPoint)

		FLAKE_MSG(FLAKE_MSG_ResetRect)
		FLAKE_MSG(FLAKE_MSG_ResetPercentRect)

		FLAKE_MSG(FLAKE_MSG_OpenPercentRect)
		FLAKE_MSG(FLAKE_MSG_ClosePercentRect)

		FLAKE_MSG(FLAKE_MSG_LButtonClick)
		FLAKE_MSG(FLAKE_MSG_RButtonClick)

		FLAKE_MSG(FLAKE_MSG_FlakeFloorChange)

		FLAKE_MSG(FLAKE_MSG_SetFloor)
		FLAKE_MSG(FLAKE_MSG_SetTitle)

		FLAKE_MSG(FLAKE_MSG_SetBackColor)
		FLAKE_MSG(FLAKE_MSG_SetMaskColor)
		FLAKE_MSG(FLAKE_MSG_SetBackImage)
		FLAKE_MSG(FLAKE_MSG_SetMaskImage)

		FLAKE_MSG(FLAKE_MSG_SetWords)
		FLAKE_MSG(FLAKE_MSG_SetTitleSize)
		FLAKE_MSG(FLAKE_MSG_SetTitleColor)
		
		FLAKE_MSG(FLAKE_MSG_GetTitleSize)
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
		MfxUI_Map myUIMap;
	public:
		MfxReturn ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam);

	private:
		static LRESULT CALLBACK AppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam);
	};
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
namespace MicroFlakeX
{	
	/**************************************************************
	*
	*	MfxUI - MicroFlakeX的UI框架
	* 
	* 
	***************************************************************/
	class MfxUI
		: public MfxBase 
	{
		MfxObject;
		friend class MfxApp;

	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
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

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);
		MfxReturn SendMessageToFlakes(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort);

	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
	private:
		MfxUI_MsgMap myMessageMap;
		MfxFloor myUnderFloor, myCoverFloor;
#define UI_ADD_FLOOR myUnderFloor--; myCoverFloor++;

	public:
		MfxReturn RemoveMessage(MfxMsg message, MfxString funcName);
		MfxReturn InsertMessage(MfxMsg message, MfxUI_MsgMap_Infor* msgValue);

#define UI_ADD_RECVMSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxUI_MsgMap_Infor(\
		(MfxUI_MsgFunc)&myClass::FuncName, Floor, MfxText(#FuncName))\
		);

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

		MfxMsg_Set myFlakeMessageSet;
		MfxUI_FlakeMsg_Map myFlakeMessageMap;

#define UI_ADD_FLAKE_RECVMSG(Msg) (myFlakeMessageSet.insert((MfxMsg)Msg))

	public:
		MfxReturn AddFlake(MfxFlake* set);
		MfxReturn RemoveFlake(MfxFlake* set);

		MfxReturn RemoveFlakeMessage(MfxFlake* target, MfxMsg message);
		MfxReturn AddFlakeMessage(MfxFlake* target, MfxMsg message, MfxUI_MsgFunc recv);

#define UI_ADD_FLAKE_MSGMAP(Flake, Msg, recvFunc)\
	AddFlakeMessage(Flake, Msg, (MfxUI_MsgFunc)&recvFunc)

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
		MfxReturn AddTimer(WPARAM timerID, clock_t delay, MfxUI_MsgFunc recv);
#define UI_ADD_TIMER_MAP(timerID, delay, recvFunc)\
	AddTimer(timerID, delay, (MfxUI_MsgFunc)&recvFunc)

	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
	private:
		MfxFlake* myMutexFocus, * myKeyboardFocus;
		bool myMutexFocusLockFlag, myKeyboardFocusLockFlag;
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
		MfxCanvas myCanvas;
	public:
		MfxReturn GetWnd(HWND* ret);
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
		MfxReturn SetRect(MfxRect set);
		MfxReturn SetSize(MfxSize set);
		MfxReturn SetPoint(MfxPoint set);

		MfxReturn SetBackColor(MfxColor set);
		MfxReturn SetMaskColor(MfxColor set);

		MfxReturn SetBackImage(MfxImage* set);
		MfxReturn SetMaskImage(MfxImage* set);

		//MfxReturn SetBigIcon(MfxImage* set);
		//MfxReturn SetSmallIcon(MfxImage* set);

	/********************************************************************************
	*
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
		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFlakeInsert(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFlakeRemove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFlakeFloorChange(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnAddTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnOpenPercentRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnClosePercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
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
	class MfxFlake
		: public MfxBase
	{
		MfxObject;

		friend class MfxApp;
		MFX_FloorCompare_Enable;
	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
	private:
		void MfxRegMessages();
		void MfxFlakeInitData();
	public:
		MfxFlake();
		MfxFlake(MfxRect set);
		virtual ~MfxFlake();
		virtual MfxReturn GetType(MfxString* ret);

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);

	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
	private:
		MfxFloor myUnderFloor, myCoverFloor;
		MfxFlake_MsgMap myMessageMap;
	public:
		MfxReturn RemoveMessage(MfxMsg message, MfxString name);
		MfxReturn InsertMessage(MfxMsg message, MfxFlake_MsgMap_Infor* msgValue);

#define FLAKE_ADD_RECVMSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxFlake_MsgMap_Infor(\
		(MfxFlake_MsgFunc)&myClass::FuncName, Floor, MfxText(#myClass#FuncName))\
		);

#define FLAKE_POST_MSG(Msg, wPara, lPara)\
	if(myUI)\
	{\
		MfxUI_FlakeMsg_Infor t_FlakeMessageKey(this, Msg); \
		MfxUI_FlakeMsg_Value t_FlakeMessageValue(wPara, lPara); \
		PostMessage(myWnd, UI_MSG_FlakeMessage, (WPARAM)&t_FlakeMessageKey, (WPARAM)&t_FlakeMessageValue);\
	}

#define FLAKE_SEND_MSG(Msg, wPara, lPara)\
	if(myUI)\
	{\
		MfxUI_FlakeMsg_Infor t_FlakeMessageKey(this, Msg); \
		MfxUI_FlakeMsg_Value t_FlakeMessageValue(wPara, lPara); \
		SendMessage(myWnd, UI_MSG_FlakeMessage, (WPARAM)&t_FlakeMessageKey, (WPARAM)&t_FlakeMessageValue);\
	}

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
		MfxCanvas* myCanvas;
		MfxUI* myUI;
		MfxFloor myFloor;
	public:
		MfxReturn GetUI(MfxUI** ret);
		MfxReturn GetWnd(HWND* ret);
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
		MfxString myType, myTitle;
		MfxRect myRect, myPercentRect;
	public:
		MfxReturn GetTitle(MfxString* ret);
		MfxReturn GetTitleSize(FLOAT* ret);
		MfxReturn GetTitleColor(MfxColor* ret);

		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);

	public:
		MfxReturn SetTitle(MfxString set);
		MfxReturn SetTitleSize(FLOAT set);
		MfxReturn SetTitleColor(MfxColor set);

		MfxReturn SetRect(MfxRect set);
		MfxReturn SetSize(MfxSize set);
		MfxReturn SetPoint(MfxPoint set);

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

		MfxReturn SetBackColor(MfxColor set);
		MfxReturn SetMaskColor(MfxColor set);

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
}