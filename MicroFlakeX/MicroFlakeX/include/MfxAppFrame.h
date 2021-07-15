#pragma once
namespace MicroFlakeX
{
	class MFX_DLL_EXPORT MfxUI;
	class MFX_DLL_EXPORT MfxFlake;

	typedef MfxUI* pMfxUI;
	typedef MfxFlake* pMfxFlake;

	typedef std::unordered_set<MfxFlake*> MfxFlake_Set;
	typedef std::deque<MfxFlake*> MfxFlake_Deque;
	typedef std::vector<MfxFlake*> MfxFlake_Vector;

	/**************************************************************
	*	App_UI_Info 映射了从win32的hwnd句柄到MfxUI指针
	**************************************************************/
	struct App_UI_Info
	{
		App_UI_Info(HWND hWnd, MfxUI* pUI)
		{
			myUI = pUI;
			myWnd = hWnd;
		}
		HWND myWnd;
		MfxUI* myUI;
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
		UI_UIRecvFunc_Info(pUIRecvFunc pFunc, MfxStringW funcName)
		{
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxStringW myRecvFuncName;
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
		FlakeEvent_Info(MfxFlake* setFlake, MfxEvent setEvent)
		{
			myFlake = setFlake;
			myEvent = setEvent;
		}
		MfxFlake* myFlake;
		MfxEvent myEvent;
		MfxStringW recvFuncName;

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
		Paper_Infor(MfxBase* father, HWND setWnd, MfxCanvas* setCanvas)
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
		MfxBase* myFather;
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
		Flake_RecvFunc_Infor(pFlakeRecvFunc pFunc, MfxStringW funcName)
		{
			recvFunc = pFunc;
			myRecvFuncName = funcName;
		}
		MfxStringW myRecvFuncName;
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
	*	MFX消息
	***************************************************************/
	const MfxMessage MSG_FlakeInsert = WM_APP + 1;
	const MfxMessage MSG_FlakeRemove = WM_APP + 2;

	const MfxMessage MSG_UIEvent = WM_APP + 3;
	const MfxMessage MSG_FlakeEvent = WM_APP + 4;

	const MfxMessage MSG_FlakeFloorChange = WM_APP + 5;

	const MfxMessage MSG_FatherSize = WM_APP + 6;
	const MfxMessage MSG_FatherPoint = WM_APP + 7;
	/**************************************************************
	*	UI消息
	***************************************************************/
	const MfxMessage UI_MSG_PaintBack = WM_APP + 8;
	const MfxMessage UI_MSG_PaintMask = WM_APP + 9;

	const MfxMessage UI_MSG_RemoveFlakeEvent = WM_APP + 10;
	const MfxMessage UI_MSG_PushBackFlakeEvent = WM_APP + 11;
	const MfxMessage UI_MSG_PushFrontFlakeEvent = WM_APP + 12;

	const MfxMessage UI_MSG_RemoveWin32Timer = WM_APP + 13;
	const MfxMessage UI_MSG_InsertWin32Timer = WM_APP + 14;

	const MfxMessage UI_MSG_OpenPercentRect = WM_APP + 15;
	const MfxMessage UI_MSG_ClosePercentRect = WM_APP + 16;

	const MfxMessage UI_MSG_SetBackColor = WM_APP + 17;
	const MfxMessage UI_MSG_SetMaskColor = WM_APP + 18;

	/**************************************************************
	*	Flake消息
	***************************************************************/
	const MfxMessage FLAKE_MSG_PaintBack = WM_APP + 19;
	const MfxMessage FLAKE_MSG_PaintMask = WM_APP + 20;

	const MfxMessage FLAKE_MSG_RemoveFlakeEvent = WM_APP + 21;
	const MfxMessage FLAKE_MSG_PushBackFlakeEvent = WM_APP + 22;
	const MfxMessage FLAKE_MSG_PushFrontFlakeEvent = WM_APP + 23;

	const MfxMessage FLAKE_MSG_SetPaper = WM_APP + 24;
	const MfxMessage FLAKE_MSG_RemovePaper = WM_APP + 25;

	const MfxMessage FLAKE_MSG_OpenPercentRect = WM_APP + 26;
	const MfxMessage FLAKE_MSG_ClosePercentRect = WM_APP + 27;

	const MfxMessage FLAKE_MSG_Rect = WM_APP + 28;
	const MfxMessage FLAKE_MSG_PercentRect = WM_APP + 29;

	const MfxMessage FLAKE_MSG_RecalculatRect = WM_APP + 30;
	const MfxMessage FLAKE_MSG_RecalculatPercentRect = WM_APP + 31;

	const MfxMessage FLAKE_MSG_SetFloor = WM_APP + 32;

	const MfxMessage FLAKE_MSG_SetTitle = WM_APP + 33;
	const MfxMessage FLAKE_MSG_SetTitleSize = WM_APP + 34;
	const MfxMessage FLAKE_MSG_SetTitleColor = WM_APP + 35;

	const MfxMessage FLAKE_MSG_SetBackColor = WM_APP + 36;
	const MfxMessage FLAKE_MSG_SetMaskColor = WM_APP + 37;
	const MfxMessage FLAKE_MSG_SetBackFrameSize = WM_APP + 38;
	const MfxMessage FLAKE_MSG_SetMaskFrameSize = WM_APP + 39;

	/**************************************************************
	*	MFX事件
	***************************************************************/
	const MfxMessage FLAKE_EVENT_FollowTheMouse = WM_APP + 40;

	const MfxMessage FLAKE_EVENT_LButtonClick = WM_APP + 41;
	const MfxMessage FLAKE_EVENT_RButtonClick = WM_APP + 42;

	const MfxMessage FLAKE_EVENT_MouseFloat = WM_APP + 43;
	const MfxMessage FLAKE_EVENT_MouseFloatOver = WM_APP + 44;

	const MfxMessage FLAKE_EVENT_LButtonPress = WM_APP + 45;
	const MfxMessage FLAKE_EVENT_LButtonPressOver = WM_APP + 46;

	const MfxMessage FLAKE_EVENT_RButtonPress = WM_APP + 47;
	const MfxMessage FLAKE_EVENT_RButtonPressOver = WM_APP + 48;

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
#define MFX_MAKE_WIN32_PARAM(name, msg, hwnd, wParam, lParam) \
	MfxParam name(msg);\
	name.push_back(hwnd);\
	name.push_back(wParam);\
	name.push_back(lParam);


#define MFXPARAM_GET_MSG MFX_CALLBACK_PARAM.GetMESSAGE()
#define MFXPARAM_GET_HWND MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, HWND, 0)
#define MFXPARAM_GET_WPARAM MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, WPARAM, 1)
#define MFXPARAM_GET_LPARAM MFXPARAM_GET_SAFE(MFX_CALLBACK_PARAM, LPARAM, 2)

	

	MFX_DLL_EXPORT WPARAM MfxAppRun();
}

namespace __MicroFlakeX
{
	MFX_DLL_EXPORT HWND MfxCreateWindowsEx(MfxUI* ui, MfxUI* father, MfxRect rect, DWORD dwStyle, DWORD dwExStyle,
		MfxStringW className, MfxStringW windowsName);

