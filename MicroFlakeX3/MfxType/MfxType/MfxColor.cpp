#include "pch.h"
#include "MfxTypes.h"

MfxObject_Init_0(MfxColor)
MfxObject_Register(MfxColor, Init, 0);
MfxObject_Register(MfxColor, SetColor, 1);
MfxObject_Register(MfxColor, GetD2D1ColorF, 2);
MfxObject_Register(MfxColor, SetA, 3);
MfxObject_Register(MfxColor, SetR, 4);
MfxObject_Register(MfxColor, SetG, 5);
MfxObject_Register(MfxColor, SetB, 6);
MfxObject_Register(MfxColor, GetA, 7);
MfxObject_Register(MfxColor, GetR, 8);
MfxObject_Register(MfxColor, GetG, 9);
MfxObject_Register(MfxColor, GetB, 10);
MfxObject_Register(MfxColor, GetRGB, 11);
MfxObject_Init_1(MfxColor)
MfxObject_Case_4(MfxColor, MfxType, Init, 0)
MfxObject_Case_2(MfxColor, MfxType, SetColor, 1)
MfxObject_Case_1(MfxColor, MfxType, GetD2D1ColorF, 2)
MfxObject_Case_1(MfxColor, MfxType, SetA, 3)
MfxObject_Case_1(MfxColor, MfxType, SetR, 4)
MfxObject_Case_1(MfxColor, MfxType, SetG, 5)
MfxObject_Case_1(MfxColor, MfxType, SetB, 6)
MfxObject_Case_1(MfxColor, MfxType, GetA, 7)
MfxObject_Case_1(MfxColor, MfxType, GetR, 8)
MfxObject_Case_1(MfxColor, MfxType, GetG, 9)
MfxObject_Case_1(MfxColor, MfxType, GetB, 10)
MfxObject_Case_1(MfxColor, MfxType, GetRGB, 11)
MfxObject_Init_2(MfxColor, MfxType);

static const UINT32 sc_redShift = 16;
static const UINT32 sc_greenShift = 8;
static const UINT32 sc_blueShift = 0;

static const UINT32 sc_redMask = 0xff << sc_redShift;
static const UINT32 sc_greenMask = 0xff << sc_greenShift;
static const UINT32 sc_blueMask = 0xff << sc_blueShift;

MicroFlakeX::MfxColor::MfxColor()
{
	myA = myR = myG = myB = 0;
}

MicroFlakeX::MfxColor::MfxColor(FLOAT setA, FLOAT setR, FLOAT setG, FLOAT setB)
{
	myA = setA;
	myR = setR;
	myG = setG;
	myB = setB;
}

MicroFlakeX::MfxColor::~MfxColor()
{
}

MfxReturn MicroFlakeX::MfxColor::Clone(MfxBase** ret)
{
	*ret = new MfxColor;
	((MfxColor*)(*ret))->Init(myA, myR, myG, myB);
	return RFine;
}

MfxBase& MicroFlakeX::MfxColor::operator=(MfxBase& rhs)
{
	rhs.AutoFunc(L"GetA", &myA);
	rhs.AutoFunc(L"GetR", &myR);
	rhs.AutoFunc(L"GetG", &myG);
	rhs.AutoFunc(L"GetB", &myB);
	return *this;
}

BOOL MicroFlakeX::MfxColor::operator==(MfxBase& rhs)
{
	FLOAT tA = 0, tR = 0, tG = 0, tB = 0;
	rhs.AutoFunc(L"GetA", &tA);
	rhs.AutoFunc(L"GetR", &tR);
	rhs.AutoFunc(L"GetG", &tG);
	rhs.AutoFunc(L"GetB", &tB);
	return tA == myA && tR == myR && tG == myG && tB == myB;
}

MfxReturn MicroFlakeX::MfxColor::Init(FLOAT setA, FLOAT setR, FLOAT setG, FLOAT setB)
{
	myA = setA;
	myR = setR;
	myG = setG;
	myB = setB;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::SetColor(FLOAT setA, UINT32 set)
{
	myR = static_cast<FLOAT>((set & sc_redMask) >> sc_redShift) / 255.f;
	myG = static_cast<FLOAT>((set & sc_greenMask) >> sc_greenShift) / 255.f;
	myB = static_cast<FLOAT>((set & sc_blueMask) >> sc_blueShift) / 255.f;
	myA = setA;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::GetD2D1ColorF(D2D1_COLOR_F* ret)
{
	GetA(&(ret->a));
	GetR(&(ret->r));
	GetG(&(ret->g));
	GetB(&(ret->b));
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::SetA(FLOAT ret)
{
	myA = ret;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::SetR(FLOAT ret)
{
	myR = ret;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::SetG(FLOAT ret)
{
	myG = ret;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::SetB(FLOAT ret)
{
	myB = ret;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::GetA(FLOAT* ret)
{
	*ret = myA;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::GetR(FLOAT* ret)
{
	*ret = myR;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::GetG(FLOAT* ret)
{
	*ret = myG;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::GetB(FLOAT* ret)
{
	*ret = myB;
	return RFine;
}

MfxReturn MicroFlakeX::MfxColor::GetRGB(UINT32* ret)
{
	*ret = RGB(myR, myG, myB);
	return RFine;
}