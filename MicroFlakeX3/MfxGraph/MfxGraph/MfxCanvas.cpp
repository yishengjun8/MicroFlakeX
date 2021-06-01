#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init(MfxCanvas)
{
	//添加一些需要提前初始化的代码
}
MfxObject_EndInit(MfxCanvas, MfxBase, \
	1, GetDC, \
	1, GetWnd, \
	1, GetBackColor, \
	\
	1, SetDC, \
	1, SetWnd, \
	1, SetBackColor, \
	\
	1, PaintBegin, \
	0, PaintFinish, \
	1, PaintCheck, \
	\
	1, GetRenderTarget, \
	\
	1, SetRect, \
	1, SetSize, \
	1, SetPoint, \
	\
	1, GetRect, \
	1, GetSize, \
	1, GetPoint \
);

MicroFlakeX::MfxCanvas::MfxCanvas()
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myRect.Reset(0, 0, 300, 300);
}

MicroFlakeX::MfxCanvas::MfxCanvas(const MfxRect* set)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myRect = set;
}

MicroFlakeX::MfxCanvas::MfxCanvas(const MfxSize* size)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myRect = size;
}

MicroFlakeX::MfxCanvas::MfxCanvas(const HDC setDC, const MfxRect* setRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myDC = setDC;
	myRect = setRect;

	MfxGraph::GetID2D1DCRenderTarget(&myRenderTarget, myDC, myRect);
}

MicroFlakeX::MfxCanvas::MfxCanvas(const HWND setWnd, const MfxRect* setRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myWnd = setWnd;
	myRect = setRect;

	MfxGraph::GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, MfxSize(myRect));
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
MfxReturn MicroFlakeX::MfxCanvas::GetDC(HDC* ret)const
{
	*ret = myDC;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetWnd(HWND* ret)const
{
	*ret = myWnd;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetBackColor(MfxColor* ret)const
{
	myBackColor.GetColor(ret);
	
	return Mfx_Return_Fine;
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

	MfxGraph::GetID2D1DCRenderTarget(&myRenderTarget, set, myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetWnd(HWND set)
{
	if (myDC || myWnd)
	{
		return Mfx_Return_Fail;
	}

	myWnd = set;

	MfxGraph::GetID2D1HwndRenderTarget(&myRenderTarget, set, MfxSize(myRect));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetBackColor(MfxColor* set)
{
	myBackColor = set;

	return Mfx_Return_Fine;
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

		D2D1_COLOR_F tColor;
		myBackColor.GetD2D1ColorF(&tColor);

		myRenderTarget->Clear(tColor);

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

MfxReturn MicroFlakeX::MfxCanvas::PaintCheck(bool* ret)const
{
	*ret = myPaintFlag;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::GetRenderTarget(ID2D1RenderTarget** ret)const
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

MfxReturn MicroFlakeX::MfxCanvas::GetRect(MfxRect* set)const
{
	myRect.GetRect(set);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetSize(MfxSize* set)const
{
	myRect.GetSize(set);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetPoint(MfxPoint* set)const
{
	myRect.GetPoint(set);

	return Mfx_Return_Fine;
}
