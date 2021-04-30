#include "pch.h"
#include "MfxTypes.h"

MfxObject_Init_0(MfxSize)
MfxObject_Register(MfxSize, Init, 0);
MfxObject_Register(MfxSize, GetD2D1SizeF, 1);
MfxObject_Register(MfxSize, GetD2D1SizeU, 2);
MfxObject_Register(MfxSize, Empty, 3);
MfxObject_Register(MfxSize, Inflate, 4);
MfxObject_Register(MfxSize, SetWidth, 5);
MfxObject_Register(MfxSize, SetHeight, 6);
MfxObject_Register(MfxSize, GetWidth, 7);
MfxObject_Register(MfxSize, GetHeight, 8);
MfxObject_Init_1(MfxSize)
MfxObject_Case_2(MfxSize, MfxType, Init, 0)
MfxObject_Case_1(MfxSize, MfxType, GetD2D1SizeF, 1)
MfxObject_Case_1(MfxSize, MfxType, GetD2D1SizeU, 2)
MfxObject_Case_1(MfxSize, MfxType, Empty, 3)
MfxObject_Case_2(MfxSize, MfxType, Inflate, 4)
MfxObject_Case_1(MfxSize, MfxType, SetWidth, 5)
MfxObject_Case_1(MfxSize, MfxType, SetHeight, 6)
MfxObject_Case_1(MfxSize, MfxType, GetWidth, 7)
MfxObject_Case_1(MfxSize, MfxType, GetHeight, 8)
MfxObject_Init_2(MfxSize, MfxType);

MicroFlakeX::MfxSize::MfxSize()
{
	myWidth = myHeight = 0;
}

MicroFlakeX::MfxSize::MfxSize(MfxRect* set)
{
	myWidth = set->myWidth;
	myHeight = set->myHeight;
}

MicroFlakeX::MfxSize::MfxSize(MfxSize* set)
{
	myWidth = set->myWidth;
	myHeight = set->myHeight;
}

MicroFlakeX::MfxSize::MfxSize(FLOAT setWidth, FLOAT setHeight)
{
	myWidth = setWidth;
	myHeight = setHeight;
}

MicroFlakeX::MfxSize::~MfxSize()
{
}

MfxReturn MicroFlakeX::MfxSize::Clone(MfxBase** ret)
{
	*ret = new MfxSize(this);
	return RFine;
}

MfxBase& MicroFlakeX::MfxSize::operator=(MfxBase& rhs)
{
	rhs.AutoFunc(MfxText("GetWidth"), &myWidth);
	rhs.AutoFunc(MfxText("GetHeight"), &myHeight);
	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxRect& rhs)
{
	myWidth = rhs.myWidth;
	myHeight = rhs.myHeight;
	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxSize& rhs)
{
	myWidth = rhs.myWidth;
	myHeight = rhs.myHeight;
	return *this;
}

BOOL MicroFlakeX::MfxSize::operator==(MfxBase& rhs)
{
	FLOAT tW = 0, tH = 0;
	rhs.AutoFunc(L"GetWidth", &tW);
	rhs.AutoFunc(L"GetHeight", &tH);
	return tW == myWidth && tH == myHeight;
	return RFine;
}

BOOL MicroFlakeX::MfxSize::operator==(MfxSize& rhs)
{
	return rhs.myWidth == myWidth && rhs.myHeight == myHeight;
}

MfxReturn MicroFlakeX::MfxSize::Init(FLOAT setWidth, FLOAT setHeight)
{
	myWidth = setWidth;
	myHeight = setHeight;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeF(D2D1_SIZE_F* ret)
{
	GetWidth(&(ret->width));
	GetHeight(&(ret->height));
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeU(D2D1_SIZE_U* ret)
{
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->width = tW;
	ret->height = tH;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetSIZE(SIZE* ret)
{
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->cx = tW;
	ret->cy = tH;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::Empty(BOOL* ret)
{
	*ret = myWidth < 0 || myHeight < 0;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::Inflate(FLOAT setX, FLOAT setY)
{
	myWidth += 2 * setX;
	myHeight += 2 * setY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::SetWidth(FLOAT set)
{
	myWidth = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::SetHeight(FLOAT set)
{
	myHeight = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetWidth(FLOAT* ret)
{
	*ret = myWidth;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetHeight(FLOAT* ret)
{
	*ret = myHeight;
	return RFine;
}