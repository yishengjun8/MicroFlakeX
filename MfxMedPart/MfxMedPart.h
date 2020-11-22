#pragma once

#ifdef MFX_MEDPART_BUILDING
#define MFX_MEDPART_IMPORT __declspec(dllexport)
#else
#include <windowsx.h>
#include <functional>
#include <thread>
#include <time.h>
#include <stack>
#include <queue>
#include "MfxLowPart.h"
#pragma comment(lib,"MfxLowPart.lib")
#define MFX_MEDPART_IMPORT __declspec(dllimport)
#endif

namespace MicroFlakeX
{
	class MFX_MEDPART_IMPORT MfxApplication;
	class MFX_MEDPART_IMPORT MfxUI;
	class MFX_MEDPART_IMPORT MfxControl;
	class MFX_MEDPART_IMPORT MfxControlMessageServer;
	
	/* ———————————————————————————————————————————— */
	/* ———————————————————————————————————————————— */

	typedef LONG_PTR MFXRETURE;// 函数返回值 
	enum MFXRETURE_ENUM// 函数返回值枚举 - 最大为60种错误 
	{
		MFXRETURE_OK = 0x0000, //成功，已处理
		MFXRETURE_ERROR = 0xBFFF - 1, //失败
		MFXRETURE_NOFIND = 0xBFFF - 2, //没找到对应的项
		MFXRETURE_FINE = 0xBFFF - 3, //完成任务
		MFXRETURE_ENUM_MAX = 0xBFFF - 60 //最大错误枚举返回值
	};

	enum MFXUIEVENT_ENUM// UI发送的事件 - 最大为120种 
	{
		MFXUIEVENT_FATHERSIZE = MFXRETURE_ENUM_MAX - 1, //MFXUI_CHANGESIZE* getSize = (MFXUI_CHANGESIZE*)lParam;
		MFXUIEVENT_DRAWBUFFERDC = MFXRETURE_ENUM_MAX - 2,
		MFXUIEVENT_DRAWMAINDC = MFXRETURE_ENUM_MAX - 3,
		//MFXUIEVENT_PAINTBUFFERDC = MFXRETURE_ENUM_MAX - 4,
		MFXUIEVENT_PAINTMAINDC  = MFXRETURE_ENUM_MAX - 5,
		MFXUIEVENT_ENUM_MAX = MFXRETURE_ENUM_MAX - 120
	};

	enum MFXCONTROLEVENT_ENUM// 控件发送的事件 - 最大为120种
	{
		MFXCONTROLEVENT_LBUTTONCLICK = MFXUIEVENT_ENUM_MAX - 1, //点击
		MFXCONTROLEVENT_RBUTTONCLICK = MFXUIEVENT_ENUM_MAX - 2, //点击
		MFXCONTROLEVENT_LDOUBLECLICK = MFXUIEVENT_ENUM_MAX - 3, //双击
		MFXCONTROLEVENT_RDOUBLECLICK = MFXUIEVENT_ENUM_MAX - 4, //双击
		MFXCONTROLEVENT_MOUSEFLOAT = MFXUIEVENT_ENUM_MAX - 5, //悬浮
		MFXCONTROLEVENT_MOUSEPRESS = MFXUIEVENT_ENUM_MAX - 6, //长按
		MFXCONTROLEVENT_ENUM_MAX = MFXUIEVENT_ENUM_MAX - 120
	};

	typedef unsigned long MFXWINDTYPE;// UI样式
	enum MFXWINDTYPE_ENUM// 函数返回值枚举
	{
		MFXWINDTYPE_ANTIFLICKER = WS_CLIPCHILDREN | WS_CLIPSIBLINGS, //防止闪烁 - 必须添加的属性
		MFXWINDTYPE_NORMAL = WS_OVERLAPPEDWINDOW | WS_VISIBLE | MFXWINDTYPE_ANTIFLICKER, //带边框窗口
		MFXWINDTYPE_POPWND = WS_POPUP | WS_VISIBLE | MFXWINDTYPE_ANTIFLICKER, //无边框窗口
		MFXWINDTYPE_CHILD = WS_CHILD, //子窗口
	};

