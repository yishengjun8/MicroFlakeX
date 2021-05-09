#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init_0(MfxFlake)
MfxObject_Init_1(MfxFlake, END)
MfxObject_Init_2(MfxFlake, MfxBase);

void MicroFlakeX::MfxFlake::MfxRegMessages()
{
	myUnderFloor--;
	myCoverFloor++;

	FLAKE_REG_MSG(UI_MSG_SetPaper, MfxFlake, __OnSetPaper, myCoverFloor);

	FLAKE_REG_MSG(UI_MSG_PaintBack, MfxFlake, __OnPaintBackDC, myCoverFloor);
	FLAKE_REG_MSG(UI_MSG_PaintMask, MfxFlake, __OnPaintMaskDC, myCoverFloor);

	FLAKE_REG_MSG(WM_SIZE, MfxFlake, __OnUISize, myCoverFloor);

	FLAKE_REG_MSG(FLAKE_MSG_Size, MfxFlake, __OnSize, myCoverFloor);
	FLAKE_REG_MSG(FLAKE_MSG_Point, MfxFlake, __OnPoint, myCoverFloor);

	FLAKE_REG_MSG(FLAKE_MSG_SetFloor, MfxFlake, __OnSetFloor, myCoverFloor);

	FLAKE_REG_MSG(WM_MOUSEMOVE, MfxFlake, __OnMouseMove, myCoverFloor);

	FLAKE_REG_MSG(WM_LBUTTONUP, MfxFlake, __OnLButtonUp, myCoverFloor);
	FLAKE_REG_MSG(WM_RBUTTONUP, MfxFlake, __OnRButtonUp, myCoverFloor);
	FLAKE_REG_MSG(WM_LBUTTONDOWN, MfxFlake, __OnLButtonDown, myCoverFloor);
	FLAKE_REG_MSG(WM_RBUTTONDOWN, MfxFlake, __OnRButtonDown, myCoverFloor);

	FLAKE_REG_MSG(FLAKE_MSG_SetTitle, MfxFlake, __OnSetTitle, myCoverFloor);
	FLAKE_REG_MSG(FLAKE_MSG_SetBackColor, MfxFlake, __OnSetBackColor, myCoverFloor);
	FLAKE_REG_MSG(FLAKE_MSG_SetMaskColor, MfxFlake, __OnSetMaskColor, myCoverFloor);
	FLAKE_REG_MSG(FLAKE_MSG_SetBackImage, MfxFlake, __OnSetBackImage, myCoverFloor);
	FLAKE_REG_MSG(FLAKE_MSG_SetMaskImage, MfxFlake, __OnSetMaskImage, myCoverFloor);
	FLAKE_REG_MSG(FLAKE_MSG_SetTitleWords, MfxFlake, __OnSetTitleWords, myCoverFloor);
}

