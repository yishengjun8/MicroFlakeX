#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxCanvas)
MfxObject_Init_1(MfxCanvas)
MfxObject_Init_2(MfxCanvas, MfxGraph);

MicroFlakeX::MfxCanvas::MfxCanvas()
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;
}

MicroFlakeX::MfxCanvas::~MfxCanvas()
{
	SafeRelease(myRenderTarget);
}

MfxReturn MicroFlakeX::MfxCanvas::Clone(MfxBase** ret)
{
	return RFine;
}

MfxBase& MicroFlakeX::MfxCanvas::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

BOOL MicroFlakeX::MfxCanvas::operator==(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return false;
}

MfxReturn MicroFlakeX::MfxCanvas::SetDC(HDC set)
{
	if (myDC || myWnd)
	{
		return RFail;
	}
	myDC = set;
	GetID2D1DCRenderTarget(&myRenderTarget, set, &myRect);
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetDC(HDC* ret)
{
	*ret = myDC;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetWnd(HWND set)
{
	if (myDC || myWnd)
	{
		return RFail;
	}
	myWnd = set;
	MfxSize tSize(&myRect);
	GetID2D1HwndRenderTarget(&myRenderTarget, set, &tSize);
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetWnd(HWND* ret)
{
	*ret = myWnd;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintBegin()
{
	myRenderTarget->BeginDraw();
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintFinish()
{
	myRenderTarget->EndDraw();
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetRenderTarget(ID2D1RenderTarget** ret)
{
	*ret = myRenderTarget;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetSize(MfxSize set)
{
	MfxGraph::SetSize(set);
	{
		if (myWnd)
		{
			SafeRelease(myRenderTarget);
			MfxSize tSize(&myRect);
			GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, &tSize);
		}
		else if (myDC)
		{
			RECT rc;
			myRect.GetRECT(&rc);
			((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);
		}
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetPoint(MfxPoint set)
{
	MfxGraph::SetPoint(set);
	{
		if (myDC)
		{
			RECT rc;
			myRect.GetRECT(&rc);
			((ID2D1DCRenderTarget*)myRenderTarget)->BindDC(myDC, &rc);
		}
	}
	return RFine;
}
