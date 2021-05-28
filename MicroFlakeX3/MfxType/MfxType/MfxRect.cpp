#include "pch.h"
#include "MfxType.h"

MfxObject_Init(MfxRect)
MfxObject_EndInit(MfxRect, MfxBase, \
	4, Reset, \
	\
	1, GetRect, \
	1, GetSize, \
	1, GetPoint, \
	\
	1, GetRECT, \
	1, GetSIZE, \
	1, GetPOINT, \
	\
	1, GetGdipRect, \
	1, GetGdipRectF, \
	\
	1, GetGdipSize, \
	1, GetGdipSizeF, \
	\
	1, GetGdipPoint, \
	1, GetGdipPointF, \
	\
	1, GetD2D1RectL, \
	1, GetD2D1RectU, \
	1, GetD2D1RectF, \
	\
	1, GetD2D1SizeU, \
	1, GetD2D1SizeF, \
	\
	1, GetD2D1Point2L, \
	1, GetD2D1Point2U, \
	1, GetD2D1Point2F, \
	\
	1, SetRect, \
	1, SetSize, \
	1, SetPoint, \
	\
	1, SetRECT, \
	1, SetSIZE, \
	1, SetPOINT, \
	\
	1, SetGdipRect, \
	1, SetGdipRectF, \
	\
	1, SetGdipSize, \
	1, SetGdipSizeF, \
	\
	1, SetGdipPoint, \
	1, SetGdipPointF, \
	\
	1, SetD2D1RectL, \
	1, SetD2D1RectU, \
	1, SetD2D1RectF, \
	\
	1, SetD2D1SizeU, \
	1, SetD2D1SizeF, \
	\
	1, SetD2D1Point2L, \
	1, SetD2D1Point2U, \
	1, SetD2D1Point2F, \
	\
	\
	1, GetX, \
	1, GetY, \
	1, GetWidth, \
	1, GetHeight, \
	\
	1, GetTop, \
	1, GetLeft, \
	1, GetRight, \
	1, GetBottom, \
	\
	1, GetCenter, \
	2, GetPointPosition, \
	\
	\
	1, SetX, \
	1, SetY, \
	1, SetWidth, \
	1, SetHeight, \
	\
	1, SetTop, \
	1, SetLeft, \
	1, SetRight, \
	1, SetBottom, \
	\
	1, SetCenter, \
	2, SetPointPosition, \
	\
	2, Union, \
	2, Union_Widely, \
	2, Intersect, \
	2, Intersect_Widely, \
	\
	2, Offset, \
	2, Inflate, \
	\
	1, IsEmpty, \
	2, IsPointInside);


