#pragma once

#ifdef MFX_APPFRAMEWORKDLL_BUILDING
#define MFX_APPFRAMEWORKDLL_IMPORT __declspec(dllexport)
#else

/* Windows 遊猟周 */
#include <time.h>
#include <windowsx.h>
/**/

/* STL庁医垂 */
#include <set>
#include <stack>
#include <queue>
#include <thread>
#include <iostream>
#include <functional>
/**/

#include "MfxBasicGraph.h"
#pragma comment(lib,"MfxBasicModules.lib")

#define MFX_APPFRAMEWORKDLL_IMPORT __declspec(dllimport)
#endif

namespace MicroFlakeX
{
	class MFX_APPFRAMEWORKDLL_IMPORT MfxApplication;

	class MFX_APPFRAMEWORKDLL_IMPORT MfxUI;
	class MFX_APPFRAMEWORKDLL_IMPORT MfxControl;
}

//Mfx窃侏
namespace MicroFlakeX
{
	typedef UINT MfxMsg;

	typedef long long MfxFloor;

	typedef MfxDataFlag<bool> MfxDataFlag_bool;
}

//Mfx否匂
namespace MicroFlakeX
{
	typedef std::map<HWND, MfxUI*> MfxUI_Map;
	typedef MfxUI_Map::value_type MfxUI_Map_elem;
	typedef MfxUI_Map::iterator MfxUI_Map_iterator;

	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

	typedef MfxReturn(MfxUI::* MfxUI_Func)(WPARAM, LPARAM);

	typedef std::set<MfxMsg> MfxUI_Message_Set;
	typedef std::set<MfxControl*> MfxUI_MfxControl_Set;

	struct MfxUI_MessageMap_Value
	{
		MfxUI_MessageMap_Value(MfxUI_Func setFunc, MfxFloor setFloor, MfxStrW setName)
		{
			myFunc = setFunc;
			myFloor = setFloor;
			myName = setName;
		}
		MfxUI_Func myFunc;
		MfxFloor myFloor;
		MfxStrW myName;
	};
	typedef std::vector< MfxUI_MessageMap_Value*> MfxUI_MessageMap_Vector;
	typedef MfxUI_MessageMap_Vector::iterator MfxUI_MessageMap_Vector_iterator;

	typedef std::map<MfxMsg, MfxUI_MessageMap_Vector*> MfxUI_MessageMap;
	typedef MfxUI_MessageMap::value_type MfxUI_MessageMap_elem;

	struct MfxUI_ControlMessage_Key
	{
		MfxUI_ControlMessage_Key(MfxControl* set, MfxMsg msg)
		{
			control = set;
			message = msg;
		}
		MfxControl* control;
		MfxMsg message;
		bool operator < (const MfxUI_ControlMessage_Key& get) const
		{
			if (control != get.control)
			{
				return (control < get.control);
			}
			else
			{
				return (control < get.control) || (message < get.message);
			}
		}
	};
	struct MfxUI_ControlMessage_Value
	{
		MfxUI_ControlMessage_Value(WPARAM wPara, LPARAM lPara)
		{
			wParam = wPara;
			lParam = lPara;
		}
		bool operator < (const MfxUI_ControlMessage_Value& get) const
		{
			return true;
		}
		WPARAM wParam;
		LPARAM lParam;
	};

	typedef std::map<MfxUI_ControlMessage_Key, MfxUI_Func> MfxUI_ControlMessage_Map;
	typedef MfxUI_ControlMessage_Map::value_type MfxUI_ControlMessage_Map_elem;
	typedef MfxUI_ControlMessage_Map::iterator MfxUI_ControlMessage_Map_iterator;

	struct MfxUI_Timer_Value
	{
		MfxUI_Timer_Value(clock_t delay, clock_t pass, MfxUI_Func func)
		{
			delayTime = delay;
			passTime = pass;
			recvFunc = func;
		}
		MfxUI_Func recvFunc;
		clock_t delayTime;
		clock_t passTime;
	};

	typedef std::map<MfxMsg, MfxUI_Timer_Value> MfxUI_Timer_Map;
	typedef MfxUI_Timer_Map::value_type MfxUI_Timer_Map_elem;
	typedef MfxUI_Timer_Map::iterator MfxUI_Timer_Map_iterator;

