#include "pch.h"
#include "MfxMedPart.h"

MicroFlakeX::MfxButton::MfxButton(MfxUI* getUI, Gdiplus::Rect setRect)
	: MfxControl(getUI, setRect)
{

}

MicroFlakeX::MfxButton::~MfxButton()
{
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLMouseDown(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}

MicroFlakeX::MFXRETURE MicroFlakeX::MfxButton::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return MFXRETURE();
}
