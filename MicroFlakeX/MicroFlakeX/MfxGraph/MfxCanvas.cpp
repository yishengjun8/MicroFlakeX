#include "pch.h"
#include "MfxGraph.h"

MFX_OBJ_REFLECTION_INIT(MfxCanvas)
{
	//添加一些需要提前初始化的代码
}
MFX_OBJ_REFLECTION_ENDINIT(MfxCanvas, MfxBase, \
	GetDC, \
	GetWnd, \
	GetBackColor, \
	\
	SetDC, \
	SetWnd, \
	SetBackColor, \
	\
	PaintBegin, \
	PaintFinish, \
	PaintCheck, \
	\
	GetRenderTarget, \
	\
	SetRect, \
	SetSize, \
	SetPoint, \
	\
	GetRect, \
	GetSize, \
	GetPoint \
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxCanvas::GetWnd(HWND* ret)const
{
	*ret = myWnd;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxCanvas::GetBackColor(MfxColor* ret)const
{
	myBackColor.GetColor(ret);
	
	return MFX_RET_SECCESS;
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
		return MFX_RET_FAILED;
	}

	myDC = set;

	MfxGraph::GetID2D1DCRenderTarget(&myRenderTarget, set, myRect);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxCanvas::SetWnd(HWND set)
{
	if (myDC || myWnd)
	{
		return MFX_RET_FAILED;
	}

	myWnd = set;

	MfxGraph::GetID2D1HwndRenderTarget(&myRenderTarget, set, MfxSize(myRect));

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxCanvas::SetBackColor(MfxColor* set)
{
	myBackColor = set;

	return MFX_RET_SECCESS;
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

		return MFX_RET_SECCESS;
	}

	return MFX_RET_FAILED;

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

		return MFX_RET_SECCESS;
	}

	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintCheck(bool* ret)const
{
	*ret = myPaintFlag;

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxCanvas::GetRenderTarget(ID2D1RenderTarget** ret)const
{
	*ret = myRenderTarget;

	return MFX_RET_SECCESS;
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

		return MFX_RET_SECCESS;
	}
	else if (myDC)
	{
		RECT rc;
		myRect.GetRECT(&rc);
		((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);

		return MFX_RET_SECCESS;
	}

	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxCanvas::SetSize(MfxSize* set)
{
	myRect = set;

	if (myWnd)
	{
		D2D1_SIZE_U tSize;
		myRect.GetD2D1SizeU(&tSize);
		((ID2D1HwndRenderTarget*)myRenderTarget)->Resize(tSize);

		return MFX_RET_SECCESS;
	}
	else if (myDC)
	{
		RECT rc;
		myRect.GetRECT(&rc);
		((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);

		return MFX_RET_SECCESS;
	}

	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxCanvas::SetPoint(MfxPoint* set)
{
	myRect = set;

	if (myDC)
	{
		RECT rc;
		myRect.GetRECT(&rc);
		((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);

		return MFX_RET_SECCESS;
	}

	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxCanvas::GetRect(MfxRect* set)const
{
	myRect.GetRect(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxCanvas::GetSize(MfxSize* set)const
{
	myRect.GetSize(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxCanvas::GetPoint(MfxPoint* set)const
{
	myRect.GetPoint(set);

	return MFX_RET_SECCESS;
}
