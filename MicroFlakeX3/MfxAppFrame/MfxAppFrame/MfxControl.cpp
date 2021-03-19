#include "pch.h"
#include "MfxAppFrame.h"

MfxObject_Init_0(MfxControl)
MfxObject_Init_1(MfxControl)
MfxObject_Init_2(MfxControl, MfxBase);

void MicroFlakeX::MfxControl::MfxRegMessages()
{
	myUnderFloor--;
	myCoverFloor++;

	CONTROL_REG_MSG(MfxUI_Message_SetPaper, MfxControl, __OnSetPaper, myCoverFloor);

	CONTROL_REG_MSG(MfxUI_Message_PaintBack, MfxControl, __OnPaintBackDC, myCoverFloor);
	CONTROL_REG_MSG(MfxUI_Message_PaintMask, MfxControl, __OnPaintMaskDC, myCoverFloor);

	CONTROL_REG_MSG(WM_SIZE, MfxControl, __OnUISize, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_Size, MfxControl, __OnSize, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_Point, MfxControl, __OnPoint, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_SetFloor, MfxControl, __OnSetFloor, myCoverFloor);

	CONTROL_REG_MSG(WM_MOUSEMOVE, MfxControl, __OnMouseMove, myCoverFloor);

	CONTROL_REG_MSG(WM_LBUTTONUP, MfxControl, __OnLButtonUp, myCoverFloor);
	CONTROL_REG_MSG(WM_RBUTTONUP, MfxControl, __OnRButtonUp, myCoverFloor);
	CONTROL_REG_MSG(WM_LBUTTONDOWN, MfxControl, __OnLButtonDown, myCoverFloor);
	CONTROL_REG_MSG(WM_RBUTTONDOWN, MfxControl, __OnRButtonDown, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_SetTitle, MfxControl, __OnSetTitle, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_SetBackColor, MfxControl, __OnSetBackColor, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_SetMaskColor, MfxControl, __OnSetMaskColor, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_SetBackImage, MfxControl, __OnSetBackImage, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_SetMaskImage, MfxControl, __OnSetMaskImage, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_SetTitleWords, MfxControl, __OnSetTitleWords, myCoverFloor);
}

