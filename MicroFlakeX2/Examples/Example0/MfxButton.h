#pragma once
#include "MfxAppFramework.h"

namespace MicroFlakeX
{
	class MFX_APPFRAMEWORKDLL_IMPORT MfxButton;
}

//MfxÃ¶¾Ù
namespace MicroFlakeX
{
	enum MfxButton_Message
	{
		MfxButton_Message_SetMouseFloatUnderColor = MfxButton_MessageBegin - 1,
		MfxButton_Message_SetMouseFloatCoverColor = MfxButton_MessageBegin - 2,

		MfxButton_Message_SetLButtonPressUnderColor = MfxButton_MessageBegin - 3,
		MfxButton_Message_SetLButtonPressCoverColor = MfxButton_MessageBegin - 4,

		MfxButton_Message_SetRButtonPressUnderColor = MfxButton_MessageBegin - 5,
		MfxButton_Message_SetRButtonPressCoverColor = MfxButton_MessageBegin - 6,

		MfxButton_Message_SetMouseFloatUnderImage = MfxButton_MessageBegin - 7,
		MfxButton_Message_SetMouseFloatCoverImage = MfxButton_MessageBegin - 8,

		MfxButton_Message_SetLButtonPressUnderImage = MfxButton_MessageBegin - 9,
		MfxButton_Message_SetLButtonPressCoverImage = MfxButton_MessageBegin - 10,

		MfxButton_Message_SetRButtonPressUnderImage = MfxButton_MessageBegin - 11,
		MfxButton_Message_SetRButtonPressCoverImage = MfxButton_MessageBegin - 12,
	};
}

namespace MicroFlakeX
{
	class MfxButton
		: public MfxControl
	{
	protected:
		void RegDefFunc();
		void MfxButtonInitData();
	public:
		MfxButton();
		virtual ~MfxButton();
	protected:
		MfxImage* myMouseFloatUnderImage;
		MfxImage* myMouseFloatCoverImage;

		MfxImage* myLButtonPressUnderImage;
		MfxImage* myLButtonPressCoverImage;

		MfxImage* myRButtonPressUnderImage;
		MfxImage* myRButtonPressCoverImage;

	public:
		MfxReturn GetMouseFloatUnderImage(MfxImage** ret);
		MfxReturn GetMouseFloatCoverImage(MfxImage** ret);

		MfxReturn GetLButtonPressUnderImage(MfxImage** ret);
		MfxReturn GetLButtonPressCoverImage(MfxImage** ret);

		MfxReturn GetRButtonPressUnderImage(MfxImage** ret);
		MfxReturn GetRButtonPressCoverImage(MfxImage** ret);

	public:
		MfxReturn SetMouseFloatUnderColor(GdipColor set);
		MfxReturn SetMouseFloatCoverColor(GdipColor set);

		MfxReturn SetLButtonPressUnderColor(GdipColor set);
		MfxReturn SetLButtonPressCoverColor(GdipColor set);

		MfxReturn SetRButtonPressUnderColor(GdipColor set);
		MfxReturn SetRButtonPressCoverColor(GdipColor set);

		MfxReturn SetMouseFloatUnderImage(MfxImage* set);
		MfxReturn SetMouseFloatCoverImage(MfxImage* set);

		MfxReturn SetLButtonPressUnderImage(MfxImage* set);
		MfxReturn SetLButtonPressCoverImage(MfxImage* set);

		MfxReturn SetRButtonPressUnderImage(MfxImage* set);
		MfxReturn SetRButtonPressCoverImage(MfxImage* set);

	protected:
		MfxReturn OnPaintUnderBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn OnPaintCoverBackDC(WPARAM wParam, LPARAM lParam);
		MfxReturn OnPaintUnderMaskDC(WPARAM wParam, LPARAM lParam);
		MfxReturn OnPaintCoverMaskDC(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetPaper(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSize(WPARAM wParam, LPARAM lParam);
		MfxReturn OnPoint(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetMouseFloatUnderColor(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSetMouseFloatCoverColor(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetLButtonPressUnderColor(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSetLButtonPressCoverColor(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetRButtonPressUnderColor(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSetRButtonPressCoverColor(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetMouseFloatUnderImage(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSetMouseFloatCoverImage(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetLButtonPressUnderImage(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSetLButtonPressCoverImage(WPARAM wParam, LPARAM lParam);

		MfxReturn OnSetRButtonPressUnderImage(WPARAM wParam, LPARAM lParam);
		MfxReturn OnSetRButtonPressCoverImage(WPARAM wParam, LPARAM lParam);
	};
}

