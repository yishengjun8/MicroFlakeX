#pragma once

#ifdef MFX_BUILDING
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
	class MFX_PORT MfxControl;
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

	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

	typedef MfxReturn(MfxUI::* MfxUI_Func)(WPARAM, LPARAM);

	typedef std::set<MfxMsg> MfxUI_Message_Set;
	typedef std::set<MfxControl*> MfxUI_MfxControl_Set;

	struct MfxUI_MessageMap_Value
	{
		MfxUI_MessageMap_Value(MfxUI_Func setFunc, MfxFloor setFloor, MfxString setName)
		{
			myFunc = setFunc;
			myFloor = setFloor;
			myName = setName;
		}
		MfxUI_Func myFunc;
		MfxFloor myFloor;
		MfxString myName;
	};
	typedef std::vector< MfxUI_MessageMap_Value*> MfxUI_MessageMap_Vector;

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

	struct MfxUI_Paper_Value
	{
		MfxUI_Paper_Value(MfxUI* setUI, HWND setWnd, MfxCanvas* setCanvas)
		{
			myUI = setUI;
			myWnd = setWnd;
			myCanvas = setCanvas;
		}
		MfxUI_Paper_Value()
		{
			myUI = nullptr;
			myWnd = NULL;
			myCanvas = nullptr;
		}
		MfxUI* myUI;
		HWND myWnd;
		MfxCanvas* myCanvas;

	};

	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

	typedef std::deque<MfxControl*> MfxControl_Deque;

	typedef MfxReturn(MfxControl::* MfxControl_Func)(WPARAM, LPARAM);

	struct MfxControl_MessageMap_Value
	{
		MfxControl_MessageMap_Value(MfxControl_Func setFunc, MfxFloor setFloor, MfxString setName)
		{
			myFunc = setFunc;
			myFloor = setFloor;
			myName = setName;
		}
		MfxControl_Func myFunc;
		MfxFloor myFloor;
		MfxString myName;
	};
	typedef std::vector< MfxControl_MessageMap_Value*> MfxControl_MessageMap_Vector;

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
		MfxUI_Message_PaintBack = MfxUI_MessageBegin - 3,
		MfxUI_Message_PaintMask = MfxUI_MessageBegin - 4,

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

		MfxUI_Message_TimerFrame = MfxUI_MessageBegin - 18,
	};

	enum MfxControl_Message
	{
		MfxControl_Message_Size = MfxControl_MessageBegin - 1,
		MfxControl_Message_Point = MfxControl_MessageBegin - 2,

		MfxControl_Message_LButtonClick = MfxControl_MessageBegin - 5,
		MfxControl_Message_RButtonClick = MfxControl_MessageBegin - 6,

		MfxControl_Message_ControlFloorChange = MfxControl_MessageBegin - 7,

		MfxControl_Message_ControlMessage = MfxControl_MessageBegin - 8,

		MfxControl_Message_SetFloor = MfxControl_MessageBegin - 9,

		MfxControl_Message_SetTitle = MfxControl_MessageBegin - 13,
		MfxControl_Message_SetBackColor = MfxControl_MessageBegin - 14,
		MfxControl_Message_SetMaskColor = MfxControl_MessageBegin - 15,
		MfxControl_Message_SetBackImage = MfxControl_MessageBegin - 16,
		MfxControl_Message_SetMaskImage = MfxControl_MessageBegin - 17,
		MfxControl_Message_SetTitleWords = MfxControl_MessageBegin - 18,

		MfxControl_Message_SetTitleSize = MfxControl_MessageBegin - 19,
		MfxControl_Message_GetTitleSize = MfxControl_MessageBegin - 20,
	};

	enum MfxUI_Style_EN
	{
		MfxUI_Style_AntiFlicker = WS_CLIPCHILDREN | WS_CLIPSIBLINGS, //契描妨
		MfxUI_Style_Normal = WS_OVERLAPPEDWINDOW | WS_VISIBLE | MfxUI_Style_AntiFlicker, //屎械
		MfxUI_Style_Pop = WS_POPUP | WS_VISIBLE | MfxUI_Style_AntiFlicker, //涙円崇
	};
}

//MfxApp
namespace MicroFlakeX
{
	class MfxApp
		: public MfxBase
	{
	public:
		static MfxApp*& theApp;
		const static HINSTANCE& theInstance;
		template<class lhsT, class rhsT = lhsT>
		static bool FloorCompare(lhsT* lhs, rhsT* rhs)
		{
			return lhs->myFloor < rhs->myFloor;
		}
	protected:
		static LRESULT CALLBACK AppProc(HWND hWnd, MfxMsg msg, WPARAM wParam, LPARAM lParam);

		MfxObject;
	public:
		MfxApp();
		virtual ~MfxApp();

	public:
		void Run();
		WPARAM overParam;

	private:
		MfxUI* myBindingUI;
	public:
		HWND MfxCreateUIExW(
			MfxUI* ui, MfxRect rect,
			DWORD dwExStyle, DWORD dwStyle,
			MfxString className, MfxString windowsName);

	private:
		MfxUI_Map myUIMap;
	public:
		MfxReturn ForwardMessage(HWND hWnd, MfxMsg message, WPARAM wParam, LPARAM lParam);
	};
}

