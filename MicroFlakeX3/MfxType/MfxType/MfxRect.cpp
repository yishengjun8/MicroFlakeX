#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxRect)
MfxObject_Init_1(MfxRect, Reset)
MfxAutoFunc_AutoEnumBig(MfxRect, \
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
	1, GetGdipSize, \
	1, GetGdipPoint, \
	\
	1, GetGdipRectF, \
	1, GetGdipSizeF, \
	1, GetGdipPointF, \
	\
	1, GetD2D1RectU, \
	1, GetD2D1SizeU, \
	1, GetD2D1PointU, \
	\
	1, GetD2D1RectF, \
	1, GetD2D1SizeF, \
	1, GetD2D1PointF, \
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
	1, SetGdipSize, \
	1, SetGdipPoint, \
	\
	1, SetGdipRectF, \
	1, SetGdipSizeF, \
	1, SetGdipPointF, \
	\
	1, SetD2D1RectU, \
	1, SetD2D1SizeU, \
	1, SetD2D1PointU, \
	\
	1, SetD2D1RectF, \
	1, SetD2D1SizeF, \
	1, SetD2D1PointF, \
	\
	\
	1, GetX, \
	1, GetY, \
	1, GetWidth, \
	1, GetHeight, \
	1, GetTop, \
	1, GetLeft, \
	1, GetRight, \
	1, GetBottom, \
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
	2, Union, \
	2, Union_Widely, \
	2, Except, \
	2, Except_Widely, \
	2, Intersect, \
	2, Intersect_Widely, \
	\
	2, Offset, \
	2, Inflate, \
	\
	1, IsEmpty, \
	2, IsPointInside, \
	\
	END, END);
MfxObject_Init_2(MfxRect, MfxType);


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

