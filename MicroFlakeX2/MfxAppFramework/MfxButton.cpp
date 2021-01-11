#include "pch.h"
#include "MfxButton.h"

void MicroFlakeX::MfxButton::RegDefFunc()
{
	MfxCodeLock t_CodeLock(this);
	myUnderFloor--;
	myCoverFloor++;

	CONTROL_REG_MSG(MfxUI_Message_PaintBackDC, MfxButton, OnPaintUnderBackDC, myUnderFloor);
	CONTROL_REG_MSG(MfxUI_Message_PaintMaskDC, MfxButton, OnPaintUnderMaskDC, myUnderFloor);

	CONTROL_REG_MSG(MfxUI_Message_SetPaper, MfxButton, OnSetPaper, myCoverFloor);

	CONTROL_REG_MSG(MfxControl_Message_Size, MfxButton, OnSize, myCoverFloor);
	CONTROL_REG_MSG(MfxControl_Message_Point, MfxButton, OnPoint, myCoverFloor);

	CONTROL_REG_MSG(MfxButton_Message_SetMouseFloatUnderColor, MfxButton, OnSetMouseFloatUnderColor, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetMouseFloatCoverColor, MfxButton, OnSetMouseFloatCoverColor, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetLButtonPressUnderColor, MfxButton, OnSetLButtonPressUnderColor, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetLButtonPressCoverColor, MfxButton, OnSetLButtonPressCoverColor, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetRButtonPressUnderColor, MfxButton, OnSetRButtonPressUnderColor, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetRButtonPressCoverColor, MfxButton, OnSetRButtonPressCoverColor, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetMouseFloatUnderImage, MfxButton, OnSetMouseFloatUnderImage, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetMouseFloatCoverImage, MfxButton, OnSetMouseFloatCoverImage, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetLButtonPressUnderImage, MfxButton, OnSetLButtonPressUnderImage, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetLButtonPressCoverImage, MfxButton, OnSetLButtonPressCoverImage, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetRButtonPressUnderImage, MfxButton, OnSetRButtonPressUnderImage, myCoverFloor);
	CONTROL_REG_MSG(MfxButton_Message_SetRButtonPressCoverImage, MfxButton, OnSetRButtonPressCoverImage, myCoverFloor);
}

void MicroFlakeX::MfxButton::MfxButtonInitData()
{
	MfxCodeLock t_CodeLock(this);
	myMouseFloatUnderImage = nullptr;
	myMouseFloatCoverImage = nullptr;

	myLButtonPressUnderImage = nullptr;
	myLButtonPressCoverImage = nullptr;

	myRButtonPressUnderImage = nullptr;
	myRButtonPressCoverImage = nullptr;

	myMouseFloatUnderImage = new MfxImage;
	myLButtonPressUnderImage = new MfxImage;
	myRButtonPressUnderImage = new MfxImage;

	myMouseFloatUnderImage->SetRect(myRect);
	myLButtonPressUnderImage->SetRect(myRect);
	myRButtonPressUnderImage->SetRect(myRect);

	myMouseFloatUnderImage->FromColor(GdipColor(80, 0, 191, 255));
	myLButtonPressUnderImage->FromColor(GdipColor(80, 0, 90, 125));
	myRButtonPressUnderImage->FromColor(GdipColor(40, 255, 255, 100));
}

MicroFlakeX::MfxButton::MfxButton() : MfxControl()
{
	MfxCodeLock t_CodeLock(this);
	RegDefFunc();
	MfxButtonInitData();
}

