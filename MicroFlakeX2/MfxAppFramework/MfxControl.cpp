#include "pch.h"
#include "MfxAppFramework.h"

void MicroFlakeX::MfxControl::MfxRegMessages()
{
	MfxCodeLock t_CodeLock(this);
	myUnderFloor--;
	myCoverFloor++;

	CONTROL_REG_MSG(MfxUI_Message_SetPaper, MfxControl, __OnSetPaper, myCoverFloor);

	CONTROL_REG_MSG(MfxUI_Message_PaintBackDC, MfxControl, __OnPaintBackDC, myCoverFloor);
	CONTROL_REG_MSG(MfxUI_Message_PaintMaskDC, MfxControl, __OnPaintMaskDC, myCoverFloor);

	CONTROL_REG_MSG(WM_SIZE, MfxControl, __OnUISize, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_Size, MfxControl, __OnSize, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_Point, MfxControl, __OnPoint, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_PercentSize, MfxControl, __OnPercentSize, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_PercentPoint, MfxControl, __OnPercentPoint, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_SetFloor, MfxControl, __OnSetFloor, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_ResetRect, MfxControl, __OnResetRect, myCoverFloor);
	CONTROL_REG_MSG(MfxUI_Message_ResetPercentRect, MfxControl, __OnResetPercentRect, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_ResetPercentRect, MfxControl, __OnResetPercentRect, myCoverFloor);

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
	MfxCodeLock t_CodeLock(this);
	myUnderFloor = 0;
	myCoverFloor = 0;

	myWnd = NULL;
	myUI = nullptr;

	myFloor = 66;

	myTitle = myType = L"MfxControl";

	myPercentRect_Check = false;;
	myBackDC = nullptr;
	myMaskDC = nullptr;

	myMouseFloat = false;
	myLButtonClickFlag = false;
	myLButtonPress = false;
	myRButtonClickFlag = false;
	myRButtonPress = false;
	myRButtonMoveFlag = false;
	myLButtonMoveFlag = false;

	myBackImage = new MfxImage;
	myMaskImage = nullptr;
	myTitleWords = new MfxWords;

	myBackImage->SetRect(myRect);
	myBackImage->FromColor(GdipColor(60, 169, 169, 169));

	myTitleWords->SetRect(myRect);
	myTitleWords->SetText(L"MfxControl");
	myTitleWords->SetFontStyle(MfxFontStyle_Bold);
	myTitleWords->SetTextColor(GdipColor::Aquamarine);
}

MicroFlakeX::MfxControl::MfxControl()
{
	MfxCodeLock t_CodeLock(this);
	myRect = GdipRect(100, 100, 128, 128);
	MfxControlInitData();
	MfxRegMessages();
}

