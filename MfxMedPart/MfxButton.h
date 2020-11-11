#pragma once
#include "MfxMedPart.h"


/* 应该采用标记的方法，只在接收到paint的时候画图 */
namespace MicroFlakeX
{
    class MFX_MEDPART_IMPORT MfxButton :
		public MfxControl
    {
	public:
		MfxButton(MfxUI* getUI, Gdiplus::Rect setRect = Gdiplus::Rect(20, 20, 160, 50));
		virtual ~MfxButton();
		MFXRETURE ThreadPaint();  //线程绘制接口
	protected:
		MfxImage* myBackImage;
		MfxWords* myMidWords;
		MfxImage* myMaskImage;

		bool myFloatImageFlag;
		MfxImage* myFloatImage;
		bool myClickImageFlag;
		MfxImage* myClickImage;

		bool myClick;
		bool myPress;
		bool myFloat;
	protected:
		virtual MFXRETURE OnPaint(WPARAM wParam, LPARAM lParam);  //
		virtual MFXRETURE OnMouseMove(WPARAM wParam, LPARAM lParam);  //移动
		virtual MFXRETURE OnLButtonDown(WPARAM wParam, LPARAM lParam);  //点击
		virtual MFXRETURE OnLButtonUp(WPARAM wParam, LPARAM lParam);  //鼠标移动
    };
}
