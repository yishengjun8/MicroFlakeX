#include "pch.h"
#include "MfxAppFrame.h"


MFXOBJ_REFLECTION_INIT(MfxFlake)
MFXOBJ_REFLECTION_ENDINIT(MfxFlake, MfxBase, \
	Send_Message, \
	Post_Message, \
	\
	RemoveFlakeEvent, \
	PushBackFlakeEvent, \
	PushFrontFlakeEvent, \
	\
	OpenPercentRect, \
	ClosePercentRect, \
	ChickPercentRect, \
	\
	GetFather, \
	GetWnd, \
	GetFloor, \
	GetCanvas, \
	\
	SetFloor, \
	\
	GetRect, \
	GetSize, \
	GetPoint, \
	GetEdgeRect, \
	\
	GetTitle, \
	GetTitleSize, \
	\
	GetBackColor, \
	GetMaskColor, \
	GetTitleColor, \
	GetBackFrameSize, \
	GetMaskFrameSize, \
	\
	SetRect, \
	SetSize, \
	SetPoint, \
	SetEdgeRect, \
	\
	SetTitle, \
	SetTitleSize, \
	\
	SetBackColor, \
	SetMaskColor, \
	SetTitleColor, \
	SetBackFrameSize, \
	SetMaskFrameSize, \
	\
	OpenLButtonMove, \
	CloseLButtonMove, \
	OpenRButtonMove, \
	CloseRButtonMove \
);


#define FLAKE_RECV(msg, func) FLAKE_ADDRECV_FLAKEMSG(msg, MfxFlake, func)




void MicroFlakeX::MfxFlake::RegisterRecvFunc()
{
	//__MFXOBJ_REFLECTIONFUNC_CASE_EX(, );


#define TestArgs(...) __VA_ARGS__



	//std::cout << GET_ARGS_NUM(TestArgs(2,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,)) << std::endl;

	Mfx_GetFuncArgc(&MfxFlake::CloseRButtonMove);

	FLAKE_RECV(WM_NCMOUSEMOVE, __OnNCMouseMove);
	FLAKE_RECV(WM_NCMOUSEHOVER, __OnNCMouseHover);

	FLAKE_RECV(WM_NCLBUTTONUP, __OnNCLButtonUp);
	FLAKE_RECV(WM_NCLBUTTONDOWN, __OnNCLButtonDown);
	FLAKE_RECV(WM_NCLBUTTONDBLCLK, __OnNCLButtonDouble);

	FLAKE_RECV(WM_NCRBUTTONUP, __OnNCRButtonUp);
	FLAKE_RECV(WM_NCRBUTTONDOWN, __OnNCRButtonDown);
	FLAKE_RECV(WM_NCRBUTTONDBLCLK, __OnNCRButtonDouble);

	/********************************************************************************
	*
	*********************************************************************************/
	FLAKE_RECV(WM_MOUSEMOVE, __OnMouseMove);
	FLAKE_RECV(WM_MOUSEHOVER, __OnMouseHover);

	FLAKE_RECV(WM_LBUTTONUP, __OnLButtonUp);
	FLAKE_RECV(WM_LBUTTONDOWN, __OnLButtonDown);
	FLAKE_RECV(WM_LBUTTONDBLCLK, __OnLButtonDouble);

	FLAKE_RECV(WM_RBUTTONUP, __OnRButtonUp);
	FLAKE_RECV(WM_RBUTTONDOWN, __OnRButtonDown);
	FLAKE_RECV(WM_RBUTTONDBLCLK, __OnRButtonDouble);

	/********************************************************************************
	*
	*
	*********************************************************************************/
	FLAKE_RECV(MSG_FatherSize, __OnFatherSize);

	FLAKE_RECV(FLAKE_MSG_SetPaper, __OnSetPaper);
	FLAKE_RECV(FLAKE_MSG_RemovePaper, __OnRemovePaper);

	FLAKE_RECV(FLAKE_MSG_SetFloor, __OnSetFloor);

	FLAKE_RECV(FLAKE_MSG_PaintBack, __OnPaintBackDC);
	FLAKE_RECV(FLAKE_MSG_PaintMask, __OnPaintMaskDC);

	FLAKE_RECV(FLAKE_MSG_Rect, __OnRect);
	FLAKE_RECV(FLAKE_MSG_PercentRect, __OnPercentRect);

	FLAKE_RECV(FLAKE_MSG_RecalculatRect, __OnRecalculatRect);
	FLAKE_RECV(FLAKE_MSG_RecalculatPercentRect, __OnRecalculatPercentRect);

	FLAKE_RECV(FLAKE_MSG_OpenPercentRect, __OnOpenPercentRect);
	FLAKE_RECV(FLAKE_MSG_ClosePercentRect, __OnClosePercentRect);

	FLAKE_RECV(FLAKE_MSG_SetTitle, __OnSetTitle);
	FLAKE_RECV(FLAKE_MSG_SetBackColor, __OnSetBackColor);
	FLAKE_RECV(FLAKE_MSG_SetMaskColor, __OnSetMaskColor);
	FLAKE_RECV(FLAKE_MSG_SetTitleColor, __OnSetTitleColor);

	FLAKE_RECV(FLAKE_MSG_SetBackFrameSize, __OnSetBackFrameSize);
	FLAKE_RECV(FLAKE_MSG_SetMaskFrameSize, __OnSetMaskFrameSize);

	FLAKE_RECV(MSG_FlakeEvent, __OnFlakeEvent);

	FLAKE_RECV(FLAKE_MSG_RemoveFlakeEvent, __OnRemoveFlakeEvent);
	FLAKE_RECV(FLAKE_MSG_PushBackFlakeEvent, __OnPushBackFlakeEvent);
	FLAKE_RECV(FLAKE_MSG_PushFrontFlakeEvent, __OnPushFrontFlakeEvent);
}