void MicroFlakeX::MfxFlake::MfxFlakeInitData()
{
	myUnderFloor = 0;
	myCoverFloor = 0;

	myWnd = NULL;
	myUI = nullptr;
	myCanvas = nullptr;

	myFloor = 66;

	myTitle = myType = MfxText("MfxFlake");

	myMouseFloat = false;
	myLButtonClickFlag = false;
	myLButtonPress = false;
	myRButtonClickFlag = false;
	myRButtonPress = false;
	myRButtonMoveFlag = false;
	myLButtonMoveFlag = false;

	myBackImage = new MfxImage(MfxColor(255,255,0,0), myRect);
	myMaskImage = nullptr;

	myTitleWords = new MfxWords(myTitle, myRect);
	myTitleWords->SetTextAlignmentX(TextAlignmentX::DWRITE_TEXT_ALIGNMENT_CENTER);
	myTitleWords->SetTextAlignmentY(TextAlignmentY::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

MicroFlakeX::MfxFlake::MfxFlake()
{
	myRect.Init(100, 100, 128, 128);
	MfxFlakeInitData();
	MfxRegMessages();
}

MicroFlakeX::MfxFlake::MfxFlake(MfxRect set)
{
	myRect = set;
	MfxFlakeInitData();
	MfxRegMessages();
}

MicroFlakeX::MfxFlake::~MfxFlake()
{
	MfxCodeLock(this);
	if (myUI)
	{
		//��支扮��叙幻完笥辛需
		myUI->ProcMessage(UI_MSG_FlakeRemove, (WPARAM)this, NULL);
	}

	SafeDelete(myBackImage);
	SafeDelete(myMaskImage);
	SafeDelete(myTitleWords);
}

MfxReturn MicroFlakeX::MfxFlake::GetType(MfxString* ret)
{
	*ret = myType;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxReturn t_Ret = RFail;

	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		if (!t_Iter->second->empty())
		{
			for (auto i : *(t_Iter->second))
			{
				t_Ret = (this->*i->myFunc)(wParam, lParam);
			}
		}
	}

	if (myUI && (
		myMouseFloat.CheckChangeFlag() || 
		myLButtonPress.CheckChangeFlag() || 
		myRButtonPress.CheckChangeFlag()))
	{
		myMouseFloat.CleanChangeFlag();
		myLButtonPress.CleanChangeFlag();
		myRButtonPress.CleanChangeFlag();
		//頁倦俶勣泡仟順中
		PostMessage(myWnd, WM_PAINT, NULL, NULL);
	}

	return t_Ret;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxFlake::GetMyUI(MfxUI** ret)
{
	*ret = myUI;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::GetFloor(MfxFloor* ret)
{
	*ret = myFloor;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitle(MfxString* ret)
{
	*ret = myTitle;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleSize(FLOAT* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleColor(MfxColor* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::GetRect(MfxRect* ret)
{
	*ret = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::GetSize(MfxSize* ret)
{
	*ret = myRect;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::GetPoint(MfxPoint* ret)
{
	*ret = myRect;
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxFlake::SetTitle(MfxString set)
{
	return ProcMessage(FLAKE_MSG_SetTitle, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleSize(FLOAT set)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleColor(MfxColor set)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxFlake::SetFloor(MfxFloor floor)
{
	return ProcMessage(FLAKE_MSG_SetFloor, NULL, floor);
}

MfxReturn MicroFlakeX::MfxFlake::SetRect(MfxRect set)
{
	MfxSize t_Size(&set);
	MfxPoint t_Point(&set);

	ProcMessage(FLAKE_MSG_Size, NULL, (LPARAM)&t_Size);
	ProcMessage(FLAKE_MSG_Point, NULL, (LPARAM)&t_Point);
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::SetSize(MfxSize set)
{
	ProcMessage(FLAKE_MSG_Size, NULL, (LPARAM)&set);
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::SetPoint(MfxPoint set)
{
	ProcMessage(FLAKE_MSG_Point, NULL, (LPARAM)&set);
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxFlake::OpenLButtonMove()
{
	MfxCodeLock(this);
	myLButtonMoveFlag = true;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::CloseLButtonMove()
{
	MfxCodeLock(this);
	myLButtonMoveFlag = false;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::OpenRButtonMove()
{
	MfxCodeLock(this);
	myRButtonMoveFlag = true;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::CloseRButtonMove()
{
	MfxCodeLock(this);
	myRButtonMoveFlag = false;
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::GetBackImage(MfxImage** ret)
{
	return myBackImage ? myBackImage->Clone(ret) : RFail;
}

MfxReturn MicroFlakeX::MfxFlake::GetMaskImage(MfxImage** ret)
{
	return myMaskImage ? myMaskImage->Clone(ret) : RFail;
}

MfxReturn MicroFlakeX::MfxFlake::GetTitleWords(MfxWords** ret)
{
	return myTitleWords ? myTitleWords->Clone(ret) : RFail;
}

MfxReturn MicroFlakeX::MfxFlake::SetBackColor(MfxColor set)
{
	return ProcMessage(FLAKE_MSG_SetBackColor, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskColor(MfxColor set)
{
	return ProcMessage(FLAKE_MSG_SetMaskColor, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxFlake::SetBackImage(MfxImage* set)
{
	return ProcMessage(FLAKE_MSG_SetBackImage, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetMaskImage(MfxImage* set)
{
	return ProcMessage(FLAKE_MSG_SetMaskImage, NULL, (LPARAM)set);
}

MfxReturn MicroFlakeX::MfxFlake::SetTitleWords(MfxWords* set)
{
	return ProcMessage(FLAKE_MSG_SetTitleWords, NULL, (LPARAM)set);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxFlake::RemoveMessage(MfxMsg message, MfxString name)
{
	MfxCodeLock(this);
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second->begin(); i != t_Iter->second->end(); i++)
		{
			if ((*i)->myName == name)
			{
				t_Iter->second->erase(i);
				return RFine;
			}
		}
	}
	return RFail;
}

MfxReturn MicroFlakeX::MfxFlake::InsertMessage(MfxMsg message, MfxFlake_MessageMap_Value* msgValue)
{
	MfxCodeLock(this);
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		auto t_AddVector = new MfxFlake_MessageMap_Vector;
		t_Iter = myMessageMap.insert(MfxFlake_MessageMap_elem(message, t_AddVector)).first;
	}

	t_Iter->second->push_back(msgValue);
	std::sort(t_Iter->second->begin(), t_Iter->second->end(), MfxApp::FloorCompare<MfxFlake_MessageMap_Value>);

	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MfxReturn MicroFlakeX::MfxFlake::__OnSetPaper(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxUI_Paper_Value* t_PaperValue = (MfxUI_Paper_Value*)lParam;
	myUI = t_PaperValue->myUI;
	myWnd = t_PaperValue->myWnd;
	myCanvas = t_PaperValue->myCanvas;

	if (myBackImage)
	{
		myBackImage->SetCanvas(myCanvas);
	}
	if (myTitleWords)
	{
		myTitleWords->SetCanvas(myCanvas);
	}
	if (myMaskImage)
	{
		myMaskImage->SetCanvas(myCanvas);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	if (myBackImage)
	{
		myBackImage->Paint();
	}
	if (myTitleWords)
	{
		myTitleWords->Paint();
	}
	if (myMaskImage)
	{
		myMaskImage->Paint();
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	return RFail;
}

MfxReturn MicroFlakeX::MfxFlake::__OnUISize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxSize* t_Size = (MfxSize*)lParam;

	if (myBackImage)
	{
		myBackImage->SetSize(*t_Size);
	}
	if (myMaskImage)
	{
		myMaskImage->SetSize(*t_Size);
	}
	if (myTitleWords)
	{
		myTitleWords->SetSize(*t_Size);
	}

	myRect.myWidth = t_Size->myWidth;
	myRect.myHeight = t_Size->myHeight;

	PostMessage(myWnd, WM_PAINT, NULL, NULL);
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnPoint(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint* t_Point = (MfxPoint*)lParam;

	if (myBackImage)
	{
		myBackImage->SetPoint(*t_Point);
	}
	if (myMaskImage)
	{
		myMaskImage->SetPoint(*t_Point);
	}
	if (myTitleWords)
	{
		myTitleWords->SetPoint(*t_Point);
	}
	myRect.myX = t_Point->myX;
	myRect.myY = t_Point->myY;

	PostMessage(myWnd, WM_PAINT, NULL, NULL);
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetFloor(WPARAM wParam, LPARAM lParam)
{
	myFloor = lParam;
	if (myUI)
	{
		myUI->ProcMessage(FLAKE_MSG_FlakeFloorChange, NULL, NULL);
		PostMessage(myWnd, WM_PAINT, NULL, NULL);
	}
	return RFine;
}


MfxReturn MicroFlakeX::MfxFlake::__OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tInside = false;
	myRect.PointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
		{
			myMouseFloat = true; //撹孔傅検 - 窟僕��連
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

		ProcMessage(FLAKE_MSG_Point, NULL, (LPARAM)&t_Point);
		myButtonMoveBegin = nowPos;
	}
	else
	{
		if (myUI)
		{
			myUI->UnLockMutexFocus();
		}
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tInside = false;
	myRect.PointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
		{
			myButtonMoveBegin = mousePos;
			myUI->SetKeyboardFocus(this); //譜崔囚徒醜泣
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tInside = false;
	myRect.PointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
		{
			if (myLButtonClickFlag) //泣似撹孔
			{
				myMouseFloat = true;
				myLButtonPress = false;
				myLButtonClickFlag = false;
				MfxSendMessageToUI(FLAKE_MSG_LButtonClick, wParam, lParam);
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tInside = false;
	myRect.PointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tInside = false;
	myRect.PointInside(&mousePos, &tInside);
	if (tInside)
	{
		MfxFlake* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
		{
			if (myRButtonClickFlag) //泣似撹孔
			{
				myMouseFloat = true;
				myRButtonPress = false;
				myRButtonClickFlag = false;
				MfxSendMessageToUI(FLAKE_MSG_RButtonClick, wParam, lParam);
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
	return RFine;
}


MfxReturn MicroFlakeX::MfxFlake::__OnSetTitle(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	myTitle = *(MfxString*)lParam;
	if (myTitleWords)
	{
		myTitleWords->SetText(myTitle);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxColor* t_Set = (MfxColor*)lParam;
	if (myBackImage)
	{
		myBackImage->FromColor(*t_Set, MfxSize(&myRect));
	}
	else
	{
		myBackImage = new MfxImage(*t_Set, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
		myBackImage->SetCanvas(myCanvas);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxColor* t_Set = (MfxColor*)lParam;
	if (myMaskImage)
	{
		myMaskImage->FromColor(*t_Set, MfxSize(&myRect));
	}
	else
	{
		myMaskImage = new MfxImage(*t_Set, MfxRect(0, 0, myRect.myWidth, myRect.myHeight));
		myMaskImage->SetCanvas(myCanvas);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxImage* t_Set = (MfxImage*)lParam;
	if (t_Set)
	{
		SafeDelete(myBackImage);
		(t_Set)->Clone(&myBackImage);
		myBackImage->SetRect(myRect);
		myBackImage->SetCanvas(myCanvas);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxImage* t_Set = (MfxImage*)lParam;
	if (t_Set)
	{
		SafeDelete(myMaskImage);
		(t_Set)->Clone(&myMaskImage);
		myMaskImage->SetRect(myRect);
		myMaskImage->SetCanvas(myCanvas);
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxFlake::__OnSetTitleWords(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxWords* t_Set = (MfxWords*)lParam;
	if (t_Set)
	{
		SafeDelete(myTitleWords);
		(t_Set)->Clone(&myTitleWords);
		myTitleWords->SetRect(myRect);
		myTitleWords->SetCanvas(myCanvas);
	}
	return RFine;
}