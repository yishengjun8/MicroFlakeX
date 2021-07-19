#include "pch.h"
#include "MfxType.h"

MFX_OBJ_REFLECTION_INIT(MfxRect)
MFX_OBJ_REFLECTION_ENDINIT(MfxRect, MfxBase, \
	Reset, \
	\
	GetRect, \
	GetSize, \
	GetPoint, \
	\
	GetRECT, \
	GetSIZE, \
	GetPOINT, \
	\
	GetGdipRect, \
	GetGdipRectF, \
	\
	GetGdipSize, \
	GetGdipSizeF, \
	\
	GetGdipPoint, \
	GetGdipPointF, \
	\
	GetD2D1RectL, \
	GetD2D1RectU, \
	GetD2D1RectF, \
	\
	GetD2D1SizeU, \
	GetD2D1SizeF, \
	\
	GetD2D1Point2L, \
	GetD2D1Point2U, \
	GetD2D1Point2F, \
	\
	SetRect, \
	SetSize, \
	SetPoint, \
	\
	SetRECT, \
	SetSIZE, \
	SetPOINT, \
	\
	SetGdipRect, \
	SetGdipRectF, \
	\
	SetGdipSize, \
	SetGdipSizeF, \
	\
	SetGdipPoint, \
	SetGdipPointF, \
	\
	SetD2D1RectL, \
	SetD2D1RectU, \
	SetD2D1RectF, \
	\
	SetD2D1SizeU, \
	SetD2D1SizeF, \
	\
	SetD2D1Point2L, \
	SetD2D1Point2U, \
	SetD2D1Point2F, \
	\
	\
	GetX, \
	GetY, \
	GetWidth, \
	GetHeight, \
	\
	GetTop, \
	GetLeft, \
	GetRight, \
	GetBottom, \
	\
	GetCenter, \
	GetPointPosition, \
	\
	\
	SetX, \
	SetY, \
	SetWidth, \
	SetHeight, \
	\
	SetTop, \
	SetLeft, \
	SetRight, \
	SetBottom, \
	\
	SetCenter, \
	SetPointPosition, \
	\
	Union, \
	Union_Widely, \
	Intersect, \
	Intersect_Widely, \
	\
	Offset, \
	Inflate, \
	\
	IsEmpty, \
	IsPointInside);


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

	set.Reflection(MFX_TXT_W("GetX"), &tSX);
	set.Reflection(MFX_TXT_W("GetY"), &tSY);
	set.Reflection(MFX_TXT_W("GetWidth"), &tSW);
	set.Reflection(MFX_TXT_W("GetHeight"), &tSH);

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

MfxReturn MicroFlakeX::MfxRect::MFX_OBJ_ENABLE_CLONE(ret)
{
	*ret = new MfxRect(*this);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/

MfxBase& MicroFlakeX::MfxRect::operator=(MfxBase& rhs)
{
	LONG tRX = 0, tRY = 0, tRW = 0, tRH = 0;

	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetX"), &tRX)))
	{
		SetX(tRX);
	}
	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetY"), &tRY)))
	{
		SetY(tRY);
	}
	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetWidth"), &tRW)))
	{
		SetWidth(tRW);
	}
	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetHeight"), &tRH)))
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

	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetX"), &tRX))
		&& MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetY"), &tRY))
		&& MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetWidth"), &tRW))
		&& MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetHeight"), &tRH))
		)
	{
		return tX == tRX && tY == tRY && tW == tRW && tH == tRH;
	}

	return false;
}

bool MicroFlakeX::MfxRect::operator==(const MfxRect* rhs) const
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

bool MicroFlakeX::MfxRect::operator==(const MfxRect& rhs) const
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

bool MicroFlakeX::MfxRect::operator==(const MfxRect&& rhs) const
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

MicroFlakeX::MfxRect::operator D2D1_RECT_L() const
{
	D2D1_RECT_L tD2D1_RECT_L;

	GetD2D1RectL(&tD2D1_RECT_L);

	return tD2D1_RECT_L;
}

