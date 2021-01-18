#include "pch.h"
#include "MfxTypes.h"

MfxOBJECT_INIT_0(MfxPoint)
MfxOBJECT_AUTOFUNC_REG(MfxPoint, Init, 0);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, GetD2D1PointU, 1);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, GetD2D1PointF, 2);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, Offset, 3);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, SetX, 4);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, SetY, 5);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, GetX, 6);
MfxOBJECT_AUTOFUNC_REG(MfxPoint, GetY, 7);
MfxOBJECT_INIT_1(MfxPoint)
MfxOBJECT_AUTOFUNC_CASE_2(MfxPoint, MfxType, Init, 0)
MfxOBJECT_AUTOFUNC_CASE_1(MfxPoint, MfxType, GetD2D1PointU, 1)
MfxOBJECT_AUTOFUNC_CASE_1(MfxPoint, MfxType, GetD2D1PointF, 2)
MfxOBJECT_AUTOFUNC_CASE_2(MfxPoint, MfxType, Offset, 3)
MfxOBJECT_AUTOFUNC_CASE_1(MfxPoint, MfxType, SetX, 4)
MfxOBJECT_AUTOFUNC_CASE_1(MfxPoint, MfxType, SetY, 5)
MfxOBJECT_AUTOFUNC_CASE_1(MfxPoint, MfxType, GetX, 6)
MfxOBJECT_AUTOFUNC_CASE_1(MfxPoint, MfxType, GetY, 7)
MfxOBJECT_INIT_2(MfxPoint, MfxType);

MicroFlakeX::MfxPoint::MfxPoint()
{
	MfxCODELOCK(this);
	myX = myY = 0;
}

MicroFlakeX::MfxPoint::~MfxPoint()
{
	MfxCODELOCK(this);
}

MfxReturn MicroFlakeX::MfxPoint::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	*ret = new MfxPoint;
	((MfxPoint*)(*ret))->Init(myX, myY);
	return MfxFINE;
}

MfxBase& MicroFlakeX::MfxPoint::operator=(MfxBase& rhs)
{
	MfxCODELOCK(this);
	rhs.AutoFunc(L"GetX", &myX);
	rhs.AutoFunc(L"GetY", &myY);
	return *this;
}

BOOL MicroFlakeX::MfxPoint::operator==(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	MfxCODELOCK(this);
	FLOAT tX = 0, tY = 0;
	rhs.AutoFunc(L"GetX", &tX);
	rhs.AutoFunc(L"GetY", &tY);
	return tX == myX && tY == myY;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::Init(FLOAT setX, FLOAT setY)
{
	MfxCODELOCK(this);
	myX = setX;
	myY = setY;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::GetD2D1PointU(D2D1_POINT_2U* ret)
{
	MfxCODELOCK(this);
	FLOAT tX = 0, tY = 0;
	GetX(&tX);
	GetY(&tY);
	ret->x = tX;
	ret->y = tY;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::GetD2D1PointF(D2D1_POINT_2F* ret)
{
	MfxCODELOCK(this);
	GetX(&(ret->x));
	GetY(&(ret->y));
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::Offset(FLOAT setX, FLOAT setY)
{
	MfxCODELOCK(this);
	myX += setX;
	myY += setY;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::SetX(FLOAT set)
{
	MfxCODELOCK(this);
	myX = set;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::SetY(FLOAT set)
{
	MfxCODELOCK(this);
	myY = set;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::GetX(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myX;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxPoint::GetY(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myY;
	return MfxFINE;
}