	struct MfxUI_Paper_Value
	{
		MfxUI_Paper_Value(MfxUI* setUI, HWND setWnd, HDC setBack, HDC setMask)
		{
			myUI = setUI;
			myWnd = setWnd;
			myBackDC = setBack;
			myMaskDC = setMask;
		}
		MfxUI_Paper_Value()
		{
			myUI = nullptr;
			myWnd = NULL;
			myBackDC = nullptr;
			myMaskDC = nullptr;
		}
		MfxUI* myUI;
		HWND myWnd;
		HDC myBackDC;
		HDC myMaskDC;

	};

	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

	typedef std::vector<MfxControl*> MfxControl_Vector;
	typedef MfxControl_Vector::iterator MfxControl_Vector_iterator;

	typedef MfxReturn(MfxControl::* MfxControl_Func)(WPARAM, LPARAM);

	struct MfxControl_MessageMap_Value
	{
		MfxControl_MessageMap_Value(MfxControl_Func setFunc, MfxFloor setFloor, MfxStrW setName)
		{
			myFunc = setFunc;
			myFloor = setFloor;
			myName = setName;
		}
		MfxControl_Func myFunc;
		MfxFloor myFloor;
		MfxStrW myName;
	};
	typedef std::vector< MfxControl_MessageMap_Value*> MfxControl_MessageMap_Vector;
	typedef MfxControl_MessageMap_Vector::iterator MfxControl_MessageMap_Vector_iterator;

	typedef std::map<MfxMsg, MfxControl_MessageMap_Vector*> MfxControl_MessageMap;
	typedef MfxControl_MessageMap::value_type MfxControl_MessageMap_elem;

	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
}

//Mfx旦訟
namespace MicroFlakeX
{
	enum MfxAppMessage
	{
		MfxUI_MessageBegin = 0xBFFF,
		MfxUI_MessageOver = MfxUI_MessageBegin - 256,

		MfxControl_MessageBegin = MfxUI_MessageOver,
		MfxControl_MessageOver = MfxControl_MessageBegin - 256,

		MfxButton_MessageBegin = MfxControl_MessageOver,
		MfxButton_MessageOver = MfxButton_MessageBegin - 256,
	};


	enum MfxUI_Message
	{
		MfxUI_Message_ResetPercentRect = MfxUI_MessageBegin - 1,
		MfxUI_Message_ClosePercentRect = MfxUI_MessageBegin - 2,

		MfxUI_Message_PaintBackDC = MfxUI_MessageBegin - 3,
		MfxUI_Message_PaintMaskDC = MfxUI_MessageBegin - 4,

		MfxUI_Message_ControlInsert = MfxUI_MessageBegin - 6,
		MfxUI_Message_ControlRemove = MfxUI_MessageBegin - 7,

		MfxUI_Message_SetPaper = MfxUI_MessageBegin - 8,

		MfxUI_Message_AddControlMessage = MfxUI_MessageBegin - 10,
		MfxUI_Message_RemoveControlMessage = MfxUI_MessageBegin - 11,

		MfxUI_Message_AddTimer = MfxUI_MessageBegin - 12,
		MfxUI_Message_RemoveTimer = MfxUI_MessageBegin - 13,

		MfxUI_Message_SetBackColor = MfxUI_MessageBegin - 14,
		MfxUI_Message_SetMaskColor = MfxUI_MessageBegin - 15,
		MfxUI_Message_SetBackImage = MfxUI_MessageBegin - 16,
		MfxUI_Message_SetMaskImage = MfxUI_MessageBegin - 17,
	};

	enum MfxControl_Message
	{
		MfxControl_Message_Size = MfxControl_MessageBegin - 1,
		MfxControl_Message_Point = MfxControl_MessageBegin - 2,
		MfxControl_Message_PercentSize = MfxControl_MessageBegin - 3,
		MfxControl_Message_PercentPoint = MfxControl_MessageBegin - 4,

		MfxControl_Message_LButtonClick = MfxControl_MessageBegin - 5,
		MfxControl_Message_RButtonClick = MfxControl_MessageBegin - 6,