	typedef struct MFXUI_CHANGESIZE//如果UI改变了大小，将会将这个结构体指针发送到MFXUIMSG_SIZE的lParam中
	{
		Gdiplus::Rect bRect; //改变前的
		Gdiplus::Rect aRect; //改变后的
	}MFXUI_CHANGESIZE;


	/* ———————————————————————————————————————————— */
	/* ———————————————————————————————————————————— */

	// WndClass映射
	typedef std::map<std::wstring, std::wstring> WNDCLASSEXW_MAP;
	typedef WNDCLASSEXW_MAP::value_type WNDCLASSEXW_MAP_ELEM;
	typedef WNDCLASSEXW_MAP::iterator WNDCLASSEXW_MAP_ITERA;
	typedef std::pair<WNDCLASSEXW_MAP::iterator, bool> WNDCLASSEXW_MAP_PAIR;

	// 服务器列表
	typedef std::vector<MfxControlMessageServer*> SERVER_LIST;
	typedef SERVER_LIST::iterator SERVER_LIST_ITERA;

	// 服务器映射
	typedef std::map<HWND, MfxControlMessageServer*> MFXCONTROL_SERVER_MAP;
	typedef MFXCONTROL_SERVER_MAP::value_type MFXCONTROL_SERVER_MAP_ELEM;
	typedef MFXCONTROL_SERVER_MAP::iterator MFXCONTROL_SERVER_MAP_ITERA;
	typedef std::pair<MFXCONTROL_SERVER_MAP::iterator, bool> MFXCONTROL_SERVER_MAP_PAIR;

	/* ———————————————————————————————————————————— */
	/* ———————————————————————————————————————————— */

	// UI列表
	typedef std::vector<MfxUI*> MFXUI_LIST;
	typedef MFXUI_LIST::iterator MFXUI_LISTITERA;

	typedef std::queue<MfxUI*> MFXUI_QUEUE;

	// UI方法映射  //MfxControl* con, UINT message, 
	typedef struct MFXUI_CONTROLEVENT
	{
		MfxControl* control;
		UINT message;
		bool operator < (const MFXUI_CONTROLEVENT& get) const
		{
			return ((control < get.control) || (message < get.message));
		}
	}MFXUI_CONTROLEVENT;
	typedef MFXRETURE(MfxUI::* MFXUI_FUNC)(WPARAM, LPARAM);

	typedef std::map<MFXUI_CONTROLEVENT, MFXUI_FUNC> MFXUI_CONTROLEVENT_MAP;
	typedef MFXUI_CONTROLEVENT_MAP::value_type MFXUI_CONTROLEVENT_MAPELEM;
	typedef MFXUI_CONTROLEVENT_MAP::iterator MFXUI_CONTROLEVENT_MAPITERA;
	typedef std::pair<MFXUI_CONTROLEVENT_MAP::iterator, bool> MFXUI_CONTROLEVENT_MAPPAIR;

	typedef std::map<UINT, MFXUI_FUNC> MFXUI_MESSAGE_MAP;
	typedef MFXUI_MESSAGE_MAP::value_type MFXUI_MESSAGE_MAPELEM;
	typedef MFXUI_MESSAGE_MAP::iterator MFXUI_MESSAGE_MAPITERA;
	typedef std::pair<MFXUI_MESSAGE_MAP::iterator, bool> MFXUI_MESSAGE_MAPPAIR;

	typedef struct MFXUI_CLOCK
	{
		MFXUI_CLOCK(UINT message = WM_APP, clock_t delay = INTMAX_MAX, WPARAM wParam = NULL, LPARAM lParam = NULL)
		{
			this->message = message;
			this->wParam = wParam;
			this->lParam = lParam;

			this->delay = delay;
			this->count = 0;
		}
		UINT message;
		WPARAM wParam; 
		LPARAM lParam;

		clock_t delay;
		clock_t count;
	}MFXUI_CLOCK;

