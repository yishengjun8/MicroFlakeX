#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init_0(MfxFlake)
MfxObject_Init_1(MfxFlake, ProcMessage)
MfxAutoFunc_AutoEnumBig(MfxFlake, \
	3, ProcMessage, \
	\
	2, RemoveFlakeMessage, \
	2, PushBackFlakeMessage, \
	2, PushFrontFlakeMessage, \
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
	1, SetMaskImage, \
	\
	END, END);
MfxObject_Init_2(MfxFlake, MfxBase);

void MicroFlakeX::MfxFlake::MfxRegMessages()
{
	/********************************************************************************
	*
	*
	*
	*
	*********************************************************************************/
	FLAKE_ADDRECV_FLAKEMSG(WM_SIZE, MfxFlake, __OnUISize);

	FLAKE_ADDRECV_FLAKEMSG(WM_MOUSEMOVE, MfxFlake, __OnMouseMove);

	FLAKE_ADDRECV_FLAKEMSG(WM_LBUTTONUP, MfxFlake, __OnLButtonUp);
	FLAKE_ADDRECV_FLAKEMSG(WM_RBUTTONUP, MfxFlake, __OnRButtonUp);
	FLAKE_ADDRECV_FLAKEMSG(WM_LBUTTONDOWN, MfxFlake, __OnLButtonDown);
	FLAKE_ADDRECV_FLAKEMSG(WM_RBUTTONDOWN, MfxFlake, __OnRButtonDown);


	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetPaper, MfxFlake, __OnSetPaper);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetFloor, MfxFlake, __OnSetFloor);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PaintBack, MfxFlake, __OnPaintBackDC);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PaintMask, MfxFlake, __OnPaintMaskDC);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_Size, MfxFlake, __OnSize);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_Point, MfxFlake, __OnPoint);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PercentSize, MfxFlake, __OnPercentSize);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PercentPoint, MfxFlake, __OnPercentPoint);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_ResetRect, MfxFlake, __OnResetRect);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_ResetPercentRect, MfxFlake, __OnResetPercentRect);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_OpenPercentRect, MfxFlake, __OnOpenPercentRect);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_ClosePercentRect, MfxFlake, __OnClosePercentRect);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetTitle, MfxFlake, __OnSetTitle);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetBackColor, MfxFlake, __OnSetBackColor);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetMaskColor, MfxFlake, __OnSetMaskColor);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetWords, MfxFlake, __OnSetWords);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetBackImage, MfxFlake, __OnSetBackImage);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetMaskImage, MfxFlake, __OnSetMaskImage);
}

void MicroFlakeX::MfxFlake::MfxFlakeInitData()
{
	/********************************************************************************
	*
	*
	*
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
	myBackImage = new MfxImage(myBackColor, myRect);
	myMaskImage = nullptr;

	myWords = new MfxWords(myTitle, myRect);
	myWords->SetTextAlignmentX(TextAlignmentX::DWRITE_TEXT_ALIGNMENT_CENTER);
	myWords->SetTextAlignmentY(TextAlignmentY::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
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
	MfxCodeLock(this);
	if (myUI)
	{
		myUI->ProcMessage(UI_MSG_FlakeRemove, (WPARAM)this, NULL);
	}

	SafeDelete(myBackImage);
	SafeDelete(myMaskImage);
	SafeDelete(myWords);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::ProcMessage(MfxMessage message, WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxReturn t_Ret = Mfx_Return_Fail;

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

	/**
	if (myUI && (
		myMouseFloat.CheckChangeFlag() || 
		myLButtonPress.CheckChangeFlag() || 
		myRButtonPress.CheckChangeFlag()))
	{
		myMouseFloat.CleanChangeFlag();
		myLButtonPress.CleanChangeFlag();
		myRButtonPress.CleanChangeFlag();

		//RECT tRECT;
		//myRect.GetRECT(&tRECT);
		//InvalidateRect(myWnd, &tRECT, TRUE);
	}
	/**/
	return t_Ret;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeMessage(MfxMessage message, MfxString name)
{
	MfxCodeLock(this);

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i)->myFuncName == name)
			{
				delete* i;
				t_Iter->second.erase(i);
				return Mfx_Return_Fine;
			}
		}
	}

	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxFlake::PushBackFlakeMessage(MfxMessage message, Flake_FlakeMsg_Infor* msgValue)
{
	MfxCodeLock(this);

	Begin:
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		t_Iter = myMessageMap.insert(Flake_FlakeMsg_Map_Elem(message, Flake_FlakeMsg_Infor_Vector())).first;
		goto Begin;
	}
	else
	{
		t_Iter->second.push_back(msgValue);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::PushFrontFlakeMessage(MfxMessage message, Flake_FlakeMsg_Infor* msgValue)
{
	MfxCodeLock(this);

Begin:
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		t_Iter = myMessageMap.insert(Flake_FlakeMsg_Map_Elem(message, Flake_FlakeMsg_Infor_Vector())).first;
		goto Begin;
	}
	else
	{
		t_Iter->second.push_front(msgValue);
	}

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
	return ProcMessage(FLAKE_MSG_OpenPercentRect, NULL, NULL);
}