void MicroFlakeX::MfxFlake::InitData_Flake()
{
	/********************************************************************************
	* 
	*********************************************************************************/
	myWnd = NULL;

	myFather = nullptr;
	myCanvas = nullptr;

	myFloor = 66;
	myPercentRectFlag = true;

	myTitle = MfxText("MfxFlake");

	myMouseFloat = false;
	myLButtonClickFlag = false;
	myLButtonPress = false;
	myRButtonClickFlag = false;
	myRButtonPress = false;
	myRButtonMoveFlag = false;
	myLButtonMoveFlag = false;


	//myEdgeRect.Reset(100, 100, 400, 400);

	myBackColor.Reset(255, 255, 0, 0);
	myMaskColor.Reset(0, 255, 0, 0);
	myTitleColor.Reset(255, 255, 0, 0);

	myBackFrameSize = 2;
	myMaskFrameSize = 2;

	myBackRectangle.SetRect(&myRect);
	myMaskRectangle.SetRect(&myRect);

	myBackRectangle.SetFillColor(&myBackColor);
	myMaskRectangle.SetFillColor(&myMaskColor);

	myBackRectangle.SetFrameSize(myBackFrameSize);
	myMaskRectangle.SetFrameSize(myMaskFrameSize);


	myWords.SetRect(&myRect);
	myWords.SetText(myTitle);
	myWords.SetTextColor(&myTitleColor);

	myWords.SetTextAlignmentX(TextAlignmentX::DWRITE_TEXT_ALIGNMENT_CENTER);
	myWords.SetTextAlignmentY(TextAlignmentY::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

MicroFlakeX::MfxFlake::MfxFlake(MfxRect set, MfxBase* father)
{
	myRect = set;
	MfxFlake::InitData_Flake();
	MfxFlake::RegisterRecvFunc();


	MfxParam msgParam(MSG_FlakeInsert);
	msgParam.push_back(this);
	father ? father->Reflection(MfxText("Send_Message"), msgParam) : 0;
}

MicroFlakeX::MfxFlake::~MfxFlake()
{
	MfxParam msgParam(MSG_FlakeRemove);
	msgParam.push_back(this);

	myMemberLock.WaitLock(&myFather);
	myFather ? myFather->Reflection(MfxText("Send_Message"), msgParam) : 0;
	myMemberLock.UnLock(&myFather);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(ProcMessage)
{
	MfxReturn t_Ret = MfxReturn_Failed;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(MFXPARAM_GET_MSG);
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

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(Send_Message)
{
	return ProcMessage(param);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(Post_Message)
{
	return MfxBeginNewThread(this, MfxText("Send_Message"), param);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeMessage(MfxMessage message, MfxString name)
{
	auto tRet = MfxReturn_Failed;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i).myRecvFuncName == name)
			{
				t_Iter->second.erase(i);
				tRet = MfxReturn_Seccess;
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

	return MfxReturn_Seccess;
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

	return MfxReturn_Seccess;
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
	return  myPercentRectFlag ? MfxReturn_Seccess : MfxReturn_Failed;
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
	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetFather(MfxBase** ret)
{
	*ret = myFather;
	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetFloor(MfxFloor* ret)
{
	*ret = myFloor;
	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;
	return MfxReturn_Seccess;
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

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetSize(MfxSize* ret)
{
	*ret = myRect;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetPoint(MfxPoint* ret)
{
	*ret = myRect;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetEdgeRect(MfxRect* ret)
{
	*ret = myEdgeRect;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitle(MfxString* ret)
{
	*ret = myTitle;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleSize(DOUBLE* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::GetBackColor(MfxColor* ret)
{
	*ret = myBackColor;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskColor(MfxColor* ret)
{
	*ret = myMaskColor;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleColor(MfxColor* ret)
{
	myMemberLock.WaitLock(&myTitleColor);
	*ret = myTitleColor;
	myMemberLock.UnLock(&myTitleColor);

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetBackFrameSize(double* ret)
{
	*ret = myBackFrameSize;
	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskFrameSize(double* ret)
{
	*ret = myMaskFrameSize;
	return MfxReturn_Seccess;
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
		MfxParam msgParam(FLAKE_MSG_RecalculatPercentRect);
		Send_Message(msgParam);
	}

	return MfxReturn_Seccess;
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
		MfxParam msgParam(FLAKE_MSG_RecalculatPercentRect);
		Send_Message(msgParam);
	}

	return MfxReturn_Seccess;
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
		MfxParam msgParam(FLAKE_MSG_RecalculatPercentRect);
		Send_Message(msgParam);
	}

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::SetEdgeRect(MfxRect* set)
{
	myMemberLock.WaitLock(&myEdgeRect);
	myEdgeRect = set;
	myMemberLock.UnLock(&myEdgeRect);

	return MfxReturn_Seccess;
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

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::CloseLButtonMove()
{
	myLButtonMoveFlag = false;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::OpenRButtonMove()
{
	myRButtonMoveFlag = true;

	return MfxReturn_Seccess;
}

MfxReturn MicroFlakeX::MfxFlake::CloseRButtonMove()
{
	myRButtonMoveFlag = false;

	return MfxReturn_Seccess;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnTest001)
{
	MessageBox(myWnd, L"__OnTest001", L"__OnTest001", 0);
	return MfxReturn_Seccess;
}

/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetPaper)
{
	Paper_Infor t_PaperValue = MFXPARAM_GET_0(Paper_Infor);

	myMemberLock.TryWaitLock(&myFather, &myWnd, &myCanvas);

	MfxParam msgParam1(MSG_FlakeRemove);
	msgParam1.push_back((MfxFlake*)this);
	myFather ? myFather->Reflection(MfxText("Send_Message"), msgParam1) : 0;

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
	myWords.SetCanvas(myCanvas);
	myMemberLock.UnLock(&myWords);

	myMemberLock.UnLock(&myCanvas);

	if (myFather)
	{
		MfxParam msgParam(FLAKE_MSG_RecalculatPercentRect);
		Send_Message(msgParam);
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRemovePaper)
{
	myMemberLock.TryWaitLock(&myFather, &myWnd, &myCanvas);

	MfxParam msgParam1(MSG_FlakeRemove);
	msgParam1.push_back((MfxFlake*)this);
	myFather ? myFather->Reflection(MfxText("Send_Message"), msgParam1) : 0;

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
	myWords.SetCanvas(myCanvas);
	myMemberLock.UnLock(&myWords);

	myMemberLock.UnLock(&myCanvas);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetFloor)
{
	MfxParam msgParam(MSG_FlakeFloorChange);

	myMemberLock.TryWaitLock(&myFloor, &myFather);

	myFloor = MFXPARAM_GET_0(MfxFloor);
	myFather ? myFather->Reflection(MfxText("Send_Message"), msgParam) : 0;

	myMemberLock.UnLock(&myFloor, &myFather);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPaintBackDC)
{
	myMemberLock.WaitLock(&myBackRectangle);
	myBackRectangle.Paint();
	myMemberLock.UnLock(&myBackRectangle);

	myMemberLock.WaitLock(&myWords);
	myWords.Paint();
	myMemberLock.UnLock(&myWords);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPaintMaskDC)
{
	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.Paint();
	myMemberLock.UnLock(&myMaskRectangle);

	return MfxReturn_Failed;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnFatherSize)
{
	bool tChick = false;

	myMemberLock.WaitLock(&myFather);
	myFather ? myFather->Reflection(MfxText("ChickPercentRect"), &tChick) : 0;
	myMemberLock.UnLock(&myFather);

	if (myPercentRectFlag || tChick)
	{
		MfxParam msgParam(FLAKE_MSG_RecalculatRect);
		Send_Message(msgParam);
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRect)
{
	MfxRect tSetRect = MFXPARAM_GET_0(MfxRect);

	myMemberLock.TryWaitLock(&myEdgeRect);
	MfxRect tEdgeRect = myEdgeRect;
	myMemberLock.UnLock(&myEdgeRect);

	bool isIn = false;
	tEdgeRect.IsEmpty(&isIn);

	if (!isIn)
	{
		tEdgeRect.InsideRect(&tSetRect, &tSetRect);
	}

	myMemberLock.WaitLock(&myBackRectangle);
	myBackRectangle.SetRect(&tSetRect);
	myMemberLock.UnLock(&myBackRectangle);

	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.SetRect(&tSetRect);
	myMemberLock.UnLock(&myMaskRectangle);

	myMemberLock.WaitLock(&myWords);
	myWords.SetRect(&tSetRect);
	myMemberLock.UnLock(&myWords);


	myMemberLock.TryWaitLock(&myFather, &myRect);

	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect, max(myBackFrameSize, myMaskFrameSize)) : 0;
	myRect.SetRect(&tSetRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect, max(myBackFrameSize, myMaskFrameSize)) : 0;

	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPercentRect)
{
	MfxRect tSetPercentRect = MFXPARAM_GET_0(MfxRect);

	myMemberLock.WaitLock(&myPercentRect);
	myPercentRect.SetRect(&tSetPercentRect);
	myMemberLock.UnLock(&myPercentRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRecalculatRect)
{
	MfxSize t_UISize;
	myMemberLock.WaitLock(&myFather);
	if (!myFather)
	{
		myMemberLock.UnLock(&myFather);
		return MfxReturn_Failed;
	}
	myFather->Reflection(MfxText("GetSize"), &t_UISize);
	myMemberLock.UnLock(&myFather);

	myMemberLock.WaitLock(&myPercentRect);
	MfxRect t_RecalculatRect(
		(myPercentRect.myX * t_UISize.myWidth) / 100000,
		(myPercentRect.myY * t_UISize.myHeight) / 100000,
		(myPercentRect.myWidth * t_UISize.myWidth) / 100000,
		(myPercentRect.myHeight * t_UISize.myHeight) / 100000
	);
	myMemberLock.UnLock(&myPercentRect);


	MfxParam msgParam(FLAKE_MSG_Rect);
	msgParam.push_back(t_RecalculatRect);
	Send_Message(msgParam);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRecalculatPercentRect)
{
	MfxSize t_UISize;

	myMemberLock.WaitLock(&myFather);
	if (!myFather)
	{
		myMemberLock.UnLock(&myFather);
		return MfxReturn_Failed;
	}
	myFather->Reflection(MfxText("GetSize"), &t_UISize);
	myMemberLock.UnLock(&myFather);


	myMemberLock.WaitLock(&myRect);
	MfxRect t_RecalculatPercentRect(
		(myRect.myX * 100000.00) / t_UISize.myWidth,
		(myRect.myY * 100000.00) / t_UISize.myHeight,
		(myRect.myWidth * 100000.00) / t_UISize.myWidth,
		(myRect.myHeight * 100000.00) / t_UISize.myHeight
	);
	myMemberLock.UnLock(&myRect);

	MfxParam msgParam(FLAKE_MSG_PercentRect);
	msgParam.push_back(t_RecalculatPercentRect);
	Send_Message(msgParam);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnOpenPercentRect)
{
	myPercentRectFlag = true;

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnClosePercentRect)
{
	myPercentRectFlag = false;

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCMouseMove)
{
	MfxParam msgParam(WM_MOUSEMOVE);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCMouseHover)
{
	MfxParam msgParam(WM_MOUSEHOVER);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCLButtonUp)
{
	MfxParam msgParam(WM_LBUTTONUP);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCLButtonDown)
{
	MfxParam msgParam(WM_LBUTTONDOWN);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCLButtonDouble)
{
	MfxParam msgParam(WM_LBUTTONDBLCLK);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCRButtonUp)
{
	MfxParam msgParam(WM_RBUTTONUP);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCRButtonDown)
{
	MfxParam msgParam(WM_RBUTTONDOWN);
	return Send_Message(msgParam);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCRButtonDouble)
{
	MfxParam msgParam(WM_RBUTTONDBLCLK);
	return Send_Message(msgParam);
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnMouseMove)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MfxText("SetMutexFocus"), this) : MfxReturn_Failed)) //获取互斥焦点成功
		{
			myMouseFloat = true; //成功悬浮

			MfxParam msgParam(MSG_FlakeEvent);
			msgParam.push_back(FlakeEvent_Info(this, FLAKE_EVENT_MouseFloat));
			myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam) : 0;
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

		MfxParam msgParam(MSG_FlakeEvent);
		msgParam.push_back(FlakeEvent_Info(this, FLAKE_EVENT_MouseFloatOver));
		myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam) : 0;
	}

	//开始移动


	if ((myLButtonPress && myLButtonMoveFlag) ||
		(myRButtonPress && myRButtonMoveFlag))
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MfxText("LockMutexFocus"), this) : MfxReturn_Failed))
		{
			myMemberLock.WaitLock(&myButtonMoveBegin);

			t_Rect.Offset(mousePos.myX - myButtonMoveBegin.myX, mousePos.myY - myButtonMoveBegin.myY);
			MfxPoint t_Point(t_Rect.myX, t_Rect.myY);
			SetPoint(&t_Point);
			myButtonMoveBegin = mousePos;

			myMemberLock.UnLock(&myButtonMoveBegin);

			MfxParam msgParam(MSG_FlakeEvent);
			msgParam.push_back(FlakeEvent_Info(this, FLAKE_EVENT_FollowTheMouse));
			msgParam.push_back(t_Point);
			myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam) : 0;
		}
	}
	else
	{
		myFather ? myFather->Reflection(MfxText("UnLockMutexFocus")) : 0;
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnMouseHover)
{
	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnLButtonUp)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MfxText("GetLocalMousePos"), &mousePos) : 0;

	MfxParam msgParam2(MSG_FlakeEvent);
	msgParam2.push_back(FlakeEvent_Info(this, FLAKE_EVENT_LButtonPressOver));
	myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam2) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MfxText("SetMutexFocus"), this) : MfxReturn_Failed)) //获取互斥焦点成功
		{
			if (myLButtonClickFlag) //点击成功
			{
				myLButtonPress = false;
				myLButtonClickFlag = false;

				MfxParam msgParam1(MSG_FlakeEvent);
				msgParam1.push_back(FlakeEvent_Info(this, FLAKE_EVENT_LButtonClick));
				myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam1) : 0;
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
		myLButtonPress = false;

		myLButtonClickFlag = false;
		myRButtonClickFlag = false;
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnLButtonDown)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MfxText("GetLocalMousePos"), &mousePos) : 0;

	//myFather ? myFather->Reflection(MfxText("WND_MIN")) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MfxText("SetMutexFocus"), this) : MfxReturn_Failed)) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;
			myFather->Reflection(MfxText("SetKeyboardFocus"), this); //设置键盘焦点
			myLButtonPress = true;
			myLButtonClickFlag = true;

			MfxParam msgParam1(MSG_FlakeEvent);
			msgParam1.push_back(FlakeEvent_Info(this, FLAKE_EVENT_LButtonPress));
			myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam1) : 0;
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myLButtonPress = false;

		myLButtonClickFlag = false;
		myRButtonClickFlag = false;

		MfxParam msgParam2(MSG_FlakeEvent);
		msgParam2.push_back(FlakeEvent_Info(this, FLAKE_EVENT_LButtonPressOver));
		myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam2) : 0;
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnLButtonDouble)
{
	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRButtonUp)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MfxText("GetLocalMousePos"), &mousePos) : 0;

	MfxParam msgParam2(MSG_FlakeEvent);
	msgParam2.push_back(FlakeEvent_Info(this, FLAKE_EVENT_RButtonPressOver));
	myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam2) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MfxText("SetMutexFocus"), this) : MfxReturn_Failed)) //获取互斥焦点成功
		{
			if (myRButtonClickFlag) //点击成功
			{
				myRButtonPress = false;
				myRButtonClickFlag = false;

				MfxParam msgParam1(MSG_FlakeEvent);
				msgParam1.push_back(FlakeEvent_Info(this, FLAKE_EVENT_RButtonClick));
				myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam1) : 0;
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
		myRButtonPress = false;

		myLButtonClickFlag = false;
		myRButtonClickFlag = false;
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRButtonDown)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MfxText("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MfxText("SetMutexFocus"), this) : MfxReturn_Failed)) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;
			myRButtonPress = true;
			myRButtonClickFlag = true;

			MfxParam msgParam1(MSG_FlakeEvent);
			msgParam1.push_back(FlakeEvent_Info(this, FLAKE_EVENT_RButtonPress));
			myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam1) : 0;
		}
		else
		{
			goto myFailed;
		}
	}
	else
	{
	myFailed:
		myRButtonPress = false;

		myLButtonClickFlag = false;
		myRButtonClickFlag = false;

		MfxParam msgParam2(MSG_FlakeEvent);
		msgParam2.push_back(FlakeEvent_Info(this, FLAKE_EVENT_RButtonPressOver));
		myFather ? myFather->Reflection(MfxText("Post_Message"), msgParam2) : 0;
	}

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRButtonDouble)
{
	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}