	typedef std::map<UINT, MFXUI_CLOCK> MFXUI_CLOCK_MAP;
	typedef MFXUI_CLOCK_MAP::value_type MFXUI_CLOCK_MAPELEM;
	typedef MFXUI_CLOCK_MAP::iterator MFXUI_CLOCK_MAPITERA;
	typedef std::pair<MFXUI_CLOCK_MAP::iterator, bool> MFXUI_CLOCK_MAPPAIR;

	typedef std::vector<MFXUI_CLOCK> MFXUI_CLOCK_LIST;
	typedef MFXUI_CLOCK_LIST::iterator MFXUI_CLOCK_LISTITERA;

	/* ———————————————————————————————————————————— */
	/* ———————————————————————————————————————————— */

	// 控件列表 
	typedef std::vector<MfxControl*> MFXCONTROL_LIST;
	typedef MFXCONTROL_LIST::iterator MFXCONTROL_LISTITERA;

	// CONTROL方法映射
	typedef MFXRETURE(MfxControl::* MFXCONTROL_FUNC)(WPARAM, LPARAM);
	typedef std::map<UINT, MFXCONTROL_FUNC> MFXCONTROL_MESSAGE_MAP;
	typedef MFXCONTROL_MESSAGE_MAP::value_type MFXCONTROL_MESSAGE_MAPELEM;
	typedef MFXCONTROL_MESSAGE_MAP::iterator MFXCONTROL_MESSAGE_MAPITERA;
	typedef std::pair<MFXCONTROL_MESSAGE_MAP::iterator, bool> MFXCONTROL_MESSAGE_MAPPAIR;

	// 快捷键栈-表
	typedef std::stack<UINT> SHORTCUTKEY;
	typedef std::map<UINT, SHORTCUTKEY> SHORTCUTKEY_MAP;
}

#define UIREGMSG(CLASS, MSG, FUNC) RegUIMessage(MSG, (MicroFlakeX::MFXUI_FUNC)&CLASS::FUNC);
#define UIREGEVE(CLASS, MSG, CONTROL, FUNC) RegControlEvent(CONTROL, MSG, (MicroFlakeX::MFXUI_FUNC)&CLASS::FUNC);

namespace MicroFlakeX
{
	/* 初始化MedPart，在开始使用MedPart之前，必须使用本初始化函数 */
	//MFX_MEDPART_IMPORT bool MfxFunc_InitMedPart(HWND hWnd);

	/* 获取一个UINT-ID，此UINT-ID独一无二，可以作为消息标识符 */
	MFX_MEDPART_IMPORT UINT MfxFunc_GetUserId();
	/* 获取程序Application */
	MFX_MEDPART_IMPORT MfxApplication* MfxFunc_GetApp();

	/* 过程函数 - 内部函数请勿使用 */
	MFX_MEDPART_IMPORT LRESULT CALLBACK MfxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	/* 注册全局Application，仅能注册一次 - 内部函数请勿使用 */
	MFX_MEDPART_IMPORT bool MfxGlobleApplication(MfxApplication* gApp);
	/* 向窗口发送重绘消息，包含用户区与非用户区 */
	MFX_MEDPART_IMPORT BOOL CALLBACK MfxEnumRedrawWindow(HWND hWnd, LPARAM lParam);
	/* 向子窗口发送父窗口改变大小的消息 */
	MFX_MEDPART_IMPORT BOOL CALLBACK MfxEnumFatherSize(HWND hWnd, LPARAM lParam);
}

namespace MicroFlakeX
{
	class MfxApplication/* >>程序唯一<< 代表程序本身，唯一 - 必须继承重写 */
	{
	public:
		MfxApplication();
		virtual ~MfxApplication();
		/* 开始消息循环 - 窗口开始运行 */
		int AppRun();

	protected:
		HINSTANCE appInstance; //程序实例句柄
	public:
		/* 获取程序实例句柄 */
		HINSTANCE GetInstance();
		
	protected:
		MfxUI* myBindingUI; //正在构造的UI
	public:
		/* 加载需要绑定的UI */
		void LoadBindingUI(MfxUI* bind);
		/* 为正在创建的UI绑定他的窗口句柄 */
		void BindUIWithWnd(HWND uiWnd);