MicroFlakeX::MfxRect::operator D2D1_RECT_U() const
{
	D2D1_RECT_U tD2D1_RECT_U;

	GetD2D1RectU(&tD2D1_RECT_U);

	return tD2D1_RECT_U;
}

MicroFlakeX::MfxRect::operator D2D1_RECT_F() const
{
	D2D1_RECT_F tD2D1_RECT_F;

	GetD2D1RectF(&tD2D1_RECT_F);

	return tD2D1_RECT_F;
}

MicroFlakeX::MfxRect::operator D2D1_SIZE_U() const
{
	D2D1_SIZE_U tD2D1_SIZE_U;

	GetD2D1SizeU(&tD2D1_SIZE_U);

	return tD2D1_SIZE_U;
}

MicroFlakeX::MfxRect::operator D2D1_SIZE_F() const
{
	D2D1_SIZE_F tD2D1_SIZE_F;

	GetD2D1SizeF(&tD2D1_SIZE_F);

	return tD2D1_SIZE_F;
}

MicroFlakeX::MfxRect::operator D2D1_POINT_2L() const
{
	D2D1_POINT_2L tD2D1_POINT_2L;

	GetD2D1Point2L(&tD2D1_POINT_2L);

	return tD2D1_POINT_2L;
}

MicroFlakeX::MfxRect::operator D2D1_POINT_2U() const
{
	D2D1_POINT_2U tD2D1_POINT_2U;

	GetD2D1Point2U(&tD2D1_POINT_2U);

	return tD2D1_POINT_2U;
}

MicroFlakeX::MfxRect::operator D2D1_POINT_2F() const
{
	D2D1_POINT_2F tD2D1_POINT_2F;

	GetD2D1Point2F(&tD2D1_POINT_2F);

	return tD2D1_POINT_2F;
}

MicroFlakeX::MfxRect::operator Gdiplus::Rect() const
{
	Gdiplus::Rect tRect;

	GetGdipRect(&tRect);

	return tRect;
}

MicroFlakeX::MfxRect::operator Gdiplus::RectF() const
{
	Gdiplus::RectF tRectF;

	GetGdipRectF(&tRectF);

	return tRectF;
}

MicroFlakeX::MfxRect::operator Gdiplus::Size() const
{
	Gdiplus::Size tSize;

	GetGdipSize(&tSize);

	return tSize;
}

MicroFlakeX::MfxRect::operator Gdiplus::SizeF() const
{
	Gdiplus::SizeF tSizeF;

	GetGdipSizeF(&tSizeF);

	return tSizeF;
}

MicroFlakeX::MfxRect::operator Gdiplus::Point() const
{
	Gdiplus::Point tPoint;

	GetGdipPoint(&tPoint);

	return tPoint;
}

MicroFlakeX::MfxRect::operator Gdiplus::PointF() const
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

	return MFX_RET_SECCESS;
}


