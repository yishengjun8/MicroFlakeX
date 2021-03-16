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

MicroFlakeX::MfxCanvas::MfxCanvas(MfxRect sRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myRect = sRect;
}

MicroFlakeX::MfxCanvas::MfxCanvas(HDC sDC, MfxRect sRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myDC = sDC;
	myRect = sRect;
	GetID2D1DCRenderTarget(&myRenderTarget, myDC, myRect);
}

MicroFlakeX::MfxCanvas::MfxCanvas(HWND sWnd, MfxRect sRect)
{
	myDC = nullptr;
	myWnd = nullptr;
	myPaintFlag = false;
	myRenderTarget = nullptr;

	myWnd = sWnd;
	myRect = sRect;
	GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, MfxSize(&myRect));
}

MicroFlakeX::MfxCanvas::~MfxCanvas()
{
	SafeRelease(myRenderTarget);
}

MfxReturn MicroFlakeX::MfxCanvas::Clone(MfxBase** ret)
{
	if (myWnd)
	{
		*ret = new MfxCanvas(myWnd, myRect);
	}
	else if(myDC)
	{
		*ret = new MfxCanvas(myDC, myRect);
	}
	*ret = new MfxCanvas(myRect);
	return RFine;
}

MfxBase& MicroFlakeX::MfxCanvas::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

MfxCanvas& MicroFlakeX::MfxCanvas::operator=(MfxCanvas& rhs)
{
	myDC = rhs.myDC;
	myWnd = rhs.myWnd;
	myRect = rhs.myRect;

	if (rhs.myWnd)
	{
		SafeRelease(myRenderTarget);
		GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, MfxSize(&myRect));
	}
	else if (rhs.myDC)
	{
		SafeRelease(myRenderTarget);
		GetID2D1DCRenderTarget(&myRenderTarget, myDC, myRect);
	}

	return *this;
}

BOOL MicroFlakeX::MfxCanvas::operator==(MfxBase& rhs)
{
	return 0;
}

BOOL MicroFlakeX::MfxCanvas::operator==(MfxCanvas& rhs)
{
	return myDC == rhs.myDC && myWnd == rhs.myWnd;
}

MfxReturn MicroFlakeX::MfxCanvas::SetDC(HDC set)
{
	if (myDC || myWnd)
	{
		return RFail;
	}
	myDC = set;
	GetID2D1DCRenderTarget(&myRenderTarget, set, myRect);
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
	GetID2D1HwndRenderTarget(&myRenderTarget, set, MfxSize(&myRect));
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
	myPaintFlag = true;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintFinish()
{
	myRenderTarget->EndDraw();
	myPaintFlag = false;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintCheck(bool* ret)
{
	*ret = myPaintFlag;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetRenderTarget(ID2D1RenderTarget** ret)
{
	*ret = myRenderTarget;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetRect(MfxRect set)
{
	myRect = set;
	{
		if (myWnd)
		{
			SafeRelease(myRenderTarget);
			GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, MfxSize(&myRect));
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

MfxReturn MicroFlakeX::MfxCanvas::SetSize(MfxSize set)
{
	myRect = set;
	{
		if (myWnd)
		{
			SafeRelease(myRenderTarget);
			GetID2D1HwndRenderTarget(&myRenderTarget, myWnd, MfxSize(&myRect));
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
	myRect = set;
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
