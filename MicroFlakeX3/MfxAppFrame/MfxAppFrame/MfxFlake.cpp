#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init(MfxFlake)
MfxObject_EndInit(MfxFlake, MfxBase, \
	1, ProcMessage, \
	\
	1, Send_Message, \
	1, Post_Message, \
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
	\
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

	FLAKE_ADDRECV_FLAKEMSG(MSG_FlakeEvent, MfxFlake, __OnFlakeEvent);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_RemoveFlakeEvent, MfxFlake, __OnRemoveFlakeEvent);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PushBackFlakeEvent, MfxFlake, __OnPushBackFlakeEvent);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_PushFrontFlakeEvent, MfxFlake, __OnPushFrontFlakeEvent);
}

void MicroFlakeX::MfxFlake::MfxFlakeInitData()
{
	/********************************************************************************
	* 
	*********************************************************************************/
	myWnd = NULL;

	myUI = nullptr;
	myCanvas = nullptr;

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
	MfxParam msgParam;
	msgParam.push_back(UI_MSG_FlakeRemove);
	msgParam.push_back(this);

	myMemberLock.WaitLock(&myUI);
	myUI ? myUI->Send_Message(msgParam) : 0;
	myMemberLock.UnLock(&myUI);

	myMemberLock.TryWaitLock(&myBackImage, &myMaskImage, &myWords);

	SafeDelete(myBackImage);
	SafeDelete(myMaskImage);
	SafeDelete(myWords);

	myMemberLock.UnLock(&myBackImage, &myMaskImage, &myWords);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::ProcMessage(MfxParam param)
{
	MfxReturn t_Ret = Mfx_Return_Fail;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(GetParam(param, MfxMessage, 0));
	if (t_Iter != myMessageMap.end())
	{
		if (!t_Iter->second.empty())
		{
			for (auto i : t_Iter->second)
			{
				t_Ret = (this->*i.recvFunc)(param);
			}
		}
	}

	myMemberLock.UnLock(&myMessageMap);

	return t_Ret;
}

MfxReturn MicroFlakeX::MfxFlake::Send_Message(MfxParam param)
{
	return ProcMessage(param);
}

MfxReturn MicroFlakeX::MfxFlake::Post_Message(MfxParam param)
{
	return MfxBeginNewThread(this, MfxText("ProcMessage"), param);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeMessage(MfxMessage message, MfxString name)
{
	auto tRet = Mfx_Return_Fail;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i).myRecvFuncName == name)
			{
				t_Iter->second.erase(i);
				tRet = Mfx_Return_Fine;
				break;
			}
		}
	}
	myMemberLock.UnLock(&myMessageMap);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::PushBackFlakeMessage(MfxMessage message, Flake_RecvFunc_Infor msgValue)
{
	myMemberLock.WaitLock(&myMessageMap);

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

	myMemberLock.UnLock(&myMessageMap);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::PushFrontFlakeMessage(MfxMessage message, Flake_RecvFunc_Infor msgValue)
{
	myMemberLock.WaitLock(&myMessageMap);

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

	myMemberLock.UnLock(&myMessageMap);

	return Mfx_Return_Fine;
}

/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeEvent(FlakeEvent_Info flakeEvent, MfxString recvFuncName)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_RemoveFlakeEvent);
	msgParam.push_back(flakeEvent);
	msgParam.push_back(recvFuncName);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::PushBackFlakeEvent(FlakeEvent_Info flakeEvent, Flake_RecvFunc_Infor recvInfo)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_PushBackFlakeEvent);
	msgParam.push_back(flakeEvent);
	msgParam.push_back(recvInfo);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::PushFrontFlakeEvent(FlakeEvent_Info flakeEvent, Flake_RecvFunc_Infor recvInfo)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_PushFrontFlakeEvent);
	msgParam.push_back(flakeEvent);
	msgParam.push_back(recvInfo);
	return Send_Message(msgParam);
}
/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::OpenPercentRect()
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_OpenPercentRect);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::ClosePercentRect()
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_ClosePercentRect);
	return Send_Message(msgParam);
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