	protected:
		MFXUI_LIST myUIList;
		MFXCONTROL_SERVER_MAP myServerMap;
	public:
		/* 注册UI */
		virtual MFXRETURE RegUI(MfxUI* regUI);
		/* 解除UI注册 */
		virtual MFXRETURE DelUI(MfxUI* regUI);
		/* 根据Wnd派送消息到UI */
		virtual MFXRETURE ForwardMessageByWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};

	class MfxControlMessageServer/* >>窗口唯一<< 窗口消息服务器 - 可以重写，但没必要 */
	{
	public:
		MfxControlMessageServer(MfxUI* myUI);
		virtual ~MfxControlMessageServer();

	protected:
		MfxUI* myUI;
		MFXCONTROL_LIST myRegisterControlList;/* 注册到本服务器的控件 */
	public:
		virtual MfxUI* GetMyUI();
		/* 注册控件 */
		MFXRETURE RegControl(MfxControl* regControl);
		/* 解除控件注册 */
		MFXRETURE DelControl(MfxControl* delControl);
		/* 转发消息到每一个控件 */
		MFXRETURE ForwardMessageToControl(UINT message, WPARAM wParam, LPARAM lParam);
	};
}

namespace MicroFlakeX
{
	class MfxUI/* >>窗口唯一<< 每个UI等同于一个窗口，UI仅支持双缓冲绘图 - 必须继承重写 */
	{
		/* 待增加的功能：用户焦点 */
	protected:
		bool myWndCreateSuccess; //窗口是否创建成功
		void MfxUIRegDef();
		void MfxUIInitData(Gdiplus::Rect value);
		void MfxUICreateWindowEx(
			DWORD exStyle, DWORD dwStyle, MfxUI* father,
			std::wstring title, std::wstring wndClass);
	public:
		void SetWnd(HWND get);

		MfxUI(Gdiplus::Rect theRect = Gdiplus::Rect(20, 16, 800, 494),
			DWORD exStyle = NULL, DWORD dwStyle = MFXWINDTYPE_NORMAL,
			std::wstring title = L"MfxUI - Title", MfxUI* father = nullptr,
			std::wstring wndClass = L"MfxNormal");

		MfxUI(Gdiplus::Rect theRect, DWORD dwStyle, std::wstring title, MfxUI* father = nullptr);

		/* 删除全部子UI，删除窗口服务器，删除APP注册 */
		virtual ~MfxUI();
		/* 检查窗口是否创建成功 */
		virtual bool CheckWndCreateSuccess();

	protected:
		MfxImage* myBackImage; //背景
		MfxImage* myMaskImage; //蒙版
	public:
		/* 将主界面拷贝到显示界面 */
		bool UICopyMainDCToShowDC();
		/* 将缓冲界面拷贝到主界面 */
		bool UICopyBufferDCToMainDC();
		/* 使用窗口背景重置缓冲界面 */
		bool UIDrawBufferDCBack();
		/* 使用蒙版覆盖主界面 */
		bool UIDrawMainDCMask();
		/* 设置UI背景 */
		virtual MfxImage* UISetBack(MfxImage* uiBack);
		/* 设置UI蒙版 */
		virtual MfxImage* UISetMask(MfxImage* uiMask);

	protected:
		MFXUI_CLOCK_MAP myClockList; /* 使用timer来进行定时 */
	public:
		/* 添加一个定时器 - 利用了WM_TIMER，如果插入已有的，则什么也不干 */
		void UIAddClock(MFXUI_CLOCK set);
		/* 删除一个定时器 */
		void UIDelClock(UINT message);
		/* 重设clock的某些属性 - 如果这是一个新的colck，则会添加新的clock */
		void UIModifyClock(MFXUI_CLOCK set);

	protected:
		MfxControl* myUserFocus; //用户焦点
		MFXCONTROL_LIST myControlList; //UI所持有的全部控件
	public:
		/* 设定用户焦点控件 */
		virtual MfxControl* SetUserFocus(MfxControl* con);
		/* 获取用户焦点控件 */
		virtual MfxControl* GetUserFocus();
		bool RegControl(MfxControl* con);
		bool DelControl(MfxControl* con);

