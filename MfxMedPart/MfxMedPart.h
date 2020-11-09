#pragma once

#ifdef MFX_MEDPART_BUILDING
#define MFX_MEDPART_IMPORT __declspec(dllexport)
#else
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
	
	typedef LONG_PTR MFXRETURE;/* 函数返回值 */
	enum MFXRETURE_ENUM/* 函数返回值枚举 - 最大为30种错误 */
	{
		MFXRETURE_OK = 0x0000, //成功，已处理
		MFXRETURE_ERROR = 0xBFFF - 1, //失败
		MFXRETURE_NOFIND = 0xBFFF - 2, //没找到对应的项
		MFXRETURE_FINE = 0xBFFF - 3 //完成任务
	};

	enum MFXUIMESSAGE_ENUM/* UI发出的消息 - 最大为x种 */
	{
		/* UICHANGESIZE* getSize = (UICHANGESIZE*)lParam; */
		MFXUIMSG_SIZE = 0xBFFF - 30
	};

	typedef unsigned long MFXWINDTYPE;/* UI样式 */
	enum MFXWINDTYPE_ENUM/* 函数返回值枚举 */
	{
		MFXWINDTYPE_ANTIFLICKER = WS_CLIPCHILDREN | WS_CLIPSIBLINGS, //防止闪烁 - 必须添加的属性
		MFXWINDTYPE_NORMAL = WS_OVERLAPPEDWINDOW | WS_VISIBLE | MFXWINDTYPE_ANTIFLICKER, //带边框窗口
		MFXWINDTYPE_POPWND = WS_POPUP | WS_VISIBLE | MFXWINDTYPE_ANTIFLICKER, //无边框窗口
		MFXWINDTYPE_CHILD = WS_CHILD, //子窗口
	};

	typedef struct UICHANGESIZE
	{
		Gdiplus::Rect bRect; //改变前的
		Gdiplus::Rect aRect; //改变后的
	}UICHANGESIZE;


	/* UI列表 */
	typedef std::vector<MfxUI*> MFXUI_LIST;
	typedef MFXUI_LIST::iterator MFXUI_LIST_ITERA;

	typedef std::queue<MfxUI*> MFXUI_QUEUE;

	/* 服务器列表
	typedef std::vector<MfxControlMessageServer*> SERVER_LIST;
	typedef SERVER_LIST::iterator SERVER_LIST_ITERA;*/

	/* 控件列表 */
	typedef std::vector<MfxControl*> MFXCONTROL_LIST;
	typedef MFXCONTROL_LIST::iterator MFXCONTROL_LIST_ITERA;

	/* 快捷键栈-表 */
	typedef std::stack<UINT> SHORTCUTKEY;
	typedef std::map<UINT, SHORTCUTKEY> SHORTCUTKEY_MAP;

	/* WndClass映射 */
	typedef std::map<std::wstring, std::wstring> WNDCLASSEXW_MAP;
	typedef WNDCLASSEXW_MAP::value_type WNDCLASSEXW_MAP_ELEM;
	typedef WNDCLASSEXW_MAP::iterator WNDCLASSEXW_MAP_ITERA;
	typedef std::pair<WNDCLASSEXW_MAP::iterator, bool> WNDCLASSEXW_MAP_PAIR;

	/* 服务器映射 */
	typedef std::map<HWND, MfxControlMessageServer*> MFXCONTROL_SERVER_MAP;
	typedef MFXCONTROL_SERVER_MAP::value_type MFXCONTROL_SERVER_MAP_ELEM;
	typedef MFXCONTROL_SERVER_MAP::iterator MFXCONTROL_SERVER_MAP_ITERA;
	typedef std::pair<MFXCONTROL_SERVER_MAP::iterator, bool> MFXCONTROL_SERVER_MAP_PAIR;


	/* UI方法映射 */  //MfxControl* con, UINT message, 
	typedef struct CONCTROLMSG
	{
		MfxControl* control;
		UINT message;
		bool operator<(const CONCTROLMSG& get) const noexcept
		{
			return ((control < get.control) && (message < get.message)); // comparision logic
		}
	}CONCTROLMSG;
	typedef MFXRETURE(MfxUI::* MFXUI_FUNC)(WPARAM, LPARAM);

	typedef std::map<CONCTROLMSG, MFXUI_FUNC> MFXUI_CONCTROL_FUNC_MAP;
	typedef MFXUI_CONCTROL_FUNC_MAP::value_type MFXUI_CONCTROL_FUNC_MAP_ELEM;
	typedef MFXUI_CONCTROL_FUNC_MAP::iterator MFXUI_CONCTROL_FUNC_MAP_ITERA;
	typedef std::pair<MFXUI_CONCTROL_FUNC_MAP::iterator, bool> MFXUI_CONCTROL_FUNC_MAP_PAIR;

	typedef std::map<UINT, MFXUI_FUNC> MFXUI_MESSAGE_FUNC_MAP;
	typedef MFXUI_MESSAGE_FUNC_MAP::value_type MFXUI_MESSAGE_FUNC_MAP_ELEM;
	typedef MFXUI_MESSAGE_FUNC_MAP::iterator MFXUI_MESSAGE_FUNC_MAP_ITERA;
	typedef std::pair<MFXUI_MESSAGE_FUNC_MAP::iterator, bool> MFXUI_MESSAGE_FUNC_MAP_PAIR;

	/* CONTROL方法映射 */
	typedef MFXRETURE(MfxControl::* MFXCONTROL_MESSAGE_FUNC)(WPARAM, LPARAM);
	typedef std::map<UINT, MFXCONTROL_MESSAGE_FUNC> MFXCONTROL_MESSAGE_FUNC_MAP;
	typedef MFXCONTROL_MESSAGE_FUNC_MAP::value_type MFXCONTROL_MESSAGE_FUNC_MAP_ELEM;
	typedef MFXCONTROL_MESSAGE_FUNC_MAP::iterator MFXCONTROL_MESSAGE_FUNC_MAP_ITERA;
	typedef std::pair<MFXCONTROL_MESSAGE_FUNC_MAP::iterator, bool> MFXCONTROL_MESSAGE_FUNC_MAP_PAIR;
}


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
	protected:
		HINSTANCE appInstance; //程序实例句柄
	public:
		/* 获取消息->翻译+转发消息 */
		virtual int AppRun();

	protected:
		MFXCONTROL_SERVER_MAP myServerMap; //映射关系: hwnd -> server
		MFXUI_LIST myUIList; //app全部的UI
		MfxUI* myUICreatNow;
	public:
		virtual HINSTANCE GetInstance();
		virtual void SetCreatUI(MfxUI* add);
		virtual void GetCreatUI(HWND uiWnd);
	public:
		/* 注册UI - 消息服务器会一起被注册 */
		virtual MFXRETURE RegisterUI(MfxUI* regUI);
		/* 删除UI - 消息服务器会一起被删除 - 不会释放消息服务器 */
		virtual MFXRETURE DelRegisterUI(MfxUI* regUI);

		/* 根据Wnd句柄转发消息到对应的消息服务器和UI */
		virtual MFXRETURE CALLBACK ForwardMessageInWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};



	class MfxUI/* >>窗口唯一<< 每个UI等同于一个窗口，UI仅支持双缓冲绘图 - 必须继承重写 */
	{
	public:
		/* 创建一个新的UI(仅支持wchar_t窗口) - 窗口大小、窗口样式、窗口名字、父窗口、wndClassName */
		MfxUI(
			Gdiplus::Rect theRect = Gdiplus::Rect(20, 20, 80, 80),
			DWORD dwStyle = MFXWINDTYPE_NORMAL,
			std::wstring titleName = L"MfxUI",
			MfxUI* father = nullptr,
			std::wstring wndClassName = L"MfxNormal"
		);
		void SetWnd(HWND hWnd);
		/* 删除全部UI，删除窗口服务器，删除APP注册 */
		virtual ~MfxUI();
		/* 检查是否成功 - true = 成功， false = 失败 */
		virtual bool CheckWndCreateSuccess();
	protected:
		bool myWndCreateSuccess; //检查是否成功
		bool myUIPaintEnum; //是否在重绘主界面的时候，重绘子界面
		HBITMAP myBackBitmap;
		MfxImage* myBackImage;
		MfxImage* myMaskImage;
	public:
		/* 将UI缓冲画板到主画板 */
		bool UIUpdateMainDc();
		/* 清理UI缓冲区 */
		bool UICleanBufferDc();
		/* 自动更新UI，默认自动开启 - 未实现 */
		bool UIAutomation(bool runType = true);
		virtual MfxImage* SetUIBack(MfxImage* uiBack);
		virtual MfxImage* SetUIMask(MfxImage* uiMask);
		/* 是否在重绘主界面的时候，重绘子界面 - 当发生显示异常时，开启这一个选项 */
		virtual void SetUIPaintEnum(bool enumType = false);
	protected:
		MFXCONTROL_LIST myControlList; //UI所持有的全部控件
	public:
		/* 注册新的控件到UI上 */
		virtual bool RegisterControl(MfxControl* con);
		/* 注册控件 - 仅删除注册，不会delete控件 */
		virtual bool DelRegisterControl(MfxControl* con);

	protected:
		MFXUI_CONCTROL_FUNC_MAP myControlMessageMap; //控件消息映射
	public:
		/* 注册控件消息响应 - 控件指针、消息名字、响应函数 - 可以在构造函数中注册 */
		virtual MFXRETURE RegisterControlMessage(MfxControl* con, UINT message, MFXUI_FUNC valFunc);
		/* 收到的控件消息(会自动转发) - 控件指针、消息名字、消息参数1、消息参数2 */
		virtual MFXRETURE ReceiveControlMessage(MfxControl* con, UINT message, WPARAM wParam, LPARAM lParam);
		/* 删除控件消息响应 - 随时可以删除 */
		virtual MFXRETURE DelControlMessage(MfxControl* con, UINT message);

	protected:
		MFXUI_MESSAGE_FUNC_MAP myUIMessageMap; //UI消息映射
	public:
		/* 注册UI消息响应 - 消息名字、响应函数 - 可以在构造函数中注册 */
		virtual MFXRETURE RegisterUIMessage(UINT message, MFXUI_FUNC valFunc);
		/* 接收到UI的消息 - 消息名字、消息参数1、消息参数2 */
		virtual MFXRETURE CALLBACK ReceiveUIMessage(UINT message, WPARAM wParam, LPARAM lParam);
		/* 删除UI消息响应 - 随时可以删除 */
		virtual MFXRETURE DelUIMessage(UINT message);

	public:
		HWND GetWnd();
		MfxControlMessageServer* GetMessageServer();
		Gdiplus::Rect GetRect();
		Gdiplus::Point GetPoint();
		Gdiplus::Size GetSize();
		Gdiplus::Graphics* GetBufferGraphics();
	protected:
		void SetX(int set);
		void SetY(int set);
		void SetWidth(int set);
		void SetHeight(int set);
	protected:
		HWND myWnd; //UI窗口句柄
		HDC myMainDc; //UI的主画板 - 需要释放
		HDC myBufferDc; //用于双缓冲 - 需要释放
		Gdiplus::Rect myRect; //UI的大小，会随窗口大小而自动调整
		Gdiplus::Graphics* myBufferGraphics; //UI绘画类，指向UI的缓冲区 - 需要释放
		MfxControlMessageServer* myMessageServer; //UI窗口消息服务器 - 需要释放

	protected:
		virtual MFXRETURE OnUIDestroy(WPARAM wParam, LPARAM lParam);  //销毁
		virtual MFXRETURE OnUIEachFrame(WPARAM wParam, LPARAM lParam);  //每一帧
		virtual MFXRETURE OnUIPaint(WPARAM wParam, LPARAM lParam);  //绘制
		virtual MFXRETURE OnUISize(WPARAM wParam, LPARAM lParam);  //大小发生变化 - WM_SIZING正在发生变化
		virtual MFXRETURE OnUISizing(WPARAM wParam, LPARAM lParam);  //大小发生变化 - WM_SIZING正在发生变化
		virtual MFXRETURE OnUIMove(WPARAM wParam, LPARAM lParam);  //移动窗口
		virtual MFXRETURE OnUISysCommand(WPARAM wParam, LPARAM lParam);  //系统消息
		virtual MFXRETURE OnUIEraseBkGnd(WPARAM wParam, LPARAM lParam); //重绘背景 - 如果开启双缓冲则忽略这一项
		virtual MFXRETURE OnUIChildActivate(WPARAM wParam, LPARAM lParam);  //系统消息 

		virtual MFXRETURE OnUIMSGSize(WPARAM wParam, LPARAM lParam); //父UI消息 - 父窗口改变大小
	};



	class MfxControlMessageServer/* >>窗口唯一<< 窗口消息服务器 - 可以重写，但没必要 */
	{
	public:
		MfxControlMessageServer(MfxUI* myUI);
		virtual ~MfxControlMessageServer();

	public:
		virtual MfxUI* GetMyUI();
		/* 注册控件 */
		virtual MFXRETURE RegisterControl(MfxControl* regControl);

		/* 根据对象删除注册的控件 - 不会delete控件，仅仅删除注册内容 */
		virtual MFXRETURE DelRegisterControl(MfxControl* delControl);

		/* 转发消息到每一个注册到本服务的控件 */
		virtual MFXRETURE ForwardMessageToControl(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		MfxUI* myUI;
		MFXCONTROL_LIST myRegisterControlList;/* 注册到本服务器的控件 */
	};
}


