#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxRect)
MfxObject_Register(MfxRect, Init, 0);
MfxObject_Register(MfxRect, GetD2D1RectU, 1);
MfxObject_Register(MfxRect, GetD2D1SizeU, 2);
MfxObject_Register(MfxRect, GetD2D1PointU, 3);
MfxObject_Register(MfxRect, GetD2D1RectF, 4);
MfxObject_Register(MfxRect, GetD2D1SizeF, 5);
MfxObject_Register(MfxRect, GetD2D1PointF, 6);
MfxObject_Register(MfxRect, SetSize, 7);
MfxObject_Register(MfxRect, SetPoint, 8);
MfxObject_Register(MfxRect, SetX, 9);
MfxObject_Register(MfxRect, SetY, 10);
MfxObject_Register(MfxRect, SetWidth, 11);
MfxObject_Register(MfxRect, SetHeight, 12);
MfxObject_Register(MfxRect, SetTop, 13);
MfxObject_Register(MfxRect, SetLeft, 14);
MfxObject_Register(MfxRect, SetRight, 15);
MfxObject_Register(MfxRect, SetBottom, 16);
MfxObject_Register(MfxRect, GetSize, 17);
MfxObject_Register(MfxRect, GetPoint, 18);
MfxObject_Register(MfxRect, GetX, 19);
MfxObject_Register(MfxRect, GetY, 20);
MfxObject_Register(MfxRect, GetWidth, 21);
MfxObject_Register(MfxRect, GetHeight, 22);
MfxObject_Register(MfxRect, GetTop, 23);
MfxObject_Register(MfxRect, GetLeft, 24);
MfxObject_Register(MfxRect, GetRight, 25);
MfxObject_Register(MfxRect, GetBottom, 26);
MfxObject_Register(MfxRect, Empty, 27);
MfxObject_Register(MfxRect, Offset, 28);
MfxObject_Register(MfxRect, Inflate, 29);
MfxObject_Register(MfxRect, Collision, 30);
MfxObject_Register(MfxRect, PointInside, 31);
MfxObject_Init_1(MfxRect)
MfxObject_Case_4(MfxRect, MfxType, Init, 0)
MfxObject_Case_1(MfxRect, MfxType, GetD2D1RectU, 1)
MfxObject_Case_1(MfxRect, MfxType, GetD2D1SizeU, 2)
MfxObject_Case_1(MfxRect, MfxType, GetD2D1PointU, 3)
MfxObject_Case_1(MfxRect, MfxType, GetD2D1RectF, 4)
MfxObject_Case_1(MfxRect, MfxType, GetD2D1SizeF, 5)
MfxObject_Case_1(MfxRect, MfxType, GetD2D1PointF, 6)
MfxObject_Case_1(MfxRect, MfxType, SetSize, 7)
MfxObject_Case_1(MfxRect, MfxType, SetPoint, 8)
MfxObject_Case_1(MfxRect, MfxType, SetX, 9)
MfxObject_Case_1(MfxRect, MfxType, SetY, 10)
MfxObject_Case_1(MfxRect, MfxType, SetWidth, 11)
MfxObject_Case_1(MfxRect, MfxType, SetHeight, 12)
MfxObject_Case_1(MfxRect, MfxType, SetTop, 13)
MfxObject_Case_1(MfxRect, MfxType, SetLeft, 14)
MfxObject_Case_1(MfxRect, MfxType, SetRight, 15)
MfxObject_Case_1(MfxRect, MfxType, SetBottom, 16)
MfxObject_Case_1(MfxRect, MfxType, GetSize, 17)
MfxObject_Case_1(MfxRect, MfxType, GetPoint, 18)
MfxObject_Case_1(MfxRect, MfxType, GetX, 19)
MfxObject_Case_1(MfxRect, MfxType, GetY, 20)
MfxObject_Case_1(MfxRect, MfxType, GetWidth, 21)
MfxObject_Case_1(MfxRect, MfxType, GetHeight, 22)
MfxObject_Case_1(MfxRect, MfxType, GetTop, 23)
MfxObject_Case_1(MfxRect, MfxType, GetLeft, 24)
MfxObject_Case_1(MfxRect, MfxType, GetRight, 25)
MfxObject_Case_1(MfxRect, MfxType, GetBottom, 26)
MfxObject_Case_1(MfxRect, MfxType, Empty, 27)
MfxObject_Case_2(MfxRect, MfxType, Offset, 28)
MfxObject_Case_2(MfxRect, MfxType, Inflate, 29)
MfxObject_Case_2(MfxRect, MfxType, Collision, 30)
MfxObject_Case_2(MfxRect, MfxType, PointInside, 31)
MfxObject_Init_2(MfxRect, MfxType);

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