/**************************************************************
* 
* 
* 
***************************************************************/
MicroFlakeX::MfxRect::MfxRect()
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(MfxBase& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.AutoFunc(MfxText("GetX"), &tSX);
	set.AutoFunc(MfxText("GetY"), &tSY);
	set.AutoFunc(MfxText("GetWidth"), &tSW);
	set.AutoFunc(MfxText("GetHeight"), &tSH);

	SetY(tSY);
	SetX(tSX);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(const MfxRect* set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);
	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(const MfxSize* set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(const MfxPoint* set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(const MfxPoint* set1, const MfxPoint* set2)
{
	LONG tX1 = 0, tX2 = 0, tY1 = 0, tY2 = 0;

	set1->GetX(&tX1);
	set1->GetY(&tY1);
	set2->GetX(&tX2);
	set2->GetY(&tY2);


	SetX(min(tX1, tX2));
	SetY(min(tY1, tY2));

	SetWidth(max(tX1, tX2) - min(tX1, tX2));
	SetHeight(max(tY1, tY2) - min(tY1, tY2));
}

MicroFlakeX::MfxRect::MfxRect(LONG setX, LONG setY, LONG setWidth, LONG setHeight)
{
	SetX(setX);
	SetY(setY);
	SetWidth(setWidth);
	SetHeight(setHeight);
}

MicroFlakeX::MfxRect::~MfxRect()
{
}

MfxReturn MicroFlakeX::MfxRect::Clone(MfxBase** ret)
{
	*ret = new MfxRect(*this);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxBase& MicroFlakeX::MfxRect::operator=(MfxBase& rhs)
{
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetX"), &tRX)))
	{
		SetX(tRX);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetY"), &tRY)))
	{
		SetY(tRY);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetWidth"), &tRW)))
	{
		SetWidth(tRW);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetHeight"), &tRH)))
	{
		SetHeight(tRH);
	}

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxRect* rhs)
{
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	rhs->GetX(&tRX);
	rhs->GetY(&tRY);
	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	SetX(tRX);
	SetY(tRY);
	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxRect& rhs)
{
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);
	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetX(tRX);
	SetY(tRY);
	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxRect&& rhs)
{
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);
	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetX(tRX);
	SetY(tRY);
	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxSize* rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxSize& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxSize&& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxPoint* rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs->GetX(&tRX);
	rhs->GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxPoint& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);	

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(const MfxPoint&& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}


/**************************************************************
*
*
*
***************************************************************/
bool MicroFlakeX::MfxRect::operator==(MfxBase& rhs)
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetX"), &tRX))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetY"), &tRY))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetWidth"), &tRW))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetHeight"), &tRH))
		)
	{
		return tX == tRX && tY == tRY && tW == tRW && tH == tRH;
	}

	return false;
}

bool MicroFlakeX::MfxRect::operator==(const MfxRect* rhs)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	rhs->GetX(&tRX);
	rhs->GetY(&tRY);
	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	return tX == tRX && tY == tRY && tW == tRW && tH == tRH;
}

bool MicroFlakeX::MfxRect::operator==(const MfxRect& rhs)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);
	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	return tX == tRX && tY == tRY && tW == tRW && tH == tRH;
}

bool MicroFlakeX::MfxRect::operator==(const MfxRect&& rhs)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);
	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	return tX == tRX && tY == tRY && tW == tRW && tH == tRH;
}

MicroFlakeX::MfxRect::operator D2D1_RECT_L()const
{
	D2D1_RECT_L tD2D1_RECT_L;

	GetD2D1RectL(&tD2D1_RECT_L);

	return tD2D1_RECT_L;
}

MicroFlakeX::MfxRect::operator D2D1_RECT_U()const
{
	D2D1_RECT_U tD2D1_RECT_U;

	GetD2D1RectU(&tD2D1_RECT_U);

	return tD2D1_RECT_U;
}

MicroFlakeX::MfxRect::operator D2D1_RECT_F()const
{
	D2D1_RECT_F tD2D1_RECT_F;

	GetD2D1RectF(&tD2D1_RECT_F);

	return tD2D1_RECT_F;
}

MicroFlakeX::MfxRect::operator D2D1_SIZE_U()const
{
	D2D1_SIZE_U tD2D1_SIZE_U;

	GetD2D1SizeU(&tD2D1_SIZE_U);

	return tD2D1_SIZE_U;
}

MicroFlakeX::MfxRect::operator D2D1_SIZE_F()const
{
	D2D1_SIZE_F tD2D1_SIZE_F;

	GetD2D1SizeF(&tD2D1_SIZE_F);

	return tD2D1_SIZE_F;
}

MicroFlakeX::MfxRect::operator D2D1_POINT_2L()const
{
	D2D1_POINT_2L tD2D1_POINT_2L;

	GetD2D1Point2L(&tD2D1_POINT_2L);

	return tD2D1_POINT_2L;
}

MicroFlakeX::MfxRect::operator D2D1_POINT_2U()const
{
	D2D1_POINT_2U tD2D1_POINT_2U;

	GetD2D1Point2U(&tD2D1_POINT_2U);

	return tD2D1_POINT_2U;
}

