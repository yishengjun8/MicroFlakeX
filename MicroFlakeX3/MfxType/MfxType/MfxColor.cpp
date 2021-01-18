#include "pch.h"
#include "MfxTypes.h"

MfxOBJECT_INIT_0(MfxColor)
MfxOBJECT_INIT_1(MfxColor)
MfxOBJECT_INIT_2(MfxColor, MfxType);

static const UINT32 sc_redShift = 16;
static const UINT32 sc_greenShift = 8;
static const UINT32 sc_blueShift = 0;

static const UINT32 sc_redMask = 0xff << sc_redShift;
static const UINT32 sc_greenMask = 0xff << sc_greenShift;
static const UINT32 sc_blueMask = 0xff << sc_blueShift;

MicroFlakeX::MfxColor::MfxColor()
{
	MfxCODELOCK(this);
	myA = myR = myG = myB = 0;
}

MicroFlakeX::MfxColor::~MfxColor()
{
	MfxCODELOCK(this);
}

MfxReturn MicroFlakeX::MfxColor::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	*ret = new MfxColor;
	((MfxColor*)(*ret))->Init(myA, myR, myG, myB);
	return MfxFINE;
}

MfxBase& MicroFlakeX::MfxColor::operator=(MfxBase& rhs)
{
	MfxCODELOCK(this);
	rhs.AutoFunc(L"GetA", &myA);
	rhs.AutoFunc(L"GetR", &myR);
	rhs.AutoFunc(L"GetG", &myG);
	rhs.AutoFunc(L"GetB", &myB);
	return *this;
}

BOOL MicroFlakeX::MfxColor::operator==(MfxBase& rhs)
{
	MfxCODELOCK(this);
	FLOAT tA = 0, tR = 0, tG = 0, tB = 0;
	rhs.AutoFunc(L"GetA", &tA);
	rhs.AutoFunc(L"GetR", &tR);
	rhs.AutoFunc(L"GetG", &tG);
	rhs.AutoFunc(L"GetB", &tB);
	return tA == myA && tR == myR && tG == myG && tB == myB;
}

MfxReturn MicroFlakeX::MfxColor::Init(FLOAT setA, FLOAT setR, FLOAT setG, FLOAT setB)
{
	MfxCODELOCK(this);
	myA = setA;
	myR = setR;
	myG = setG;
	myB = setB;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::SetColor(FLOAT setA, UINT32 set)
{
	MfxCODELOCK(this);
	myR = static_cast<FLOAT>((set & sc_redMask) >> sc_redShift) / 255.f;
	myG = static_cast<FLOAT>((set & sc_greenMask) >> sc_greenShift) / 255.f;
	myB = static_cast<FLOAT>((set & sc_blueMask) >> sc_blueShift) / 255.f;
	myA = setA;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::GetD2D1ColorF(D2D1_COLOR_F* ret)
{
	MfxCODELOCK(this);
	GetA(&(ret->a));
	GetR(&(ret->r));
	GetG(&(ret->g));
	GetB(&(ret->b));
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::GetA(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myA;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::GetR(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myR;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::GetG(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myG;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::GetB(FLOAT* ret)
{
	MfxCODELOCK(this);
	*ret = myB;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxColor::GetRGB(UINT32* ret)
{
	MfxCODELOCK(this);
	*ret = RGB(myR, myG, myB);
	return MfxFINE;
}