	MFX_DLL_EXPORT LRESULT CALLBACK MfxAppFrameProc(HWND hWnd, MfxMessage msg, WPARAM wParam, LPARAM lParam);
}


#define MFX_APPFRAME_RETURN(ret) MFX_CALLBACK_PARAM.SetRETURN(ret);return ret;

namespace MicroFlakeX
{
	/* 延迟初始化MfxUI - 暂时还没想好怎么做 */
	class MfxUI :
		public MfxBase
	{
		MFXOBJ_ENABLE_REFLECTION;
	private:
		void InitData_UI();
		void RegisterRecvFunc();
	public:
		MfxUI(MfxRect set = MfxRect(60, 60, 400, 400), MfxStringW title = MfxTextW("MfxNormalUI"), DWORD myStyle = UI_WINDOWS_STYLE_Normal, DWORD myStyleEx = WS_EX_LAYERED, MfxUI* father = nullptr);
		virtual ~MfxUI();

		MfxReturn CreateSuccess();
	private:
		MfxReturn MFX_CALLBACK(ProcMessage);
		MfxReturn MFX_CALLBACK(ProcFlakesMessage);
		MfxReturn MFX_CALLBACK(RProcFlakesMessage);
	
	public:
		MfxReturn MFX_CALLBACK(Send_Message);
		MfxReturn MFX_CALLBACK(Post_Message);

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
		MfxReturn RemoveUIMessage(MfxMessage message, MfxStringW recvFuncName);
		MfxReturn PushBackUIMessage(MfxMessage message, UI_UIRecvFunc_Info msgValue);
		MfxReturn PushFrontUIMessage(MfxMessage message, UI_UIRecvFunc_Info msgValue);
		
		/********************************************************************************
		*
		*********************************************************************************/
	private:
		UI_FlakeEvent_Map myFlakeEventMap;
	public:
		MfxReturn RemoveFlakeEvent(FlakeEvent_Info message, MfxStringW recvFuncName);
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


		//LWA_ALPHA
		//LWA_COLORKEY
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
		MfxReturn WND_MAX();
		MfxReturn WND_MIN();
		MfxReturn WND_SHOW();
		MfxReturn WND_HIDE();
		MfxReturn WND_NORMAL();

		/********************************************************************************
		* 
		*********************************************************************************/
	public:
		MfxReturn MFX_CALLBACK(__OnTest00);
		MfxReturn MFX_CALLBACK(__OnTest01);
	private:
		MfxReturn MFX_CALLBACK(__OnCreate);
		MfxReturn MFX_CALLBACK(__OnDestroy);

		MfxReturn MFX_CALLBACK(__OnSize);
		MfxReturn MFX_CALLBACK(__OnMove);

		MfxReturn MFX_CALLBACK(__OnPaint);
		MfxReturn MFX_CALLBACK(__OnEraseBackGrand);

		MfxReturn MFX_CALLBACK(__OnPaintBack);
		MfxReturn MFX_CALLBACK(__OnPaintMask);

		MfxReturn MFX_CALLBACK(__OnFlakeInsert);
		MfxReturn MFX_CALLBACK(__OnFlakeRemove);
		MfxReturn MFX_CALLBACK(__OnFlakeFloorChange);

		MfxReturn MFX_CALLBACK(__OnWin32Timer);

		MfxReturn MFX_CALLBACK(__OnInsertWin32Timer);
		MfxReturn MFX_CALLBACK(__OnRemoveWin32Timer);

		MfxReturn MFX_CALLBACK(__OnFlakeEvent);

		MfxReturn MFX_CALLBACK(__OnRemoveFlakeEvent);
		MfxReturn MFX_CALLBACK(__OnPushBackFlakeEvent);
		MfxReturn MFX_CALLBACK(__OnPushFrontFlakeEvent);

		MfxReturn MFX_CALLBACK(__OnOpenPercentRect);
		MfxReturn MFX_CALLBACK(__OnClosePercentRect);

		MfxReturn MFX_CALLBACK(__OnSetBackColor);
		MfxReturn MFX_CALLBACK(__OnSetMaskColor);



		MfxReturn MFX_CALLBACK(__OnNCPaint);
		MfxReturn MFX_CALLBACK(__OnNCHitTest);
		MfxReturn MFX_CALLBACK(__OnNCActivate);

		MfxReturn MFX_CALLBACK(__OnNCMouseMove);
		MfxReturn MFX_CALLBACK(__OnNCMouseHover);

		MfxReturn MFX_CALLBACK(__OnNCLButtonUp);
		MfxReturn MFX_CALLBACK(__OnNCLButtonDown);
		MfxReturn MFX_CALLBACK(__OnNCLButtonDouble);

		MfxReturn MFX_CALLBACK(__OnNCRButtonUp);
		MfxReturn MFX_CALLBACK(__OnNCRButtonDown);
		MfxReturn MFX_CALLBACK(__OnNCRButtonDouble);
	};


/********************************************************************************
*	在消息处理队列末尾添加一个UIMessage回调
*	对于UI来说，并不区分Event和Message
*********************************************************************************/
#define UI_ADDRECV_UIMSG(Msg, myClass, recvFunc) this->PushBackUIMessage(Msg, UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));
#define UI_FRONTRECV_UIMSG(Msg, myClass, recvFunc) this->PushFrontUIMessage(Msg, UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));

/********************************************************************************
*	移除一个UI消息映射
*********************************************************************************/
#define UI_DELRECV_UIMSG(Msg, myClass, recvFunc) this->RemoveUIMessage(Msg, MfxTextW(#myClass#recvFunc)));



/********************************************************************************
*	在事件处理队列末尾添加一个FlakeEvent回调
*********************************************************************************/
#define UI_ADDRECV_FLAKEEVENT(Flake, Event, myClass, recvFunc) this->PushBackFlakeEvent(FlakeEvent_Info(Flake, Event), UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));
#define UI_FRONTECV_FLAKEEVENT(Flake, Event, myClass, recvFunc) this->PushFrontFlakeEvent(FlakeEvent_Info(Flake, Event), UI_UIRecvFunc_Info((pUIRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));

/********************************************************************************
*	移除一个FlakeEvent映射
*********************************************************************************/
#define UI_DELRECV_FLAKEEVENT(Flake, Event, myClass, recvFunc) this->RemoveFlakeEvent(FlakeEvent_Info(Flake, Event), MfxTextW(#myClass#recvFunc)));



/********************************************************************************
*	添加Win32计时器
*********************************************************************************/
#define UI_ADDRECV_TIMER(timerID, delay, myClass, recvFunc) this->InsertWin32Timer(Win32_Timer_Info(timerID, delay, (pUIRecvFunc)&myClass::recvFunc))
#define UI_DELRECV_TIMER(timerID) this->RemoveWin32Timer(timerID)


#define UI_ADDFLAKE(flake) this->InsertFlake(flake);
}

namespace MicroFlakeX
{
	/********************************************************************************
	*
	*********************************************************************************/
	class MfxFlake :
		public MfxBase
	{
		MFXOBJ_ENABLE_REFLECTION;
		MFXOBJ_ENABLE_FLOORCOMPARE;
	private:
		void InitData_Flake();
		void RegisterRecvFunc();
	public:
		MfxFlake(MfxRect set = MfxRect(60, 60, 100, 100), MfxBase* father = nullptr);
		virtual ~MfxFlake();

	private:
		MfxReturn MFX_CALLBACK(ProcMessage);

	public:
		MfxReturn MFX_CALLBACK(Send_Message);
		MfxReturn MFX_CALLBACK(Post_Message);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		Flake_FlakeMessage_Map myMessageMap;
	public:
		MfxReturn RemoveFlakeMessage(MfxMessage message, MfxStringW name);
		MfxReturn PushBackFlakeMessage(MfxMessage message, Flake_RecvFunc_Infor msgValue);
		MfxReturn PushFrontFlakeMessage(MfxMessage message, Flake_RecvFunc_Infor msgValue);

		/********************************************************************************
		*
		*********************************************************************************/
	private:
		Flake_FlakeEvent_Map myFlakeEventMap;
	public:
		MfxReturn RemoveFlakeEvent(FlakeEvent_Info message, MfxStringW recvFuncName);
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

	protected:
		HWND myWnd;
		MfxBase* myFather;
		MfxFloor myFloor;
		MfxCanvas* myCanvas;
	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetFloor(MfxFloor* ret);
		MfxReturn GetFather(MfxBase** ret);
		MfxReturn GetCanvas(MfxCanvas** ret);

		MfxReturn SetFloor(MfxFloor floor);
		

		/********************************************************************************
		*
		*********************************************************************************/
	protected:
		MfxRect myRect;
		MfxRect myEdgeRect;
		MfxRect myPercentRect;

		MfxStringW myTitle;

		MfxColor myBackColor;
		MfxColor myMaskColor;
		MfxColor myTitleColor;
		double myBackFrameSize;
		double myMaskFrameSize;

		MfxWords myWords;
		MfxRectangle myBackRectangle;
		MfxRectangle myMaskRectangle;

	public:
		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);
		MfxReturn GetEdgeRect(MfxRect* ret);