		MfxControl_Message_ControlFloorChange = MfxControl_MessageBegin - 7,

		MfxControl_Message_ControlMessage = MfxControl_MessageBegin - 8,

		MfxControl_Message_SetFloor = MfxControl_MessageBegin - 9,

		MfxControl_Message_ResetRect = MfxControl_MessageBegin - 10,
		MfxControl_Message_ResetPercentRect = MfxControl_MessageBegin - 11,
		MfxControl_Message_ClosePercentRect = MfxControl_MessageBegin - 12,

		MfxControl_Message_SetTitle = MfxControl_MessageBegin - 13,
		MfxControl_Message_SetBackColor = MfxControl_MessageBegin - 14,
		MfxControl_Message_SetMaskColor = MfxControl_MessageBegin - 15,
		MfxControl_Message_SetBackImage = MfxControl_MessageBegin - 16,
		MfxControl_Message_SetMaskImage = MfxControl_MessageBegin - 17,
		MfxControl_Message_SetTitleWords = MfxControl_MessageBegin - 18,
	};

	enum MfxUI_Style_EN
	{
		MfxUI_Style_AntiFlicker = WS_CLIPCHILDREN | WS_CLIPSIBLINGS, //契描妨
		MfxUI_Style_Normal = WS_OVERLAPPEDWINDOW | WS_VISIBLE | MfxUI_Style_AntiFlicker, //屎械
		MfxUI_Style_Pop = WS_POPUP | WS_VISIBLE | MfxUI_Style_AntiFlicker, //涙円崇
	};
}

//Mfx蝕慧痕方
namespace MicroFlakeX
{
	// 資函殻會Application
	MFX_APPFRAMEWORKDLL_IMPORT MfxApplication* MfxGetApp();
}

//坪何痕方
namespace __MicroFlakeX
{
	using namespace MicroFlakeX;
	MFX_APPFRAMEWORKDLL_IMPORT LRESULT CALLBACK MfxAppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam);
	MFX_APPFRAMEWORKDLL_IMPORT void MfxRegApp(MfxApplication* reg);
	MFX_APPFRAMEWORKDLL_IMPORT bool MfxUIMessageFloorCompare(MfxUI_MessageMap_Value* lhs, MfxUI_MessageMap_Value* rhs);
	MFX_APPFRAMEWORKDLL_IMPORT bool MfxControlMessageFloorCompare(MfxControl_MessageMap_Value* lhs, MfxControl_MessageMap_Value* rhs);
	MFX_APPFRAMEWORKDLL_IMPORT bool MfxControlFloorCompare(MfxControl* lhs, MfxControl* rhs);
}

//MfxApplication
namespace MicroFlakeX
{
	class MfxApplication
		: public MfxBasicObject
	{
	public:
		MfxApplication();
		virtual ~MfxApplication();
		MfxReturn Run();

	protected:
		MfxUI* myUIMap_Value;
	public:
		HWND MfxCreateWindowExW(
			MfxUI* value, GdipRect gdiRect, 
			DWORD dwExStyle, DWORD dwStyle,
			MfxStrW lpClassName, MfxStrW lpWindowName);

	protected:
		HINSTANCE myInstance;
	public:
		MfxReturn GetInstance(HINSTANCE* ret);

	protected:
		MfxUI_Map myUIMap;
	public:
		MfxReturn ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam);
		//DECLARE_AUTOFUNC(ForwardMessage);
	};
}

//MfxUI
namespace MicroFlakeX
{
	class MfxUI
		: public MfxBasicObject 
	{
		friend class MfxApplication
			;
	protected:
		void MfxUIInitData();
		void MfxRegMessages();
	public:
		MfxUI(GdipRect gdiRect, MfxStrW title);
		MfxUI(GdipRect gdiRect, DWORD myStyle_EN, MfxStrW title);
		MfxUI(GdipRect gdiRect, DWORD myStyleEx_EN, DWORD myStyle_EN, MfxStrW myClass, MfxStrW title);
		virtual ~MfxUI();
		MfxReturn CreateSuccess();

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);
		MfxReturn SendMessageToControls(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort);

