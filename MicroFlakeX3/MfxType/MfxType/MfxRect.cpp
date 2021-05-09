#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxRect)
MfxObject_Init_1(MfxRect, Init)
MfxAutoFunc_4(MfxRect, Init, GetD2D1RectU)
MfxAutoFunc_1(MfxRect, GetD2D1RectU, GetD2D1SizeU)
MfxAutoFunc_1(MfxRect, GetD2D1SizeU, GetD2D1PointU)
MfxAutoFunc_1(MfxRect, GetD2D1PointU, GetD2D1RectF)
MfxAutoFunc_1(MfxRect, GetD2D1RectF, GetD2D1SizeF)
MfxAutoFunc_1(MfxRect, GetD2D1SizeF, GetD2D1PointF)
MfxAutoFunc_1(MfxRect, GetD2D1PointF, SetSize)
MfxAutoFunc_1(MfxRect, SetSize, SetPoint)
MfxAutoFunc_1(MfxRect, SetPoint, SetX)
MfxAutoFunc_1(MfxRect, SetX, SetY)
MfxAutoFunc_1(MfxRect, SetY, SetWidth)
MfxAutoFunc_1(MfxRect, SetWidth, SetHeight)
MfxAutoFunc_1(MfxRect, SetHeight, SetTop)
MfxAutoFunc_1(MfxRect, SetTop, SetLeft)
MfxAutoFunc_1(MfxRect, SetLeft, SetRight)
MfxAutoFunc_1(MfxRect, SetRight, SetBottom)
MfxAutoFunc_1(MfxRect, SetBottom, GetSize)
MfxAutoFunc_1(MfxRect, GetSize, GetPoint)
MfxAutoFunc_1(MfxRect, GetPoint, GetX)
MfxAutoFunc_1(MfxRect, GetX, GetY)
MfxAutoFunc_1(MfxRect, GetY, GetWidth)
MfxAutoFunc_1(MfxRect, GetWidth, GetHeight)
MfxAutoFunc_1(MfxRect, GetHeight, GetTop)
MfxAutoFunc_1(MfxRect, GetTop, GetLeft)
MfxAutoFunc_1(MfxRect, GetLeft, GetRight)
MfxAutoFunc_1(MfxRect, GetRight, GetBottom)
MfxAutoFunc_1(MfxRect, GetBottom, Empty)
MfxAutoFunc_1(MfxRect, Empty, Offset)
MfxAutoFunc_2(MfxRect, Offset, Inflate)
MfxAutoFunc_2(MfxRect, Inflate, Collision)
MfxAutoFunc_2(MfxRect, Collision, PointInside)
MfxAutoFunc_2(MfxRect, PointInside, END)
MfxObject_Init_2(MfxRect, MfxType)

MicroFlakeX::MfxRect::MfxRect()
{
	myX = myY = myWidth = myHeight = 0;
}

MicroFlakeX::MfxRect::MfxRect(MfxRect* set)
{
	myX = set->myX;
	myY = set->myY;
	myWidth = set->myWidth;
	myHeight = set->myHeight;
}

MicroFlakeX::MfxRect::MfxRect(MfxSize* set)
{
	myX = 0;
	myY = 0;
	myWidth = set->myWidth;
	myHeight = set->myHeight;
}

MicroFlakeX::MfxRect::MfxRect(MfxPoint* set)
{
	myX = set->myX;
	myY = set->myY;
	myWidth = 0;
	myHeight = 0;
}

MicroFlakeX::MfxRect::MfxRect(FLOAT setX, FLOAT setY, FLOAT setWidth, FLOAT setHeight)
{
	myX = setX;
	myY = setY;
	myWidth = setWidth;
	myHeight = setHeight;
}

MicroFlakeX::MfxRect::~MfxRect()
{
}

MfxReturn MicroFlakeX::MfxRect::Clone(MfxBase** ret)
{
	*ret = new MfxRect(this);
	return RFine;
}

