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
		Gdiplus::Point myMoveBegin;
	protected:
		void SetRect(Gdiplus::Rect set);
		void SetSize(Gdiplus::Size set);
		void SetPoint(Gdiplus::Point set);

	protected:
		bool myBackImageFlag;
		bool myMidWordsFlag;
		bool myMaskImageFlag;

		bool myFloatImageFlag;

		bool myLButtonPressImageFlag;
		bool myRButtonPressImageFlag;

		MfxImage* myBackImage;
		MfxWords* myMidWords;
		MfxImage* myMaskImage;

		MfxImage* myFloatImage;

		MfxImage* myLButtonPressImage;
		MfxImage* myRButtonPressImage;
	public:
		MfxImage* SetBackImage(MfxImage* set);
		MfxImage* GetBackImage();
		MfxWords* SetMidWords(MfxWords* set);
		MfxWords* GetMidWords();
		MfxImage* SetMaskImage(MfxImage* set);
		MfxImage* GetMaskImage();

		MfxImage* SetFloatImage(MfxImage* set);
		MfxImage* GetFloatImage();

		MfxImage* SetLButtonPressImage(MfxImage* set);
		MfxImage* GetLButtonPressImage();
		MfxImage* SetRButtonPressImage(MfxImage* set);
		MfxImage* GetRButtonPressImage();

	protected:
		MFXRETURE OnPaint(WPARAM wParam, LPARAM lParam);

		MFXRETURE OnMouseMove(WPARAM wParam, LPARAM lParam);

		MFXRETURE OnLButtonDown(WPARAM wParam, LPARAM lParam);
		MFXRETURE OnLButtonUp(WPARAM wParam, LPARAM lParam);

		MFXRETURE OnRButtonDown(WPARAM wParam, LPARAM lParam);
		MFXRETURE OnRButtonUp(WPARAM wParam, LPARAM lParam);
    };
}