MicroFlakeX::MfxRect::MfxRect(MfxRect& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.GetX(&tSX);
	set.GetY(&tSY);
	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(MfxRect&& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.GetX(&tSX);
	set.GetY(&tSY);
	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(MfxSize& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(MfxSize&& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(MfxPoint& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.GetX(&tSX);
	set.GetY(&tSY);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxRect::MfxRect(MfxPoint&& set)
{
	LONG tSX = 0, tSY = 0, tSW = 0, tSH = 0;

	set.GetX(&tSX);
	set.GetY(&tSY);

	SetX(tSX);
	SetY(tSY);
	SetWidth(tSW);
	SetHeight(tSH);
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

MfxRect& MicroFlakeX::MfxRect::operator=(MfxRect& rhs)
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

MfxRect& MicroFlakeX::MfxRect::operator=(MfxRect&& rhs)
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

MfxRect& MicroFlakeX::MfxRect::operator=(MfxSize& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(MfxSize&& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(MfxPoint& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);	

	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(MfxPoint&& rhs)
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

bool MicroFlakeX::MfxRect::operator==(MfxRect& rhs)
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

bool MicroFlakeX::MfxRect::operator==(MfxRect&& rhs)
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
* 
* 
* 
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetRect(MfxRect* ret)
{
	return ret->Reset(myX, myY, myWidth, myHeight);
}

MfxReturn MicroFlakeX::MfxRect::GetSize(MfxSize* ret)
{
	return ret->Reset(myWidth, myHeight);
}

MfxReturn MicroFlakeX::MfxRect::GetPoint(MfxPoint* ret)
{
	return ret->Reset(myX, myY);
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetRECT(RECT* ret)
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

MfxReturn MicroFlakeX::MfxRect::GetSIZE(SIZE* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->cx = tW;
	ret->cy = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetPOINT(POINT* ret)
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
MfxReturn MicroFlakeX::MfxRect::GetGdipRect(Gdiplus::Rect* ret)
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

MfxReturn MicroFlakeX::MfxRect::GetGdipSize(Gdiplus::Size* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipPoint(Gdiplus::Point* ret)
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipRectF(Gdiplus::RectF* ret)
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

MfxReturn MicroFlakeX::MfxRect::GetGdipSizeF(Gdiplus::SizeF* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetGdipPointF(Gdiplus::PointF* ret)
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
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::GetD2D1RectU(D2D1_RECT_U* ret)
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

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeU(D2D1_SIZE_U* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1PointU(D2D1_POINT_2U* ret)
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectF(D2D1_RECT_F* ret)
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

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeF(D2D1_SIZE_F* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1PointF(D2D1_POINT_2F* ret)
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
MfxReturn MicroFlakeX::MfxRect::SetRect(MfxRect* set)
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

MfxReturn MicroFlakeX::MfxRect::SetSize(MfxSize* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetPoint(MfxPoint* set)
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
MfxReturn MicroFlakeX::MfxRect::SetRECT(RECT* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->left);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetSIZE(SIZE* set)
{
	SetWidth(set->cx);
	SetHeight(set->cy);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetPOINT(POINT* set)
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
MfxReturn MicroFlakeX::MfxRect::SetGdipRect(Gdiplus::Rect* set)
{
	SetX(set->X);
	SetY(set->Y);
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipSize(Gdiplus::Size* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipPoint(Gdiplus::Point* set)
{
	SetX(set->X);
	SetY(set->Y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipRectF(Gdiplus::RectF* set)
{
	SetX(set->X);
	SetY(set->Y);
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipSizeF(Gdiplus::SizeF* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetGdipPointF(Gdiplus::PointF* set)
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
MfxReturn MicroFlakeX::MfxRect::SetD2D1RectU(D2D1_RECT_U* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->right);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1SizeU(D2D1_SIZE_U* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1PointU(D2D1_POINT_2U* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1RectF(D2D1_RECT_F* set)
{
	SetTop(set->top);
	SetLeft(set->left);
	SetRight(set->right);
	SetBottom(set->bottom);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1SizeF(D2D1_SIZE_F* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetD2D1PointF(D2D1_POINT_2F* set)
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
MfxReturn MicroFlakeX::MfxRect::GetX(LONG* ret)
{
	*ret = myX;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetY(LONG* ret)
{
	*ret = myY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetWidth(LONG* ret)
{
	*ret = myWidth;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetHeight(LONG* ret)
{
	*ret = myHeight;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetTop(LONG* ret)
{
	*ret = myY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetLeft(LONG* ret)
{
	*ret = myX;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetRight(LONG* ret)
{
	*ret = myX + myWidth;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::GetBottom(LONG* ret)
{
	*ret = myY + myHeight;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::SetX(LONG set)
{
	myX = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetY(LONG set)
{
	myY = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetWidth(LONG set)
{
	myWidth = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetHeight(LONG set)
{
	myHeight = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetTop(LONG set)
{
	myY = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetLeft(LONG set)
{
	myX = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetRight(LONG set)
{
	myWidth = set - myX;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::SetBottom(LONG set)
{
	myHeight = set - myY;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxRect::Union(MfxRect* set, MfxRect* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxRect::Union_Widely(MfxBase* set, MfxRect* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxRect::Except(MfxRect* set, MfxRect* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxRect::Except_Widely(MfxBase* set, MfxRect* ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxRect::Intersect(MfxRect* set, MfxRect* ret)
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
MfxReturn MicroFlakeX::MfxRect::Offset(LONG setX, LONG setY)
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	SetX(tX + setX);
	SetY(tY + setY);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxRect::Inflate(LONG setX, LONG setY)
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

MfxReturn MicroFlakeX::MfxRect::IsPointInside(MfxPoint* set, bool* ret)
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

/**
MfxReturn MicroFlakeX::MfxRect::Collision(MfxBase* set, BOOL* ret)
{
	LONG myTop = 0, myLeft = 0, myRight = 0, myBottom = 0;
	LONG setTop = 0, setLeft = 0, setRight = 0, setBottom = 0;

	GetTop(&myTop); set->AutoFunc(MfxText("GetBottom"), &setTop);
	GetLeft(&myLeft); set->AutoFunc(MfxText("GetLeft"), &myLeft);
	GetRight(&myRight); set->AutoFunc(MfxText("GetRight"), &myRight);
	GetBottom(&myBottom); set->AutoFunc(MfxText("GetBottom"), &myBottom);

	*ret = (myLeft < setRight) && (myTop < setBottom) &&
		(myRight > setLeft) && (myBottom > setTop);
	return Mfx_Return_Fine;
}
/**/