	protected:
		MfxUI_Timer_Map __myTimerMap;
		MfxUI_ControlMessage_Map __myControlMessageMap;
		bool myPercentRect_Check;
		MfxControl_Vector myControlVector;
		MfxUI_MfxControl_Set myControlSet;
	public:
		MfxReturn ResetPercentRect();
		MfxReturn ClosePercentRect();
		MfxReturn ChickPercentRect();

		MfxReturn AddControl(MfxControl* set);
		MfxReturn RemoveControl(MfxControl* set);

		MfxReturn AddControlMessage(MfxControl* target, MfxMsg message, MfxUI_Func recv);
#define UI_ADD_CONMSG(Control, Msg, recvFunc)\
	AddControlMessage(Control, Msg, (MfxUI_Func)&recvFunc)
		MfxReturn RemoveControlMessage(MfxControl* target, MfxMsg message);

		MfxReturn AddTimer(WPARAM timerID, clock_t delay, MfxUI_Func recv);
#define UI_ADD_TIMER(timerID, delay, recvFunc)\
	AddTimer(timerID, delay, (MfxUI_Func)&recvFunc)
		MfxReturn RemoveTimer(WPARAM cid);

	protected:
		GdipBitmap* myTestImage;
		HWND myWnd;
		GdipRect myRect;
		HDC myWndDc, myBackDC, myMaskDC;
		MfxImage* myBackImage, * myMaskImage;
		GdipGraphics* myWndGraphics;
	public:
		MfxReturn GetWnd(HWND* ret);
		MfxReturn GetWndDC(HDC* ret);
		MfxReturn GetBackDC(HDC* ret);
		MfxReturn GetMaskDC(HDC* ret);

		MfxReturn GetRect(GdipRect* ret);
		MfxReturn GetSize(GdipSize* ret);
		MfxReturn GetPoint(GdipPoint* ret);
		MfxReturn GetBackImage(MfxImage** ret);
		MfxReturn GetMaskImage(MfxImage** ret);
	public:
		MfxReturn SetRect(GdipRect set);
		MfxReturn SetSize(GdipSize set);
		MfxReturn SetPoint(GdipPoint set);

		MfxReturn SetBackColor(GdipColor set);
		MfxReturn SetMaskColor(GdipColor set);

		MfxReturn SetBackImage(MfxImage* set);
		MfxReturn SetMaskImage(MfxImage* set);

		MfxReturn SetBigIcon(MfxImage* set);
		MfxReturn SetSmallIcon(MfxImage* set);

	protected:
		MfxControl* myMutexFocus, * myKeyboardFocus;
		bool myMutexFocusLockFlag, myKeyboardFocusLockFag;
	public:
		MfxReturn LockMutexFocus(MfxControl* set);
		MfxReturn UnLockMutexFocus();
		MfxReturn SetMutexFocus(MfxControl* set);
		MfxReturn SetKeyboardFocus(MfxControl* set);
		MfxReturn GetMutexFocus(MfxControl** ret);
		MfxReturn GetKeyboardFocus(MfxControl** ret);


	protected:
		MfxFloor myUnderFloor, myCoverFloor;
		MfxUI_MessageMap myMessageMap;
		MfxUI_Message_Set myControlMessageSet;
#define UI_CON_RECV_MSG(Msg)\
	(myControlMessageSet.insert((MfxMsg)Msg))