/**************************************************************
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetRect(MfxRect* ret) const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	return ret->Reset(tX, tY, tW, tH);
}

MfxReturn MicroFlakeX::MfxRect::GetSize(MfxSize* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	return ret->Reset(tW, tH);
}

MfxReturn MicroFlakeX::MfxRect::GetPoint(MfxPoint* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	return ret->Reset(tX, tY);
}



/**************************************************************
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetRECT(RECT* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetSIZE(SIZE* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->cx = tW;
	ret->cy = tH;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetPOINT(POINT* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return MFX_RET_SECCESS;
}


/**************************************************************
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetGdipRect(Gdiplus::Rect* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipRectF(Gdiplus::RectF* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipSize(Gdiplus::Size* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipSizeF(Gdiplus::SizeF* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipPoint(Gdiplus::Point* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipPointF(Gdiplus::PointF* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return MFX_RET_SECCESS;
}


/**************************************************************
* 
* 
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetD2D1RectL(D2D1_RECT_L* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectU(D2D1_RECT_U* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectF(D2D1_RECT_F* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeU(D2D1_SIZE_U* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeF(D2D1_SIZE_F* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1Point2L(D2D1_POINT_2L* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return MFX_RET_SECCESS;
}
MfxReturn MicroFlakeX::MfxRect::GetD2D1Point2U(D2D1_POINT_2U* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1Point2F(D2D1_POINT_2F* ret) const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetSize(const MfxSize* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetPoint(const MfxPoint* set)
{
	LONG tSX = 0, tSY = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);

	SetX(tSX);
	SetY(tSY);

	return MFX_RET_SECCESS;
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
	
	SetWidth(set->right - set->left);
	SetHeight(set->bottom - set->top);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetSIZE(const SIZE* set)
{
	SetWidth(set->cx);
	SetHeight(set->cy);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetPOINT(const POINT* set)
{
	SetX(set->x);
	SetY(set->y);

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipRectF(const Gdiplus::RectF* set)
{
	SetX(set->X);
	SetY(set->Y);
	SetWidth(set->Width);
	SetHeight(set->Height);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipSize(const Gdiplus::Size* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipSizeF(const Gdiplus::SizeF* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipPoint(const Gdiplus::Point* set)
{
	SetX(set->X);
	SetY(set->Y);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipPointF(const Gdiplus::PointF* set)
{
	SetX(set->X);
	SetY(set->Y);

	return MFX_RET_SECCESS;
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

	SetWidth(set->right - set->left);
	SetHeight(set->bottom - set->top);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1RectU(const D2D1_RECT_U* set)
{
	SetTop(set->top);
	SetLeft(set->left);

	SetWidth(set->right - set->left);
	SetHeight(set->bottom - set->top);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1RectF(const D2D1_RECT_F* set)
{
	SetTop(set->top);
	SetLeft(set->left);

	SetWidth(set->right - set->left);
	SetHeight(set->bottom - set->top);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1SizeU(const D2D1_SIZE_U* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1SizeF(const D2D1_SIZE_F* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1Point2L(const D2D1_POINT_2L* set)
{
	SetX(set->x);
	SetY(set->y);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1Point2U(const D2D1_POINT_2U* set)
{
	SetX(set->x);
	SetY(set->y);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1Point2F(const D2D1_POINT_2F* set)
{
	SetX(set->x);
	SetY(set->y);

	return MFX_RET_SECCESS;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetX(LONG* ret) const
{
	*ret = myX;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetY(LONG* ret) const
{
	*ret = myY;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetWidth(LONG* ret) const
{
	*ret = myWidth;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetHeight(LONG* ret) const
{
	*ret = myHeight;

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetTop(LONG* ret) const
{
	LONG tY = 0;

	GetY(&tY);

	*ret = tY;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetLeft(LONG* ret) const
{
	LONG tX = 0;

	GetX(&tX);

	*ret = tX;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetRight(LONG* ret) const
{
	LONG tX = 0, tW = 0;

	GetX(&tX);
	GetWidth(&tW);

	*ret = tX + tW;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetBottom(LONG* ret) const
{
	LONG tY = 0, tH = 0;

	GetY(&tY);
	GetHeight(&tH);

	*ret = tY + tH;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetCenter(MfxPoint* ret) const
{
	LONG tX = 0, tY = 0, tW = 0, tH = 0;

	GetX(&tX);
	GetY(&tY);
	GetWidth(&tW);
	GetHeight(&tH);

	ret->SetX((tX + tW) / 2);
	ret->SetY((tY + tH) / 2);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::GetPointPosition(MfxPoint* ret1, MfxPoint* ret2) const
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

	return MFX_RET_SECCESS;
}



/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetX(LONG set)
{
	myMemberLock.WaitLock(&myX);

	myX = set;

	myMemberLock.UnLock(&myX);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetY(LONG set)
{
	myMemberLock.WaitLock(&myY);

	myY = set;

	myMemberLock.UnLock(&myY);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetWidth(LONG set)
{
	myMemberLock.WaitLock(&myWidth);

	myWidth = set;

	myMemberLock.UnLock(&myWidth);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetHeight(LONG set)
{
	myMemberLock.WaitLock(&myHeight);

	myHeight = set;

	myMemberLock.UnLock(&myHeight);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetTop(const LONG set)
{
	SetY(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetLeft(const LONG set)
{
	SetX(set);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetRight(const LONG set)
{
	SetX(set - myWidth);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::SetBottom(const LONG set)
{
	SetY(set - myHeight);

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::Union(const MfxRect* set, MfxRect* ret) const
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

	ret->SetWidth(max(tR, tRR) - min(tL, tRL));
	ret->SetHeight(max(tB, tRB) - min(tT, tRT));

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::Union_Widely(MfxBase* set, MfxRect* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tRT = 0, tRL = 0, tRR = 0, tRB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	if (MFX_SECCESS(set->Reflection(MFX_TXT_W("GetTop"), (&tRT))))
	{
		ret->SetTop(min(tT, tRT));
		if (MFX_SECCESS(set->Reflection(MFX_TXT_W("GetBottom"), (&tRB))))
		{
			ret->SetHeight(max(tB, tRB) - min(tT, tRT));
		}
	}
	if (MFX_SECCESS(set->Reflection(MFX_TXT_W("GetLeft"), (&tRL))))
	{
		ret->SetLeft(min(tL, tRL));
		if (MFX_SECCESS(set->Reflection(MFX_TXT_W("GetRight"), (&tRR))))
		{
			ret->SetWidth(max(tR, tRR) - min(tL, tRL));
		}
	}
	
	

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::Intersect(const MfxRect* set, MfxRect* ret) const
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

	ret->SetWidth(tRight - tLeft);
	ret->SetHeight(tBottom - tTop);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::Intersect_Widely(MfxBase* set, MfxRect* ret)
{
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tST = 0, tSL = 0, tSR = 0, tSB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	if (MFX_SECCESS(set->Reflection(MFX_TXT_W("GetTop"), &tST))
		&& MFX_SECCESS(set->Reflection(MFX_TXT_W("GetLeft"), &tSL))
		&& MFX_SECCESS(set->Reflection(MFX_TXT_W("GetRight"), &tSR))
		&& MFX_SECCESS(set->Reflection(MFX_TXT_W("GetBottom"), &tSB))
		)
	{
		LONG tTop = max(tT, tST);
		LONG tLeft = max(tL, tSL);
		LONG tRight = min(tR, tSR);
		LONG tBottom = min(tB, tSB);

		ret->SetTop(tTop);
		ret->SetLeft(tLeft);

		ret->SetWidth(tRight - tLeft);
		ret->SetHeight(tBottom - tTop);

		return MFX_RET_SECCESS;
	}

	return MFX_RET_FAILED;
}

MfxReturn MicroFlakeX::MfxRect::InsideRect(const MfxRect* set, MfxRect* ret) const
{
	ret->SetRect(set);

	// ret最大大小限制为this的最大大小
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;
	GetWidth(&tW);
	GetHeight(&tH);

	ret->GetWidth(&tRW);
	ret->GetHeight(&tRH);

	if (tRW > tW)
	{
		ret->SetWidth(tW);
	}
	if (tRH > tH)
	{
		ret->SetHeight(tH);
	}

	// ret偏移到最接近的边上
	LONG tT = 0, tL = 0, tR = 0, tB = 0;
	LONG tRT = 0, tRL = 0, tRR = 0, tRB = 0;

	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->GetTop(&tRT);
	ret->GetLeft(&tRL);
	ret->GetRight(&tRR);
	ret->GetBottom(&tRB);

	if (tRT < tT)
	{
		ret->SetTop(tT);
	}

	if (tRL < tL)
	{
		ret->SetLeft(tL);
	}

	if (tRR > tR)
	{
		ret->SetRight(tR);
	}

	if (tRB > tB)
	{
		ret->SetBottom(tB);
	}

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
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

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::IsEmpty(bool* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	*ret = (tW <= 0 || tH <= 0);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::IsRectInside(const MfxRect* set, bool* ret) const
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

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxRect::IsPointInside(const MfxPoint* set, bool* ret) const
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

	return MFX_RET_SECCESS;
}