namespace MicroFlakeX
{
	class MfxControl/* 控件基类 - 用户自定义控件从这里继承，也可以直接用已经有的控件 */
	{
	public:
		/* 创建在某个UI上的控件 - 父UI、位置和大小 */
		MfxControl(MfxUI* getUI, Gdiplus::Rect setRect = Gdiplus::Rect(20, 20, 80, 80));
		/* 删除UI注册 */
		virtual ~MfxControl();
	public:
		/* 接收到的消息 - 消息名字、消息参数1、消息参数2 */
		virtual MFXRETURE ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);

		/* 注册消息映射 */
		virtual MFXRETURE RegisterMessage(UINT keyMsg, MFXCONTROL_MESSAGE_FUNC valFunc);
		/* 删除注册的消息映射 */
		virtual MFXRETURE DelRegisterControl(UINT keyMsg);

	
	protected:
		void SetX(int set);
		void SetY(int set);
		void SetWidth(int set);
		void SetHeight(int set);
	public:
		virtual MfxUI* GetMyUI();
		virtual std::wstring GetMyType();
		Gdiplus::Rect GetRect();
		Gdiplus::Point GetPoint();
		Gdiplus::Size GetSize();
	protected:
		MfxUI* myUI;// 控件所属UI
		std::wstring myType;// 控件类型
		MFXCONTROL_MESSAGE_FUNC_MAP myMessageMap;// 函数映射表
		Gdiplus::Rect myRect;
		Gdiplus::Graphics* myGraphics; //因为比较常用

	protected:
		//WM_PAINT - 检查WPARAM是否为空，如果为空则为系统刷新，否则则为UI发出的重绘消息，根据ps可以观察自己是否需要重绘
		virtual MFXRETURE OnEachFrame(WPARAM wParam, LPARAM lParam);  //每一帧
		
	};
}


namespace MicroFlakeX
{
	class MfxButton : public MfxControl
	{
	public:
		MfxButton(MfxUI* getUI, Gdiplus::Rect setRect = Gdiplus::Rect(20, 20, 80, 80));
		~MfxButton();
	protected:
		
		virtual MFXRETURE OnLMouseDown(WPARAM wParam, LPARAM lParam);  //
		virtual MFXRETURE OnLButtonUp(WPARAM wParam, LPARAM lParam);  //
		virtual MFXRETURE OnRButtonDown(WPARAM wParam, LPARAM lParam);  //
		virtual MFXRETURE OnRButtonUp(WPARAM wParam, LPARAM lParam);  //
		virtual MFXRETURE OnMouseMove(WPARAM wParam, LPARAM lParam);  //
		virtual MFXRETURE OnMouseWheel(WPARAM wParam, LPARAM lParam);  //
	};
}