void MicroFlakeX::MfxControl::MfxControlInitData()
{
	myUnderFloor = 0;
	myCoverFloor = 0;

	myWnd = NULL;
	myUI = nullptr;
	myCanvas = nullptr;

	myFloor = 66;

	myTitle = myType = L"MfxControl";

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

MicroFlakeX::MfxControl::MfxControl()
{
	myRect.Init(100, 100, 128, 128);
	MfxControlInitData();
	MfxRegMessages();
}

MicroFlakeX::MfxControl::MfxControl(MfxRect set)
{
	myRect = set;
	MfxControlInitData();
	MfxRegMessages();
}

MicroFlakeX::MfxControl::~MfxControl()
{
	MfxCodeLock(this);
	if (myUI)
	{
		myUI->ProcMessage(MfxUI_Message_ControlRemove, (WPARAM)this, NULL);
	}

	SafeDelete(myBackImage);
	SafeDelete(myMaskImage);
	SafeDelete(myTitleWords);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetType(MfxStrW* ret)
{
	*ret = myType;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
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
		PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	}

	return t_Ret;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetMyUI(MfxUI** ret)
{
	*ret = myUI;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetFloor(MfxFloor* ret)
{
	*ret = myFloor;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetTitle(MfxStrW* ret)
{
	*ret = myTitle;
	return RFine;
}

MfxReturn MicroFlakeX::MfxControl::GetTitleSize(FLOAT* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxControl::GetTitleColor(MfxColor* ret)
{
	return MfxReturn();
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetRect(MfxRect* ret)
{
	*ret = myRect;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetSize(MfxSize* ret)
{
	*ret = myRect;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetPoint(MfxPoint* ret)
{
	*ret = myRect;
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetTitle(MfxStrW set)
{
	return ProcMessage(MfxControl_Message_SetTitle, NULL, (LPARAM)&set);
}

MfxReturn MicroFlakeX::MfxControl::SetTitleSize(FLOAT set)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxControl::SetTitleColor(MfxColor set)
{
	return MfxReturn();
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetFloor(MfxFloor floor)
{
	return ProcMessage(MfxControl_Message_SetFloor, NULL, floor);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetRect(MfxRect set)
{
	MfxSize t_Size(&set);
	MfxPoint t_Point(&set);

	ProcMessage(MfxControl_Message_Size, NULL, (LPARAM)&t_Size);
	ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&t_Point);
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetSize(MfxSize set)
{
	ProcMessage(MfxControl_Message_Size, NULL, (LPARAM)&set);
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetPoint(MfxPoint set)
{
	ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&set);
	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::OpenLButtonMove()
{
	MfxCodeLock(this);
	myLButtonMoveFlag = true;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::CloseLButtonMove()
{
	MfxCodeLock(this);
	myLButtonMoveFlag = false;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::OpenRButtonMove()
{
	MfxCodeLock(this);
	myRButtonMoveFlag = true;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::CloseRButtonMove()
{
	MfxCodeLock(this);
	myRButtonMoveFlag = false;
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetBackImage(MfxImage** ret)
{
	return myBackImage ? myBackImage->Clone(ret) : RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetMaskImage(MfxImage** ret)
{
	return myMaskImage ? myMaskImage->Clone(ret) : RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetTitleWords(MfxWords** ret)
{
	return myTitleWords ? myTitleWords->Clone(ret) : RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetBackColor(MfxColor set)
{
	return ProcMessage(MfxControl_Message_SetBackColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetMaskColor(MfxColor set)
{
	return ProcMessage(MfxControl_Message_SetMaskColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetBackImage(MfxImage* set)
{
	return ProcMessage(MfxControl_Message_SetBackImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetMaskImage(MfxImage* set)
{
	return ProcMessage(MfxControl_Message_SetMaskImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetTitleWords(MfxWords* set)
{
	return ProcMessage(MfxControl_Message_SetTitleWords, NULL, (LPARAM)set);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::RemoveMessage(MfxMsg message, MfxStrW name)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::InsertMessage(MfxMsg message, MfxControl_MessageMap_Value* msgValue)
{
	MfxCodeLock(this);
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		auto t_AddVector = new MfxControl_MessageMap_Vector;
		t_Iter = myMessageMap.insert(MfxControl_MessageMap_elem(message, t_AddVector)).first;
	}

	t_Iter->second->push_back(msgValue);
	std::sort(t_Iter->second->begin(), t_Iter->second->end(), MfxApp::FloorCompare<MfxControl_MessageMap_Value>);

	return RFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetPaper(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	return RFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnUISize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSize(WPARAM wParam, LPARAM lParam)
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

	PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPoint(WPARAM wParam, LPARAM lParam)
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

	PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	return RFine;
}

MfxReturn MicroFlakeX::MfxControl::__OnSetFloor(WPARAM wParam, LPARAM lParam)
{
	myFloor = lParam;
	if (myUI)
	{
		myUI->ProcMessage(MfxControl_Message_ControlFloorChange, NULL, NULL);
		PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	}
	return RFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tCollision = false;
	myRect.Collision(&mousePos, &tCollision);
	if (tCollision)
	{
		MfxControl* t_Conctrol = nullptr;
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

	if ((*myLButtonPress && *myLButtonMoveFlag) ||
		(*myRButtonPress && *myRButtonMoveFlag))
	{
		if (myUI)
		{
			myUI->LockMutexFocus(this);
		}
		MfxPoint nowPos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		MfxRect t_Rect = myRect;
		t_Rect.Offset(nowPos.myX - myButtonMoveBegin.myX, nowPos.myY - myButtonMoveBegin.myY);

		MfxPoint t_Point(t_Rect.myX, t_Rect.myY);

		ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&t_Point);
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tCollision = false;
	myRect.Collision(&mousePos, &tCollision);
	if (tCollision)
	{
		MfxControl* t_Conctrol = nullptr;
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tCollision = false;
	myRect.Collision(&mousePos, &tCollision);
	if (tCollision)
	{
		MfxControl* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
		{
			if (*myLButtonClickFlag) //泣似撹孔
			{
				myMouseFloat = true;
				myLButtonPress = false;
				myLButtonClickFlag = false;
				CONTORL_SendMessageToUI(MfxControl_Message_LButtonClick, wParam, lParam);
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tCollision = false;
	myRect.Collision(&mousePos, &tCollision);
	if (tCollision)
	{
		MfxControl* t_Conctrol = nullptr;
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	MfxPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	BOOL tCollision = false;
	myRect.Collision(&mousePos, &tCollision);
	if (tCollision)
	{
		MfxControl* t_Conctrol = nullptr;
		myUI->SetMutexFocus(this);
		myUI->GetMutexFocus(&t_Conctrol);

		if (t_Conctrol == this) //資函札鰍醜泣撹孔
		{
			if (*myRButtonClickFlag) //泣似撹孔
			{
				myMouseFloat = true;
				myRButtonPress = false;
				myRButtonClickFlag = false;
				CONTORL_SendMessageToUI(MfxControl_Message_RButtonClick, wParam, lParam);
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


MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetTitle(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock(this);
	myTitle = *(MfxStrW*)lParam;
	if (myTitleWords)
	{
		myTitleWords->SetText(myTitle);
	}
	return RFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
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

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetTitleWords(WPARAM wParam, LPARAM lParam)
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