/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetTitle)
{
	myMemberLock.TryWaitLock(&myTitle, &myWords);

	myTitle = MFXPARAM_GET_0(MfxString);

	myWords.SetText(myTitle);

	myMemberLock.UnLock(&myTitle, &myWords);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetBackColor)
{
	myMemberLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMemberLock.UnLock(&myRect);

	myMemberLock.TryWaitLock(&myBackRectangle, &myBackColor, &myCanvas);

	myBackColor = MFXPARAM_GET_0(MfxColor);
	myBackRectangle.SetFillColor(&myBackColor);

	myMemberLock.UnLock(&myBackRectangle, &myBackColor, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect, myBackFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetMaskColor)
{
	myMemberLock.TryWaitLock(&myRect);
	MfxSize tSize(myRect);
	myMemberLock.UnLock(&myRect);

	myMemberLock.TryWaitLock(&myMaskRectangle, &myMaskColor, &myCanvas);

	myMaskColor = MFXPARAM_GET_0(MfxColor);
	myMaskRectangle.SetFillColor(&myMaskColor);

	myMemberLock.UnLock(&myMaskRectangle, &myBackColor, &myCanvas);

	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect, myMaskFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetTitleColor)
{
	myMemberLock.TryWaitLock(&myWords, &myTitleColor, &myCanvas);

	myTitleColor = MFXPARAM_GET_0(MfxColor);
	myWords.SetTextColor(&myTitleColor);

	myMemberLock.UnLock(&myWords, &myTitleColor, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetBackFrameSize)
{
	myMemberLock.TryWaitLock(&myBackFrameSize, &myBackRectangle, &myCanvas);

	myBackFrameSize = MFXPARAM_GET_0(double);
	myBackRectangle.SetFrameSize(myBackFrameSize);

	myMemberLock.UnLock(&myBackFrameSize, &myBackRectangle, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect, myBackFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetMaskFrameSize)
{
	myMemberLock.TryWaitLock(&myMaskFrameSize, &myMaskRectangle, &myCanvas);

	myMaskFrameSize = MFXPARAM_GET_0(double);
	myMaskRectangle.SetFrameSize(myMaskFrameSize);

	myMemberLock.UnLock(&myMaskFrameSize, &myMaskRectangle, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MfxText("UnionInvalidateRect"), myRect, myMaskFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnFlakeEvent)
{
	MfxReturn tRet = MfxReturn_Failed;

	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tInfo = MFXPARAM_GET_0(FlakeEvent_Info);

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

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRemoveFlakeEvent)
{
	MfxReturn tRet = MfxReturn_Failed;

	FlakeEvent_Info tFlakeEvent = MFXPARAM_GET_0(FlakeEvent_Info);
	MfxString tRecvFuncName = MFXPARAM_GET_1(MfxString);

	myMemberLock.WaitLock(&myFlakeEventMap);

	auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
	if (t_Iter != myFlakeEventMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i).myRecvFuncName == tRecvFuncName)
			{
				t_Iter->second.erase(i);
				tRet = MfxReturn_Seccess;
				break;
			}
		}
	}

	myMemberLock.UnLock(&myFlakeEventMap);

	MFX_APPFRAME_RETURN(tRet);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPushBackFlakeEvent)
{
	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tFlakeEvent = MFXPARAM_GET_0(FlakeEvent_Info);
	Flake_RecvFunc_Infor tRecvInfo = MFXPARAM_GET_1(Flake_RecvFunc_Infor);

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

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPushFrontFlakeEvent)
{
	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tFlakeEvent = MFXPARAM_GET_0(FlakeEvent_Info);
	Flake_RecvFunc_Infor tRecvInfo = MFXPARAM_GET_1(Flake_RecvFunc_Infor);

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

	MFX_APPFRAME_RETURN(MfxReturn_Seccess);
}