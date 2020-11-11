#pragma once
#include "MfxMedPart.h"


/* 应该采用标记的方法，只在接收到paint的时候画图 */
namespace MicroFlakeX
{
    class MFX_MEDPART_IMPORT MfxButton :
		public MfxControl
    {
	public:
		MfxButton(MfxUI* father, Gdiplus::Rect value = Gdiplus::Rect(20, 20, 160, 50));
		virtual ~MfxButton();
	protected:
		MfxImage* myBackImage;
		MfxWords* myMidWords;
		MfxImage* myMaskImage;

		MfxImage* myFloatImage;
		MfxImage* myPressImage;
	protected:
		virtual MFXRETURE OnPaint(WPARAM wParam, LPARAM lParam);

		virtual MFXRETURE OnMouseMove(WPARAM wParam, LPARAM lParam);

		virtual MFXRETURE OnLButtonDown(WPARAM wParam, LPARAM lParam);
		virtual MFXRETURE OnLButtonUp(WPARAM wParam, LPARAM lParam);
    };
}
