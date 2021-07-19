#include "pch.h"
#include "MfxType.h"

MFX_OBJ_REFLECTION_INIT(MfxColor)
MFX_OBJ_REFLECTION_ENDINIT(MfxColor, MfxBase, \
	Reset, \
	\
	GetPRGB, \
	GetRGB, \
	\
	GetD2D1ColorF, \
	\
	SetPRGB, \
	SetRGB, \
	\
	SetD2D1ColorF, \
	\
	GetA, \
	GetR, \
	GetG, \
	GetB, \
	\
	SetA, \
	SetR, \
	SetG, \
	SetB);


/**************************************************************
*
*
*
***************************************************************/
static UINT32 sc_rShift = 16;
static UINT32 sc_gShift = 8;
static UINT32 sc_bShift = 0;

static UINT32 sc_rMask = 0xff << sc_rShift;
static UINT32 sc_gMask = 0xff << sc_gShift;
static UINT32 sc_bMask = 0xff << sc_bShift;


/**************************************************************
*
*
*
***************************************************************/
MicroFlakeX::MfxColor::MfxColor()
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	SetA(tA);
	SetR(tR);
	SetG(tG);
	SetB(tB);
}

MicroFlakeX::MfxColor::MfxColor(MfxBase& set)
{
	LONG tSA = 0, tSR = 0, tSG = 0, tSB = 0;

	set.Reflection(MFX_TXT_W("GetA"), &tSA);
	set.Reflection(MFX_TXT_W("GetR"), &tSR);
	set.Reflection(MFX_TXT_W("GetG"), &tSG);
	set.Reflection(MFX_TXT_W("GetB"), &tSB);

	SetA(tSA);
	SetR(tSR);
	SetG(tSG);
	SetB(tSB);
}

MicroFlakeX::MfxColor::MfxColor(const MfxColor* set)
{
	LONG tSA = 0, tSR = 0, tSG = 0, tSB = 0;

	set->GetA(&tSA);
	set->GetR(&tSR);
	set->GetG(&tSG);
	set->GetB(&tSB);

	SetA(tSA);
	SetR(tSR);
	SetG(tSG);
	SetB(tSB);
}

MicroFlakeX::MfxColor::MfxColor(const LONG setA, const LONG setR, const LONG setG, const LONG setB)
{
	SetA(setA);
	SetR(setR);
	SetG(setG);
	SetB(setB);
}

MicroFlakeX::MfxColor::~MfxColor()
{
}

MfxReturn MicroFlakeX::MfxColor::MFX_OBJ_ENABLE_CLONE(ret)
{
	*ret = new MfxColor(this);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxBase& MicroFlakeX::MfxColor::operator=(MfxBase& rhs)
{
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetA"), &tRA)))
	{
		SetA(tRA);
	}
	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetR"), &tRR)))
	{
		SetR(tRR);
	}
	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetG"), &tRG)))
	{
		SetG(tRG);
	}
	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetB"), &tRB)))
	{
		SetB(tRB);
	}

	return *this;
}

MfxColor& MicroFlakeX::MfxColor::operator=(const MfxColor* rhs)
{
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	rhs->GetA(&tRA);
	rhs->GetR(&tRR);
	rhs->GetG(&tRG);
	rhs->GetB(&tRB);

	SetA(tRA);
	SetR(tRR);
	SetG(tRG);
	SetB(tRB);

	return *this;
}

MfxColor& MicroFlakeX::MfxColor::operator=(const MfxColor& rhs)
{
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	rhs.GetA(&tRA);
	rhs.GetR(&tRR);
	rhs.GetG(&tRG);
	rhs.GetB(&tRB);

	SetA(tRA);
	SetR(tRR);
	SetG(tRG);
	SetB(tRB);

	return *this;
}

MfxColor& MicroFlakeX::MfxColor::operator=(const MfxColor&& rhs)
{
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	rhs.GetA(&tRA);
	rhs.GetR(&tRR);
	rhs.GetG(&tRG);
	rhs.GetB(&tRB);

	SetA(tRA);
	SetR(tRR);
	SetG(tRG);
	SetB(tRB);

	return *this;
}


/**************************************************************
*
*
*
***************************************************************/
bool MicroFlakeX::MfxColor::operator==(MfxBase& rhs)
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	if (MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetA"), &tRA))
		&& MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetR"), &tRR))
		&& MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetG"), &tRG))
		&& MFX_SECCESS(rhs.Reflection(MFX_TXT_W("GetB"), &tRB))
		)
	{
		return tA == tRA && tR == tRR && tG == tRG && tB == tRB;
	}

	return false;
}

bool MicroFlakeX::MfxColor::operator==(const MfxColor* rhs) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	rhs->GetA(&tRA);
	rhs->GetR(&tRR);
	rhs->GetG(&tRG);
	rhs->GetB(&tRB);

	return tA == tRA && tR == tRR && tG == tRG && tB == tRB;
}