MfxReturn MicroFlakeX::MfxFlake::ClosePercentRect()
{
	return ProcMessage(FLAKE_MSG_ClosePercentRect, NULL, NULL);
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
	return ProcMessage(FLAKE_MSG_SetFloor, NULL, floor);
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

MfxReturn MicroFlakeX::MfxFlake::GetTitle(MfxString* ret)
{
	*ret = myTitle;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleSize(FLOAT* ret)
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
	return MfxReturn();
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::SetRect(MfxRect* set)
{
	MfxSize t_Size(set);
	MfxPoint t_Point(set);

	ProcMessage(FLAKE_MSG_Size, NULL, (LPARAM)&t_Size);
	ProcMessage(FLAKE_MSG_Point, NULL, (LPARAM)&t_Point);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetSize(MfxSize* set)
{
	MfxSize t_Size(set);

	ProcMessage(FLAKE_MSG_Size, NULL, (LPARAM)&t_Size);

	if (myUI)
	{
		MfxSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(FLAKE_MSG_ResetPercentRect, NULL, MAKELONG(t_UISize.myWidth, t_UISize.myHeight));
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetPoint(MfxPoint* set)
{
	MfxPoint t_Point(set);

	ProcMessage(FLAKE_MSG_Point, NULL, (LPARAM)&t_Point);

	if (myUI)
	{
		MfxSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(FLAKE_MSG_ResetPercentRect, NULL, MAKELONG(t_UISize.myWidth, t_UISize.myHeight));
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetTitle(MfxString set)
{
	return ProcMessage(FLAKE_MSG_SetTitle, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleSize(FLOAT set)
{
	return ProcMessage(FLAKE_MSG_SetTitleSize, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackColor(MfxColor* set)
{
	MfxColor tColor = *set;

	return ProcMessage(FLAKE_MSG_SetBackColor, NULL, (LPARAM)&tColor);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskColor(MfxColor* set)
{
	MfxColor tColor = *set;

	return ProcMessage(FLAKE_MSG_SetMaskColor, NULL, (LPARAM)&tColor);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleColor(MfxColor* set)
{
	MfxColor tColor = *set;

	return ProcMessage(FLAKE_MSG_SetTitleColor, NULL, (LPARAM)&tColor);
}




/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::OpenLButtonMove()
{
	MfxCodeLock(this);

	myLButtonMoveFlag = true;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::CloseLButtonMove()
{
	MfxCodeLock(this);

	myLButtonMoveFlag = false;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::OpenRButtonMove()
{
	MfxCodeLock(this);

	myRButtonMoveFlag = true;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::CloseRButtonMove()
{
	MfxCodeLock(this);

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
	return myWords ? myWords->Clone(ret) : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxFlake::GetBackImage(MfxImage** ret)
{
	return myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskImage(MfxImage** ret)
{
	return myMaskImage ? myMaskImage->Clone(ret) : Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::SetWords(MfxWords* set)
{
	return ProcMessage(FLAKE_MSG_SetWords, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackImage(MfxImage* set)
{
	return ProcMessage(FLAKE_MSG_SetBackImage, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskImage(MfxImage* set)
{
	return ProcMessage(FLAKE_MSG_SetMaskImage, NULL, (LPARAM)set);
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetPaper(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	Paper_Infor* t_PaperValue = (Paper_Infor*)lParam;

	myUI = t_PaperValue->myUI;
	myWnd = t_PaperValue->myWnd;
	myCanvas = t_PaperValue->myCanvas;
	myUIThreadID = t_PaperValue->myUIThreadID;

	if (myBackImage)
	{
		myBackImage->SetCanvas(myCanvas);
	}
	if (myWords)
	{
		myWords->SetCanvas(myCanvas);
	}
	if (myMaskImage)
	{
		myMaskImage->SetCanvas(myCanvas);
	}

	ProcMessage(FLAKE_MSG_ResetPercentRect, 0, 0);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetFloor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);

	myFloor = lParam;
	if (myUI)
	{
		myUI->ProcMessage(UI_MSG_FlakeFloorChange, NULL, NULL);
	}

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
	MfxCodeLock(this);

	if (myBackImage)
	{
		myBackImage->Paint();
	}
	if (myWords)
	{
		myWords->Paint();
	}
	if (myMaskImage)
	{
		myMaskImage->Paint();
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);

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
	MfxCodeLock(this);

	if (myPercentRectFlag || (myPercentRectFlag && myUI->ChickPercentRect()))
	{
		ProcMessage(FLAKE_MSG_ResetRect, wParam, lParam);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxSize* t_Size = (MfxSize*)lParam;

	if (myBackImage)
	{
		myBackImage->SetSize(t_Size);
	}
	if (myMaskImage)
	{
		myMaskImage->SetSize(t_Size);
	}
	if (myWords)
	{
		myWords->SetSize(t_Size);
	}

	myRect.myWidth = t_Size->myWidth;
	myRect.myHeight = t_Size->myHeight;

	RECT tRECT;
	myRect.GetRECT(&tRECT);
	InvalidateRect(myWnd, &tRECT, TRUE);

	//FLAKE_POSTMSG_UITHREAD()

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPoint(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint* t_Point = (MfxPoint*)lParam;

	if (myBackImage)
	{
		myBackImage->SetPoint(t_Point);
	}
	if (myMaskImage)
	{
		myMaskImage->SetPoint(t_Point);
	}
	if (myWords)
	{
		myWords->SetPoint(t_Point);
	}
	myRect.myX = t_Point->myX;
	myRect.myY = t_Point->myY;

	RECT tRECT;
	myRect.GetRECT(&tRECT);
	InvalidateRect(myWnd, &tRECT, TRUE);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPercentSize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxSize* t_Size = (MfxSize*)lParam;

	myPercentRect.myWidth = t_Size->myWidth;
	myPercentRect.myHeight = t_Size->myHeight;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPercentPoint(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint* t_Point = (MfxPoint*)lParam;

	myPercentRect.myX = t_Point->myX;
	myPercentRect.myY = t_Point->myY;

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
	MfxCodeLock(this);
	if (!myUI)
	{
		return Mfx_Return_Fail;
	}
	MfxSize t_UISize;
	myUI->GetSize(&t_UISize);

	MfxRect t_RestRect(
		(myPercentRect.myX * t_UISize.myWidth) / 100000,
		(myPercentRect.myY * t_UISize.myHeight) / 100000,
		(myPercentRect.myWidth * t_UISize.myWidth) / 100000,
		(myPercentRect.myHeight * t_UISize.myHeight) / 100000
	);

	MfxSize t_RestSize(t_RestRect.myWidth, t_RestRect.myHeight);
	MfxPoint t_RestPoint(t_RestRect.myX, t_RestRect.myY);

	ProcMessage(FLAKE_MSG_Size, NULL, (LPARAM)&t_RestSize);
	ProcMessage(FLAKE_MSG_Point, NULL, (LPARAM)&t_RestPoint);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnResetPercentRect(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	if (!myUI)
	{
		return Mfx_Return_Fail;
	}
	MfxSize t_UISize;
	myUI->GetSize(&t_UISize);

	MfxRect t_ResetPercentRect(
		(myRect.myX * 100000.00) / t_UISize.myWidth,
		(myRect.myY * 100000.00) / t_UISize.myHeight,
		(myRect.myWidth * 100000.00) / t_UISize.myWidth,
		(myRect.myHeight * 100000.00) / t_UISize.myHeight
	);

	MfxSize t_ResetPercentSize(t_ResetPercentRect.myWidth, t_ResetPercentRect.myHeight);
	MfxPoint t_ResetPercentPoint(t_ResetPercentRect.myX, t_ResetPercentRect.myY);

	ProcMessage(FLAKE_MSG_PercentSize, NULL, (LPARAM)&t_ResetPercentSize);
	ProcMessage(FLAKE_MSG_PercentPoint, NULL, (LPARAM)&t_ResetPercentPoint);

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
	MfxCodeLock(this);

	if (Mfx_Seccess(ProcMessage(FLAKE_MSG_ResetPercentRect, 0, 0)))
	{
		myPercentRectFlag = true;
		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxFlake::__OnClosePercentRect(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);

	myPercentRectFlag = false;

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	bool tInside = false;
	myRect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

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

	if ((myLButtonPress && myLButtonMoveFlag) ||
		(myRButtonPress && myRButtonMoveFlag))
	{
		if (myUI)
		{
			myUI->LockMutexFocus(this);
		}
		MfxPoint nowPos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		MfxRect t_Rect = myRect;
		t_Rect.Offset(nowPos.myX - myButtonMoveBegin.myX, nowPos.myY - myButtonMoveBegin.myY);

		MfxPoint t_Point(t_Rect.myX, t_Rect.myY);
		SetPoint(&t_Point);
		myButtonMoveBegin = nowPos;
	}
	else
	{
		if (myUI)
		{
			myUI->UnLockMutexFocus();
		}
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	bool tInside = false;
	myRect.IsPointInside(&mousePos, &tInside);
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

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	bool tInside = false;
	myRect.IsPointInside(&mousePos, &tInside);
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

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	bool tInside = false;
	myRect.IsPointInside(&mousePos, &tInside);
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

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	bool tInside = false;
	myRect.IsPointInside(&mousePos, &tInside);
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


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetTitle(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	myTitle = *(MfxString*)lParam;

	if (myWords)
	{
		myWords->SetText(myTitle);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	myBackColor = *(MfxColor*)lParam;

	if (myBackImage)
	{
		myBackImage->FromColor(myBackColor, MfxSize(myRect));
	}
	else
	{
		myBackImage = new MfxImage(myBackColor, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
		myBackImage->SetCanvas(myCanvas);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	myMaskColor = *(MfxColor*)lParam;

	if (myMaskImage)
	{
		myMaskImage->FromColor(myMaskColor, MfxSize(myRect));
	}
	else
	{
		myMaskImage = new MfxImage(myMaskColor, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
		myMaskImage->SetCanvas(myCanvas);
	}

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
	MfxCodeLock(this);
	MfxWords* t_Set = (MfxWords*)lParam;

	if (t_Set)
	{
		SafeDelete(myWords);
		(t_Set)->Clone(&myWords);
		myWords->SetRect(&myRect);
		myWords->SetCanvas(myCanvas);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxImage* t_Set = (MfxImage*)lParam;

	if (t_Set)
	{
		SafeDelete(myBackImage);
		(t_Set)->Clone(&myBackImage);
		myBackImage->SetRect(&myRect);
		myBackImage->SetCanvas(myCanvas);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxImage* t_Set = (MfxImage*)lParam;

	if (t_Set)
	{
		SafeDelete(myMaskImage);
		(t_Set)->Clone(&myMaskImage);
		myMaskImage->SetRect(&myRect);
		myMaskImage->SetCanvas(myCanvas);
	}

	return Mfx_Return_Fine;
}