	protected:
		MFXUI_CONTROLEVENT_MAP myControlEventMap; //控件消息映射
	public:
		MFXRETURE RegControlEvent(MfxControl* con, UINT eventID, MFXUI_FUNC valFunc);
		MFXRETURE RecvControlEvent(MfxControl* con, UINT eventID, WPARAM wParam, LPARAM lParam);
		MFXRETURE DelControlEvent(MfxControl* con, UINT eventID);

	protected:
		MFXUI_MESSAGE_MAP myUIMessageMap; //UI消息映射
	public:
		MFXRETURE RegUIMessage(UINT message, MFXUI_FUNC valFunc);
		MFXRETURE RecvUIMessage(UINT message, WPARAM wParam, LPARAM lParam);
		MFXRETURE DelUIMessage(UINT message);

	protected:
		MFXUI_MESSAGE_MAP myMfxDefUIMessageMap; //UI缺省消息映射
	protected:
		MFXRETURE MfxRegDefMessage(UINT message, MFXUI_FUNC valFunc);
		MFXRETURE MfxRecvDefMessage(UINT message, WPARAM wParam, LPARAM lParam);
		MFXRETURE MfxDelDefMessage(UINT message);

	protected:
		HWND myWnd;
		HDC myShowDc; //展示DC
		HDC myMainDc; //主画板 - 需要释放
		HDC myBuffDc; //双缓冲 - 需要释放
		Gdiplus::Graphics* myMainGraphics; //主绘图 - 需要释放
		Gdiplus::Graphics* myBuffGraphics; //双缓冲 - 需要释放
		MfxControlMessageServer* myMessageServer; //消息服务器 - 需要释放
	public:
		/* 获取UI窗口句柄 */
		HWND GetWnd();
		/* 默认画板，当你不知道使用哪个画板，请使用这个画板 */
		Gdiplus::Graphics* GetDefGraphics();
		/* 获取主界面画板 */
		Gdiplus::Graphics* GetMainGraphics();
		/* 获取缓冲区画板 */
		Gdiplus::Graphics* GetBuffGraphics();
		/* 获取UI消息服务器 */
		MfxControlMessageServer* GetMessageServer();

	protected:
		Gdiplus::Rect myRect; //窗口显示区域
	public:
		virtual Gdiplus::Rect GetRect();
		virtual Gdiplus::Size GetSize();
		virtual Gdiplus::Point GetPoint();
	protected:
		void SetRect(Gdiplus::Rect set);
		void SetSize(Gdiplus::Size set);
		void SetPoint(Gdiplus::Point set);

		//默认消息响应
	protected:
		MFXRETURE MfxDefOnDrawBufferDC(WPARAM wParam, LPARAM lParam);	//重绘 - wParam = &ps
		MFXRETURE MfxDefOnDrawMainDC(WPARAM wParam, LPARAM lParam);		//重绘 - wParam = &ps

		MFXRETURE MfxDefOnUIPaint(WPARAM wParam, LPARAM lParam);		//绘制

		MFXRETURE MfxDefOnUITimer(WPARAM wParam, LPARAM lParam);		//定时器

		MFXRETURE MfxDefOnUIDestroy(WPARAM wParam, LPARAM lParam);		//销毁

		MFXRETURE MfxDefOnUISysCommand(WPARAM wParam, LPARAM lParam);	//系统消息
		MFXRETURE MfxDefOnUIEraseBack(WPARAM wParam, LPARAM lParam);	//重绘背景-双缓冲置空

		MFXRETURE MfxDefOnUISize(WPARAM wParam, LPARAM lParam);			//改变大小
		MFXRETURE MfxDefOnUISizing(WPARAM wParam, LPARAM lParam);		//正在改变大小

		MFXRETURE MfxDefOnUIMove(WPARAM wParam, LPARAM lParam);			//移动
		MFXRETURE MfxDefOnUIMoving(WPARAM wParam, LPARAM lParam);		//正在移动

		MFXRETURE MfxDefOnUILButtonDown(WPARAM wParam, LPARAM lParam);	//左键按下
		MFXRETURE MfxDefOnUILButtonUp(WPARAM wParam, LPARAM lParam);	//左键释放
		MFXRETURE MfxDefOnUILDoubleClick(WPARAM wParam, LPARAM lParam);	//左键双击