	protected:
		MfxReturn RemoveMessage(MfxMsg message, MfxStrW name);
		MfxReturn InsertMessage(MfxMsg message, MfxUI_MessageMap_Value* msgValue);
#define UI_REG_MSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxUI_MessageMap_Value(\
		(MfxUI_Func)&myClass::FuncName, Floor, L#FuncName)\
		);

	public:
		MfxReturn __OnTest00(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnTest01(WPARAM wParam, LPARAM lParam);
	protected:

		MfxReturn __OnCreate(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnDestroy(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnMove(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaint(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnControlInsert(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnControlRemove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnControlFloorChange(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveTimer(WPARAM wParam, LPARAM lParam);
		
		MfxReturn __OnControlMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddControlMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveControlMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnResetPercentRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnClosePercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
	};
}

//MfxControl
namespace MicroFlakeX
{
	class MfxControl
		: public MfxBasicObject
	{
	protected:
		void MfxRegMessages();
		void MfxControlInitData();
	public:
		MfxControl();
		virtual ~MfxControl();

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);

	protected:
		HWND myWnd;
		MfxUI* myUI;// 陣周侭奉UI
		MfxFloor myFloor; //厘議蚊肝
		MfxStrW myType, myTitle;// 陣周窃侏 - 陣周炎籾
		bool myPercentRect_Check;
		GdipRect myRect, myPercentRect;
		HDC myBackDC, myMaskDC;
	public:
		MfxReturn GetMyUI(MfxUI** ret);

		MfxReturn GetType(MfxStrW* ret);
		MfxReturn GetTitle(MfxStrW* ret);
		MfxReturn GetFloor(MfxFloor* ret);

		MfxReturn GetRect(GdipRect* ret);
		MfxReturn GetSize(GdipSize* ret);
		MfxReturn GetPoint(GdipPoint* ret);

		MfxReturn GetPercentRect(GdipRect* ret);
		MfxReturn GetPercentSize(GdipSize* ret);
		MfxReturn GetPercentPoint(GdipPoint* ret);
	public:
		MfxReturn SetTitle(MfxStrW set);
		MfxReturn SetFloor(MfxFloor floor);

		MfxReturn SetRect(GdipRect set);
		MfxReturn SetSize(GdipSize set);
		MfxReturn SetPoint(GdipPoint set);

		MfxReturn SetPercentRect(GdipRect set);
		MfxReturn SetPercentSize(GdipSize set);
		MfxReturn SetPercentPoint(GdipPoint set);

	protected:
		MfxDataFlag_bool myMouseFloat;
		MfxDataFlag_bool myLButtonPress;
		MfxDataFlag_bool myLButtonClickFlag;
		MfxDataFlag_bool myRButtonPress;
		MfxDataFlag_bool myRButtonClickFlag;
		MfxDataFlag_bool myLButtonMoveFlag, myRButtonMoveFlag;
		GdipPoint myButtonMoveBegin;

		MfxImage* myBackImage;
		MfxImage* myMaskImage;
		MfxWords* myTitleWords;
	public:
		MfxReturn OpenLButtonMove();
		MfxReturn CloseLButtonMove();
		MfxReturn OpenRButtonMove();
		MfxReturn CloseRButtonMove();

		MfxReturn GetBackImage(MfxImage** ret);
		MfxReturn GetMaskImage(MfxImage** ret);
		MfxReturn GetTitleWords(MfxWords** ret);

		MfxReturn SetBackColor(GdipColor set);
		MfxReturn SetMaskColor(GdipColor set);

		MfxReturn SetBackImage(MfxImage* set);
		MfxReturn SetMaskImage(MfxImage* set);
		MfxReturn SetTitleWords(MfxWords* set);

	protected:
		MfxFloor myUnderFloor, myCoverFloor;
		MfxControl_MessageMap myMessageMap;
	public:
		MfxReturn RemoveMessage(MfxMsg message, MfxStrW name);
		MfxReturn InsertMessage(MfxMsg message, MfxControl_MessageMap_Value* msgValue);
#define CONTROL_REG_MSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxControl_MessageMap_Value(\
		(MfxControl_Func)&myClass::FuncName, Floor, L#myClass#FuncName)\
		);

#define CONTORL_SendMessageToUI(Msg, wPara, lPara)\
	if(myUI)\
	{\
		MfxUI_ControlMessage_Key t_ControlMessageKey(this, Msg); \
		MfxUI_ControlMessage_Value t_ControlMessageValue(wPara, lPara); \
		myUI->ProcMessage(MfxControl_Message_ControlMessage, (WPARAM)&t_ControlMessageKey, (WPARAM)&t_ControlMessageValue);\
	}
	
	protected:
		MfxReturn __OnSetPaper(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnUISize(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPoint(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPercentSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPercentPoint(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetFloor(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnResetRect(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnResetPercentRect(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnMouseMove(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnLButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRButtonUp(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnLButtonDown(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRButtonDown(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetTitle(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetTitleWords(WPARAM wParam, LPARAM lParam);
	};
}