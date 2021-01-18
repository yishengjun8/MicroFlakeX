#include "pch.h"
#include "MfxTypes.h"

MfxOBJECT_INIT_0(MfxSize)
MfxOBJECT_AUTOFUNC_REG(MfxSize, Init, 0);
MfxOBJECT_AUTOFUNC_REG(MfxSize, GetD2D1SizeF, 1);
MfxOBJECT_AUTOFUNC_REG(MfxSize, GetD2D1SizeU, 2);
MfxOBJECT_AUTOFUNC_REG(MfxSize, Empty, 3);
MfxOBJECT_AUTOFUNC_REG(MfxSize, Inflate, 4);
MfxOBJECT_AUTOFUNC_REG(MfxSize, SetWidth, 5);
MfxOBJECT_AUTOFUNC_REG(MfxSize, SetHeight, 6);
MfxOBJECT_AUTOFUNC_REG(MfxSize, GetWidth, 7);
MfxOBJECT_AUTOFUNC_REG(MfxSize, GetHeight, 8);
MfxOBJECT_INIT_1(MfxSize)
MfxOBJECT_AUTOFUNC_CASE_2(MfxSize, MfxType, Init, 0)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, GetD2D1SizeF, 1)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, GetD2D1SizeU, 2)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, Empty, 3)
MfxOBJECT_AUTOFUNC_CASE_2(MfxSize, MfxType, Inflate, 4)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, SetWidth, 5)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, SetHeight, 6)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, GetWidth, 7)
MfxOBJECT_AUTOFUNC_CASE_1(MfxSize, MfxType, GetHeight, 8)
MfxOBJECT_INIT_2(MfxSize, MfxType);

MicroFlakeX::MfxSize::MfxSize()
{
	MfxCODELOCK(this);
	myWidth = myHeight = 0;
}

MicroFlakeX::MfxSize::~MfxSize()
{
	MfxCODELOCK(this);
}

MfxReturn MicroFlakeX::MfxSize::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	*ret = new MfxSize;
	((MfxSize*)(*ret))->Init(myWidth, myHeight);
	return MfxFINE;
}

MfxBase& MicroFlakeX::MfxSize::operator=(MfxBase& rhs)
{
	MfxCODELOCK(this);
	rhs.AutoFunc(L"GetWidth", &myWidth);
	rhs.AutoFunc(L"GetHeight", &myHeight);
	return *this;
}

BOOL MicroFlakeX::MfxSize::operator==(MfxBase& rhs)
{
	MfxCODELOCK(this);
	FLOAT tW = 0, tH = 0;
	rhs.AutoFunc(L"GetWidth", &tW);
	rhs.AutoFunc(L"GetHeight", &tH);
	return tW == myWidth && tH == myHeight;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::Init(FLOAT setWidth, FLOAT setHeight)
{
	MfxCODELOCK(this);
	myWidth = setWidth;
	myHeight = setHeight;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeF(D2D1_SIZE_F* ret)
{
	MfxCODELOCK(this);
	GetWidth(&(ret->width));
	GetHeight(&(ret->height));
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeU(D2D1_SIZE_U* ret)
{
	MfxCODELOCK(this);
	FLOAT tW = 0, tH = 0;
	GetWidth(&tW);
	GetHeight(&tH);
	ret->width = tW;
	ret->height = tH;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::Empty(BOOL* ret)
{
	MfxCODELOCK(this);
	*ret = myWidth < 0 || myHeight < 0;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::Inflate(FLOAT setX, FLOAT setY)
{
	MfxCODELOCK(this);
	myWidth += 2 * setX;
	myHeight += 2 * setY;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::SetWidth(FLOAT set)
{
	MfxCODELOCK(this);
	myWidth = set;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::SetHeight(FLOAT set)
{
	MfxCODELOCK(this);
	myHeight = set;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::GetWidth(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myWidth;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxSize::GetHeight(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myHeight;
	return MfxFINE;
}