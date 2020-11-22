#include "pch.h"
#include "MfxButton.h"

MicroFlakeX::MfxButton::MfxButton(MfxUI* father, Gdiplus::Rect value)
	: MfxControl(father, value)
{	
	/**/
	RegMessage(MFXUIEVENT_DRAWBUFFERDC, (MFXCONTROL_FUNC)&MfxButton::OnDrawBufferDC);

	RegMessage(WM_MOUSEMOVE, (MFXCONTROL_FUNC)&MfxButton::OnMouseMove);

	RegMessage(WM_LBUTTONDOWN, (MFXCONTROL_FUNC)&MfxButton::OnLButtonDown);
	RegMessage(WM_LBUTTONUP, (MFXCONTROL_FUNC)&MfxButton::OnLButtonUp);

	RegMessage(WM_RBUTTONDOWN, (MFXCONTROL_FUNC)&MfxButton::OnRButtonDown);
	RegMessage(WM_RBUTTONUP, (MFXCONTROL_FUNC)&MfxButton::OnRButtonUp);
	/**/

	/**/
	myBackImageFlag = false;
	myMidWordsFlag = false;
	myMaskImageFlag = false;

	myFloatUnderImageFlag = false;
	myFloatCoverImageFlag = false;

	myLButtonPressImageFlag = false;
	myRButtonPressImageFlag = false;

	myBackImage = nullptr;
	myMidWords = nullptr;
	myMaskImage = nullptr;

	myFloatUnderImage = nullptr;
	myFloatCoverImage = nullptr;

	myLButtonPressImage = nullptr;
	myRButtonPressImage = nullptr;
	/**/

	/**/
	myBackImage = new MfxImage(myGraphics, Gdiplus::Color::DarkGray);
	myBackImage->SetImageRect(myRect);
	myMidWords = new MfxWords(myGraphics);
	myMidWords->SetWords(L"MfxButton");
	myMidWords->SetFormat(MFXWORDS_FORMATX_CENTER);
	myMidWords->SetRect(myRect);

	myFloatCoverImage = new MfxImage(myGraphics, Gdiplus::Color(60, 100, 255, 100));
	myFloatCoverImage->SetImageRect(myRect);

	myLButtonPressImage = new MfxImage(myGraphics, Gdiplus::Color(60, 255, 100, 100));
	myLButtonPressImage->SetImageRect(myRect);
	myRButtonPressImage = new MfxImage(myGraphics, Gdiplus::Color(60, 100, 100, 255));
	myRButtonPressImage->SetImageRect(myRect);
	/**/
}

MicroFlakeX::MfxButton::~MfxButton()
{
	/**/
	if(!myBackImageFlag)
		delete myBackImage;
	if (!myMidWordsFlag)
		delete myMidWords;
	if (!myMaskImageFlag)
		delete myMaskImage;

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
	myRect.Width = set.Width;
	myRect.Height = set.Height;

	if (myBackImage)
		myBackImage->SetImageSize(set);
	if (myMidWords)
		myMidWords->SetSize(set);
	if (myMaskImage)
		myMaskImage->SetImageSize(set);

	if (myFloatUnderImage)
		myFloatUnderImage->SetImageSize(set);
	if (myFloatCoverImage)
		myFloatCoverImage->SetImageSize(set);

	if (myLButtonPressImage)
		myLButtonPressImage->SetImageSize(set);
	if (myRButtonPressImage)
		myRButtonPressImage->SetImageSize(set);
}

void MicroFlakeX::MfxButton::SetPoint(Gdiplus::Point set)
{
	myRect.X = set.X;
	myRect.Y = set.Y;

	if (myBackImage)
		myBackImage->SetImagePoint(set);
	if (myMidWords)
		myMidWords->SetPoint(set);
	if (myMaskImage)
		myMaskImage->SetImagePoint(set);

	if (myFloatUnderImage)
		myFloatUnderImage->SetImagePoint(set);
	if (myFloatCoverImage)
		myFloatCoverImage->SetImagePoint(set);

	if (myLButtonPressImage)
		myLButtonPressImage->SetImagePoint(set);
	if (myRButtonPressImage)
		myRButtonPressImage->SetImagePoint(set);
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetBackImage(MfxImage* set)
{
	MfxImage* retImage = myBackImage;
	myBackImageFlag = true;
	myBackImage = set;
	myBackImage->SetImageRect(myRect);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetBackImage()
{
	return myBackImage;
}

MicroFlakeX::MfxWords* MicroFlakeX::MfxButton::SetMidWords(MfxWords* set)
{
	MfxWords* retWords = myMidWords;
	myMidWordsFlag = true;
	myMidWords = set;
	myMidWords->SetRect(myRect);
	return retWords;
}

MicroFlakeX::MfxWords* MicroFlakeX::MfxButton::GetMidWords()
{
	return myMidWords;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetMaskImage(MfxImage* set)
{
	MfxImage* retImage = myMaskImage;
	myMaskImageFlag = true;
	myMaskImage = set;
	myMaskImage->SetImageRect(myRect);
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetMaskImage()
{
	return myMaskImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetFloatUnderImage(MfxImage* set)
{
	MfxImage* retImage = myFloatUnderImage;
	myFloatUnderImageFlag = true;
	myFloatUnderImage = set;
	myFloatUnderImage->SetImageRect(myRect);
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
	myFloatCoverImage->SetImageRect(myRect);
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
	myLButtonPressImage->SetImageRect(myRect);
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
	myRButtonPressImage->SetImageRect(myRect);
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

	if (myBackImage)
		myBackImage->Draw();
	if (myMidWords)
		myMidWords->Draw();
	if (myMaskImage)
		myMaskImage->Draw();

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