MfxBase& MicroFlakeX::MfxRect::operator=(MfxBase& rhs)
{
	rhs.AutoFunc(MfxText("GetX"), &myX);
	rhs.AutoFunc(MfxText("GetY"), &myY);
	rhs.AutoFunc(MfxText("GetWidth"), &myWidth);
	rhs.AutoFunc(MfxText("GetHeight"), &myHeight);
	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(MfxRect& rhs)
{
	myX = rhs.myX;
	myY = rhs.myY;
	myWidth = rhs.myWidth;
	myHeight = rhs.myHeight;
	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(MfxSize& rhs)
{
	myWidth = rhs.myWidth;
	myHeight = rhs.myHeight;
	return *this;
}

MfxRect& MicroFlakeX::MfxRect::operator=(MfxPoint& rhs)
{
	myX = rhs.myX;
	myY = rhs.myY;
	return *this;
}

BOOL MicroFlakeX::MfxRect::operator==(MfxBase& rhs)
{
	FLOAT tX = 0, tY = 0, tW = 0, tH = 0;
	rhs.AutoFunc(MfxText("GetX"), &tX);
	rhs.AutoFunc(MfxText("GetY"), &tY);
	rhs.AutoFunc(MfxText("GetWidth"), &tW);
	rhs.AutoFunc(MfxText("GetHeight"), &tH);
	return tX == myX && tY == myY && tW == myWidth && tH == myHeight;
}

BOOL MicroFlakeX::MfxRect::operator==(MfxRect& rhs)
{
	return rhs.myX == myX && rhs.myY == myY && rhs.myWidth == myWidth && rhs.myHeight == myHeight;
}

MfxReturn MicroFlakeX::MfxRect::Init(FLOAT setX, FLOAT setY, FLOAT setWidth, FLOAT setHeight)
{
	myX = setX;
	myY = setY;
	myWidth = setWidth;
	myHeight = setHeight;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectU(D2D1_RECT_U* ret)
{
	FLOAT tT = 0, tL = 0, tR = 0, tB = 0;
	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->top = tT;
	ret->left = tL;
	ret->right = tR;
	ret->bottom = tB;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeU(D2D1_SIZE_U* ret)
{
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->width = tW;
	ret->height = tH;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1PointU(D2D1_POINT_2U* ret)
{
	FLOAT tX = 0, tY = 0;
	GetX(&tX);
	GetY(&tY);
	ret->x = tX;
	ret->y = tY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1RectF(D2D1_RECT_F* ret)
{
	GetTop(&(ret->top));
	GetLeft(&(ret->left));
	GetRight(&(ret->right));
	GetBottom(&(ret->bottom));
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1SizeF(D2D1_SIZE_F* ret)
{
	GetWidth(&(ret->width));
	GetHeight(&(ret->height));
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetD2D1PointF(D2D1_POINT_2F* ret)
{
	GetX(&(ret->x));
	GetY(&(ret->y));
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetRECT(RECT* ret)
{
	FLOAT tT = 0, tL = 0, tR = 0, tB = 0;
	GetTop(&tT);
	GetLeft(&tL);
	GetRight(&tR);
	GetBottom(&tB);

	ret->top = tT;
	ret->left = tL;
	ret->right = tR;
	ret->bottom = tB;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetSIZE(SIZE* ret)
{
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->cx = tW;
	ret->cy = tH;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetPOINT(POINT* ret)
{
	FLOAT tX = 0, tY = 0;
	GetX(&tX);
	GetY(&tY);
	ret->x = tX;
	ret->y = tY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetSize(MfxSize* set)
{
	set->GetWidth(&myWidth);
	set->GetHeight(&myHeight);
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetPoint(MfxPoint* set)
{
	set->GetX(&myX);
	set->GetY(&myY);
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetX(FLOAT set)
{
	myX = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetY(FLOAT set)
{
	myY = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetWidth(FLOAT set)
{
	myWidth = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetHeight(FLOAT set)
{
	myHeight = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetTop(FLOAT set)
{
	myY = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetLeft(FLOAT set)
{
	myX = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetRight(FLOAT set)
{
	myWidth = set - myX;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::SetBottom(FLOAT set)
{
	myHeight = set - myY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetSize(MfxSize* ret)
{
	ret->Init(myWidth, myHeight);
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetPoint(MfxPoint* ret)
{
	ret->Init(myX, myY);
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetX(FLOAT* ret)
{
	*ret = myX;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetY(FLOAT* ret)
{
	*ret = myY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetWidth(FLOAT* ret)
{
	*ret = myWidth;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetHeight(FLOAT* ret)
{
	*ret = myHeight;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetTop(FLOAT* ret)
{
	*ret = myY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetLeft(FLOAT* ret)
{
	*ret = myX;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetRight(FLOAT* ret)
{
	*ret = myX + myWidth;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::GetBottom(FLOAT* ret)
{
	*ret = myY + myHeight;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::Empty(BOOL* ret)
{
	*ret = myWidth < 0 || myHeight < 0;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::Offset(FLOAT setX, FLOAT setY)
{
	myX += setX;
	myY += setY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::Inflate(FLOAT setX, FLOAT setY)
{
	myX -= setX;
	myX -= setY;
	myWidth += 2 * setX;
	myHeight += 2 * setY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::Collision(MfxBase* set, BOOL* ret)
{
	FLOAT myTop = 0, myLeft = 0, myRight = 0, myBottom = 0;
	FLOAT setTop = 0, setLeft = 0, setRight = 0, setBottom = 0;

	GetTop(&myTop); set->AutoFunc(MfxText("GetBottom"), &setTop);
	GetLeft(&myLeft); set->AutoFunc(MfxText("GetLeft"), &myLeft);
	GetRight(&myRight); set->AutoFunc(MfxText("GetRight"), &myRight);
	GetBottom(&myBottom); set->AutoFunc(MfxText("GetBottom"), &myBottom);

	*ret = (myLeft < setRight) && (myTop < setBottom) &&
		(myRight > setLeft) && (myBottom > setTop);
	return RFine;
}

MfxReturn MicroFlakeX::MfxRect::PointInside(MfxPoint* set, BOOL* ret)
{
	FLOAT myTop = 0, myLeft = 0, myRight = 0, myBottom = 0;

	GetTop(&myTop); GetLeft(&myLeft); GetRight(&myRight); GetBottom(&myBottom);

	*ret = (myTop < set->myY) && (myBottom > set->myY) &&
		(myLeft < set->myX) && (myRight > set->myX);

	return RFine;
}