		MfxReturn GetTitle(MfxStringW* ret);
		MfxReturn GetTitleSize(DOUBLE* ret);

		MfxReturn GetBackColor(MfxColor* ret);
		MfxReturn GetMaskColor(MfxColor* ret);
		MfxReturn GetTitleColor(MfxColor* ret);

		MfxReturn GetBackFrameSize(MfxReal* ret);
		MfxReturn GetMaskFrameSize(MfxReal* ret);

	public:
		MfxReturn SetRect(MfxRect* set);
		MfxReturn SetSize(MfxSize* set);
		MfxReturn SetPoint(MfxPoint* set);
		MfxReturn SetEdgeRect(MfxRect* set);

		MfxReturn SetTitle(MfxStringW set);
		MfxReturn SetTitleSize(DOUBLE set);

		MfxReturn SetBackColor(MfxColor* set);
		MfxReturn SetMaskColor(MfxColor* set);
		MfxReturn SetTitleColor(MfxColor* set);

		MfxReturn SetBackFrameSize(MfxReal set);
		MfxReturn SetMaskFrameSize(MfxReal set);


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
		MfxReturn MFX_CALLBACK(__OnTest001);
	private:
		MfxReturn MFX_CALLBACK(__OnSetPaper);
		MfxReturn MFX_CALLBACK(__OnRemovePaper);

