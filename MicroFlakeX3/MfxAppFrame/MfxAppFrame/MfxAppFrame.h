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

	class MFX_PORT MfxFlake;
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
	typedef std::set<MfxFlake*> MfxUI_MfxFlake_Set;

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

	struct MfxUI_FlakeMessage_Key
	{
		MfxUI_FlakeMessage_Key(MfxFlake* set, MfxMsg msg)
		{
			Flake = set;
			message = msg;
		}
		MfxFlake* Flake;
		MfxMsg message;
		bool operator < (const MfxUI_FlakeMessage_Key& get) const
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
	struct MfxUI_FlakeMessage_Value
	{
		MfxUI_FlakeMessage_Value(WPARAM wPara, LPARAM lPara)
		{
			wParam = wPara;
			lParam = lPara;
		}
		bool operator < (const MfxUI_FlakeMessage_Value& get) const
		{
			return true;
		}
		WPARAM wParam;
		LPARAM lParam;
	};

	typedef std::map<MfxUI_FlakeMessage_Key, MfxUI_Func> MfxUI_FlakeMessage_Map;
	typedef MfxUI_FlakeMessage_Map::value_type MfxUI_FlakeMessage_Map_elem;

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

	typedef std::deque<MfxFlake*> MfxFlake_Deque;

	typedef MfxReturn(MfxFlake::* MfxFlake_Func)(WPARAM, LPARAM);

	struct MfxFlake_MessageMap_Value
	{
		MfxFlake_MessageMap_Value(MfxFlake_Func setFunc, MfxFloor setFloor, MfxString setName)
		{
			myFunc = setFunc;
			myFloor = setFloor;
			myName = setName;
		}
		MfxFlake_Func myFunc;
		MfxFloor myFloor;
		MfxString myName;
	};
	typedef std::vector< MfxFlake_MessageMap_Value*> MfxFlake_MessageMap_Vector;

	typedef std::map<MfxMsg, MfxFlake_MessageMap_Vector*> MfxFlake_MessageMap;
	typedef MfxFlake_MessageMap::value_type MfxFlake_MessageMap_elem;

	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
	/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
}

//Mfx旦訟
namespace MicroFlakeX
{
	enum MFX_MSG
	{
		UI_MSG_BEGIN = 0xBFFF,
		UI_MSG_END = UI_MSG_BEGIN - 256,
#define UI_MSG(msg, id) msg = UI_MSG_BEGIN - id,

		FLAKE_MSG_BEGIN = UI_MSG_END,
		FLAKE_MSG_END = FLAKE_MSG_BEGIN - 256,
#define FLAKE_MSG(msg, id) msg = FLAKE_MSG_BEGIN - id,

		BUTTON_MSG_BEGIN = FLAKE_MSG_END,
		BUTTON_MSG_END = BUTTON_MSG_BEGIN - 256,
#define BUTTON_MSG(msg, id) msg = BUTTON_MSG_BEGIN - id,

	};

	enum UI_MSG
	{
		UI_MSG(UI_MSG_PaintBack, 1)
		UI_MSG(UI_MSG_PaintMask, 2)

		UI_MSG(UI_MSG_FlakeInsert, 3)
		UI_MSG(UI_MSG_FlakeRemove, 4)

		UI_MSG(UI_MSG_SetPaper, 5)

		UI_MSG(UI_MSG_AddFlakeMessage, 6)
		UI_MSG(UI_MSG_RemoveFlakeMessage, 7)

		UI_MSG(UI_MSG_AddTimer, 8)
		UI_MSG(UI_MSG_RemoveTimer, 9)

		UI_MSG(UI_MSG_SetBackColor, 10)
		UI_MSG(UI_MSG_SetMaskColor, 11)
		UI_MSG(UI_MSG_SetBackImage, 12)
		UI_MSG(UI_MSG_SetMaskImage, 13)
	};

	enum FLAKE_MSG
	{
		FLAKE_MSG(FLAKE_MSG_Size, 1)
		FLAKE_MSG(FLAKE_MSG_Point, 2)

		FLAKE_MSG(FLAKE_MSG_LButtonClick, 3)
		FLAKE_MSG(FLAKE_MSG_RButtonClick, 4)

		FLAKE_MSG(FLAKE_MSG_FlakeFloorChange, 5)
		FLAKE_MSG(FLAKE_MSG_FlakeMessage, 6)

		FLAKE_MSG(FLAKE_MSG_SetFloor, 7)
		FLAKE_MSG(FLAKE_MSG_SetTitle, 8)

