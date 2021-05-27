#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init(MfxFlake)
MfxObject_EndInit(MfxFlake, MfxBase, \
	3, ProcMessage, \
	\
	2, RemoveFlakeEvent, \
	2, PushBackFlakeEvent, \
	2, PushFrontFlakeEvent, \
	\
	0, OpenPercentRect, \
	0, ClosePercentRect, \
	0, ChickPercentRect, \
	\
	1, GetUI, \
	1, GetWnd, \
	1, GetFloor, \
	1, GetCanvas, \
	\
	1, SetFloor, \
	\
	1, GetRect, \
	1, GetSize, \
	1, GetPoint, \
	\
	1, GetTitle, \
	1, GetTitleSize, \
	\
	1, GetBackColor, \
	1, GetMaskColor, \
	1, GetTitleColor, \
	\
	1, SetRect, \
	1, SetSize, \
	1, SetPoint, \
	\
	1, SetTitle, \
	1, SetTitleSize, \
	1, SetBackColor, \
	1, SetMaskColor, \
	1, SetTitleColor, \
	\
	0, OpenLButtonMove, \
	0, CloseLButtonMove, \
	0, OpenRButtonMove, \
	0, CloseRButtonMove, \
	\
	1, GetWords, \
	1, GetBackImage, \
	1, GetMaskImage, \
	\
	1, SetWords, \
	1, SetBackImage, \
	1, SetMaskImage);

void MicroFlakeX::MfxFlake::MfxRegMessages()
{
	FLAKE_ADDRECV_FLAKEMSG(WM_NCMOUSEMOVE, MfxFlake, __OnNCMouseMove);
	FLAKE_ADDRECV_FLAKEMSG(WM_NCMOUSEHOVER, MfxFlake, __OnNCMouseHover);

	FLAKE_ADDRECV_FLAKEMSG(WM_NCLBUTTONUP, MfxFlake, __OnNCLButtonUp);
	FLAKE_ADDRECV_FLAKEMSG(WM_NCLBUTTONDOWN, MfxFlake, __OnNCLButtonDown);
	FLAKE_ADDRECV_FLAKEMSG(WM_NCLBUTTONDBLCLK, MfxFlake, __OnNCLButtonDouble);

	FLAKE_ADDRECV_FLAKEMSG(WM_NCRBUTTONUP, MfxFlake, __OnNCRButtonUp);
	FLAKE_ADDRECV_FLAKEMSG(WM_NCRBUTTONDOWN, MfxFlake, __OnNCRButtonDown);
	FLAKE_ADDRECV_FLAKEMSG(WM_NCRBUTTONDBLCLK, MfxFlake, __OnNCRButtonDouble);

	/********************************************************************************
	*
	*********************************************************************************/
	FLAKE_ADDRECV_FLAKEMSG(WM_MOUSEMOVE, MfxFlake, __OnMouseMove);
	FLAKE_ADDRECV_FLAKEMSG(WM_MOUSEHOVER, MfxFlake, __OnMouseHover);

	FLAKE_ADDRECV_FLAKEMSG(WM_LBUTTONUP, MfxFlake, __OnLButtonUp);
	FLAKE_ADDRECV_FLAKEMSG(WM_LBUTTONDOWN, MfxFlake, __OnLButtonDown);
	FLAKE_ADDRECV_FLAKEMSG(WM_LBUTTONDBLCLK, MfxFlake, __OnLButtonDouble);

	FLAKE_ADDRECV_FLAKEMSG(WM_RBUTTONUP, MfxFlake, __OnRButtonUp);
	FLAKE_ADDRECV_FLAKEMSG(WM_RBUTTONDOWN, MfxFlake, __OnRButtonDown);
	FLAKE_ADDRECV_FLAKEMSG(WM_RBUTTONDBLCLK, MfxFlake, __OnRButtonDouble);

	/********************************************************************************
	*
	*
	*********************************************************************************/
	FLAKE_ADDRECV_FLAKEMSG(WM_SIZE, MfxFlake, __OnUISize);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetPaper, MfxFlake, __OnSetPaper);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_RemovePaper, MfxFlake, __OnRemovePaper);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetFloor, MfxFlake, __OnSetFloor);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PaintBack, MfxFlake, __OnPaintBackDC);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PaintMask, MfxFlake, __OnPaintMaskDC);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_Rect, MfxFlake, __OnRect);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PercentRect, MfxFlake, __OnPercentRect);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_ResetRect, MfxFlake, __OnResetRect);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_ResetPercentRect, MfxFlake, __OnResetPercentRect);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_OpenPercentRect, MfxFlake, __OnOpenPercentRect);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_ClosePercentRect, MfxFlake, __OnClosePercentRect);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetTitle, MfxFlake, __OnSetTitle);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetBackColor, MfxFlake, __OnSetBackColor);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetMaskColor, MfxFlake, __OnSetMaskColor);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetTitleColor, MfxFlake, __OnSetTitleColor);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetWords, MfxFlake, __OnSetWords);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetBackImage, MfxFlake, __OnSetBackImage);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetMaskImage, MfxFlake, __OnSetMaskImage);
}

