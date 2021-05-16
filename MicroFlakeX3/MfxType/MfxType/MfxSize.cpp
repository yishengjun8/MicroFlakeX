#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxSize)
MfxObject_Init_1(MfxSize, Reset)
MfxAutoFunc_AutoEnumBig(MfxSize, \
	2, Reset, \
	\
	1, GetSize,\
	\
	1, GetSIZE, \
	\
	1, GetGdipSize, \
	1, GetGdipSizeF, \
	\
	1, GetD2D1SizeF, \
	1, GetD2D1SizeU, \
	\
	\
	1, SetSize, \
	\
	1, SetSIZE, \
	\
	1, SetGdipSize, \
	1, SetGdipSizeF, \
	\
	1, SetD2D1SizeF, \
	1, SetD2D1SizeU, \
	\
	\
	1, GetWidth, \
	1, GetHeight, \
	\
	1, SetWidth, \
	1, SetHeight, \
	\
	\
	2, Inflate, \
	\
	1, IsEmpty, \
	\
	END, END);
MfxObject_Init_2(MfxSize, MfxBase);


/**************************************************************
*
*
*
***************************************************************/
MicroFlakeX::MfxSize::MfxSize()
{
	LONG tSW = 0, tSH = 0;

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxBase& set)
{
	LONG tSW = 0, tSH = 0;

	set.AutoFunc(MfxText("GetWidth"), &tSW);
	set.AutoFunc(MfxText("GetHeight"), &tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxRect* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxRect& set)
{
	LONG tSW = 0, tSH = 0;

	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxRect&& set)
{
	LONG tSW = 0, tSH = 0;

	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxSize* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxSize& set)
{
	LONG tSW = 0, tSH = 0;

	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(MfxSize&& set)
{
	LONG tSW = 0, tSH = 0;

	set.GetWidth(&tSW);
	set.GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(LONG setWidth, LONG setHeight)
{
	SetWidth(setWidth);
	SetHeight(setHeight);
}

MicroFlakeX::MfxSize::~MfxSize()
{
}

MfxReturn MicroFlakeX::MfxSize::Clone(MfxBase** ret)
{
	*ret = new MfxSize(*this);
	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxBase& MicroFlakeX::MfxSize::operator=(MfxBase& rhs)
{
	LONG tRW = 0, tRH = 0;

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetWidth"), &tRW)))
	{
		SetWidth(tRW);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetHeight"), &tRH)))
	{
		SetHeight(tRH);
	}

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxRect* rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxRect& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxRect&& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxSize* rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxSize& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(MfxSize&& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}


/**************************************************************
*
*
*
***************************************************************/
bool MicroFlakeX::MfxSize::operator==(MfxBase& rhs) const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetWidth"), &tRW))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetHeight"), &tRH))
		)
	{
		return tW == tRW && tH == tRH;
	}

	return false;
}

bool MicroFlakeX::MfxSize::operator==(MfxSize* rhs) const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	return tW == tRW && tH == tRH;
}

bool MicroFlakeX::MfxSize::operator==(MfxSize& rhs) const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	return tW == tRW && tH == tRH;
}

bool MicroFlakeX::MfxSize::operator==(MfxSize&& rhs) const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	return tW == tRW && tH == tRH;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::Reset(LONG setWidth, LONG setHeight)
{
	SetWidth(setWidth);
	SetHeight(setHeight);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::GetSize(MfxSize* ret) const
{
	return ret->Reset(myWidth, myHeight);
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::GetSIZE(SIZE* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->cx = tW;
	ret->cy = tH;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::GetGdipSize(Gdiplus::Size* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetGdipSizeF(Gdiplus::SizeF* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeF(D2D1_SIZE_F* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeU(D2D1_SIZE_U* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::SetSize(MfxSize* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::SetSIZE(SIZE* set)
{
	SetWidth(set->cx);
	SetHeight(set->cy);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::SetGdipSize(Gdiplus::Size* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetGdipSizeF(Gdiplus::SizeF* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetD2D1SizeF(D2D1_SIZE_F* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetD2D1SizeU(D2D1_SIZE_U* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::GetWidth(LONG* ret) const
{
	*ret = myWidth;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetHeight(LONG* ret) const
{
	*ret = myHeight;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::SetWidth(LONG set)
{
	myWidth = set;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetHeight(LONG set)
{
	myHeight = set;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::Inflate(LONG setX, LONG setY)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	SetWidth(tW + 2 * setX);
	SetHeight(tH + 2 * setY);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::IsEmpty(bool* ret) const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	*ret = (tW <= 0 || tH <= 0);

	return Mfx_Return_Fine;
}