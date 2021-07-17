#include "pch.h"
#include "MfxAppFrame.h"


MFX_OBJ_REFLECTION_INIT(MfxFlake)
MFX_OBJ_REFLECTION_ENDINIT(MfxFlake, MfxBase, \
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

	GetFuncArgNum(&MfxFlake::CloseRButtonMove);

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

	myTitle = MFX_TXT_W("MfxFlake");

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

	father ? father->Reflection(MFX_TXT_W("Send_Message"), MFX_MAKE_PARAM(this).SetMESSAGE(MSG_FlakeInsert)) : 0;
}

MicroFlakeX::MfxFlake::~MfxFlake()
{
	myMemberLock.WaitLock(&myFather);
	myFather ? myFather->Reflection(MFX_TXT_W("Send_Message"), MFX_MAKE_PARAM(this).SetMESSAGE(MSG_FlakeRemove)) : 0;
	myMemberLock.UnLock(&myFather);
}


/********************************************************************************
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(ProcMessage)
{
	MfxReturn t_Ret = MFX_RET_FAILED;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(MFXPARAM_GET_MSG);
	if (t_Iter != myMessageMap.end())
	{
		if (!t_Iter->second.empty())
		{
			for (auto i : t_Iter->second)
			{
				t_Ret = (this->*i.recvFunc)(MFX_CALLBACK_PARAM);
			}
		}
	}

	myMemberLock.UnLock(&myMessageMap);

	return t_Ret;
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(Send_Message)
{
	return ProcMessage(MFX_CALLBACK_PARAM);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(Post_Message)
{
	return MfxBeginNewThread(this, MFX_TXT_W("Send_Message"), MFX_CALLBACK_PARAM);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeMessage(MfxMessage message, MfxStringW name)
{
	auto tRet = MFX_RET_FAILED;

	myMemberLock.WaitLock(&myMessageMap);

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i).myRecvFuncName == name)
			{
				t_Iter->second.erase(i);
				tRet = MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
}

/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::RemoveFlakeEvent(FlakeEvent_Info flakeEvent, MfxStringW recvFuncName)
{
	return Send_Message(MFX_MAKE_PARAM(flakeEvent, recvFuncName).SetMESSAGE(FLAKE_MSG_RemoveFlakeEvent));
}

MfxReturn MicroFlakeX::MfxFlake::PushBackFlakeEvent(FlakeEvent_Info flakeEvent, Flake_RecvFunc_Infor recvInfo)
{
	return Send_Message(MFX_MAKE_PARAM(flakeEvent, recvInfo).SetMESSAGE(FLAKE_MSG_PushBackFlakeEvent));
}

MfxReturn MicroFlakeX::MfxFlake::PushFrontFlakeEvent(FlakeEvent_Info flakeEvent, Flake_RecvFunc_Infor recvInfo)
{
	return Send_Message(MFX_MAKE_PARAM(flakeEvent, recvInfo).SetMESSAGE(FLAKE_MSG_PushFrontFlakeEvent));
}
/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::OpenPercentRect()
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_OpenPercentRect));
}

MfxReturn MicroFlakeX::MfxFlake::ClosePercentRect()
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_ClosePercentRect));
}

MfxReturn MicroFlakeX::MfxFlake::ChickPercentRect()
{
	return  myPercentRectFlag ? MFX_RET_SECCESS : MFX_RET_FAILED;
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
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetFather(MfxBase** ret)
{
	*ret = myFather;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetFloor(MfxFloor* ret)
{
	*ret = myFloor;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::SetFloor(MfxFloor floor)
{
	return Send_Message(MFX_MAKE_PARAM(floor).SetMESSAGE(FLAKE_MSG_SetFloor));
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetSize(MfxSize* ret)
{
	*ret = myRect;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetPoint(MfxPoint* ret)
{
	*ret = myRect;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetEdgeRect(MfxRect* ret)
{
	*ret = myEdgeRect;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitle(MfxStringW* ret)
{
	*ret = myTitle;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleSize(DOUBLE* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::GetBackColor(MfxColor* ret)
{
	*ret = myBackColor;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskColor(MfxColor* ret)
{
	*ret = myMaskColor;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleColor(MfxColor* ret)
{
	myMemberLock.WaitLock(&myTitleColor);
	*ret = myTitleColor;
	myMemberLock.UnLock(&myTitleColor);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetBackFrameSize(MfxReal* ret)
{
	*ret = myBackFrameSize;
	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskFrameSize(MfxReal* ret)
{
	*ret = myMaskFrameSize;
	return MFX_RET_SECCESS;
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::SetRect(MfxRect* set)
{
	Send_Message(MFX_MAKE_PARAM(MfxRect(set)).SetMESSAGE(FLAKE_MSG_Rect));

	if (myFather)
	{
		Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_RecalculatPercentRect));
	}

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::SetSize(MfxSize* set)
{
	myMemberLock.WaitLock(&myRect);
	MfxRect tRect = myRect;
	myMemberLock.UnLock(&myRect);

	tRect.SetSize(set);

	Send_Message(MFX_MAKE_PARAM(tRect).SetMESSAGE(FLAKE_MSG_Rect));

	if (myFather)
	{
		Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_RecalculatPercentRect));
	}

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::SetPoint(MfxPoint* set)
{
	myMemberLock.WaitLock(&myRect);
	MfxRect tRect = myRect;
	myMemberLock.UnLock(&myRect);

	tRect.SetPoint(set);

	Send_Message(MFX_MAKE_PARAM(tRect).SetMESSAGE(FLAKE_MSG_Rect));

	if (myFather)
	{
		Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_RecalculatPercentRect));
	}

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::SetEdgeRect(MfxRect* set)
{
	myMemberLock.WaitLock(&myEdgeRect);
	myEdgeRect = set;
	myMemberLock.UnLock(&myEdgeRect);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::SetTitle(MfxStringW set)
{
	return Send_Message(MFX_MAKE_PARAM(set).SetMESSAGE(FLAKE_MSG_SetTitle));
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleSize(DOUBLE set)
{
	return Send_Message(MFX_MAKE_PARAM(set).SetMESSAGE(FLAKE_MSG_SetTitleSize));
}

MfxReturn MicroFlakeX::MfxFlake::SetBackColor(MfxColor* set)
{
	return Send_Message(MFX_MAKE_PARAM(MfxColor(set)).SetMESSAGE(FLAKE_MSG_SetBackColor));
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskColor(MfxColor* set)
{
	return Send_Message(MFX_MAKE_PARAM(MfxColor(set)).SetMESSAGE(FLAKE_MSG_SetMaskColor));
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleColor(MfxColor* set)
{
	return Send_Message(MFX_MAKE_PARAM(MfxColor(set)).SetMESSAGE(FLAKE_MSG_SetTitleColor));
}

MfxReturn MicroFlakeX::MfxFlake::SetBackFrameSize(MfxReal set)
{
	return Send_Message(MFX_MAKE_PARAM(set).SetMESSAGE(FLAKE_MSG_SetBackFrameSize));
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskFrameSize(MfxReal set)
{
	return Send_Message(MFX_MAKE_PARAM(set).SetMESSAGE(FLAKE_MSG_SetMaskFrameSize));
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::CloseLButtonMove()
{
	myLButtonMoveFlag = false;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::OpenRButtonMove()
{
	myRButtonMoveFlag = true;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxFlake::CloseRButtonMove()
{
	myRButtonMoveFlag = false;

	return MFX_RET_SECCESS;
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
	return MFX_RET_SECCESS;
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

	myFather ? myFather->Reflection(MFX_TXT_W("Send_Message"), MFX_MAKE_PARAM(this).SetMESSAGE(MSG_FlakeRemove)) : 0;

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
		Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_RecalculatPercentRect));
	}

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRemovePaper)
{
	myMemberLock.TryWaitLock(&myFather, &myWnd, &myCanvas);

	myFather ? myFather->Reflection(MFX_TXT_W("Send_Message"), MFX_MAKE_PARAM(this).SetMESSAGE(MSG_FlakeRemove)) : 0;

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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetFloor)
{
	myMemberLock.TryWaitLock(&myFloor, &myFather);

	myFloor = MFXPARAM_GET_0(MfxFloor);
	myFather ? myFather->Reflection(MFX_TXT_W("Send_Message"), MFX_MAKE_PARAM().SetMESSAGE(MSG_FlakeFloorChange)) : 0;

	myMemberLock.UnLock(&myFloor, &myFather);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPaintMaskDC)
{
	myMemberLock.WaitLock(&myMaskRectangle);
	myMaskRectangle.Paint();
	myMemberLock.UnLock(&myMaskRectangle);

	return MFX_RET_FAILED;
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
	myFather ? myFather->Reflection(MFX_TXT_W("ChickPercentRect"), &tChick) : 0;
	myMemberLock.UnLock(&myFather);

	if (myPercentRectFlag || tChick)
	{
		Send_Message(MFX_MAKE_PARAM().SetMESSAGE(FLAKE_MSG_RecalculatRect));
	}

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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

	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect, max(myBackFrameSize, myMaskFrameSize)) : 0;
	myRect.SetRect(&tSetRect);
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect, max(myBackFrameSize, myMaskFrameSize)) : 0;

	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnPercentRect)
{
	MfxRect tSetPercentRect = MFXPARAM_GET_0(MfxRect);

	myMemberLock.WaitLock(&myPercentRect);
	myPercentRect.SetRect(&tSetPercentRect);
	myMemberLock.UnLock(&myPercentRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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
		return MFX_RET_FAILED;
	}
	myFather->Reflection(MFX_TXT_W("GetSize"), &t_UISize);
	myMemberLock.UnLock(&myFather);

	myMemberLock.WaitLock(&myPercentRect);
	MfxRect t_RecalculatRect(
		(myPercentRect.myX * t_UISize.myWidth) / 100000,
		(myPercentRect.myY * t_UISize.myHeight) / 100000,
		(myPercentRect.myWidth * t_UISize.myWidth) / 100000,
		(myPercentRect.myHeight * t_UISize.myHeight) / 100000
	);
	myMemberLock.UnLock(&myPercentRect);


	Send_Message(MFX_MAKE_PARAM(t_RecalculatRect).SetMESSAGE(FLAKE_MSG_Rect));

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRecalculatPercentRect)
{
	MfxSize t_UISize;

	myMemberLock.WaitLock(&myFather);
	if (!myFather)
	{
		myMemberLock.UnLock(&myFather);
		return MFX_RET_FAILED;
	}
	myFather->Reflection(MFX_TXT_W("GetSize"), &t_UISize);
	myMemberLock.UnLock(&myFather);


	myMemberLock.WaitLock(&myRect);
	MfxRect t_RecalculatPercentRect(
		(myRect.myX * 100000.00) / t_UISize.myWidth,
		(myRect.myY * 100000.00) / t_UISize.myHeight,
		(myRect.myWidth * 100000.00) / t_UISize.myWidth,
		(myRect.myHeight * 100000.00) / t_UISize.myHeight
	);
	myMemberLock.UnLock(&myRect);

	Send_Message(MFX_MAKE_PARAM(t_RecalculatPercentRect).SetMESSAGE(FLAKE_MSG_PercentRect));

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnClosePercentRect)
{
	myPercentRectFlag = false;

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCMouseMove)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_MOUSEMOVE));
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCMouseHover)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_MOUSEHOVER));
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCLButtonUp)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_LBUTTONUP));
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCLButtonDown)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_LBUTTONDOWN));
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCLButtonDouble)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_LBUTTONDBLCLK));
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCRButtonUp)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_RBUTTONUP));
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCRButtonDown)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_RBUTTONDOWN));
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnNCRButtonDouble)
{
	return Send_Message(MFX_MAKE_PARAM().SetMESSAGE(WM_RBUTTONDBLCLK));
}


/********************************************************************************
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnMouseMove)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MFX_TXT_W("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MFX_TXT_W("SetMutexFocus"), this) : MFX_RET_FAILED)) //获取互斥焦点成功
		{
			myMouseFloat = true; //成功悬浮

			myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_MouseFloat)).SetMESSAGE(MSG_FlakeEvent)) : 0;
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

		myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_MouseFloatOver)).SetMESSAGE(MSG_FlakeEvent)) : 0;
	}

	//开始移动


	if ((myLButtonPress && myLButtonMoveFlag) ||
		(myRButtonPress && myRButtonMoveFlag))
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MFX_TXT_W("LockMutexFocus"), this) : MFX_RET_FAILED))
		{
			myMemberLock.WaitLock(&myButtonMoveBegin);

			t_Rect.Offset(mousePos.myX - myButtonMoveBegin.myX, mousePos.myY - myButtonMoveBegin.myY);
			MfxPoint t_Point(t_Rect.myX, t_Rect.myY);
			SetPoint(&t_Point);
			myButtonMoveBegin = mousePos;

			myMemberLock.UnLock(&myButtonMoveBegin);

			myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_FollowTheMouse), t_Point).SetMESSAGE(MSG_FlakeEvent)) : 0;
		}
	}
	else
	{
		myFather ? myFather->Reflection(MFX_TXT_W("UnLockMutexFocus")) : 0;
	}

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnMouseHover)
{
	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnLButtonUp)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MFX_TXT_W("GetLocalMousePos"), &mousePos) : 0;
	myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_LButtonPressOver)).SetMESSAGE(MSG_FlakeEvent)) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MFX_TXT_W("SetMutexFocus"), this) : MFX_RET_FAILED)) //获取互斥焦点成功
		{
			if (myLButtonClickFlag) //点击成功
			{
				myLButtonPress = false;
				myLButtonClickFlag = false;

				myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_LButtonClick)).SetMESSAGE(MSG_FlakeEvent)) : 0;
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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnLButtonDown)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MFX_TXT_W("GetLocalMousePos"), &mousePos) : 0;

	//myFather ? myFather->Reflection(MFX_TXT_W("WND_MIN")) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MFX_TXT_W("SetMutexFocus"), this) : MFX_RET_FAILED)) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;

			myFather ? myFather->Reflection(MFX_TXT_W("SetKeyboardFocus"), this) : 0; //设置键盘焦点

			myLButtonPress = true;
			myLButtonClickFlag = true;

			myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_LButtonPress)).SetMESSAGE(MSG_FlakeEvent)) : 0;
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

		myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_LButtonPressOver)).SetMESSAGE(MSG_FlakeEvent)) : 0;
	}

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnLButtonDouble)
{
	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}


MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRButtonUp)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MFX_TXT_W("GetLocalMousePos"), &mousePos) : 0;

	myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_RButtonPressOver)).SetMESSAGE(MSG_FlakeEvent)) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MFX_TXT_W("SetMutexFocus"), this) : MFX_RET_FAILED)) //获取互斥焦点成功
		{
			if (myRButtonClickFlag) //点击成功
			{
				myRButtonPress = false;
				myRButtonClickFlag = false;

				myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_RButtonClick)).SetMESSAGE(MSG_FlakeEvent)) : 0;
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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRButtonDown)
{
	MfxPoint mousePos;

	myFather ? myFather->Reflection(MFX_TXT_W("GetLocalMousePos"), &mousePos) : 0;

	myMemberLock.WaitLock(&myRect);
	MfxRect t_Rect = myRect;
	myMemberLock.UnLock(&myRect);

	bool tInside = false;
	t_Rect.IsPointInside(&mousePos, &tInside);
	if (tInside)
	{
		if (MFX_SECCESS(myFather ? myFather->Reflection(MFX_TXT_W("SetMutexFocus"), this) : MFX_RET_FAILED)) //获取互斥焦点成功
		{
			myButtonMoveBegin = mousePos;
			myRButtonPress = true;
			myRButtonClickFlag = true;

			myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_RButtonPress)).SetMESSAGE(MSG_FlakeEvent)) : 0;
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

		myFather ? myFather->Reflection(MFX_TXT_W("Post_Message"), MFX_MAKE_PARAM(FlakeEvent_Info(this, FLAKE_EVENT_RButtonPressOver)).SetMESSAGE(MSG_FlakeEvent)) : 0;
	}

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRButtonDouble)
{
	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}



/********************************************************************************
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetTitle)
{
	myMemberLock.TryWaitLock(&myTitle, &myWords);

	myTitle = MFXPARAM_GET_0(MfxStringW);

	myWords.SetText(myTitle);

	myMemberLock.UnLock(&myTitle, &myWords);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect, myBackFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect, myMaskFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetTitleColor)
{
	myMemberLock.TryWaitLock(&myWords, &myTitleColor, &myCanvas);

	myTitleColor = MFXPARAM_GET_0(MfxColor);
	myWords.SetTextColor(&myTitleColor);

	myMemberLock.UnLock(&myWords, &myTitleColor, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetBackFrameSize)
{
	myMemberLock.TryWaitLock(&myBackFrameSize, &myBackRectangle, &myCanvas);

	myBackFrameSize = MFXPARAM_GET_0(double);
	myBackRectangle.SetFrameSize(myBackFrameSize);

	myMemberLock.UnLock(&myBackFrameSize, &myBackRectangle, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect, myBackFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnSetMaskFrameSize)
{
	myMemberLock.TryWaitLock(&myMaskFrameSize, &myMaskRectangle, &myCanvas);

	myMaskFrameSize = MFXPARAM_GET_0(double);
	myMaskRectangle.SetFrameSize(myMaskFrameSize);

	myMemberLock.UnLock(&myMaskFrameSize, &myMaskRectangle, &myCanvas);


	myMemberLock.TryWaitLock(&myFather, &myRect);
	myFather ? myFather->Reflection(MFX_TXT_W("UnionInvalidateRect"), myRect, myMaskFrameSize) : 0;
	myMemberLock.UnLock(&myFather, &myRect);

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}


/********************************************************************************
*
*
*
*
*********************************************************************************/
MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnFlakeEvent)
{
	MfxReturn tRet = MFX_RET_FAILED;

	myMemberLock.WaitLock(&myFlakeEventMap);

	FlakeEvent_Info tInfo = MFXPARAM_GET_0(FlakeEvent_Info);

	auto t_Iter = myFlakeEventMap.find(tInfo);
	if (t_Iter != myFlakeEventMap.end())
	{
		if (!t_Iter->second.empty())
		{
			for (auto i : (t_Iter->second))
			{
				tRet = (this->*i.recvFunc)(MFX_CALLBACK_PARAM);
			}
		}
	}

	myMemberLock.UnLock(&myFlakeEventMap);

	return tRet;
}

MfxReturn MicroFlakeX::MfxFlake::MFX_CALLBACK(__OnRemoveFlakeEvent)
{
	MfxReturn tRet = MFX_RET_FAILED;

	FlakeEvent_Info tFlakeEvent = MFXPARAM_GET_0(FlakeEvent_Info);
	MfxStringW tRecvFuncName = MFXPARAM_GET_1(MfxStringW);

	myMemberLock.WaitLock(&myFlakeEventMap);

	auto t_Iter = myFlakeEventMap.find(tFlakeEvent);
	if (t_Iter != myFlakeEventMap.end())
	{
		for (auto i = t_Iter->second.begin(); i != t_Iter->second.end(); i++)
		{
			if ((*i).myRecvFuncName == tRecvFuncName)
			{
				t_Iter->second.erase(i);
				tRet = MFX_RET_SECCESS;
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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
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

	MFX_APPFRAME_RETURN(MFX_RET_SECCESS);
}