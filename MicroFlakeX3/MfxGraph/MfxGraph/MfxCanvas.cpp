#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxCanvas)
MfxObject_Init_1(MfxCanvas)
MfxObject_Init_2(MfxCanvas, MfxGraph);

MicroFlakeX::MfxCanvas::MfxCanvas()
{
}

MicroFlakeX::MfxCanvas::~MfxCanvas()
{
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetDC(HDC* ret)
{
	*ret = myDC;
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetWnd(HWND set)
{
	myWnd = set;
	MfxSize tSize; tSize = myRect;
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::PaintFinish()
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::GetRenderTarget(ID2D1RenderTarget** ret)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetSize(MfxSize* set)
{
	MfxGraph::SetSize(set);
	return RFine;
}

MfxReturn MicroFlakeX::MfxCanvas::SetPoint(MfxPoint* set)
{
	MfxGraph::SetPoint(set);
	return RFine;
}