		MFXRETURE MfxDefOnUIRButtonDown(WPARAM wParam, LPARAM lParam);	//右键按下
		MFXRETURE MfxDefOnUIRButtonUp(WPARAM wParam, LPARAM lParam);	//右键释放
		MFXRETURE MfxDefOnUIRDoubleClick(WPARAM wParam, LPARAM lParam);	//右键双击

		MFXRETURE MfxDefOnUIEventSize(WPARAM wParam, LPARAM lParam);	//窗口大小改变事件
		MFXRETURE MfxDefOnUIEventSizing(WPARAM wParam, LPARAM lParam);	//窗口大小改变事件
	};
}

/* —————————————————————————————————————————————————— */

namespace MicroFlakeX
{
	class MfxControl/* 控件基类 - 用户自定义控件从这里继承，也可以直接用已经有的控件 */
	{
	protected:
		void MfxRegDef();
		void MfxInitData(MfxUI* father, Gdiplus::Rect value);
	public:
		MfxControl(MfxUI* father, Gdiplus::Rect value = Gdiplus::Rect(20, 12, 80, 49));
		virtual ~MfxControl();

	protected:
		MFXCONTROL_MESSAGE_MAP myMessageMap;// 函数映射表
	public:
		MFXRETURE RegMessage(UINT message, MFXCONTROL_FUNC valFunc);
		MFXRETURE RecvMessage(UINT message, WPARAM wParam, LPARAM lParam);
		MFXRETURE DelMessage(UINT message);

	protected:
		MFXCONTROL_MESSAGE_MAP myMfxDefMessageMap; //UI缺省消息映射
	protected:
		MFXRETURE MfxRegDefMessage(UINT message, MFXCONTROL_FUNC valFunc);
		MFXRETURE MfxRecvDefMessage(UINT message, WPARAM wParam, LPARAM lParam);
		MFXRETURE MfxDelDefMessage(UINT message);

	protected:
		MfxUI* myUI;// 控件所属UI
		std::wstring myType;// 控件类型
		Gdiplus::Rect myRect;
		Gdiplus::Graphics* myGraphics; //比较常用
	public:
		MfxUI* GetMyUI();
		virtual std::wstring GetMyType();
		virtual Gdiplus::Rect GetRect();
		virtual Gdiplus::Size GetSize();
		virtual Gdiplus::Point GetPoint();
	protected:
		void SetRect(Gdiplus::Rect set);
		void SetSize(Gdiplus::Size set);
		void SetPoint(Gdiplus::Point set);
	
	protected:
		bool myLButtonClick; //点击
		bool myLButtonPress; //按压
		bool myRButtonClick; //点击
		bool myRButtonPress; //按压
		bool myMouseFloat; //悬浮
		/* 基础事件：鼠标滑轮、鼠标持续按压 用户焦点是否在这里 */
	protected:
		MFXRETURE MfxDefOnDrawBufferDC(WPARAM wParam, LPARAM lParam);//重绘 - wParam = &ps
		MFXRETURE MfxDefOnDrawMainDC(WPARAM wParam, LPARAM lParam);	//重绘 - wParam = &ps

		MFXRETURE MfxDefOnMouseMove(WPARAM wParam, LPARAM lParam);	//移动

		MFXRETURE MfxDefOnLButtonDown(WPARAM wParam, LPARAM lParam);	//左键按下
		MFXRETURE MfxDefOnLButtonUp(WPARAM wParam, LPARAM lParam);		//左键释放
		MFXRETURE MfxDefOnLDoubleClick(WPARAM wParam, LPARAM lParam);	//左键双击

		MFXRETURE MfxDefOnRButtonDown(WPARAM wParam, LPARAM lParam);	//右键按下
		MFXRETURE MfxDefOnRButtonUp(WPARAM wParam, LPARAM lParam);		//右键释放
		MFXRETURE MfxDefOnRDoubleClick(WPARAM wParam, LPARAM lParam);	//右键双击
	};
}