MicroFlakeX::MfxControl::~MfxControl()
{
	MfxCodeLock t_CodeLock(this);
	if (myUI)
	{
		myUI->ProcMessage(MfxUI_Message_ControlRemove, (WPARAM)this, NULL);
	}
	delete myBackImage;
	myBackImage = nullptr;
	delete myMaskImage;
	myMaskImage = nullptr;
	delete myTitleWords;
	myTitleWords = nullptr;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::ProcMessage(MfxMsg message, WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	MfxReturn t_Ret = MfxFail;

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
	MfxCodeLock t_CodeLock(this);
	*ret = myUI;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetType(MfxStrW* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = myType;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetTitle(MfxStrW* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = myTitle;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetFloor(MfxFloor* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = myFloor;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetRect(GdipRect* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = myRect;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetSize(GdipSize* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = GdipSize(myRect.Width, myRect.Height);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetPoint(GdipPoint* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = GdipPoint(myRect.X, myRect.Y);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetPercentRect(GdipRect* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = myPercentRect;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetPercentSize(GdipSize* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = GdipSize(myPercentRect.Width, myPercentRect.Height);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetPercentPoint(GdipPoint* ret)
{
	MfxCodeLock t_CodeLock(this);
	*ret = GdipPoint(myPercentRect.X, myPercentRect.Y);
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetTitle(MfxStrW set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetTitle, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetFloor(MfxFloor floor)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetFloor, NULL, floor);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetRect(GdipRect set)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize t_Size(set.Width, set.Height);
	GdipPoint t_Point(set.X, set.Y);

	ProcMessage(MfxControl_Message_Size, NULL, (LPARAM)&t_Size);
	ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&t_Point);


	if (myUI)
	{
		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetPercentRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetSize(GdipSize set)
{
	MfxCodeLock t_CodeLock(this);
	ProcMessage(MfxControl_Message_Size, NULL, (LPARAM)&set);

	if (myUI)
	{
		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetPercentRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetPoint(GdipPoint set)
{
	MfxCodeLock t_CodeLock(this);
	ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&set);

	if (myUI)
	{
		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetPercentRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetPercentRect(GdipRect set)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize t_Size(set.Width, set.Height);
	GdipPoint t_Point(set.X, set.Y);

	ProcMessage(MfxControl_Message_PercentSize, NULL, (LPARAM)&t_Size);
	ProcMessage(MfxControl_Message_PercentPoint, NULL, (LPARAM)&t_Point);

	if (myUI)
	{
		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetPercentSize(GdipSize set)
{
	MfxCodeLock t_CodeLock(this);
	ProcMessage(MfxControl_Message_PercentSize, NULL, (LPARAM)&set);

	if (myUI)
	{
		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetPercentPoint(GdipPoint set)
{
	MfxCodeLock t_CodeLock(this);
	ProcMessage(MfxControl_Message_PercentPoint, NULL, (LPARAM)&set);

	if (myUI)
	{
		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));
	}
	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::OpenLButtonMove()
{
	MfxCodeLock t_CodeLock(this);
	myLButtonMoveFlag = true;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::CloseLButtonMove()
{
	MfxCodeLock t_CodeLock(this);
	myLButtonMoveFlag = false;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::OpenRButtonMove()
{
	MfxCodeLock t_CodeLock(this);
	myRButtonMoveFlag = true;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::CloseRButtonMove()
{
	MfxCodeLock t_CodeLock(this);
	myRButtonMoveFlag = false;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetBackImage(MfxImage** ret)
{
	MfxCodeLock t_CodeLock(this);
	return myBackImage ? myBackImage->Clone(ret) : MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetMaskImage(MfxImage** ret)
{
	MfxCodeLock t_CodeLock(this);
	return myMaskImage ? myMaskImage->Clone(ret) : MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::GetTitleWords(MfxWords** ret)
{
	MfxCodeLock t_CodeLock(this);
	return myTitleWords ? myTitleWords->Clone(ret) : MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetBackColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetBackColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetMaskColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetMaskColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetBackImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetBackImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetMaskImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetMaskImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::SetTitleWords(MfxWords* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxControl_Message_SetTitleWords, NULL, (LPARAM)set);
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::RemoveMessage(MfxMsg message, MfxStrW name)
{
	MfxCodeLock t_CodeLock(this);
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter != myMessageMap.end())
	{
		for (auto i = t_Iter->second->begin(); i != t_Iter->second->end(); i++)
		{
			if ((*i)->myName == name)
			{
				t_Iter->second->erase(i);
				return MfxFine;
			}
		}
	}
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::InsertMessage(MfxMsg message, MfxControl_MessageMap_Value* msgValue)
{
	MfxCodeLock t_CodeLock(this);
	auto t_Iter = myMessageMap.find(message);
	if (t_Iter == myMessageMap.end())
	{
		auto t_AddVector = new MfxControl_MessageMap_Vector;
		t_Iter = myMessageMap.insert(MfxControl_MessageMap_elem(message, t_AddVector)).first;
	}

	t_Iter->second->push_back(msgValue);
	std::sort(t_Iter->second->begin(), t_Iter->second->end(), __MicroFlakeX::MfxControlMessageFloorCompare);

	return MfxFine;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetPaper(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	MfxUI_Paper_Value* t_PaperValue = (MfxUI_Paper_Value*)lParam;
	myUI = t_PaperValue->myUI;
	myWnd = t_PaperValue->myWnd;
	myBackDC = t_PaperValue->myBackDC;
	myMaskDC = t_PaperValue->myMaskDC;

	if (myBackImage)
	{
		myBackImage->SetDC(myBackDC);
	}
	if (myTitleWords)
	{
		myTitleWords->SetDC(myBackDC);
	}
	if (myMaskImage)
	{
		myMaskImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPaintBackDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myBackImage)
	{
		myBackImage->Draw();
	}
	if (myTitleWords)
	{
		myTitleWords->Draw();
	}
	if (myMaskImage)
	{
		myMaskImage->Draw();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPaintMaskDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	return MfxFail;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnUISize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myUI->ChickPercentRect() == MfxFine)
	{
		ProcMessage(MfxControl_Message_ResetRect, wParam, lParam);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize* t_Size = (GdipSize*)lParam;

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

	myRect.Width = t_Size->Width;
	myRect.Height = t_Size->Height;

	PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPoint(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint* t_Point = (GdipPoint*)lParam;

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
	myRect.X = t_Point->X;
	myRect.Y = t_Point->Y;

	PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPercentSize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize* t_Size = (GdipSize*)lParam;

	myPercentRect.Width = t_Size->Width;
	myPercentRect.Height = t_Size->Height;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnPercentPoint(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint* t_Point = (GdipPoint*)lParam;

	myPercentRect.X = t_Point->X;
	myPercentRect.Y = t_Point->Y;

	//std::cout << "__OnPercentPoint:" << t_Point->X << t_Point->Y << std::endl;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetFloor(WPARAM wParam, LPARAM lParam)
{
	myFloor = lParam;
	if (myUI)
	{
		myUI->ProcMessage(MfxControl_Message_ControlFloorChange, NULL, NULL);
		PostMessageW(myWnd, WM_PAINT, NULL, NULL);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnResetRect(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize t_UISize(LOWORD(lParam), HIWORD(lParam));
	//std::cout << "t_UISize:" << t_UISize.Width << "|" << t_UISize.Height << std::endl;

	GdipRect t_RestRect(
		((__int64)myPercentRect.X * t_UISize.Width) / 100000.00,
		((__int64)myPercentRect.Y * t_UISize.Height) / 100000.00,
		((__int64)myPercentRect.Width * t_UISize.Width) / 100000.00,
		((__int64)myPercentRect.Height * t_UISize.Height) / 100000.00
	);

	GdipSize t_RestSize(t_RestRect.Width, t_RestRect.Height);
	GdipPoint t_RestPoint(t_RestRect.X, t_RestRect.Y);

	ProcMessage(MfxControl_Message_Size, NULL, (LPARAM)&t_RestSize);
	ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&t_RestPoint);
	//std::cout << "myRect: " << myRect.X << "|" << myRect.Y << "|" << myRect.Height << "|" << myRect.Width << "|" << std::endl;
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnResetPercentRect(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize t_UISize(LOWORD(lParam), HIWORD(lParam));
	//std::cout << "t_UISize:" << t_UISize.Width << "|" << t_UISize.Height << std::endl;

	GdipRect t_ResetPercentRect(
		(myRect.X * 100000.00) / t_UISize.Width,
		(myRect.Y * 100000.00) / t_UISize.Height,
		(myRect.Width * 100000.00) / t_UISize.Width,
		(myRect.Height * 100000.00) / t_UISize.Height
	);

	GdipSize t_ResetPercentSize(t_ResetPercentRect.Width, t_ResetPercentRect.Height);
	GdipPoint t_ResetPercentPoint(t_ResetPercentRect.X, t_ResetPercentRect.Y);

	ProcMessage(MfxControl_Message_PercentSize, NULL, (LPARAM)&t_ResetPercentSize);
	ProcMessage(MfxControl_Message_PercentPoint, NULL, (LPARAM)&t_ResetPercentPoint);

	//std::cout << "myPercentRect: " << myPercentRect.X << "|" << myPercentRect.Y << "|" << myPercentRect.Height << "|" << myPercentRect.Width << "|" << std::endl;
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
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
		GdipPoint nowPos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		GdipRect t_Rect = myRect;
		t_Rect.Offset(nowPos - myButtonMoveBegin);

		GdipPoint t_Point(t_Rect.X, t_Rect.Y);

		ProcMessage(MfxControl_Message_Point, NULL, (LPARAM)&t_Point);

		GdipSize t_UISize;
		myUI->GetSize(&t_UISize);
		ProcMessage(MfxControl_Message_ResetPercentRect, NULL, MAKELONG(t_UISize.Width, t_UISize.Height));

		myButtonMoveBegin = nowPos;
	}
	else
	{
		if (myUI)
		{
			myUI->UnLockMutexFocus();
		}
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
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
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
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
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
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
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint mousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
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
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetTitle(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	myTitle = *(MfxStrW*)lParam;
	if (myTitleWords)
	{
		myTitleWords->SetText(myTitle);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetBackColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipColor* t_Set = (GdipColor*)lParam;
	if (myBackImage)
	{
		myBackImage->FromColor(*t_Set);
	}
	else
	{
		myBackImage = new MfxImage;
		myBackImage->SetRect(myRect);
		myBackImage->FromColor(*t_Set);
		myBackImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetMaskColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipColor* t_Set = (GdipColor*)lParam;
	if (myMaskImage)
	{
		myMaskImage->FromColor(*t_Set);
	}
	else
	{
		myMaskImage = new MfxImage;
		myMaskImage->SetRect(myRect);
		myMaskImage->FromColor(*t_Set);
		myMaskImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetBackImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	MfxImage* t_Set = (MfxImage*)lParam;
	delete myBackImage;
	myBackImage = nullptr;
	if (t_Set)
	{
		(t_Set)->Clone(&myBackImage);
		myBackImage->SetRect(myRect);
		myBackImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetMaskImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	MfxImage* t_Set = (MfxImage*)lParam;
	delete myMaskImage;
	myMaskImage = nullptr;
	if (t_Set)
	{
		(t_Set)->Clone(&myMaskImage);
		myMaskImage->SetRect(myRect);
		myMaskImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxControl::__OnSetTitleWords(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	MfxWords* t_Set = (MfxWords*)lParam;
	delete myTitleWords;
	myTitleWords = nullptr;
	if (t_Set)
	{
		(t_Set)->Clone(&myTitleWords);
		myTitleWords->SetRect(myRect);
		myTitleWords->GetText(&myTitle);
		myTitleWords->SetDC(myBackDC);
	}
	return MfxFine;
}

