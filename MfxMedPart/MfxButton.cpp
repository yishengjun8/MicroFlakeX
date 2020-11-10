#include "pch.h"
#include "MfxButton.h"

MicroFlakeX::MfxButton::MfxButton(MfxUI* getUI, Gdiplus::Rect setRect)
	: MfxControl(getUI, setRect)
{	
	/**/
	RegisterMessage(WM_PAINT, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnPaint);
	RegisterMessage(WM_MOUSEMOVE, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnMouseMove);
	RegisterMessage(WM_LBUTTONDOWN, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnLButtonDown);
	RegisterMessage(WM_LBUTTONUP, (MFXCONTROL_MESSAGE_FUNC)&MfxButton::OnLButtonUp);
	/**/
	myBackImage = nullptr;
	myMidWords = nullptr;
	myMaskImage = nullptr;
	myFloatImage = nullptr;
	myClickImage = nullptr;
	myFloatImageFlag = false;
	myClickImageFlag = false;

	/**/
	myBackImage = new MfxImage(myGraphics);
	myBackImage->LoadPureColor(Gdiplus::Color::DarkGray);
	myBackImage->SetImageRect(myRect);
	myMidWords = new MfxWords(myGraphics);
	myMidWords->SetWords(L"MfxButton");
	myMidWords->SetFormat(MFXWORDS_FORMATX_CENTER);
	myMidWords->SetRect(myRect);

	myFloatImage = new MfxImage(myGraphics);
	myFloatImage->LoadPureColor(Gdiplus::Color(60, 100, 150, 255));
	myFloatImage->SetImageRect(myRect);

	myClickImage = new MfxImage(myGraphics);
	myClickImage->LoadPureColor(Gdiplus::Color(60, 255, 100, 100));
	myClickImage->SetImageRect(myRect);
	/**/

}

/**/
MicroFlakeX::MfxButton::~MfxButton()
{
	delete myBackImage;
	delete myMidWords;
	delete myMaskImage;

	delete myFloatImage;
	delete myClickImage;
}
MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::ThreadPaint()
{
	OnPaint(0, 0);
	return 0;
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
	if (myFloatImageFlag)
		myFloatImage->Draw();
	if (myClickImageFlag)
		myClickImage->Draw();

	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
	{
		myFloatImageFlag = true;
	}
	else
	{
		myFloatImageFlag = false;
	}
	PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
	//myUI->UIDrawToMainDc(); //这个是不对的，应该是主UI每秒30帧自动刷新！！
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	Gdiplus::Point mousePos = Gdiplus::Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (myRect.Contains(mousePos))
	{
		myClickImageFlag = true;
	}
	else
	{
		myClickImageFlag = false;
	}
	PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
	return 0;
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	myClickImageFlag = false;
	PostMessage(myUI->GetWnd(), WM_PAINT, 0, 0);
	return 0;
}