MicroFlakeX::MfxButton::~MfxButton()
{
	MfxCodeLock t_CodeLock(this);
	delete myMouseFloatUnderImage;
	myMouseFloatUnderImage = nullptr;
	delete myMouseFloatCoverImage;
	myMouseFloatCoverImage = nullptr;

	delete myLButtonPressUnderImage;
	myLButtonPressUnderImage = nullptr;
	delete myLButtonPressCoverImage;
	myLButtonPressCoverImage = nullptr;

	delete myRButtonPressUnderImage;
	myRButtonPressUnderImage = nullptr;
	delete myRButtonPressCoverImage;
	myRButtonPressCoverImage = nullptr;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::GetMouseFloatUnderImage(MfxImage** ret)
{
	if (myMouseFloatUnderImage)
	{
		myMouseFloatUnderImage->Clone(ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::GetMouseFloatCoverImage(MfxImage** ret)
{
	if (myMouseFloatCoverImage)
	{
		myMouseFloatCoverImage->Clone(ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::GetLButtonPressUnderImage(MfxImage** ret)
{
	if (myLButtonPressUnderImage)
	{
		myLButtonPressUnderImage->Clone(ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::GetLButtonPressCoverImage(MfxImage** ret)
{
	if (myLButtonPressCoverImage)
	{
		myLButtonPressCoverImage->Clone(ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::GetRButtonPressUnderImage(MfxImage** ret)
{
	if (myRButtonPressUnderImage)
	{
		myRButtonPressUnderImage->Clone(ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::GetRButtonPressCoverImage(MfxImage** ret)
{
	if (myRButtonPressCoverImage)
	{
		myRButtonPressCoverImage->Clone(ret);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetMouseFloatUnderColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetMouseFloatUnderColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetMouseFloatCoverColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetMouseFloatCoverColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetLButtonPressUnderColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetLButtonPressUnderColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetLButtonPressCoverColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetLButtonPressCoverColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetRButtonPressUnderColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetRButtonPressUnderColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetRButtonPressCoverColor(GdipColor set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetRButtonPressCoverColor, NULL, (LPARAM)&set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetMouseFloatUnderImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetMouseFloatUnderImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetMouseFloatCoverImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetMouseFloatCoverImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetLButtonPressUnderImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetLButtonPressUnderImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetLButtonPressCoverImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetLButtonPressCoverImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetRButtonPressUnderImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetRButtonPressUnderImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::SetRButtonPressCoverImage(MfxImage* set)
{
	MfxCodeLock t_CodeLock(this);
	return ProcMessage(MfxButton_Message_SetRButtonPressCoverImage, NULL, (LPARAM)set);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnPaintUnderBackDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (*myMouseFloat && myMouseFloatUnderImage)
	{
		myMouseFloatUnderImage->Draw();
	}
	if (*myLButtonPress && myLButtonPressUnderImage)
	{
		myLButtonPressUnderImage->Draw();
	}
	if (*myRButtonPress && myRButtonPressUnderImage)
	{
		myRButtonPressUnderImage->Draw();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnPaintCoverBackDC(WPARAM wParam, LPARAM lParam)
{
	if (*myMouseFloat && myMouseFloatCoverImage)
	{
		myMouseFloatCoverImage->Draw();
	}
	if (*myLButtonPress && myLButtonPressCoverImage)
	{
		myLButtonPressCoverImage->Draw();
	}
	if (*myRButtonPress && myRButtonPressCoverImage)
	{
		myRButtonPressCoverImage->Draw();
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnPaintUnderMaskDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnPaintCoverMaskDC(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetPaper(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myMouseFloatUnderImage)
	{
		myMouseFloatUnderImage->SetDC(myBackDC);
	}
	if (myMouseFloatCoverImage)
	{
		myMouseFloatCoverImage->SetDC(myBackDC);
	}
	if (myLButtonPressUnderImage)
	{
		myLButtonPressUnderImage->SetDC(myBackDC);
	}
	if (myLButtonPressCoverImage)
	{
		myLButtonPressCoverImage->SetDC(myBackDC);
	}
	if (myRButtonPressUnderImage)
	{
		myRButtonPressUnderImage->SetDC(myBackDC);
	}
	if (myRButtonPressCoverImage)
	{
		myRButtonPressCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSize(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipSize* t_Size = (GdipSize*)lParam;

	if (myMouseFloatUnderImage)
	{
		myMouseFloatUnderImage->SetSize(*t_Size);
	}
	if (myMouseFloatCoverImage)
	{
		myMouseFloatCoverImage->SetSize(*t_Size);
	}

	if (myLButtonPressUnderImage)
	{
		myLButtonPressUnderImage->SetSize(*t_Size);
	}
	if (myLButtonPressCoverImage)
	{
		myLButtonPressCoverImage->SetSize(*t_Size);
	}

	if (myRButtonPressUnderImage)
	{
		myRButtonPressUnderImage->SetSize(*t_Size);
	}
	if (myRButtonPressCoverImage)
	{
		myRButtonPressCoverImage->SetSize(*t_Size);
	}

	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnPoint(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	GdipPoint* t_Point = (GdipPoint*)lParam;

	if (myMouseFloatUnderImage)
	{
		myMouseFloatUnderImage->SetPoint(*t_Point);
	}
	if (myMouseFloatCoverImage)
	{
		myMouseFloatCoverImage->SetPoint(*t_Point);
	}

	if (myLButtonPressUnderImage)
	{
		myLButtonPressUnderImage->SetPoint(*t_Point);
	}
	if (myLButtonPressCoverImage)
	{
		myLButtonPressCoverImage->SetPoint(*t_Point);
	}

	if (myRButtonPressUnderImage)
	{
		myRButtonPressUnderImage->SetPoint(*t_Point);
	}
	if (myRButtonPressCoverImage)
	{
		myRButtonPressCoverImage->SetPoint(*t_Point);
	}
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetMouseFloatUnderColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myMouseFloatUnderImage)
	{
		myMouseFloatUnderImage->FromColor(*(GdipColor*)lParam);
	}
	else
	{
		myMouseFloatUnderImage = new MfxImage;
		myMouseFloatUnderImage->SetRect(myRect);
		myMouseFloatUnderImage->FromColor(*(GdipColor*)lParam);
		myMouseFloatUnderImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetMouseFloatCoverColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myMouseFloatCoverImage)
	{
		myMouseFloatCoverImage->FromColor(*(GdipColor*)lParam);
	}
	else
	{
		myMouseFloatCoverImage = new MfxImage;
		myMouseFloatCoverImage->SetRect(myRect);
		myMouseFloatCoverImage->FromColor(*(GdipColor*)lParam);
		myMouseFloatCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetLButtonPressUnderColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myLButtonPressUnderImage)
	{
		myLButtonPressUnderImage->FromColor(*(GdipColor*)lParam);
	}
	else
	{
		myLButtonPressUnderImage = new MfxImage;
		myLButtonPressUnderImage->SetRect(myRect);
		myLButtonPressUnderImage->FromColor(*(GdipColor*)lParam);
		myLButtonPressUnderImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetLButtonPressCoverColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myLButtonPressCoverImage)
	{
		myLButtonPressCoverImage->FromColor(*(GdipColor*)lParam);
	}
	else
	{
		myLButtonPressCoverImage = new MfxImage;
		myLButtonPressCoverImage->SetRect(myRect);
		myLButtonPressCoverImage->FromColor(*(GdipColor*)lParam);
		myLButtonPressCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetRButtonPressUnderColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myRButtonPressUnderImage)
	{
		myRButtonPressUnderImage->FromColor(*(GdipColor*)lParam);
	}
	else
	{
		myRButtonPressUnderImage = new MfxImage;
		myRButtonPressUnderImage->SetRect(myRect);
		myRButtonPressUnderImage->FromColor(*(GdipColor*)lParam);
		myRButtonPressUnderImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetRButtonPressCoverColor(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	if (myRButtonPressCoverImage)
	{
		myRButtonPressCoverImage->FromColor(*(GdipColor*)lParam);
	}
	else
	{
		myRButtonPressCoverImage = new MfxImage;
		myRButtonPressCoverImage->SetRect(myRect);
		myRButtonPressCoverImage->FromColor(*(GdipColor*)lParam);
		myRButtonPressCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetMouseFloatUnderImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	delete myMouseFloatUnderImage;
	myMouseFloatUnderImage = nullptr;

	if (lParam)
	{
		((MfxImage*)lParam)->Clone(&myMouseFloatUnderImage);
		myMouseFloatUnderImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
		myMouseFloatUnderImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetMouseFloatCoverImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	delete myMouseFloatCoverImage;
	myMouseFloatCoverImage = nullptr;

	if (lParam)
	{
		((MfxImage*)lParam)->Clone(&myMouseFloatCoverImage);
		myMouseFloatCoverImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
		myMouseFloatCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetLButtonPressUnderImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	delete myLButtonPressUnderImage;
	myLButtonPressUnderImage = nullptr;

	if (lParam)
	{
		((MfxImage*)lParam)->Clone(&myLButtonPressUnderImage);
		myLButtonPressUnderImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
		myLButtonPressUnderImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetLButtonPressCoverImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	delete myLButtonPressCoverImage;
	myLButtonPressCoverImage = nullptr;

	if (lParam)
	{
		((MfxImage*)lParam)->Clone(&myLButtonPressCoverImage);
		myLButtonPressCoverImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
		myLButtonPressCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetRButtonPressUnderImage(WPARAM wParam, LPARAM lParam)
{
	MfxCodeLock t_CodeLock(this);
	delete myRButtonPressUnderImage;
	myRButtonPressUnderImage = nullptr;

	if (lParam)
	{
		((MfxImage*)lParam)->Clone(&myRButtonPressUnderImage);
		myRButtonPressUnderImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
		myRButtonPressUnderImage->SetDC(myBackDC);
	}
	return MfxFine;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxButton::OnSetRButtonPressCoverImage(WPARAM wParam, LPARAM lParam)
{
	delete myRButtonPressCoverImage;
	myRButtonPressCoverImage = nullptr;

	if (lParam)
	{
		((MfxImage*)lParam)->Clone(&myRButtonPressCoverImage);
		myRButtonPressCoverImage->SetRect(GdipRect(0, 0, myRect.Width, myRect.Height));
		myRButtonPressCoverImage->SetDC(myBackDC);
	}
	return MfxFine;
}