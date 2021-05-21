#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init(MfxCanvas)
MfxObject_EndInit(MfxCanvas, MfxGraph)

MicroFlakeX::MfxCanvas::MfxCanvas()
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myRect.Reset(0, 0, 300, 300);
}

MicroFlakeX::MfxCanvas::MfxCanvas(MfxRect set)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myRect = set;
}

MicroFlakeX::MfxCanvas::MfxCanvas(HDC setDC, MfxRect setRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myDC = setDC;
	myRect = setRect;

	GetID2D1DCRenderTarget(&myRenderTarget, myDC, myRect);
}

MicroFlakeX::MfxCanvas::MfxCanvas(HWND setWnd, MfxRect setRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myWnd = setWnd;
	myRect = setRect;

	GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, MfxSize(myRect));
}

MicroFlakeX::MfxCanvas::~MfxCanvas()
{
	SafeRelease(myRenderTarget);
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::GetDC(HDC* ret) const
{
	*ret = myDC;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetWnd(HWND* ret) const
{
	*ret = myWnd;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetBackColor(MfxColor* ret) const
{
	return MfxReturn();
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::SetDC(HDC set)
{
	if (myDC || myWnd)
	{
		return Mfx_Return_Fail;
	}

	myDC = set;

	GetID2D1DCRenderTarget(&myRenderTarget, set, myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetWnd(HWND set)
{
	if (myDC || myWnd)
	{
		return Mfx_Return_Fail;
	}

	myWnd = set;

	GetID2D1HwndRenderTarget(&myRenderTarget, set, MfxSize(myRect));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetBackColor(MfxColor* set)
{
	return MfxReturn();
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::PaintBegin(MfxRect* clip)
{
	if (!myPaintFlag)
	{
		myRenderTarget->BeginDraw();

		clip->GetRect(&myClipRect);
		bool tEmpty = false;
		myClipRect.IsEmpty(&tEmpty);

		if (!tEmpty)
		{
			D2D1_RECT_F tRectF;
			myClipRect.GetD2D1RectF(&tRectF);
			myRenderTarget->PushAxisAlignedClip(tRectF, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		}

		myPaintFlag = true;

		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintFinish()
{
	if (myPaintFlag)
	{
		bool tEmpty = false;
		myClipRect.IsEmpty(&tEmpty);

		if (!tEmpty)
		{
			myClipRect.Reset(0, 0, 0, 0);
			myRenderTarget->PopAxisAlignedClip();
		}

		myRenderTarget->EndDraw();

		myPaintFlag = false;

		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintCheck(bool* ret)
{
	*ret = myPaintFlag;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::GetRenderTarget(ID2D1RenderTarget** ret) const
{
	*ret = myRenderTarget;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::SetRect(MfxRect* set)
{
	myRect = set;

	if (myWnd)
	{
		D2D1_SIZE_U tSize;
		myRect.GetD2D1SizeU(&tSize);
		((ID2D1HwndRenderTarget*)myRenderTarget)->Resize(tSize);

		return Mfx_Return_Fine;
	}
	else if (myDC)
	{
		RECT rc;
		myRect.GetRECT(&rc);
		((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);

		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxCanvas::SetSize(MfxSize* set)
{
	myRect = set;

	if (myWnd)
	{
		D2D1_SIZE_U tSize;
		myRect.GetD2D1SizeU(&tSize);
		((ID2D1HwndRenderTarget*)myRenderTarget)->Resize(tSize);

		return Mfx_Return_Fine;
	}
	else if (myDC)
	{
		RECT rc;
		myRect.GetRECT(&rc);
		((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);

		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxCanvas::SetPoint(MfxPoint* set)
{
	myRect = set;

	if (myDC)
	{
		RECT rc;
		myRect.GetRECT(&rc);
		((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);

		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}