		FLAKE_MSG(FLAKE_MSG_SetBackColor, 9)
		FLAKE_MSG(FLAKE_MSG_SetMaskColor, 10)
		FLAKE_MSG(FLAKE_MSG_SetBackImage, 11)
		FLAKE_MSG(FLAKE_MSG_SetMaskImage, 12)

		FLAKE_MSG(FLAKE_MSG_SetTitleWords, 13)
		FLAKE_MSG(FLAKE_MSG_SetTitleSize, 14)
		FLAKE_MSG(FLAKE_MSG_GetTitleSize, 15)
	};

	enum UI_STYLE
	{
		UI_STYLE_AntiFlicker = WS_CLIPCHILDREN | WS_CLIPSIBLINGS, //契描妨
		UI_STYLE_Normal = WS_OVERLAPPEDWINDOW | WS_VISIBLE | UI_STYLE_AntiFlicker, //屎械
		UI_STYLE_Pop = WS_POPUP | WS_VISIBLE | UI_STYLE_AntiFlicker, //涙円崇
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
		HWND MfxCreateUIEx(
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
		MfxReturn SendMessageToFlakes(MfxMsg message, WPARAM wParam, LPARAM lParam, bool sort);

	private:
		MfxUI_Timer_Map __myTimerMap;
		MfxUI_FlakeMessage_Map __myFlakeMessageMap;
		MfxFlake_Deque myFlakeDeque;
		MfxUI_MfxFlake_Set myFlakeSet;
	public:
		MfxReturn AddFlake(MfxFlake* set);
		MfxReturn RemoveFlake(MfxFlake* set);

		MfxReturn AddFlakeMessage(MfxFlake* target, MfxMsg message, MfxUI_Func recv);
#define UI_ADD_CONMSG(Flake, Msg, recvFunc)\
	AddFlakeMessage(Flake, Msg, (MfxUI_Func)&recvFunc)
		MfxReturn RemoveFlakeMessage(MfxFlake* target, MfxMsg message);

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
		MfxFlake* myMutexFocus, * myKeyboardFocus;
		bool myMutexFocusLockFlag, myKeyboardFocusLockFag;
	public:
		MfxReturn LockMutexFocus(MfxFlake* set);
		MfxReturn UnLockMutexFocus();
		MfxReturn SetMutexFocus(MfxFlake* set);
		MfxReturn SetKeyboardFocus(MfxFlake* set);
		MfxReturn GetMutexFocus(MfxFlake** ret);
		MfxReturn GetKeyboardFocus(MfxFlake** ret);


	private:
		MfxFloor myUnderFloor, myCoverFloor;
		MfxUI_MessageMap myMessageMap;
		MfxUI_Message_Set myFlakeMessageSet;
#define UI_CON_RECV_MSG(Msg)\
	(myFlakeMessageSet.insert((MfxMsg)Msg))

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

		MfxReturn __OnFlakeInsert(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFlakeRemove(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnFlakeFloorChange(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddTimer(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveTimer(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnAddFlakeMessage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnRemoveFlakeMessage(WPARAM wParam, LPARAM lParam);

		MfxReturn __OnSetBackColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskColor(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetBackImage(WPARAM wParam, LPARAM lParam);
		MfxReturn __OnSetMaskImage(WPARAM wParam, LPARAM lParam);
	};
}

//MfxFlake
/**/
namespace MicroFlakeX
{
	class MfxFlake
		: public MfxBase
	{
		MfxObject;

		friend class MfxApp;
	private:
		void MfxRegMessages();
		void MfxFlakeInitData();
	public:
		MfxFlake();
		MfxFlake(MfxRect set);
		virtual ~MfxFlake();
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

	private:
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
		MfxFlake_MessageMap myMessageMap;
	public:
		MfxReturn RemoveMessage(MfxMsg message, MfxString name);
		MfxReturn InsertMessage(MfxMsg message, MfxFlake_MessageMap_Value* msgValue);
#define FLAKE_REG_MSG(Msg, myClass, FuncName, Floor)\
	InsertMessage(Msg, new MfxFlake_MessageMap_Value(\
		(MfxFlake_Func)&myClass::FuncName, Floor, L#myClass#FuncName)\
		);

#define MfxSendMessageToUI(Msg, wPara, lPara)\
	if(myUI)\
	{\
		MfxUI_FlakeMessage_Key t_FlakeMessageKey(this, Msg); \
		MfxUI_FlakeMessage_Value t_FlakeMessageValue(wPara, lPara); \
		myUI->ProcMessage(FLAKE_MSG_FlakeMessage, (WPARAM)&t_FlakeMessageKey, (WPARAM)&t_FlakeMessageValue);\
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