void MicroFlakeX::MfxFlake::MfxFlakeInitData()
{
	/********************************************************************************
	* 
	*********************************************************************************/
	myWnd = NULL;

	myUI = nullptr;
	myCanvas = nullptr;
	myUIThreadID = NULL;

	myFloor = 66;
	myPercentRectFlag = false;

	myTitle = MfxText("MfxFlake");

	myMouseFloat = false;
	myLButtonClickFlag = false;
	myLButtonPress = false;
	myRButtonClickFlag = false;
	myRButtonPress = false;
	myRButtonMoveFlag = false;
	myLButtonMoveFlag = false;


	myBackColor.Reset(255, 255, 0, 0);
	myMaskColor.Reset(0, 255, 0, 0);
	myTitleColor.Reset(255, 255, 0, 0);

	myBackImage = new MfxImage(&myBackColor, &myRect);
	myMaskImage = nullptr;

	myWords = new MfxWords(myTitle, &myRect);
	myWords->SetTextAlignmentX(TextAlignmentX::DWRITE_TEXT_ALIGNMENT_CENTER);
	myWords->SetTextAlignmentY(TextAlignmentY::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	myWords->SetTextColor(&myTitleColor);
}

MicroFlakeX::MfxFlake::MfxFlake()
{
	myRect.Reset(100, 100, 128, 128);
	MfxFlake::MfxFlakeInitData();
	MfxFlake::MfxRegMessages();
}

MicroFlakeX::MfxFlake::MfxFlake(MfxRect set)
{
	myRect = set;
	MfxFlake::MfxFlakeInitData();
	MfxFlake::MfxRegMessages();
}

MicroFlakeX::MfxFlake::~MfxFlake()
{
	myMutexLock.WaitLock(&myUI);
	myUI ? myUI->ProcMessage(UI_MSG_FlakeRemove, (WPARAM)this, NULL) : 0;
	myMutexLock.UnLock(&myUI);

	myMutexLock.TryWaitLock(&myBackImage, &myMaskImage, &myWords);

	SafeDelete(myBackImage);
	SafeDelete(myMaskImage);
	SafeDelete(myWords);

	myMutexLock.UnLock(&myBackImage, &myMaskImage, &myWords);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::ProcMessage(MfxMessage message, WPARAM wParam, LPARAM lParam)
{
	MfxReturn t_Ret = Mfx_Return_Fail;

	myMutexLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		if (!t_Iter->second.empty())
		{
			for (auto i : t_Iter->second)
			{
				t_Ret = (this->*i->recvFunc)(wParam, lParam);
			}
		}
	}

	myMutexLock.UnLock(&myMessageMap);

	ClearDeleteVctor();

	return t_Ret;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeEvent(MfxMessage message, MfxString name)
{
	auto tRet = Mfx_Return_Fail;

	myMutexLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i)->myFuncName == name)
			{
				delete* i;
				t_Iter->second.erase(i);
				tRet = Mfx_Return_Fine;
				break;
			}
		}
	}
	myMutexLock.UnLock(&myMessageMap);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::PushBackFlakeEvent(MfxMessage message, Flake_RecvFunc_Infor* msgValue)
{
	myMutexLock.WaitLock(&myMessageMap);

	Begin:
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		t_Iter = myMessageMap.insert(Flake_FlakeMessage_Map_Elem(message, Flake_RecvFunc_Infor_Deque())).first;
		goto Begin;
	}
	else
	{
		t_Iter->second.push_back(msgValue);
	}

	myMutexLock.UnLock(&myMessageMap);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::PushFrontFlakeEvent(MfxMessage message, Flake_RecvFunc_Infor* msgValue)
{
	myMutexLock.WaitLock(&myMessageMap);

	Begin:
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		t_Iter = myMessageMap.insert(Flake_FlakeMessage_Map_Elem(message, Flake_RecvFunc_Infor_Deque())).first;
		goto Begin;
	}
	else
	{
		t_Iter->second.push_front(msgValue);
	}

	myMutexLock.UnLock(&myMessageMap);

	return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*