MicroFlakeX::MfxRect::operator D2D1_POINT_2F()const
{
	D2D1_POINT_2F tD2D1_POINT_2F;

	GetD2D1Point2F(&tD2D1_POINT_2F);

	return tD2D1_POINT_2F;
}

MicroFlakeX::MfxRect::operator Gdiplus::Rect()const
{
	Gdiplus::Rect tRect;

	GetGdipRect(&tRect);

	return tRect;
}

MicroFlakeX::MfxRect::operator Gdiplus::RectF()const
{
	Gdiplus::RectF tRectF;

	GetGdipRectF(&tRectF);

	return tRectF;
}

MicroFlakeX::MfxRect::operator Gdiplus::Size()const
{
	Gdiplus::Size tSize;

	GetGdipSize(&tSize);

	return tSize;
}

MicroFlakeX::MfxRect::operator Gdiplus::SizeF()const
{
	Gdiplus::SizeF tSizeF;

	GetGdipSizeF(&tSizeF);

	return tSizeF;
}

MicroFlakeX::MfxRect::operator Gdiplus::Point()const
{
	Gdiplus::Point tPoint;

	GetGdipPoint(&tPoint);

	return tPoint;
}

MicroFlakeX::MfxRect::operator Gdiplus::PointF()const
{
	Gdiplus::PointF tPointF;

	GetGdipPointF(&tPointF);

	return tPointF;
}
/**/
/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::Reset(LONG setX, LONG setY, LONG setWidth, LONG setHeight)
{
	SetX(setX);
	SetY(setY);
	SetWidth(setWidth);
	SetHeight(setHeight);

	return Mfx_Return_Fine;
}


