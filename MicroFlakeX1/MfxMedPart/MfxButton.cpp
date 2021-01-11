#include "pch.h"
#include "MfxButton.h"

void MicroFlakeX::MfxButton::Reg()
{
	/**/
	RegMessage(MFXUIEVENT_DRAWBUFFDC, (MFXCONTROL_FUNC)&MfxButton::OnDrawBufferDC);

	RegMessage(WM_MOUSEMOVE, (MFXCONTROL_FUNC)&MfxButton::OnMouseMove);

	RegMessage(WM_LBUTTONDOWN, (MFXCONTROL_FUNC)&MfxButton::OnLButtonDown);
	RegMessage(WM_LBUTTONUP, (MFXCONTROL_FUNC)&MfxButton::OnLButtonUp);

	RegMessage(WM_RBUTTONDOWN, (MFXCONTROL_FUNC)&MfxButton::OnRButtonDown);
	RegMessage(WM_RBUTTONUP, (MFXCONTROL_FUNC)&MfxButton::OnRButtonUp);
	/**/
}

void MicroFlakeX::MfxButton::InitData()
{
	/**/
	myFloatUnderImageFlag = false;
	myFloatCoverImageFlag = false;

	myLButtonPressImageFlag = false;
	myRButtonPressImageFlag = false;

	myFloatUnderImage = nullptr;
	myFloatCoverImage = nullptr;

	myLButtonPressImage = nullptr;
	myRButtonPressImage = nullptr;
	/**/

	/**/
	myFloatCoverImage = new MfxImage(myBuffGraphics, Gdiplus::Color(60, 100, 255, 100), myRect);
	myLButtonPressImage = new MfxImage(myBuffGraphics, Gdiplus::Color(60, 255, 100, 100), myRect);
	myRButtonPressImage = new MfxImage(myBuffGraphics, Gdiplus::Color(60, 100, 100, 255), myRect);
	/**/
}

MicroFlakeX::MfxButton::MfxButton(MfxUI* father)
	: MfxControl(father)
{
	Reg();
	InitData();
}

MicroFlakeX::MfxButton::MfxButton(MfxUI* father, Gdiplus::Rect rect)
	: MfxControl(father, rect)
{	
	Reg();
	InitData();
}

MicroFlakeX::MfxButton::MfxButton(MfxUI* father, std::wstring title)
	: MfxControl(father, title)
{
	Reg();
	InitData();
}

MicroFlakeX::MfxButton::MfxButton(MfxUI* father, Gdiplus::Rect rect, std::wstring title)
	: MfxControl(father, rect, title)
{
	Reg();
	InitData();
}

MicroFlakeX::MfxButton::~MfxButton()
{
	/**/
	if (!myFloatUnderImageFlag)
		delete myFloatUnderImage;
	if (!myFloatCoverImageFlag)
		delete myFloatCoverImage;

	if (!myLButtonPressImageFlag)
		delete myLButtonPressImage;
	if (!myRButtonPressImageFlag)
		delete myRButtonPressImage;
	/**/
}

void MicroFlakeX::MfxButton::SetRect(Gdiplus::Rect set)
{
	SetSize(Gdiplus::Size(set.Width, set.Height));
	SetPoint(Gdiplus::Point(set.X, set.Y));
}

void MicroFlakeX::MfxButton::SetSize(Gdiplus::Size set)
{
	MfxControl::SetSize(set);
	if (myFloatUnderImage)
		myFloatUnderImage->SetSize(set);
	if (myFloatCoverImage)
		myFloatCoverImage->SetSize(set);

	if (myLButtonPressImage)
		myLButtonPressImage->SetSize(set);
	if (myRButtonPressImage)
		myRButtonPressImage->SetSize(set);
}

void MicroFlakeX::MfxButton::SetPoint(Gdiplus::Point set)
{
	MfxControl::SetPoint(set);
	if (myFloatUnderImage)
		myFloatUnderImage->SetPoint(set);
	if (myFloatCoverImage)
		myFloatCoverImage->SetPoint(set);

	if (myLButtonPressImage)
		myLButtonPressImage->SetPoint(set);
	if (myRButtonPressImage)
		myRButtonPressImage->SetPoint(set);
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetFloatUnderImage(MfxImage* set)
{
	MfxImage* retImage = myFloatUnderImage;
	myFloatUnderImageFlag = true;
	myFloatUnderImage = set;
	myFloatUnderImage->SetRect(myRect);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetFloatUnderImage()
{
	return myFloatUnderImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetFloatCoverImage(MfxImage* set)
{
	MfxImage* retImage = myFloatCoverImage;
	myFloatCoverImageFlag = true;
	myFloatCoverImage = set;
	myFloatCoverImage->SetRect(myRect);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetFloatCoverImage()
{
	return myFloatCoverImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetLButtonPressImage(MfxImage* set)
{
	MfxImage* retImage = myLButtonPressImage;
	myLButtonPressImageFlag = true;
	myLButtonPressImage = set;
	myLButtonPressImage->SetRect(myRect);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetLButtonPressImage()
{
	return myLButtonPressImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetRButtonPressImage(MfxImage* set)
{
	MfxImage* retImage = myRButtonPressImage;
	myRButtonPressImageFlag = true;
	myRButtonPressImage = set;
	myRButtonPressImage->SetRect(myRect);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetRButtonPressImage()
{
	return myRButtonPressImage;
}

/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！和中議旗鷹頁潮範�贄Α�！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */
/* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！ */

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnDrawBufferDC(WPARAM wParam, LPARAM lParam)
{
	if (myMouseFloat && myFloatUnderImage)
		myFloatUnderImage->Draw();

	MfxControl::MfxDefOnDrawBuffDC(wParam, lParam); //廾蔑議圭隈距喘

	if (myMouseFloat && myFloatCoverImage)
		myFloatCoverImage->Draw();

	if (myLButtonPress && myLButtonPressImage)
		myLButtonPressImage->Draw();
	if (myRButtonPress && myRButtonPressImage)
		myRButtonPressImage->Draw();

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	
	MfxRecvDefMessage(WM_MOUSEMOVE, wParam, lParam);
	if (myRButtonPress)
	{
		Gdiplus::Point nowPos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		myRect.Offset(nowPos - myMoveBegin);
		myMoveBegin = nowPos;
		SetRect(myRect);
	}
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxRecvDefMessage(WM_LBUTTONDOWN, wParam, lParam);
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxRecvDefMessage(WM_LBUTTONUP, wParam, lParam);
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxRecvDefMessage(WM_RBUTTONDOWN, wParam, lParam);
	myMoveBegin = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxRecvDefMessage(WM_RBUTTONUP, wParam, lParam);
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}