*
*********************************************************************************/

MfxReturn MicroFlakeX::MfxFlake::ClearDeleteVctor()
{
	myMutexLock.WaitLock(&myDeleteSet_pVoid);
	for (auto iter : myDeleteSet_pVoid)
	{
		delete iter;
	}
	myDeleteSet_pVoid.clear();
	myMutexLock.UnLock(&myDeleteSet_pVoid);


	myMutexLock.WaitLock(&myDeleteSet_pMfxBase);
	for (auto iter : myDeleteSet_pMfxBase)
	{
		delete iter;
	}
	myDeleteSet_pMfxBase.clear();
	myMutexLock.UnLock(&myDeleteSet_pMfxBase);

	return Mfx_Return_Fine;
}
MfxReturn MicroFlakeX::MfxFlake::AddDelete_pVoid(void* set)
{
	myMutexLock.WaitLock(&myDeleteSet_pVoid);

	myDeleteSet_pVoid.insert(set);

	myMutexLock.UnLock(&myDeleteSet_pVoid);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::AddDelete_pMfxBase(MfxBase* set)
{
	myMutexLock.WaitLock(&myDeleteSet_pMfxBase);

	myDeleteSet_pMfxBase.insert(set);

	myMutexLock.UnLock(&myDeleteSet_pMfxBase);

	return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::OpenPercentRect()
{
	return ProcMessage(FLAKE_MSG_OpenPercentRect, (WPARAM)this, NULL);
}

MfxReturn MicroFlakeX::MfxFlake::ClosePercentRect()
{
	return ProcMessage(FLAKE_MSG_ClosePercentRect, (WPARAM)this, NULL);
}

MfxReturn MicroFlakeX::MfxFlake::ChickPercentRect()
{
	return  myPercentRectFlag ? Mfx_Return_Fine : Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::GetWnd(HWND* ret)
{
	*ret = myWnd;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetUI(MfxUI** ret)
{
	*ret = myUI;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetFloor(MfxFloor* ret)
{
	*ret = myFloor;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetFloor(MfxFloor floor)
{
	return ProcMessage(FLAKE_MSG_SetFloor, (WPARAM)this, floor);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::GetRect(MfxRect* ret)
{
	*ret = myRect;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetSize(MfxSize* ret)
{
	*ret = myRect;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetPoint(MfxPoint* ret)
{
	*ret = myRect;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetEdgeRect(MfxRect* ret)
{
	*ret = myEdgeRect;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitle(MfxString* ret)
{
	*ret = myTitle;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleSize(DOUBLE* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::GetBackColor(MfxColor* ret)
{
	*ret = myBackColor;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskColor(MfxColor* ret)
{
	*ret = myMaskColor;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleColor(MfxColor* ret)
{
	myMutexLock.WaitLock(&myTitleColor);

	*ret = myTitleColor;

	myMutexLock.UnLock(&myTitleColor);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::SetRect(MfxRect* set)
{
	ProcMessage(FLAKE_MSG_Rect, (WPARAM)this, (LPARAM)set);

	if (myUI)
	{
		ProcMessage(FLAKE_MSG_ResetPercentRect, (WPARAM)this, NULL);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetSize(MfxSize* set)
{
	myMutexLock.WaitLock(&myRect);
	MfxRect tRect = myRect;
	myMutexLock.UnLock(&myRect);

	tRect.SetSize(set);
	ProcMessage(FLAKE_MSG_Rect, (WPARAM)this, (LPARAM)&tRect);

	if (myUI)
	{
		ProcMessage(FLAKE_MSG_ResetPercentRect, (WPARAM)this, NULL);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetPoint(MfxPoint* set)
{
	myMutexLock.WaitLock(&myRect);
	MfxRect tRect = myRect;
	myMutexLock.UnLock(&myRect);

	tRect.SetPoint(set);
	ProcMessage(FLAKE_MSG_Rect, (WPARAM)this, (LPARAM)&tRect);

	if (myUI)
	{
		ProcMessage(FLAKE_MSG_ResetPercentRect, (WPARAM)this, NULL);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetEdgeRect(MfxRect* set)
{
	myMutexLock.WaitLock(&myEdgeRect);

	myEdgeRect = set;

	myMutexLock.UnLock(&myEdgeRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetTitle(MfxString set)
{
	return ProcMessage(FLAKE_MSG_SetTitle, (WPARAM)this, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleSize(DOUBLE set)
{
	return ProcMessage(FLAKE_MSG_SetTitleSize, (WPARAM)this, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackColor(MfxColor* set)
{
	return ProcMessage(FLAKE_MSG_SetBackColor, (WPARAM)this, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskColor(MfxColor* set)
{
	return ProcMessage(FLAKE_MSG_SetMaskColor, (WPARAM)this, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleColor(MfxColor* set)
{
	return ProcMessage(FLAKE_MSG_SetTitleColor, (WPARAM)this, (LPARAM)set);
}




/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::OpenLButtonMove()
{
	myLButtonMoveFlag = true;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::CloseLButtonMove()
{
	myLButtonMoveFlag = false;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::OpenRButtonMove()
{
	myRButtonMoveFlag = true;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::CloseRButtonMove()
{
	myRButtonMoveFlag = false;

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::GetWords(MfxWords** ret)
{
	myMutexLock.WaitLock(&myWords);

	auto tRet = myWords ? myWords->Clone(ret) : Mfx_Return_Fail;

	myMutexLock.UnLock(&myWords);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::GetBackImage(MfxImage** ret)
{
	myMutexLock.WaitLock(&myBackImage);

	auto tRet = myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;

	myMutexLock.UnLock(&myBackImage);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskImage(MfxImage** ret)
{
	myMutexLock.WaitLock(&myMaskImage);

	auto tRet = myMaskImage ? myMaskImage->Clone(ret) : Mfx_Return_Fail;

	myMutexLock.UnLock(&myMaskImage);

	return tRet;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::SetWords(MfxWords* set)
{
	return ProcMessage(FLAKE_MSG_SetWords, (WPARAM)this, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackImage(MfxImage* set)
{
	return ProcMessage(FLAKE_MSG_SetBackImage, (WPARAM)this, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskImage(MfxImage* set)
{
	return ProcMessage(FLAKE_MSG_SetMaskImage, (WPARAM)this, (LPARAM)set);
}



MfxReturn MicroFlakeX::MfxFlake::__OnTest001(WPARAM wParam, LPARAM lParam)
{
	MessageBox(myWnd, L"__OnTest001", L"__OnTest001", 0);
	return Mfx_Return_Fine;
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetPaper(WPARAM wParam, LPARAM lParam)
{
	Paper_Infor* t_PaperValue = (Paper_Infor*)lParam;

	myMutexLock.TryWaitLock(&myUI, &myWnd, &myCanvas, &myUIThreadID);

	myUI = t_PaperValue->myUI;
	myWnd = t_PaperValue->myWnd;
	myCanvas = t_PaperValue->myCanvas;
	myUIThreadID = t_PaperValue->myUIThreadID;

	myMutexLock.UnLock(&myUI, &myWnd, &myUIThreadID);

	myMutexLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->SetCanvas(myCanvas) : 0;
	myMutexLock.UnLock(&myBackImage);
	
	myMutexLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->SetCanvas(myCanvas) : 0;
	myMutexLock.UnLock(&myMaskImage);

	myMutexLock.WaitLock(&myWords);
	myWords ? myWords->SetCanvas(myCanvas) : 0;
	myMutexLock.UnLock(&myWords);

	myMutexLock.UnLock(&myCanvas);

	ProcMessage(FLAKE_MSG_ResetPercentRect, (WPARAM)this, 0);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRemovePaper(WPARAM wParam, LPARAM lParam)
{
	myMutexLock.TryWaitLock(&myUI, &myWnd, &myCanvas, &myUIThreadID);

	myUI = NULL;
	myWnd = NULL;
	myCanvas = NULL;
	myUIThreadID = NULL;

	myMutexLock.UnLock(&myUI, &myWnd, &myUIThreadID);

	myMutexLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->SetCanvas(myCanvas) : 0;
	myMutexLock.UnLock(&myBackImage);

	myMutexLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->SetCanvas(myCanvas) : 0;
	myMutexLock.UnLock(&myMaskImage);

	myMutexLock.WaitLock(&myWords);
	myWords ? myWords->SetCanvas(myCanvas) : 0;
	myMutexLock.UnLock(&myWords);

	myMutexLock.UnLock(&myCanvas);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetFloor(WPARAM wParam, LPARAM lParam)
{

	myMutexLock.TryWaitLock(&myFloor, &myUI);

	myFloor = lParam;
	myUI ? myUI->ProcMessage(UI_MSG_FlakeFloorChange, (WPARAM)this, NULL) : 0;

	myMutexLock.UnLock(&myFloor, &myUI);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
	myMutexLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->Paint() : 0;
	myMutexLock.UnLock(&myBackImage);

	myMutexLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->Paint() : 0;
	myMutexLock.UnLock(&myMaskImage);

	myMutexLock.WaitLock(&myWords);
	myWords ? myWords->Paint() : 0;
	myMutexLock.UnLock(&myWords);


	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
	return Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnUISize(WPARAM wParam, LPARAM lParam)
{
	bool tChick = false;

	myMutexLock.WaitLock(&myUI);
	myUI ? myUI->ChickPercentRect(&tChick) : 0;
	myMutexLock.UnLock(&myUI);

	if (myPercentRectFlag || tChick)
	{
		ProcMessage(FLAKE_MSG_ResetRect, (WPARAM)this, NULL);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRect(WPARAM wParam, LPARAM lParam)
{
	MfxRect* tSetRect = (MfxRect*)lParam;

	myMutexLock.TryWaitLock(&myEdgeRect);
	MfxRect tEdgeRect = myEdgeRect;
	myMutexLock.UnLock(&myEdgeRect);

	bool isIn = false;
	tEdgeRect.IsEmpty(&isIn);

	if (!isIn)
	{
		tEdgeRect.IsRectInside(tSetRect, &isIn);
		if (!isIn)
		{
			tSetRect->Intersect(&tEdgeRect, tSetRect);
		}
	}

	myMutexLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->SetRect(tSetRect) : 0;
	myMutexLock.UnLock(&myBackImage);

	myMutexLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->SetRect(tSetRect) : 0;
	myMutexLock.UnLock(&myMaskImage);

	myMutexLock.WaitLock(&myWords);
	myWords ? myWords->SetRect(tSetRect) : 0;
	myMutexLock.UnLock(&myWords);


	myMutexLock.TryWaitLock(&myUI, &myRect);

	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;

	myRect.SetRect(tSetRect);

	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;

	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPercentRect(WPARAM wParam, LPARAM lParam)
{
	MfxRect* tSetPercentRect = (MfxRect*)lParam;

	myMutexLock.WaitLock(&myPercentRect);

	myPercentRect.SetRect(tSetPercentRect);

	myMutexLock.UnLock(&myPercentRect);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnResetRect(WPARAM wParam, LPARAM lParam)
{
	MfxSize t_UISize;
	myMutexLock.WaitLock(&myUI);

	if (!myUI)
	{
		return Mfx_Return_Fail;
	}
	myUI->GetSize(&t_UISize);

	myMutexLock.UnLock(&myUI);

	myMutexLock.WaitLock(&myPercentRect);
	MfxRect t_RestRect(
		(myPercentRect.myX * t_UISize.myWidth) / 100000,
		(myPercentRect.myY * t_UISize.myHeight) / 100000,
		(myPercentRect.myWidth * t_UISize.myWidth) / 100000,
		(myPercentRect.myHeight * t_UISize.myHeight) / 100000
	);
	myMutexLock.UnLock(&myPercentRect);

	ProcMessage(FLAKE_MSG_Rect, (WPARAM)this, (LPARAM)&t_RestRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnResetPercentRect(WPARAM wParam, LPARAM lParam)
{
	MfxSize t_UISize;
	myMutexLock.WaitLock(&myUI);

	if (!myUI)
	{
		return Mfx_Return_Fail;
	}
	myUI->GetSize(&t_UISize);

	myMutexLock.UnLock(&myUI);

	myMutexLock.WaitLock(&myRect);
	MfxRect t_ResetPercentRect(
		(myRect.myX * 100000.00) / t_UISize.myWidth,
		(myRect.myY * 100000.00) / t_UISize.myHeight,
		(myRect.myWidth * 100000.00) / t_UISize.myWidth,
		(myRect.myHeight * 100000.00) / t_UISize.myHeight
	);
	myMutexLock.UnLock(&myRect);

	ProcMessage(FLAKE_MSG_PercentRect, (WPARAM)this, (LPARAM)&t_ResetPercentRect);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnOpenPercentRect(WPARAM wParam, LPARAM lParam)
{
	if (Mfx_Seccess(ProcMessage(FLAKE_MSG_ResetPercentRect, (WPARAM)this, 0)))
	{
		myPercentRectFlag = true;

		return Mfx_Return_Fine;
	}
	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxFlake::__OnClosePercentRect(WPARAM wParam, LPARAM lParam)
{
	myPercentRectFlag = false;

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCMouseMove(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_MOUSEMOVE, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCMouseHover(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_MOUSEHOVER, wParam, lParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_LBUTTONUP, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_LBUTTONDOWN, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonDouble(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_LBUTTONDBLCLK, wParam, lParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_RBUTTONUP, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_RBUTTONDOWN, wParam, lParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonDouble(WPARAM wParam, LPARAM lParam)
{
	return ProcMessage(WM_RBUTTONDBLCLK, wParam, lParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMutexLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMutexLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;

		myUI ? myUI->SetMutexFocus(this) : 0;
		myUI ? myUI->GetMutexFocus(&t_Conctrol) : 0;

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			myMouseFloat = true; //成功悬浮 - 发送消息
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myMouseFloat = false;
		myLButtonClickFlag = false;
		myRButtonClickFlag = false;
	}

	//开始移动
	if ((myLButtonPress && myLButtonMoveFlag) ||
		(myRButtonPress && myRButtonMoveFlag))
	{
		if (Mfx_Seccess(myUI ? myUI->LockMutexFocus(this) : Mfx_Return_Fail))
		{
			myMutexLock.WaitLock(&myButtonMoveBegin);

			t_Rect.Offset(mousePos.myX - myButtonMoveBegin.myX, mousePos.myY - myButtonMoveBegin.myY);
			MfxPoint t_Point(t_Rect.myX, t_Rect.myY);
			SetPoint(&t_Point);
			myButtonMoveBegin = mousePos;

			myMutexLock.UnLock(&myButtonMoveBegin);
		}
	}
	else
	{
		myUI ? myUI->UnLockMutexFocus() : 0;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMutexLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMutexLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			if (myLButtonClickFlag) //点击成功
			{
				myMouseFloat = true;
				myLButtonPress = false;
				myLButtonClickFlag = false;
				FLAKE_POSTMSG_UITHREAD(FLAKE_MSG_LButtonClick, wParam, lParam);
			}
			else
			{
				goto myFailed;
			}
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myMouseFloat = false;
		myLButtonPress = false;
		myLButtonClickFlag = false;
		myRButtonClickFlag = false;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMutexLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMutexLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;
			myUI->SetKeyboardFocus(this); //设置键盘焦点
			myMouseFloat = true;
			myLButtonPress = true;
			myLButtonClickFlag = true;
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myMouseFloat = false;
		myLButtonPress = false;
		myLButtonClickFlag = false;
		myRButtonClickFlag = false;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonDouble(WPARAM wParam, LPARAM lParam)
{
	return MfxReturn();
}


MfxReturn MicroFlakeX::MfxFlake::__OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMutexLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMutexLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			if (myRButtonClickFlag) //点击成功
			{
				myMouseFloat = true;
				myRButtonPress = false;
				myRButtonClickFlag = false;
				FLAKE_POSTMSG_UITHREAD(FLAKE_MSG_RButtonClick, wParam, lParam);
			}
			else
			{
				goto myFailed;
			}
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myMouseFloat = false;
		myRButtonPress = false;
		myRButtonClickFlag = false;
		myLButtonClickFlag = false;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMutexLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMutexLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;
			myMouseFloat = true;
			myRButtonPress = true;
			myRButtonClickFlag = true;
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myMouseFloat = false;
		myRButtonPress = false;
		myRButtonClickFlag = false;
		myLButtonClickFlag = false;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonDouble(WPARAM wParam, LPARAM lParam)
{
	return MfxReturn();
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetTitle(WPARAM wParam, LPARAM lParam)
{
	myMutexLock.TryWaitLock(&myTitle, &myWords);

	myTitle = *(MfxString*)lParam;

	myWords ? myWords->SetText(myTitle) : 0;

	myMutexLock.UnLock(&myTitle, &myWords);


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
	myMutexLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMutexLock.UnLock(&myRect);

	myMutexLock.TryWaitLock(&myBackImage, &myBackColor, &myCanvas);
	myBackColor = (MfxColor*)lParam;
	if (myBackImage)
	{
		myBackImage->FromColor(&myBackColor, &tSize);
	}
	else
	{
		myBackImage = new MfxImage(&myBackColor, &tSize);
		myBackImage->SetCanvas(myCanvas);
	}
	myMutexLock.UnLock(&myBackImage, &myBackColor, &myCanvas);


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
	myMutexLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMutexLock.UnLock(&myRect);

	myMutexLock.TryWaitLock(&myMaskImage, &myMaskColor, &myCanvas);
	myMaskColor = (MfxColor*)lParam;
	if (myMaskImage)
	{
		myMaskImage->FromColor(&myMaskColor, &tSize);
	}
	else
	{
		myMaskImage = new MfxImage(&myMaskColor, &tSize);
		myMaskImage->SetCanvas(myCanvas);
	}
	myMutexLock.UnLock(&myMaskImage, &myMaskColor, &myCanvas);


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetTitleColor(WPARAM wParam, LPARAM lParam)
{
	myMutexLock.TryWaitLock(&myWords, &myTitleColor, &myCanvas);
	myTitleColor = (MfxColor*)lParam;
	if (myWords)
	{
		myWords->SetTextColor(&myTitleColor);
	}
	myMutexLock.UnLock(&myWords, &myTitleColor, &myCanvas);


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetWords(WPARAM wParam, LPARAM lParam)
{
	MfxWords* t_Set = (MfxWords*)lParam;
	if (t_Set)
	{
		myMutexLock.TryWaitLock(&myBackImage, &myRect, &myCanvas);

		SafeDelete(myWords);
		(t_Set)->Clone(&myWords);
		myWords->SetRect(&myRect);
		myWords->SetCanvas(myCanvas);

		myMutexLock.UnLock(&myBackImage, &myRect, &myCanvas);
	}


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
	MfxImage* t_Set = (MfxImage*)lParam;
	if (t_Set)
	{
		myMutexLock.TryWaitLock(&myBackImage, &myRect, &myCanvas);

		SafeDelete(myBackImage);
		(t_Set)->Clone(&myBackImage);
		myBackImage->SetRect(&myRect);
		myBackImage->SetCanvas(myCanvas);

		myMutexLock.UnLock(&myBackImage, &myRect, &myCanvas);
	}


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
	MfxImage* t_Set = (MfxImage*)lParam;
	if (t_Set)
	{
		myMutexLock.TryWaitLock(&myMaskImage, &myRect, &myCanvas);

		SafeDelete(myMaskImage);
		(t_Set)->Clone(&myMaskImage);
		myMaskImage->SetRect(&myRect);
		myMaskImage->SetCanvas(myCanvas);

		myMutexLock.UnLock(&myMaskImage, &myRect, &myCanvas);
	}


	myMutexLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMutexLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}