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
	/**/

	/**/
	myBackImage = nullptr;
	myMidWords = nullptr;
	myMaskImage = nullptr;
	myFloatImage = nullptr;
	myPressImage = nullptr;
	/**/

	/**/
	myBackImage = new MfxImage(myGraphics, Gdiplus::Color::DarkGray);
	myBackImage->SetImageRect(myRect);

	myMidWords = new MfxWords(myGraphics);
	myMidWords->SetWords(L"MfxButton");
	myMidWords->SetFormat(MFXWORDS_FORMATX_CENTER);
	myMidWords->SetRect(myRect);

	myFloatImage = new MfxImage(myGraphics, Gdiplus::Color(60, 100, 150, 255));
	myFloatImage->SetImageRect(myRect);

	myPressImage = new MfxImage(myGraphics, Gdiplus::Color(60, 255, 100, 100));
	myPressImage->SetImageRect(myRect);
	/**/
}

/**/
MicroFlakeX::MfxButton::~MfxButton()
{
	delete myBackImage;
	delete myMidWords;
	delete myMaskImage;

	delete myFloatImage;
	delete myPressImage;
}
/**/
MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnPaint(WPARAM wParam, LPARAM lParam)
{
	if (myBackImage)
		myBackImage->Draw();
	if (myMidWords)
		myMidWords->Draw();
	if (myMaskImage)
		myMaskImage->Draw();
	if (myFloat)
		myFloatImage->Draw();
	if (myPress)
		myPressImage->Draw();

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	MfxRecDefMessage(WM_MOUSEMOVE, wParam, lParam);
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