/**************************************************************
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetRect(MfxRect* ret)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	return ret->Reset(tX, tY, tW, tH);
}

MfxReturn MicroFlakeX::MfxRect::GetSize(MfxSize* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	return ret->Reset(tW, tH);
}

MfxReturn MicroFlakeX::MfxRect::GetPoint(MfxPoint* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	return ret->Reset(tX, tY);
}



/**************************************************************
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetRECT(RECT* ret)const
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->top = tT;
	ret->left = tL;
	ret->right = tR;
	ret->bottom = tB;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetSIZE(SIZE* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->cx = tW;
	ret->cy = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetPOINT(POINT* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}


/**************************************************************
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetGdipRect(Gdiplus::Rect* ret)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	ret->X = tX;
	ret->Y = tY;
	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipRectF(Gdiplus::RectF* ret)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	ret->X = tX;
	ret->Y = tY;
	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipSize(Gdiplus::Size* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipSizeF(Gdiplus::SizeF* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipPoint(Gdiplus::Point* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipPointF(Gdiplus::PointF* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return Mfx_Return_Fine;
}


/**************************************************************
* 
* 
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetD2D1RectL(D2D1_RECT_L* ret)const
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->top = tT;
	ret->left = tL;
	ret->right = tR;
	ret->bottom = tB;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectU(D2D1_RECT_U* ret)const
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->top = tT;
	ret->left = tL;
	ret->right = tR;
	ret->bottom = tB;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectF(D2D1_RECT_F* ret)const
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->top = tT;
	ret->left = tL;
	ret->right = tR;
	ret->bottom = tB;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeU(D2D1_SIZE_U* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeF(D2D1_SIZE_F* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1Point2L(D2D1_POINT_2L* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}
MfxReturn MicroFlakeX::MfxRect::GetD2D1Point2U(D2D1_POINT_2U* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1Point2F(D2D1_POINT_2F* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetRect(const MfxRect* set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);
	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetSize(const MfxSize* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetPoint(const MfxPoint* set)
{
	LONG tSX = 0, tSY = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);

	SetX(tSX);
	SetY(tSY);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetRECT(const RECT* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->right);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetSIZE(const SIZE* set)
{
	SetWidth(set->cx);
	SetHeight(set->cy);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetPOINT(const POINT* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetGdipRect(const Gdiplus::Rect* set)
{
	SetX(set->X);
	SetY(set->Y);
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipRectF(const Gdiplus::RectF* set)
{
	SetX(set->X);
	SetY(set->Y);
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipSize(const Gdiplus::Size* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipSizeF(const Gdiplus::SizeF* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipPoint(const Gdiplus::Point* set)
{
	SetX(set->X);
	SetY(set->Y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipPointF(const Gdiplus::PointF* set)
{
	SetX(set->X);
	SetY(set->Y);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/

MfxReturn MicroFlakeX::MfxRect::SetD2D1RectL(const D2D1_RECT_L* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->right);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1RectU(const D2D1_RECT_U* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->right);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1RectF(const D2D1_RECT_F* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->right);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1SizeU(const D2D1_SIZE_U* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1SizeF(const D2D1_SIZE_F* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1Point2L(const D2D1_POINT_2L* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1Point2U(const D2D1_POINT_2U* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1Point2F(const D2D1_POINT_2F* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetX(LONG* ret)const
{
	*ret = myX;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetY(LONG* ret)const
{
	*ret = myY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetWidth(LONG* ret)const
{
	*ret = myWidth;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetHeight(LONG* ret)const
{
	*ret = myHeight;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetTop(LONG* ret)const
{
	LONG tY = 0;

	GetY(&tY);

	*ret = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetLeft(LONG* ret)const
{
	LONG tX = 0;

	GetX(&tX);

	*ret = tX;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetRight(LONG* ret)const
{
	LONG tX = 0, tW = 0;

	GetX(&tX);
	GetWidth(&tW);

	*ret = tX + tW;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetBottom(LONG* ret)const
{
	LONG tY = 0, tH = 0;

	GetY(&tY);
	GetHeight(&tH);

	*ret = tY + tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetCenter(MfxPoint* ret)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	ret->SetX((tX + tW) / 2);
	ret->SetY((tY + tH) / 2);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetPointPosition(MfxPoint* ret1, MfxPoint* ret2)const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	ret1->SetX(tX);
	ret1->SetY(tY);

	ret1->SetX(tX + tW);
	ret1->SetY(tY + tH);

	return Mfx_Return_Fine;
}



/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetX(LONG set)
{
	myMutexLock.WaitLock(&myX);

	myX = set;

	myMutexLock.UnLock(&myX);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetY(LONG set)
{
	myMutexLock.WaitLock(&myY);

	myY = set;

	myMutexLock.UnLock(&myY);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetWidth(LONG set)
{
	myMutexLock.WaitLock(&myWidth);

	myWidth = set;

	myMutexLock.UnLock(&myWidth);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetHeight(LONG set)
{
	myMutexLock.WaitLock(&myHeight);

	myHeight = set;

	myMutexLock.UnLock(&myHeight);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetTop(const LONG set)
{
	SetY(set);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetLeft(const LONG set)
{
	SetX(set);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetRight(const LONG set)
{
	SetWidth(set - myX);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetBottom(const LONG set)
{
	SetHeight(set - myY);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetCenter(const MfxPoint* set)
{
	MfxPoint tCPoint;
	LONG tX = 0, tY = 0;
	LONG tCX = 0, tCY = 0;
	LONG tSCX = 0, tSCY = 0;

	GetCenter(&tCPoint);

	tCPoint.GetX(&tCX);
	tCPoint.GetY(&tCY);

	GetX(&tX);
	GetY(&tY);

	set->GetX(&tSCX);
	set->GetY(&tSCY);

	SetX(tX + (tSCX - tCX));
	SetY(tY + (tSCY - tCY));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetPointPosition(const MfxPoint* set1, const MfxPoint* set2)
{
	LONG tX1 = 0, tX2 = 0, tY1 = 0, tY2 = 0;

	set1->GetX(&tX1);
	set1->GetY(&tY1);
	set2->GetX(&tX2);
	set2->GetY(&tY2);


	SetX(min(tX1, tX2));
	SetY(min(tY1, tY2));

	SetWidth(max(tX1, tX2) - min(tX1, tX2));
	SetHeight(max(tY1, tY2) - min(tY1, tY2));

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::Union(const MfxRect* set, MfxRect* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tRT = 0, tRL = 0, tRR = 0, tRB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	set->GetTop(&tRT);
	set->GetLeft(&tRL);
	set->GetRight(&tRR);
	set->GetBottom(&tRB);

	ret->SetTop(min(tT, tRT));
	ret->SetLeft(min(tL, tRL));
	ret->SetRight(max(tR, tRR));
	ret->SetBottom(max(tB, tRB));

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::Union_Widely(MfxBase* set, MfxRect* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tRT = 0, tRL = 0, tRR = 0, tRB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	if (Mfx_Seccess(set->AutoFunc(MfxText("GetTop"), (&tRT))))
	{
		ret->SetTop(min(tT, tRT));
	}
	if (Mfx_Seccess(set->AutoFunc(MfxText("GetLeft"), (&tRL))))
	{
		ret->SetLeft(min(tL, tRL));
	}
	if (Mfx_Seccess(set->AutoFunc(MfxText("GetRight"), (&tRR))))
	{
		ret->SetRight(max(tR, tRR));
	}
	if (Mfx_Seccess(set->AutoFunc(MfxText("GetBottom"), (&tRB))))
	{
		ret->SetBottom(max
		(tB, tRB));
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::Intersect(const MfxRect* set, MfxRect* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tST = 0, tSL = 0, tSR = 0, tSB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	set->GetTop(&tST);
	set->GetLeft(&tSL);
	set->GetRight(&tSR);
	set->GetBottom(&tSB);

	LONG tTop = max(tT, tST);
	LONG tLeft = max(tL, tSL);
	LONG tRight = min(tR, tSR);
	LONG tBottom = min(tB, tSB);

	ret->SetTop(tTop);
	ret->SetLeft(tLeft);
	ret->SetRight(tRight);
	ret->SetBottom(tBottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::Intersect_Widely(MfxBase* set, MfxRect* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tST = 0, tSL = 0, tSR = 0, tSB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	if (Mfx_Seccess(set->AutoFunc(MfxText("GetTop"), &tST))
		&& Mfx_Seccess(set->AutoFunc(MfxText("GetLeft"), &tSL))
		&& Mfx_Seccess(set->AutoFunc(MfxText("GetRight"), &tSR))
		&& Mfx_Seccess(set->AutoFunc(MfxText("GetBottom"), &tSB))
		)
	{
		LONG tTop = max(tT, tST);
		LONG tLeft = max(tL, tSL);
		LONG tRight = min(tR, tSR);
		LONG tBottom = min(tB, tSB);

		ret->SetTop(tTop);
		ret->SetLeft(tLeft);
		ret->SetRight(tRight);
		ret->SetBottom(tBottom);

		return Mfx_Return_Fine;
	}

	return Mfx_Return_Fail;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::Offset(const LONG setX, const LONG setY)
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	SetX(tX + setX);
	SetY(tY + setY);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::Inflate(const LONG setX, const LONG setY)
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	SetX(tX - setX);
	SetY(tY - setY);
	SetWidth(tW + 2 * setX);
	SetHeight(tH + 2 * setY);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::IsEmpty(bool* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	*ret = (tW <= 0 || tH <= 0);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::IsRectInside(const MfxRect* set, bool* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tST = 0, tSL = 0, tSR = 0, tSB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	set->GetTop(&tST);
	set->GetLeft(&tSL);
	set->GetRight(&tSR);
	set->GetBottom(&tSB);

	*ret = (tT <= tST) && (tR >= tSR) && (tL <= tSL) && (tB >= tSB);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::IsPointInside(const MfxPoint* set, bool* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tSX = 0, tSY = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	set->GetX(&tSX);
	set->GetY(&tSY);

	*ret = (tT < tSY) && (tB > tSY) && (tL < tSX) && (tR > tSX);

	return Mfx_Return_Fine;
}
