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
	MfxCodeLock(this);
	myWidth = myHeight = 0;
}

MicroFlakeX::MfxSize::~MfxSize()
{
	MfxCodeLock(this);
}

MfxReturn MicroFlakeX::MfxSize::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	*ret = new MfxSize;
	((MfxSize*)(*ret))->Init(myWidth, myHeight);
	return RFine;
}

MfxBase& MicroFlakeX::MfxSize::operator=(MfxBase& rhs)
{
	MfxCodeLock(this);
	rhs.AutoFunc(L"GetWidth", &myWidth);
	rhs.AutoFunc(L"GetHeight", &myHeight);
	return *this;
}

BOOL MicroFlakeX::MfxSize::operator==(MfxBase& rhs)
{
	MfxCodeLock(this);
	FLOAT tW = 0, tH = 0;
	rhs.AutoFunc(L"GetWidth", &tW);
	rhs.AutoFunc(L"GetHeight", &tH);
	return tW == myWidth && tH == myHeight;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::Init(FLOAT setWidth, FLOAT setHeight)
{
	MfxCodeLock(this);
	myWidth = setWidth;
	myHeight = setHeight;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeF(D2D1_SIZE_F* ret)
{
	MfxCodeLock(this);
	GetWidth(&(ret->width));
	GetHeight(&(ret->height));
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeU(D2D1_SIZE_U* ret)
{
	MfxCodeLock(this);
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->width = tW;
	ret->height = tH;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetSIZE(SIZE* ret)
{
	MfxCodeLock(this);
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->cx = tW;
	ret->cy = tH;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::Empty(BOOL* ret)
{
	MfxCodeLock(this);
	*ret = myWidth < 0 || myHeight < 0;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::Inflate(FLOAT setX, FLOAT setY)
{
	MfxCodeLock(this);
	myWidth += 2 * setX;
	myHeight += 2 * setY;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::SetWidth(FLOAT set)
{
	MfxCodeLock(this);
	myWidth = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::SetHeight(FLOAT set)
{
	MfxCodeLock(this);
	myHeight = set;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetWidth(FLOAT* ret)
{
	MfxCodeLock(this);
	*ret = myWidth;
	return RFine;
}

MfxReturn MicroFlakeX::MfxSize::GetHeight(FLOAT* ret)
{
	MfxCodeLock(this);
	*ret = myHeight;
	return RFine;
}