MfxReturn MicroFlakeX::MfxFlake::GetUI(pMfxUI* ret)
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
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetFloor);
	return Send_Message(msgParam);
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
	myMemberLock.WaitLock(&myTitleColor);

	*ret = myTitleColor;

	myMemberLock.UnLock(&myTitleColor);

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
	MfxParam msgParam1;
	msgParam1.push_back(FLAKE_MSG_Rect);
	msgParam1.push_back(MfxRect(set));
	Send_Message(msgParam1);

	if (myUI)
	{
		MfxParam msgParam2;
		msgParam1.push_back(FLAKE_MSG_ResetPercentRect);
		Send_Message(msgParam1);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetSize(MfxSize* set)
{
	myMemberLock.WaitLock(&myRect);
	MfxRect tRect = myRect;
	myMemberLock.UnLock(&myRect);

	tRect.SetSize(set);
	MfxParam msgParam1;
	msgParam1.push_back(FLAKE_MSG_Rect);
	msgParam1.push_back(tRect);
	Send_Message(msgParam1);

	if (myUI)
	{
		MfxParam msgParam2;
		msgParam1.push_back(FLAKE_MSG_ResetPercentRect);
		Send_Message(msgParam1);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetPoint(MfxPoint* set)
{
	myMemberLock.WaitLock(&myRect);
	MfxRect tRect = myRect;
	myMemberLock.UnLock(&myRect);

	tRect.SetPoint(set);
	MfxParam msgParam1;
	msgParam1.push_back(FLAKE_MSG_Rect);
	msgParam1.push_back(tRect);
	Send_Message(msgParam1);

	if (myUI)
	{
		MfxParam msgParam2;
		msgParam1.push_back(FLAKE_MSG_ResetPercentRect);
		Send_Message(msgParam1);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetEdgeRect(MfxRect* set)
{
	myMemberLock.WaitLock(&myEdgeRect);
	myEdgeRect = set;
	myMemberLock.UnLock(&myEdgeRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::SetTitle(MfxString set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetTitle);
	msgParam.push_back(set);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleSize(DOUBLE set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetTitleSize);
	msgParam.push_back(set);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackColor(MfxColor* set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetBackColor);
	msgParam.push_back(MfxColor(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskColor(MfxColor* set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetMaskColor);
	msgParam.push_back(MfxColor(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleColor(MfxColor* set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetTitleColor);
	msgParam.push_back(MfxColor(set));
	return Send_Message(msgParam);
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
	myMemberLock.WaitLock(&myWords);
	auto tRet = myWords ? myWords->Clone(ret) : Mfx_Return_Fail;
	myMemberLock.UnLock(&myWords);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::GetBackImage(MfxImage** ret)
{
	myMemberLock.WaitLock(&myBackImage);
	auto tRet = myBackImage ? myBackImage->Clone(ret) : Mfx_Return_Fail;
	myMemberLock.UnLock(&myBackImage);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskImage(MfxImage** ret)
{
	myMemberLock.WaitLock(&myMaskImage);
	auto tRet = myMaskImage ? myMaskImage->Clone(ret) : Mfx_Return_Fail;
	myMemberLock.UnLock(&myMaskImage);

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
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetWords);
	msgParam.push_back(MfxWords(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackImage(MfxImage* set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetBackImage);
	msgParam.push_back(MfxImage(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskImage(MfxImage* set)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_SetMaskImage);
	msgParam.push_back(MfxImage(set));
	return Send_Message(msgParam);
}



MfxReturn MicroFlakeX::MfxFlake::__OnTest001(MfxParam param)
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
MfxReturn MicroFlakeX::MfxFlake::__OnSetPaper(MfxParam param)
{
	Paper_Infor t_PaperValue = GetParam_Safe(param, Paper_Infor, 1);

	myMemberLock.TryWaitLock(&myUI, &myWnd, &myCanvas);

	myUI = t_PaperValue.myUI;
	myWnd = t_PaperValue.myWnd;
	myCanvas = t_PaperValue.myCanvas;

	myMemberLock.UnLock(&myUI, &myWnd);

	myMemberLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myBackImage);
	
	myMemberLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myMaskImage);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myWords);

	myMemberLock.UnLock(&myCanvas);

	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_ResetPercentRect);
	Send_Message(msgParam);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRemovePaper(MfxParam param)
{
	myMemberLock.TryWaitLock(&myUI, &myWnd, &myCanvas);

	myUI = NULL;
	myWnd = NULL;
	myCanvas = NULL;

	myMemberLock.UnLock(&myUI, &myWnd);

	myMemberLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myBackImage);

	myMemberLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myMaskImage);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myWords);

	myMemberLock.UnLock(&myCanvas);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetFloor(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back(UI_MSG_FlakeFloorChange);

	myMemberLock.TryWaitLock(&myFloor, &myUI);

	myFloor = GetParam_Safe(param, MfxFloor, 1);
	myUI ? myUI->Send_Message(msgParam) : 0;

	myMemberLock.UnLock(&myFloor, &myUI);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnPaintBackDC(MfxParam param)
{
	myMemberLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->Paint() : 0;
	myMemberLock.UnLock(&myBackImage);

	myMemberLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->Paint() : 0;
	myMemberLock.UnLock(&myMaskImage);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->Paint() : 0;
	myMemberLock.UnLock(&myWords);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPaintMaskDC(MfxParam param)
{
	return Mfx_Return_Fail;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnUISize(MfxParam param)
{
	bool tChick = false;

	myMemberLock.WaitLock(&myUI);
	myUI ? myUI->ChickPercentRect(&tChick) : 0;
	myMemberLock.UnLock(&myUI);

	if (myPercentRectFlag || tChick)
	{
		MfxParam msgParam;
		msgParam.push_back(FLAKE_MSG_ResetRect);
		Send_Message(msgParam);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRect(MfxParam param)
{
	MfxRect tSetRect = GetParam_Safe(param, MfxRect, 1);

	myMemberLock.TryWaitLock(&myEdgeRect);
	MfxRect tEdgeRect = myEdgeRect;
	myMemberLock.UnLock(&myEdgeRect);

	bool isIn = false;
	tEdgeRect.IsEmpty(&isIn);

	if (!isIn)
	{
		tEdgeRect.IsRectInside(&tSetRect, &isIn);
		if (!isIn)
		{
			tSetRect.Intersect(&tEdgeRect, &tSetRect);
		}
	}

	myMemberLock.WaitLock(&myBackImage);
	myBackImage ? myBackImage->SetRect(&tSetRect) : 0;
	myMemberLock.UnLock(&myBackImage);

	myMemberLock.WaitLock(&myMaskImage);
	myMaskImage ? myMaskImage->SetRect(&tSetRect) : 0;
	myMemberLock.UnLock(&myMaskImage);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->SetRect(&tSetRect) : 0;
	myMemberLock.UnLock(&myWords);


	myMemberLock.TryWaitLock(&myUI, &myRect);

	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myRect.SetRect(&tSetRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;

	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPercentRect(MfxParam param)
{
	MfxRect tSetPercentRect = GetParam_Safe(param, MfxRect, 1);

	myMemberLock.WaitLock(&myPercentRect);
	myPercentRect.SetRect(&tSetPercentRect);
	myMemberLock.UnLock(&myPercentRect);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnResetRect(MfxParam param)
{
	MfxSize t_UISize;
	myMemberLock.WaitLock(&myUI);

	if (!myUI)
	{
		return Mfx_Return_Fail;
	}
	myUI->GetSize(&t_UISize);

	myMemberLock.UnLock(&myUI);

	myMemberLock.WaitLock(&myPercentRect);
	MfxRect t_RestRect(
		(myPercentRect.myX * t_UISize.myWidth) / 100000,
		(myPercentRect.myY * t_UISize.myHeight) / 100000,
		(myPercentRect.myWidth * t_UISize.myWidth) / 100000,
		(myPercentRect.myHeight * t_UISize.myHeight) / 100000
	);
	myMemberLock.UnLock(&myPercentRect);


	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_Rect);
	msgParam.push_back(t_RestRect);
	Send_Message(msgParam);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnResetPercentRect(MfxParam param)
{
	MfxSize t_UISize;
	myMemberLock.WaitLock(&myUI);

	if (!myUI)
	{
		return Mfx_Return_Fail;
	}
	myUI->GetSize(&t_UISize);

	myMemberLock.UnLock(&myUI);

	myMemberLock.WaitLock(&myRect);
	MfxRect t_ResetPercentRect(
		(myRect.myX * 100000.00) / t_UISize.myWidth,
		(myRect.myY * 100000.00) / t_UISize.myHeight,
		(myRect.myWidth * 100000.00) / t_UISize.myWidth,
		(myRect.myHeight * 100000.00) / t_UISize.myHeight
	);
	myMemberLock.UnLock(&myRect);

	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_PercentRect);
	msgParam.push_back(t_ResetPercentRect);
	Send_Message(msgParam);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnOpenPercentRect(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back(FLAKE_MSG_ResetPercentRect);

	if (Mfx_Seccess(ProcMessage(msgParam)))
	{
		myPercentRectFlag = true;

		return Mfx_Return_Fine;
	}
	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxFlake::__OnClosePercentRect(MfxParam param)
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
MfxReturn MicroFlakeX::MfxFlake::__OnNCMouseMove(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_MOUSEMOVE);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCMouseHover(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_MOUSEHOVER);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonUp(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_LBUTTONUP);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonDown(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_LBUTTONDOWN);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonDouble(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_LBUTTONDBLCLK);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonUp(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_RBUTTONUP);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonDown(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_RBUTTONDOWN);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonDouble(MfxParam param)
{
	MfxParam msgParam;
	msgParam.push_back((MfxMessage)WM_RBUTTONDBLCLK);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnMouseMove(MfxParam param)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

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
			myMemberLock.WaitLock(&myButtonMoveBegin);

			t_Rect.Offset(mousePos.myX - myButtonMoveBegin.myX, mousePos.myY - myButtonMoveBegin.myY);
			MfxPoint t_Point(t_Rect.myX, t_Rect.myY);
			SetPoint(&t_Point);
			myButtonMoveBegin = mousePos;

			myMemberLock.UnLock(&myButtonMoveBegin);
		}
	}
	else
	{
		myUI ? myUI->UnLockMutexFocus() : 0;
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnMouseHover(MfxParam param)
{
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonUp(MfxParam param)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

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
				MfxParam msgParam;
				msgParam.push_back(MSG_FlakeEvent);
				msgParam.push_back(FlakeEvent_Info(this, FLAKE_MSG_LButtonClick));
				myUI ? myUI->Send_Message(msgParam) : 0;
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

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonDown(MfxParam param)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

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

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonDouble(MfxParam param)
{
	return MfxReturn();
}


MfxReturn MicroFlakeX::MfxFlake::__OnRButtonUp(MfxParam param)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

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
				MfxParam msgParam;
				msgParam.push_back(MSG_FlakeEvent);
				msgParam.push_back(FlakeEvent_Info(this, FLAKE_MSG_RButtonClick));
				myUI ? myUI->Send_Message(msgParam) : 0;
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

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonDown(MfxParam param)
{
	MfxPoint mousePos;

	myUI ? myUI->GetLocalMousePos(&mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

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

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonDouble(MfxParam param)
{
	return MfxReturn();
}



/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetTitle(MfxParam param)
{
	myMemberLock.TryWaitLock(&myTitle, &myWords);

	myTitle = GetParam_Safe(param, MfxString, 1);

	myWords ? myWords->SetText(myTitle) : 0;

	myMemberLock.UnLock(&myTitle, &myWords);


	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackColor(MfxParam param)
{
	myMemberLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMemberLock.UnLock(&myRect);

	myMemberLock.TryWaitLock(&myBackImage, &myBackColor, &myCanvas);
	myBackColor = GetParam_Safe(param, MfxColor, 1);
	if (myBackImage)
	{
		myBackImage->FromColor(&myBackColor, &tSize);
	}
	else
	{
		myBackImage = new MfxImage(&myBackColor, &tSize);
		myBackImage->SetCanvas(myCanvas);
	}
	myMemberLock.UnLock(&myBackImage, &myBackColor, &myCanvas);


	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskColor(MfxParam param)
{
	myMemberLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMemberLock.UnLock(&myRect);

	myMemberLock.TryWaitLock(&myMaskImage, &myMaskColor, &myCanvas);
	myMaskColor = GetParam_Safe(param, MfxColor, 1);
	if (myMaskImage)
	{
		myMaskImage->FromColor(&myMaskColor, &tSize);
	}
	else
	{
		myMaskImage = new MfxImage(&myMaskColor, &tSize);
		myMaskImage->SetCanvas(myCanvas);
	}
	myMemberLock.UnLock(&myMaskImage, &myMaskColor, &myCanvas);


	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetTitleColor(MfxParam param)
{
	myMemberLock.TryWaitLock(&myWords, &myTitleColor, &myCanvas);
	myTitleColor = GetParam_Safe(param, MfxColor, 1);
	if (myWords)
	{
		myWords->SetTextColor(&myTitleColor);
	}
	myMemberLock.UnLock(&myWords, &myTitleColor, &myCanvas);


	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnSetWords(MfxParam param)
{
	myMemberLock.TryWaitLock(&myBackImage, &myRect, &myCanvas);

	SafeDelete(myWords);
	GetParam_Safe(param, MfxWords, 1).Clone(&myWords);
	myWords->SetRect(&myRect);
	myWords->SetCanvas(myCanvas);

	myMemberLock.UnLock(&myBackImage, &myRect, &myCanvas);



	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackImage(MfxParam param)
{
	myMemberLock.TryWaitLock(&myBackImage, &myRect, &myCanvas);

	SafeDelete(myBackImage);
	GetParam_Safe(param, MfxImage, 1).Clone(&myBackImage);
	myBackImage->SetRect(&myRect);
	myBackImage->SetCanvas(myCanvas);

	myMemberLock.UnLock(&myBackImage, &myRect, &myCanvas);


	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskImage(MfxParam param)
{
	myMemberLock.TryWaitLock(&myMaskImage, &myRect, &myCanvas);

	SafeDelete(myMaskImage);
	GetParam_Safe(param, MfxImage, 1).Clone(&myMaskImage);
	myMaskImage->SetRect(&myRect);
	myMaskImage->SetCanvas(myCanvas);

	myMemberLock.UnLock(&myMaskImage, &myRect, &myCanvas);


	myMemberLock.TryWaitLock(&myUI, &myRect);
	myUI ? myUI->UnionInvalidateRect(&myRect) : 0;
	myMemberLock.UnLock(&myUI, &myRect);

	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxFlake::__OnFlakeEvent(MfxParam param)
{
	MfxReturn tRet = Mfx_Return_Fail;

	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tInfo = GetParam_Safe(param, FlakeEvent_Info, 1);

	auto t_Iter = myFlakeEventMap.find(tInfo);
	if (t_Iter != myFlakeEventMap.end())
	{
		if (!t_Iter->second.empty())
		{
			for (auto i : (t_Iter->second))
			{
				tRet = (this->*i.recvFunc)(param);
			}
		}
	}

	myMemberLock.UnLock(&myFlakeEventMap);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRemoveFlakeEvent(MfxParam param)
{
	MfxReturn tRet = Mfx_Return_Fail;

	FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 1);
	MfxString tRecvFuncName = GetParam_Safe(param, MfxString, 2);

	myMemberLock.WaitLock(&myFlakeEventMap);

	auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
	if (t_Iter != myFlakeEventMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i).myRecvFuncName == tRecvFuncName)
			{
				t_Iter->second.erase(i);
				tRet = Mfx_Return_Fine;
				break;
			}
		}
	}

	myMemberLock.UnLock(&myFlakeEventMap);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPushBackFlakeEvent(MfxParam param)
{
	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 1);
	Flake_RecvFunc_Infor tRecvInfo = GetParam_Safe(param, Flake_RecvFunc_Infor, 2);

Begin:
	auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
	if (t_Iter == myFlakeEventMap.end())
	{
		t_Iter = myFlakeEventMap.insert(Flake_FlakeEvent_Map_Elem(tFlakeEvent, Flake_RecvFunc_Infor_Deque())).first;
		goto Begin;
	}
	else
	{
		t_Iter->second.push_back(tRecvInfo);
	}

	myMemberLock.UnLock(&myFlakeEventMap);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPushFrontFlakeEvent(MfxParam param)
{
	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 1);
	Flake_RecvFunc_Infor tRecvInfo = GetParam_Safe(param, Flake_RecvFunc_Infor, 2);

Begin:
	auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
	if (t_Iter == myFlakeEventMap.end())
	{
		t_Iter = myFlakeEventMap.insert(Flake_FlakeEvent_Map_Elem(tFlakeEvent, Flake_RecvFunc_Infor_Deque())).first;
		goto Begin;
	}
	else
	{
		t_Iter->second.push_front(tRecvInfo);
	}

	myMemberLock.UnLock(&myFlakeEventMap);

	return Mfx_Return_Fine;
}