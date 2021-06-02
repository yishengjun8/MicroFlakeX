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
	1, GetFather, \
	1, GetWnd, \
	1, GetFloor, \
	1, GetCanvas, \
	\
	1, SetFloor, \
	\
	1, GetRect, \
	1, GetSize, \
	1, GetPoint, \
	1, GetEdgeRect, \
	\
	1, GetTitle, \
	1, GetTitleSize, \
	\
	1, GetWords, \
	1, GetBackColor, \
	1, GetMaskColor, \
	1, GetTitleColor, \
	1, GetBackFrameSize, \
	1, GetMaskFrameSize, \
	\
	1, SetRect, \
	1, SetSize, \
	1, SetPoint, \
	1, SetEdgeRect, \
	\
	1, SetTitle, \
	1, SetTitleSize, \
	\
	1, SetWords, \
	1, SetBackColor, \
	1, SetMaskColor, \
	1, SetTitleColor, \
	1, SetBackFrameSize, \
	1, SetMaskFrameSize, \
	\
	0, OpenLButtonMove, \
	0, CloseLButtonMove, \
	0, OpenRButtonMove, \
	0, CloseRButtonMove \
);

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

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetBackFrameSize, MfxFlake, __OnSetBackFrameSize);
	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetMaskFrameSize, MfxFlake, __OnSetMaskFrameSize);

	FLAKE_ADDRECV_FLAKEMSG(FLAKE_MSG_SetWords, MfxFlake, __OnSetWords);

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

	myFather = nullptr;
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

	myBackFrameSize = 2;
	myMaskFrameSize = 2;

	myBackRectangle.SetFillColor(&myBackColor);
	myMaskRectangle.SetFillColor(&myMaskColor);

	myBackRectangle.SetFrameSize(myBackFrameSize);
	myMaskRectangle.SetFrameSize(myMaskFrameSize);

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
	MfxParam msgParam(MSG_FlakeRemove);
	msgParam.push_back((pMfxFlake)this);

	myMemberLock.WaitLock(&myFather);
	myFather ? myFather->AutoFunc(MfxText("Send_Message"), msgParam) : 0;
	myMemberLock.UnLock(&myFather);

	myMemberLock.TryWaitLock(&myWords);
	SafeDelete(myWords);
	myMemberLock.UnLock(&myWords);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::ProcMessage(MfxParam param)
{
	MfxReturn t_Ret = Mfx_Return_Fail;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(GetMSG(param));
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
	MfxParam msgParam(FLAKE_MSG_RemoveFlakeEvent);
	msgParam.push_back(flakeEvent);
	msgParam.push_back(recvFuncName);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::PushBackFlakeEvent(FlakeEvent_Info flakeEvent, Flake_RecvFunc_Infor recvInfo)
{
	MfxParam msgParam(FLAKE_MSG_PushBackFlakeEvent);
	msgParam.push_back(flakeEvent);
	msgParam.push_back(recvInfo);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::PushFrontFlakeEvent(FlakeEvent_Info flakeEvent, Flake_RecvFunc_Infor recvInfo)
{
	MfxParam msgParam(FLAKE_MSG_PushFrontFlakeEvent);
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
	MfxParam msgParam(FLAKE_MSG_OpenPercentRect);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::ClosePercentRect()
{
	MfxParam msgParam(FLAKE_MSG_ClosePercentRect);
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

MfxReturn MicroFlakeX::MfxFlake::GetFather(pMfxBase* ret)
{
	*ret = myFather;
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
	MfxParam msgParam(FLAKE_MSG_SetFloor);
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

MfxReturn MicroFlakeX::MfxFlake::GetBackFrameSize(double* ret)
{
	*ret = myBackFrameSize;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskFrameSize(double* ret)
{
	*ret = myMaskFrameSize;
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
	MfxParam msgParam1(FLAKE_MSG_Rect);
	msgParam1.push_back(MfxRect(set));
	Send_Message(msgParam1);

	if (myFather)
	{
		MfxParam msgParam2(FLAKE_MSG_ResetPercentRect);
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
	MfxParam msgParam1(FLAKE_MSG_Rect);
	msgParam1.push_back(tRect);
	Send_Message(msgParam1);

	if (myFather)
	{
		MfxParam msgParam2(FLAKE_MSG_ResetPercentRect);
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
	MfxParam msgParam1(FLAKE_MSG_Rect);
	msgParam1.push_back(tRect);
	Send_Message(msgParam1);

	if (myFather)
	{
		MfxParam msgParam2(FLAKE_MSG_ResetPercentRect);
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
	MfxParam msgParam(FLAKE_MSG_SetTitle);
	msgParam.push_back(set);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleSize(DOUBLE set)
{
	MfxParam msgParam(FLAKE_MSG_SetTitleSize);
	msgParam.push_back(set);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackColor(MfxColor* set)
{
	MfxParam msgParam(FLAKE_MSG_SetBackColor);
	msgParam.push_back(MfxColor(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskColor(MfxColor* set)
{
	MfxParam msgParam(FLAKE_MSG_SetMaskColor);
	msgParam.push_back(MfxColor(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleColor(MfxColor* set)
{
	MfxParam msgParam(FLAKE_MSG_SetTitleColor);
	msgParam.push_back(MfxColor(set));
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackFrameSize(double set)
{
	MfxParam msgParam(FLAKE_MSG_SetBackFrameSize);
	msgParam.push_back(set);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskFrameSize(double set)
{
	MfxParam msgParam(FLAKE_MSG_SetMaskFrameSize);
	msgParam.push_back(set);
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


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::SetWords(MfxWords* set)
{
	MfxParam msgParam(FLAKE_MSG_SetWords);
	msgParam.push_back(MfxWords(set));
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
	Paper_Infor t_PaperValue = GetParam_Safe(param, Paper_Infor, 0);

	myMemberLock.TryWaitLock(&myFather, &myWnd, &myCanvas);

	MfxParam msgParam1(MSG_FlakeRemove);
	msgParam1.push_back((pMfxFlake)this);
	myFather ? myFather->AutoFunc(MfxText("Send_Message"), msgParam1) : 0;

	myFather = t_PaperValue.myFather;
	myWnd = t_PaperValue.myWnd;
	myCanvas = t_PaperValue.myCanvas;

	myMemberLock.UnLock(&myFather, &myWnd);

	myMemberLock.WaitLock(&myBackRectangle);
	myBackRectangle.SetCanvas(myCanvas);
	myMemberLock.UnLock(&myBackRectangle);
	
	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.SetCanvas(myCanvas);
	myMemberLock.UnLock(&myMaskRectangle);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myWords);

	myMemberLock.UnLock(&myCanvas);

	MfxParam msgParam2(FLAKE_MSG_ResetPercentRect);
	Send_Message(msgParam2);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRemovePaper(MfxParam param)
{
	myMemberLock.TryWaitLock(&myFather, &myWnd, &myCanvas);

	MfxParam msgParam1(MSG_FlakeRemove);
	msgParam1.push_back((pMfxFlake)this);
	myFather ? myFather->AutoFunc(MfxText("Send_Message"), msgParam1) : 0;

	myFather = NULL;
	myWnd = NULL;
	myCanvas = NULL;

	myMemberLock.UnLock(&myFather, &myWnd);

	myMemberLock.WaitLock(&myBackRectangle);
	myBackRectangle.SetCanvas(myCanvas);
	myMemberLock.UnLock(&myBackRectangle);

	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.SetCanvas(myCanvas);
	myMemberLock.UnLock(&myMaskRectangle);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->SetCanvas(myCanvas) : 0;
	myMemberLock.UnLock(&myWords);

	myMemberLock.UnLock(&myCanvas);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetFloor(MfxParam param)
{
	MfxParam msgParam(MSG_FlakeFloorChange);

	myMemberLock.TryWaitLock(&myFloor, &myFather);

	myFloor = GetParam_Safe(param, MfxFloor, 0);
	myFather ? myFather->AutoFunc(MfxText("Send_Message"), msgParam) : 0;

	myMemberLock.UnLock(&myFloor, &myFather);

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
	myMemberLock.WaitLock(&myBackRectangle);
	myBackRectangle.Paint();
	myMemberLock.UnLock(&myBackRectangle);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->Paint() : 0;
	myMemberLock.UnLock(&myWords);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPaintMaskDC(MfxParam param)
{
	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.Paint();
	myMemberLock.UnLock(&myMaskRectangle);

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

	myMemberLock.WaitLock(&myFather);
	myFather ? myFather->AutoFunc(MfxText("ChickPercentRect"), &tChick) : 0;
	myMemberLock.UnLock(&myFather);

	if (myPercentRectFlag || tChick)
	{
		MfxParam msgParam(FLAKE_MSG_ResetRect);
		Send_Message(msgParam);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRect(MfxParam param)
{
	MfxRect tSetRect = GetParam_Safe(param, MfxRect, 0);

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

	myMemberLock.WaitLock(&myBackRectangle);
	myBackRectangle.SetRect(&tSetRect);
	myMemberLock.UnLock(&myBackRectangle);

	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.SetRect(&tSetRect);
	myMemberLock.UnLock(&myMaskRectangle);

	myMemberLock.WaitLock(&myWords);
	myWords ? myWords->SetRect(&tSetRect) : 0;
	myMemberLock.UnLock(&myWords);


	myMemberLock.TryWaitLock(&myFather, &myRect);

	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect, max(myBackFrameSize, myMaskFrameSize)) : 0;
	myRect.SetRect(&tSetRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect, max(myBackFrameSize, myMaskFrameSize)) : 0;

	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPercentRect(MfxParam param)
{
	MfxRect tSetPercentRect = GetParam_Safe(param, MfxRect, 0);

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
	myMemberLock.WaitLock(&myFather);

	if (!myFather)
	{
		return Mfx_Return_Fail;
	}
	myFather->AutoFunc(MfxText("GetSize"), &t_UISize);

	myMemberLock.UnLock(&myFather);

	myMemberLock.WaitLock(&myPercentRect);
	MfxRect t_RestRect(
		(myPercentRect.myX * t_UISize.myWidth) / 100000,
		(myPercentRect.myY * t_UISize.myHeight) / 100000,
		(myPercentRect.myWidth * t_UISize.myWidth) / 100000,
		(myPercentRect.myHeight * t_UISize.myHeight) / 100000
	);
	myMemberLock.UnLock(&myPercentRect);


	MfxParam msgParam(FLAKE_MSG_Rect);
	msgParam.push_back(t_RestRect);
	Send_Message(msgParam);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnResetPercentRect(MfxParam param)
{
	MfxSize t_UISize;
	myMemberLock.WaitLock(&myFather);

	if (!myFather)
	{
		return Mfx_Return_Fail;
	}
	myFather->AutoFunc(MfxText("GetSize"), &t_UISize);

	myMemberLock.UnLock(&myFather);

	myMemberLock.WaitLock(&myRect);
	MfxRect t_ResetPercentRect(
		(myRect.myX * 100000.00) / t_UISize.myWidth,
		(myRect.myY * 100000.00) / t_UISize.myHeight,
		(myRect.myWidth * 100000.00) / t_UISize.myWidth,
		(myRect.myHeight * 100000.00) / t_UISize.myHeight
	);
	myMemberLock.UnLock(&myRect);

	MfxParam msgParam(FLAKE_MSG_PercentRect);
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
	MfxParam msgParam(FLAKE_MSG_ResetPercentRect);

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
	MfxParam msgParam(WM_MOUSEMOVE);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCMouseHover(MfxParam param)
{
	MfxParam msgParam(WM_MOUSEHOVER);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonUp(MfxParam param)
{
	MfxParam msgParam(WM_LBUTTONUP);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonDown(MfxParam param)
{
	MfxParam msgParam(WM_LBUTTONDOWN);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCLButtonDouble(MfxParam param)
{
	MfxParam msgParam(WM_LBUTTONDBLCLK);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonUp(MfxParam param)
{
	MfxParam msgParam(WM_RBUTTONUP);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonDown(MfxParam param)
{
	MfxParam msgParam(WM_RBUTTONDOWN);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::__OnNCRButtonDouble(MfxParam param)
{
	MfxParam msgParam(WM_RBUTTONDBLCLK);
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

	myFather ? myFather->AutoFunc(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;

		myFather ? myFather->AutoFunc(MfxText("SetMutexFocus"), this) : 0;
		myFather ? myFather->AutoFunc(MfxText("GetMutexFocus"), &t_Conctrol) : 0;

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
		if (Mfx_Seccess(myFather ? myFather->AutoFunc(MfxText("LockMutexFocus"), this) : Mfx_Return_Fail))
		{
			myMemberLock.WaitLock(&myButtonMoveBegin);

			t_Rect.Offset(mousePos.myX - myButtonMoveBegin.myX, mousePos.myY - myButtonMoveBegin.myY);
			MfxPoint t_Point(t_Rect.myX, t_Rect.myY);
			SetPoint(&t_Point);
			myButtonMoveBegin = mousePos;

			myMemberLock.UnLock(&myButtonMoveBegin);

			MfxParam msgParam(MSG_FlakeEvent);
			msgParam.push_back(FlakeEvent_Info(this, FLAKE_EVENT_MouseMove));
			msgParam.push_back(t_Point);
			myFather ? myFather->AutoFunc(MfxText("Post_Message"), msgParam) : 0;
		}
	}
	else
	{
		myFather ? myFather->AutoFunc(MfxText("UnLockMutexFocus")) : 0;
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

	myFather ? myFather->AutoFunc(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myFather->AutoFunc(MfxText("SetMutexFocus"), this);
		myFather->AutoFunc(MfxText("GetMutexFocus"), &t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			if (myLButtonClickFlag) //点击成功
			{
				myMouseFloat = true;
				myLButtonPress = false;
				myLButtonClickFlag = false;
				MfxParam msgParam(MSG_FlakeEvent);
				msgParam.push_back(FlakeEvent_Info(this, FLAKE_EVENT_LButtonClick));
				myFather ? myFather->AutoFunc(MfxText("Post_Message"), msgParam) : 0;
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

	myFather ? myFather->AutoFunc(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myFather->AutoFunc(MfxText("SetMutexFocus"), this);
		myFather->AutoFunc(MfxText("GetMutexFocus"), &t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;
			myFather->AutoFunc(MfxText("SetKeyboardFocus"), this); //设置键盘焦点
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
	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxFlake::__OnRButtonUp(MfxParam param)
{
	MfxPoint mousePos;

	myFather ? myFather->AutoFunc(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myFather->AutoFunc(MfxText("SetMutexFocus"), this);
		myFather->AutoFunc(MfxText("GetMutexFocus"), &t_Conctrol);

		if (t_Conctrol == this) //获取互斥焦点成功
		{
			if (myRButtonClickFlag) //点击成功
			{
				myMouseFloat = true;
				myRButtonPress = false;
				myRButtonClickFlag = false;
				MfxParam msgParam(MSG_FlakeEvent);
				msgParam.push_back(FlakeEvent_Info(this, FLAKE_EVENT_RButtonClick));
				myFather ? myFather->AutoFunc(MfxText("Post_Message"), msgParam) : 0;
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

	myFather ? myFather->AutoFunc(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myFather->AutoFunc(MfxText("SetMutexFocus"), this);
		myFather->AutoFunc(MfxText("GetMutexFocus"), &t_Conctrol);

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

	myTitle = GetParam_Safe(param, MfxString, 0);

	myWords ? myWords->SetText(myTitle) : 0;

	myMemberLock.UnLock(&myTitle, &myWords);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackColor(MfxParam param)
{
	myMemberLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMemberLock.UnLock(&myRect);

	myMemberLock.TryWaitLock(&myBackRectangle, &myBackColor, &myCanvas);

	myBackColor = GetParam_Safe(param, MfxColor, 0);
	myBackRectangle.SetFillColor(&myBackColor);

	myMemberLock.UnLock(&myBackRectangle, &myBackColor, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect, myBackFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskColor(MfxParam param)
{
	myMemberLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMemberLock.UnLock(&myRect);

	myMemberLock.TryWaitLock(&myMaskRectangle, &myMaskColor, &myCanvas);

	myMaskColor = GetParam_Safe(param, MfxColor, 0);
	myMaskRectangle.SetFillColor(&myMaskColor);

	myMemberLock.UnLock(&myMaskRectangle, &myBackColor, &myCanvas);

	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect, myMaskFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetTitleColor(MfxParam param)
{
	myMemberLock.TryWaitLock(&myWords, &myTitleColor, &myCanvas);
	myTitleColor = GetParam_Safe(param, MfxColor, 0);
	if (myWords)
	{
		myWords->SetTextColor(&myTitleColor);
	}
	myMemberLock.UnLock(&myWords, &myTitleColor, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackFrameSize(MfxParam param)
{
	myMemberLock.TryWaitLock(&myBackFrameSize, &myBackRectangle, &myCanvas);

	myBackFrameSize = GetParam_Safe(param, double, 0);
	myBackRectangle.SetFrameSize(myBackFrameSize);

	myMemberLock.UnLock(&myBackFrameSize, &myBackRectangle, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect, myBackFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskFrameSize(MfxParam param)
{
	myMemberLock.TryWaitLock(&myMaskFrameSize, &myMaskRectangle, &myCanvas);

	myMaskFrameSize = GetParam_Safe(param, double, 0);
	myMaskRectangle.SetFrameSize(myMaskFrameSize);

	myMemberLock.UnLock(&myMaskFrameSize, &myMaskRectangle, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect, myMaskFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

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
	myMemberLock.TryWaitLock(&myWords, &myRect, &myCanvas);

	SafeDelete(myWords);
	GetParam_Safe(param, MfxWords, 0).Clone(&myWords);
	myWords->SetRect(&myRect);
	myWords->SetCanvas(myCanvas);

	myMemberLock.UnLock(&myWords, &myRect, &myCanvas);

	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->AutoFunc(MfxText("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnFlakeEvent(MfxParam param)
{
	MfxReturn tRet = Mfx_Return_Fail;

	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tInfo = GetParam_Safe(param, FlakeEvent_Info, 0);

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

	FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 0);
	MfxString tRecvFuncName = GetParam_Safe(param, MfxString, 1);

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

	FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 0);
	Flake_RecvFunc_Infor tRecvInfo = GetParam_Safe(param, Flake_RecvFunc_Infor, 1);

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

	FlakeEvent_Info tFlakeEvent = GetParam_Safe(param, FlakeEvent_Info, 0);
	Flake_RecvFunc_Infor tRecvInfo = GetParam_Safe(param, Flake_RecvFunc_Infor, 1);

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