		MfxReturn MFX_CALLBACK(__OnSetFloor);

		MfxReturn MFX_CALLBACK(__OnPaintBackDC);
		MfxReturn MFX_CALLBACK(__OnPaintMaskDC);

		MfxReturn MFX_CALLBACK(__OnFatherSize);

		MfxReturn MFX_CALLBACK(__OnRect);
		MfxReturn MFX_CALLBACK(__OnPercentRect);

		MfxReturn MFX_CALLBACK(__OnRecalculatRect);
		MfxReturn MFX_CALLBACK(__OnRecalculatPercentRect);

		MfxReturn MFX_CALLBACK(__OnOpenPercentRect);
		MfxReturn MFX_CALLBACK(__OnClosePercentRect);

		//
		MfxReturn MFX_CALLBACK(__OnNCMouseMove);
		MfxReturn MFX_CALLBACK(__OnNCMouseHover);

		MfxReturn MFX_CALLBACK(__OnNCLButtonUp);
		MfxReturn MFX_CALLBACK(__OnNCLButtonDown);
		MfxReturn MFX_CALLBACK(__OnNCLButtonDouble);

		MfxReturn MFX_CALLBACK(__OnNCRButtonUp);
		MfxReturn MFX_CALLBACK(__OnNCRButtonDown);
		MfxReturn MFX_CALLBACK(__OnNCRButtonDouble);
		//