//MfxUI
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

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);
		MfxReturn SendMessageToControls(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort);

	private:
		MfxUI_Timer_Map __myTimerMap;
		MfxUI_ControlMessage_Map __myControlMessageMap;
		MfxControl_Deque myControlDeque;
		MfxUI_MfxControl_Set myControlSet;
	public:
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

	private:
		HWND myWnd;
		MfxRect myRect;
		MfxCanvas myCanvas;
		MfxImage* myBackImage, * myMaskImage;
	public:
		MfxReturn GetWnd(HWND* ret);

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

	private:
		MfxControl* myMutexFocus, * myKeyboardFocus;
		bool myMutexFocusLockFlag, myKeyboardFocusLockFag;
	public:
		MfxReturn LockMutexFocus(MfxControl* set);
		MfxReturn UnLockMutexFocus();
		MfxReturn SetMutexFocus(MfxControl* set);
		MfxReturn SetKeyboardFocus(MfxControl* set);
		MfxReturn GetMutexFocus(MfxControl** ret);
		MfxReturn GetKeyboardFocus(MfxControl** ret);


	private:
		MfxFloor myUnderFloor, myCoverFloor;
		MfxUI_MessageMap myMessageMap;
		MfxUI_Message_Set myControlMessageSet;
#define UI_CON_RECV_MSG(Msg)\
	(myControlMessageSet.insert((MfxMsg)Msg))

	public:
		MfxReturn RemoveMessage(MfxMsg message, MfxString name);
		MfxReturn InsertMessage(MfxMsg message, MfxUI_MessageMap_Value* msgValue);
#define UI_REG_MSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxUI_MessageMap_Value(\
		(MfxUI_Func)&myClass::FuncName, Floor, L#FuncName)\
		);

	private:
		MfxBase_Vector myFrame;
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

		MfxReturn __OnControlInsert(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnControlRemove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnControlFloorChange(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFrame(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFrameMSGPost(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnControlMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddControlMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveControlMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
	};
}

//MfxControl
/**/
namespace MicroFlakeX
{
	class MfxControl
		: public MfxBase
	{
		MfxObject;

		friend class MfxApp;
	private:
		void MfxRegMessages();
		void MfxControlInitData();
	public:
		MfxControl();
		MfxControl(MfxRect set);
		virtual ~MfxControl();
		virtual MfxReturn GetType(MfxString* ret);

		MfxReturn ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam);

	private:
		HWND myWnd;
		MfxCanvas* myCanvas;
		MfxUI* myUI;// 陣周侭奉UI
		MfxFloor myFloor; //厘議蚊肝
		MfxString myType, myTitle;// 陣周窃侏 - 陣周炎籾
		MfxRect myRect;
	public:
		MfxReturn GetMyUI(MfxUI** ret);
		MfxReturn GetFloor(MfxFloor* ret);

		MfxReturn GetTitle(MfxString* ret);
		MfxReturn GetTitleSize(FLOAT* ret);
		MfxReturn GetTitleColor(MfxColor* ret);

		MfxReturn GetRect(MfxRect* ret);
		MfxReturn GetSize(MfxSize* ret);
		MfxReturn GetPoint(MfxPoint* ret);
	public:
		MfxReturn SetFloor(MfxFloor floor);

		MfxReturn SetTitle(MfxString set);
		MfxReturn SetTitleSize(FLOAT set);
		MfxReturn SetTitleColor(MfxColor set);

		MfxReturn SetRect(MfxRect set);
		MfxReturn SetSize(MfxSize set);
		MfxReturn SetPoint(MfxPoint set);

	protected:
		MfxDataFlag_bool myMouseFloat;
		MfxDataFlag_bool myLButtonPress;
		MfxDataFlag_bool myLButtonClickFlag;
		MfxDataFlag_bool myRButtonPress;
		MfxDataFlag_bool myRButtonClickFlag;
		MfxDataFlag_bool myLButtonMoveFlag, myRButtonMoveFlag;
		MfxPoint myButtonMoveBegin;

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

		MfxReturn SetBackColor(MfxColor set);
		MfxReturn SetMaskColor(MfxColor set);

		MfxReturn SetBackImage(MfxImage* set);
		MfxReturn SetMaskImage(MfxImage* set);
		MfxReturn SetTitleWords(MfxWords* set);

	private:
		MfxFloor myUnderFloor, myCoverFloor;
		MfxControl_MessageMap myMessageMap;
	public:
		MfxReturn RemoveMessage(MfxMsg message, MfxString name);
		MfxReturn InsertMessage(MfxMsg message, MfxControl_MessageMap_Value* msgValue);
#define CONTROL_REG_MSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxControl_MessageMap_Value(\
		(MfxControl_Func)&myClass::FuncName, Floor, L#myClass#FuncName)\
		);

#define MfxSendMessageToUI(Msg, wPara, lPara)\
	if(myUI)\
	{\
		MfxUI_ControlMessage_Key t_ControlMessageKey(this, Msg); \
		MfxUI_ControlMessage_Value t_ControlMessageValue(wPara, lPara); \
		myUI->ProcMessage(MfxControl_Message_ControlMessage, (WPARAM)&t_ControlMessageKey, (WPARAM)&t_ControlMessageValue);\
	}
	
	private:
		MfxReturn __OnSetPaper(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnPaintBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPaintMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnUISize(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSize(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnPoint(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetFloor(WPARAM wParam, LPARAM lParam);

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
/**/

namespace MicroFlakeX
{

}