bool MicroFlakeX::MfxColor::operator==(const MfxColor& rhs) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	rhs.GetA(&tRA);
	rhs.GetR(&tRR);
	rhs.GetG(&tRG);
	rhs.GetB(&tRB);
	
	return tA == tRA && tR == tRR && tG == tRG && tB == tRB;
}

bool MicroFlakeX::MfxColor::operator==(const MfxColor&& rhs) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	rhs.GetA(&tRA);
	rhs.GetR(&tRR);
	rhs.GetG(&tRG);
	rhs.GetB(&tRB);

	return tA == tRA && tR == tRR && tG == tRG && tB == tRB;
}


MicroFlakeX::MfxColor::operator COLORREF() const
{
	LONG a;
	COLORREF tCOLORREF;
	GetRGB(&a, &tCOLORREF);

	return tCOLORREF;
}

MicroFlakeX::MfxColor::operator D2D1_COLOR_F() const
{
	D2D1_COLOR_F tCOLORF;

	GetD2D1ColorF(&tCOLORF);

	return tCOLORF;
}

MicroFlakeX::MfxColor::operator Gdiplus::Color() const
{
	Gdiplus::Color tColor;

	GetGdipColor(&tColor);

	return tColor;
}

/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::Reset(LONG setA, LONG setR, LONG setG, LONG setB)
{
	SetA(setA);
	SetR(setR);
	SetG(setG);
	SetB(setB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetColor(MfxColor* ret) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	ret->SetA(tA);
	ret->SetR(tR);
	ret->SetG(tG);
	ret->SetB(tB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetGdipColor(Gdiplus::Color* ret) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	ret->SetValue(Gdiplus::Color::MakeARGB(tA, tR, tG, tB));

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::GetPRGB(UINT32* ret) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	tR = tR * tA / 255;
	tG = tG * tA / 255;
	tB = tB * tA / 255;

	*ret = RGB(tR, tG, tB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetRGB(LONG* retA, COLORREF* ret) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	*retA = tA;
	*ret = RGB(tR, tG, tB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetD2D1ColorF(D2D1_COLOR_F* ret) const
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	ret->a = (double)tA / 255;
	ret->r = (double)tR / 255;
	ret->g = (double)tG / 255;
	ret->b = (double)tB / 255;

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::SetColor(const MfxColor* set)
{
	LONG tSA = 0, tSR = 0, tSG = 0, tSB = 0;

	set->GetA(&tSA);
	set->GetR(&tSR);
	set->GetG(&tSG);
	set->GetB(&tSB);

	SetA(tSA);
	SetR(tSR);
	SetG(tSG);
	SetB(tSB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetGdipColor(const Gdiplus::Color* set)
{
	LONG tSA = 0, tSR = 0, tSG = 0, tSB = 0;

	tSA = set->GetA();
	tSR = set->GetR();
	tSG = set->GetG();
	tSB = set->GetB();

	SetA(tSA);
	SetR(tSR);
	SetG(tSG);
	SetB(tSB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetPRGB(const UINT32 set)
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	tA = 255;
	tR = static_cast<LONG>((set & sc_rMask) >> sc_rShift) / 255.f;
	tG = static_cast<LONG>((set & sc_gMask) >> sc_gShift) / 255.f;
	tB = static_cast<LONG>((set & sc_bMask) >> sc_bShift) / 255.f;

	SetA(tA);
	SetR(tR);
	SetG(tG);
	SetB(tB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetRGB(const LONG setA, const UINT32 set)
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	tA = setA;
	tR = static_cast<LONG>((set & sc_rMask) >> sc_rShift) / 255.f;
	tG = static_cast<LONG>((set & sc_gMask) >> sc_gShift) / 255.f;
	tB = static_cast<LONG>((set & sc_bMask) >> sc_bShift) / 255.f;

	SetA(tA);
	SetR(tR);
	SetG(tG);
	SetB(tB);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetD2D1ColorF(const D2D1_COLOR_F* set)
{
	SetA(set->a * 255);
	SetR(set->r * 255);
	SetG(set->g * 255);
	SetB(set->b * 255);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::GetA(LONG* ret) const
{
	*ret = myA;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetR(LONG* ret) const
{
	*ret = myR;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetG(LONG* ret) const
{
	*ret = myG;

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::GetB(LONG* ret) const
{
	*ret = myB;

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::SetA(const LONG set)
{
	myMemberLock.WaitLock(&myA);

	myA = set;
	
	myMemberLock.UnLock(&myA);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetR(const LONG set)
{
	myMemberLock.WaitLock(&myR);

	myR = set;

	myMemberLock.UnLock(&myR);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetG(const LONG set)
{
	myMemberLock.WaitLock(&myG);

	myG = set;

	myMemberLock.UnLock(&myG);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxColor::SetB(const LONG set)
{
	myMemberLock.WaitLock(&myB);

	myB = set;

	myMemberLock.UnLock(&myB);

	return MFX_RET_SECCESS;
}