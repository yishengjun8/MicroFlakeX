#include "pch.h"
#include "MfxButton.h"

MicroFlakeX::MfxButton::MfxButton(MfxUI* father, Gdiplus::Rect value)
	: MfxControl(father, value)
{	
	/**/
	RegMessage(WM_PAINT, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnPaint);

	RegMessage(WM_MOUSEMOVE, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnMouseMove);

	RegMessage(WM_LBUTTONDOWN, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnLButtonDown);
	RegMessage(WM_LBUTTONUP, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnLButtonUp);

	RegMessage(WM_RBUTTONDOWN, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnRButtonDown);
	RegMessage(WM_RBUTTONUP, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnRButtonUp);
	/**/

	/**/
	myBackImageFlag = false;
	myMidWordsFlag = false;
	myMaskImageFlag = false;

	myFloatImageFlag = false;

	myLButtonPressImageFlag = false;
	myRButtonPressImageFlag = false;

	myBackImage = nullptr;
	myMidWords = nullptr;
	myMaskImage = nullptr;

	myFloatImage = nullptr;

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

	myFloatImage = new MfxImage(myGraphics, Gdiplus::Color(60, 100, 255, 100));
	myFloatImage->SetImageRect(myRect);

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

	if (!myFloatImageFlag)
		delete myFloatImage;

	if (!myLButtonPressImageFlag)
		delete myLButtonPressImage;
	if (!myRButtonPressImageFlag)
		delete myRButtonPressImage;
	/**/
}

void MicroFlakeX::MfxButton::SetRect(Gdiplus::Rect set)
{
	if (myBackImage)
		myBackImage->SetImageRect(set);
	if (myMidWords)
		myMidWords->SetRect(set);
	if (myMaskImage)
		myMaskImage->SetImageRect(set);

	if (myFloatImage)
		myFloatImage->SetImageRect(set);

	if (myLButtonPressImage)
		myLButtonPressImage->SetImageRect(set);
	if (myRButtonPressImage)
		myRButtonPressImage-> SetImageRect(set);
}

void MicroFlakeX::MfxButton::SetSize(Gdiplus::Size set)
{
}

void MicroFlakeX::MfxButton::SetPoint(Gdiplus::Point set)
{
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetBackImage(MfxImage* set)
{
	MfxImage* retImage = myBackImage;
	myBackImageFlag = true;
	myBackImage = set;
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
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetMaskImage()
{
	return myMaskImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetFloatImage(MfxImage* set)
{
	MfxImage* retImage = myFloatImage;
	myFloatImageFlag = true;
	myFloatImage = set;
	return retImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::GetFloatImage()
{
	return myFloatImage;
}

MicroFlakeX::MfxImage* MicroFlakeX::MfxButton::SetLButtonPressImage(MfxImage* set)
{
	MfxImage* retImage = myLButtonPressImage;
	myLButtonPressImageFlag = true;
	myLButtonPressImage = set;
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

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnPaint(WPARAM wParam, LPARAM lParam)
{
	if (myBackImage)
		myBackImage->Draw();
	if (myMidWords)
		myMidWords->Draw();
	if (myMaskImage)
		myMaskImage->Draw();

	if (myFloat && myFloatImage)
		myFloatImage->Draw();

	if (myLButtonPress && myLButtonPressImage)
		myLButtonPressImage->Draw();
	if (myRButtonPress && myRButtonPressImage)
		myRButtonPressImage->Draw();

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	
	MfxRecDefMessage(WM_MOUSEMOVE, wParam, lParam);
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
	MfxRecDefMessage(WM_LBUTTONDOWN, wParam, lParam);
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxRecDefMessage(WM_LBUTTONUP, wParam, lParam);
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	MfxRecDefMessage(WM_RBUTTONDOWN, wParam, lParam);
	myMoveBegin = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	MfxRecDefMessage(WM_RBUTTONUP, wParam, lParam);
	return PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
}