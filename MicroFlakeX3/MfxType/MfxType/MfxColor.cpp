#include "pch.h"
#include "MfxType.h"

MfxObject_Init(MfxColor)
MfxObject_EndInit(MfxColor, MfxBase, \
	4, Reset, \
	\
	1, GetPRGB, \
	2, GetRGB, \
	\
	1, GetD2D1ColorF, \
	\
	1, SetPRGB, \
	2, SetRGB, \
	\
	1, SetD2D1ColorF, \
	\
	1, GetA, \
	1, GetR, \
	1, GetG, \
	1, GetB, \
	\
	1, SetA, \
	1, SetR, \
	1, SetG, \
	1, SetB);


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

	set.AutoFunc(MfxText("GetA"), &tSA);
	set.AutoFunc(MfxText("GetR"), &tSR);
	set.AutoFunc(MfxText("GetG"), &tSG);
	set.AutoFunc(MfxText("GetB"), &tSB);

	SetA(tSA);
	SetR(tSR);
	SetG(tSG);
	SetB(tSB);
}

MicroFlakeX::MfxColor::MfxColor(MfxColor* set)
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

MicroFlakeX::MfxColor::MfxColor(LONG setA, LONG setR, LONG setG, LONG setB)
{
	SetA(setA);
	SetR(setR);
	SetG(setG);
	SetB(setB);
}

MicroFlakeX::MfxColor::~MfxColor()
{
}

MfxReturn MicroFlakeX::MfxColor::Clone(MfxBase** ret)
{
	*ret = new MfxColor(this);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxBase& MicroFlakeX::MfxColor::operator=(MfxBase& rhs)
{
	LONG tRA = 0, tRR = 0, tRG = 0, tRB = 0;

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetA"), &tRA)))
	{
		SetA(tRA);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetR"), &tRR)))
	{
		SetR(tRR);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetG"), &tRG)))
	{
		SetG(tRG);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetB"), &tRB)))
	{
		SetB(tRB);
	}

	return *this;
}

MfxColor& MicroFlakeX::MfxColor::operator=(MfxColor* rhs)
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

MfxColor& MicroFlakeX::MfxColor::operator=(MfxColor& rhs)
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

MfxColor& MicroFlakeX::MfxColor::operator=(MfxColor&& rhs)
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

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetA"), &tRA))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetR"), &tRR))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetG"), &tRG))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetB"), &tRB))
		)
	{
		return tA == tRA && tR == tRR && tG == tRG && tB == tRB;
	}

	return false;
}

bool MicroFlakeX::MfxColor::operator==(MfxColor* rhs)
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

bool MicroFlakeX::MfxColor::operator==(MfxColor& rhs)
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

bool MicroFlakeX::MfxColor::operator==(MfxColor&& rhs)
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


MicroFlakeX::MfxColor::operator COLORREF()
{
	LONG a;
	COLORREF tCOLORREF;
	GetRGB(&a, &tCOLORREF);

	return tCOLORREF;
}

MicroFlakeX::MfxColor::operator D2D1_COLOR_F()
{
	D2D1_COLOR_F tCOLORF;

	GetD2D1ColorF(&tCOLORF);

	return tCOLORF;
}

MicroFlakeX::MfxColor::operator Gdiplus::Color()
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetColor(MfxColor* ret)
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetGdipColor(Gdiplus::Color* ret)
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	ret->SetValue(Gdiplus::Color::MakeARGB(tA, tR, tG, tB));

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::GetPRGB(UINT32* ret)
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetRGB(LONG* retA, COLORREF* ret)
{
	LONG tA = 0, tR = 0, tG = 0, tB = 0;

	GetA(&tA);
	GetR(&tR);
	GetG(&tG);
	GetB(&tB);

	*retA = tA;
	*ret = RGB(tR, tG, tB);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetD2D1ColorF(D2D1_COLOR_F* ret)
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

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::SetColor(MfxColor* set)
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetGdipColor(Gdiplus::Color* set)
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetPRGB(UINT32 set)
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetRGB(LONG setA, UINT32 set)
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetD2D1ColorF(D2D1_COLOR_F* set)
{
	SetA(set->a * 255);
	SetR(set->r * 255);
	SetG(set->g * 255);
	SetB(set->b * 255);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::GetA(LONG* ret)
{
	*ret = myA;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetR(LONG* ret)
{
	*ret = myR;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetG(LONG* ret)
{
	*ret = myG;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::GetB(LONG* ret)
{
	*ret = myB;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxColor::SetA(LONG set)
{
	myMutexLock.WaitLock(&myA);

	myA = set;
	
	myMutexLock.UnLock(&myA);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetR(LONG set)
{
	myMutexLock.WaitLock(&myR);

	myR = set;

	myMutexLock.UnLock(&myR);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetG(LONG set)
{
	myMutexLock.WaitLock(&myG);

	myG = set;

	myMutexLock.UnLock(&myG);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxColor::SetB(LONG set)
{
	myMutexLock.WaitLock(&myB);

	myB = set;

	myMutexLock.UnLock(&myB);

	return Mfx_Return_Fine;
}