		MfxReturn MFX_CALLBACK(__OnMouseMove);
		MfxReturn MFX_CALLBACK(__OnMouseHover);

		MfxReturn MFX_CALLBACK(__OnLButtonUp);
		MfxReturn MFX_CALLBACK(__OnLButtonDown);
		MfxReturn MFX_CALLBACK(__OnLButtonDouble);

		MfxReturn MFX_CALLBACK(__OnRButtonUp);
		MfxReturn MFX_CALLBACK(__OnRButtonDown);
		MfxReturn MFX_CALLBACK(__OnRButtonDouble);

		MfxReturn MFX_CALLBACK(__OnSetTitle);

		MfxReturn MFX_CALLBACK(__OnSetBackColor);
		MfxReturn MFX_CALLBACK(__OnSetMaskColor);
		MfxReturn MFX_CALLBACK(__OnSetTitleColor);

		MfxReturn MFX_CALLBACK(__OnSetBackFrameSize);
		MfxReturn MFX_CALLBACK(__OnSetMaskFrameSize);

		MfxReturn MFX_CALLBACK(__OnFlakeEvent);

		MfxReturn MFX_CALLBACK(__OnRemoveFlakeEvent);
		MfxReturn MFX_CALLBACK(__OnPushBackFlakeEvent);
		MfxReturn MFX_CALLBACK(__OnPushFrontFlakeEvent);
	};

/********************************************************************************
*	在消息处理队列末尾添加一个FlakeMessage回调
*	一般情况下，用户不需要处理FlakeMessage，只需要响应FlakeEvent即可，Message包含了大量无用的消息，Event则是翻译好的有重要意义的事件
*********************************************************************************/
#define FLAKE_ADDRECV_FLAKEMSG(Msg, myClass, recvFunc) this->PushBackFlakeMessage(Msg, Flake_RecvFunc_Infor((pFlakeRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));
#define FLAKE_FRONTRECV_FLAKEMSG(Msg, myClass, recvFunc) this->PushFrontFlakeMessage(Msg, Flake_RecvFunc_Infor((pFlakeRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));
/********************************************************************************
*	移除消息映射
*********************************************************************************/
#define FLAKE_DELRECV_FLAKEMSG(Msg, myClass, recvFunc) this->RemoveFlakeMessage(Msg, MfxTextW(#myClass#recvFunc)));



/********************************************************************************
*	在事件处理队列末尾添加一个FlakeEvent回调
*********************************************************************************/
#define FLAKE_ADDRECV_FLAKEEVENT(Flake, Event, myClass, recvFunc) this->PushBackFlakeEvent(FlakeEvent_Info(Flake, Event), Flake_RecvFunc_Infor((pFlakeRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));
#define FLAKE_FRONTRECV_FLAKEEVENT(Flake, Event, myClass, recvFunc) this->PushFrontFlakeEvent(FlakeEvent_Info(Flake, Event), Flake_RecvFunc_Infor((pFlakeRecvFunc)&myClass::recvFunc, MfxTextW(#myClass#recvFunc)));

/********************************************************************************
*	移除一个FlakeEvent映射
*********************************************************************************/
#define FLAKE_DELRECV_FLAKEEVENT(Flake, Event, myClass, recvFunc) this->RemoveFlakeEvent(FlakeEvent_Info(Flake, Event), MfxTextW(#myClass#recvFunc)));

}