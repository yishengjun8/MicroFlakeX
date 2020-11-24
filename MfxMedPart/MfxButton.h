#pragma once
#include "MfxMedPart.h"


/* 应该采用标记的方法，只在接收到paint的时候画图 */
namespace MicroFlakeX
{
    class MFX_MEDPART_IMPORT MfxButton :
		public MfxControl
    {
	protected:
		void Reg();
		void InitData();
	public:
		MfxButton(MfxUI* father);
		MfxButton(MfxUI* father, Gdiplus::Rect rect);
		MfxButton(MfxUI* father, std::wstring title);
		MfxButton(MfxUI* father, Gdiplus::Rect rect, std::wstring title);
		virtual ~MfxButton();

	protected:
		Gdiplus::Point myMoveBegin;
	protected:
		void SetRect(Gdiplus::Rect set);
		void SetSize(Gdiplus::Size set);
		void SetPoint(Gdiplus::Point set);

	protected:
		bool myFloatUnderImageFlag;
		bool myFloatCoverImageFlag;

		bool myLButtonPressImageFlag;
		bool myRButtonPressImageFlag;

		MfxImage* myFloatUnderImage;
		MfxImage* myFloatCoverImage;

		MfxImage* myLButtonPressImage;
		MfxImage* myRButtonPressImage;
	public:
		MfxImage* SetFloatUnderImage(MfxImage* set);
		MfxImage* GetFloatUnderImage();
		MfxImage* SetFloatCoverImage(MfxImage* set);
		MfxImage* GetFloatCoverImage();

		MfxImage* SetLButtonPressImage(MfxImage* set);
		MfxImage* GetLButtonPressImage();
		MfxImage* SetRButtonPressImage(MfxImage* set);
		MfxImage* GetRButtonPressImage();

	protected:
		MFXRETURE OnDrawBufferDC(WPARAM wParam, LPARAM lParam);//重绘 - wParam = &ps

		MFXRETURE OnMouseMove(WPARAM wParam, LPARAM lParam);

		MFXRETURE OnLButtonDown(WPARAM wParam, LPARAM lParam);
		MFXRETURE OnLButtonUp(WPARAM wParam, LPARAM lParam);

		MFXRETURE OnRButtonDown(WPARAM wParam, LPARAM lParam);
		MFXRETURE OnRButtonUp(WPARAM wParam, LPARAM lParam);
    };
}
