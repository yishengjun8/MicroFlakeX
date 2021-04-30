#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxPoint)
MfxObject_Register(MfxPoint, Init, 0);
MfxObject_Register(MfxPoint, GetD2D1PointU, 1);
MfxObject_Register(MfxPoint, GetD2D1PointF, 2);
MfxObject_Register(MfxPoint, Offset, 3);
MfxObject_Register(MfxPoint, SetX, 4);
MfxObject_Register(MfxPoint, SetY, 5);
MfxObject_Register(MfxPoint, GetX, 6);
MfxObject_Register(MfxPoint, GetY, 7);
MfxObject_Init_1(MfxPoint)
MfxObject_Case_2(MfxPoint, MfxType, Init, 0)
MfxObject_Case_1(MfxPoint, MfxType, GetD2D1PointU, 1)
MfxObject_Case_1(MfxPoint, MfxType, GetD2D1PointF, 2)
MfxObject_Case_2(MfxPoint, MfxType, Offset, 3)
MfxObject_Case_1(MfxPoint, MfxType, SetX, 4)
MfxObject_Case_1(MfxPoint, MfxType, SetY, 5)
MfxObject_Case_1(MfxPoint, MfxType, GetX, 6)
MfxObject_Case_1(MfxPoint, MfxType, GetY, 7)
MfxObject_Init_2(MfxPoint, MfxType);

MicroFlakeX::MfxPoint::MfxPoint()
{
	myX = myY = 0;
}

MicroFlakeX::MfxPoint::MfxPoint(MfxRect* set)
{
	myX = set->myX;
	myY = set->myY;
}

MicroFlakeX::MfxPoint::MfxPoint(MfxPoint* set)
{
	myX = set->myX;
	myY = set->myY;
}

MicroFlakeX::MfxPoint::MfxPoint(FLOAT setX, FLOAT setY)
{
	myX = setX;
	myY = setY;
}

MicroFlakeX::MfxPoint::~MfxPoint()
{
}

MfxReturn MicroFlakeX::MfxPoint::Clone(MfxBase** ret)
{
	*ret = new MfxPoint(this);
	return RFine;
}

MfxBase& MicroFlakeX::MfxPoint::operator=(MfxBase& rhs)
{
	rhs.AutoFunc(MfxText("GetX"), &myX);
	rhs.AutoFunc(MfxText("GetY"), &myY);
	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(MfxRect& rhs)
{
	myX = rhs.myX;
	myY = rhs.myY;
	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(MfxPoint& rhs)
{
	myX = rhs.myX;
	myY = rhs.myY;
	return *this;
}

BOOL MicroFlakeX::MfxPoint::operator==(MfxBase& rhs)
{
	FLOAT tX = 0, tY = 0;
	rhs.AutoFunc(MfxText("GetX"), &tX);
	rhs.AutoFunc(MfxText("GetY"), &tY);
	return tX == myX && tY == myY;
	return RFine;
}

BOOL MicroFlakeX::MfxPoint::operator==(MfxPoint& rhs)
{
	return rhs.myX == myX && rhs.myY == myY;
}

MfxReturn MicroFlakeX::MfxPoint::Init(FLOAT setX, FLOAT setY)
{
	myX = setX;
	myY = setY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::GetD2D1PointU(D2D1_POINT_2U* ret)
{
	FLOAT tX = 0, tY = 0;
	GetX(&tX);
	GetY(&tY);
	ret->x = tX;
	ret->y = tY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::GetD2D1PointF(D2D1_POINT_2F* ret)
{
	GetX(&(ret->x));
	GetY(&(ret->y));
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::Offset(FLOAT setX, FLOAT setY)
{
	myX += setX;
	myY += setY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::SetX(FLOAT set)
{
	myX = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::SetY(FLOAT set)
{
	myY = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::GetX(FLOAT* ret)
{
	*ret = myX;
	return RFine;
}

MfxReturn MicroFlakeX::MfxPoint::GetY(FLOAT* ret)
{
	*ret = myY;
	return RFine;
}