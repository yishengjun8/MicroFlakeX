#include "pch.h"
#include "MfxType.h"

MfxObject_Init(MfxSize)
MfxObject_EndInit(MfxSize, MfxBase, \
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
	1, IsEmpty);


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

MicroFlakeX::MfxSize::MfxSize(const MfxRect* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(const MfxSize* set)
{
	LONG tSW = 0, tSH = 0;

	set->GetWidth(&tSW);
	set->GetHeight(&tSH);

	SetWidth(tSW);
	SetHeight(tSH);
}

MicroFlakeX::MfxSize::MfxSize(const LONG setWidth, const LONG setHeight)
{
	SetWidth(setWidth);
	SetHeight(setHeight);
}

MicroFlakeX::MfxSize::~MfxSize()
{
}

MfxReturn MicroFlakeX::MfxSize::Clone(pMfxBase* ret)const
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

MfxSize& MicroFlakeX::MfxSize::operator=(const MfxRect* rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(const MfxRect& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(const MfxRect&& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(const MfxSize* rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(const MfxSize& rhs)
{
	LONG tRW = 0, tRH = 0;

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	SetWidth(tRW);
	SetHeight(tRH);

	return *this;
}

MfxSize& MicroFlakeX::MfxSize::operator=(const MfxSize&& rhs)
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
bool MicroFlakeX::MfxSize::operator==(MfxBase& rhs)
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

bool MicroFlakeX::MfxSize::operator==(const MfxSize* rhs)const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	rhs->GetWidth(&tRW);
	rhs->GetHeight(&tRH);

	return tW == tRW && tH == tRH;
}

bool MicroFlakeX::MfxSize::operator==(const MfxSize& rhs)const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	return tW == tRW && tH == tRH;
}

bool MicroFlakeX::MfxSize::operator==(const MfxSize&& rhs)const
{
	LONG tW = 0, tH = 0;
	LONG tRW = 0, tRH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	rhs.GetWidth(&tRW);
	rhs.GetHeight(&tRH);

	return tW == tRW && tH == tRH;
}

MicroFlakeX::MfxSize::operator D2D1_SIZE_U()const
{
	D2D1_SIZE_U tD2D1_SIZE_U;

	GetD2D1SizeU(&tD2D1_SIZE_U);

	return tD2D1_SIZE_U;
}

MicroFlakeX::MfxSize::operator D2D1_SIZE_F()const
{
	D2D1_SIZE_F tD2D1_SIZE_F;

	GetD2D1SizeF(&tD2D1_SIZE_F);

	return tD2D1_SIZE_F;
}

MicroFlakeX::MfxSize::operator Gdiplus::Size()const
{
	Gdiplus::Size tSize;

	GetGdipSize(&tSize);

	return tSize;
}

MicroFlakeX::MfxSize::operator Gdiplus::SizeF()const
{
	Gdiplus::SizeF tSizeF;

	GetGdipSizeF(&tSizeF);

	return tSizeF;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::Reset(const LONG setWidth, const LONG setHeight)
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
MfxReturn MicroFlakeX::MfxSize::GetSize(MfxSize* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	return ret->Reset(tW, tH);
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::GetSIZE(SIZE* ret)const
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
MfxReturn MicroFlakeX::MfxSize::GetGdipSize(Gdiplus::Size* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetGdipSizeF(Gdiplus::SizeF* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->Width = tW;
	ret->Height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeF(D2D1_SIZE_F* ret)const
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	ret->width = tW;
	ret->height = tH;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetD2D1SizeU(D2D1_SIZE_U* ret)const
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
MfxReturn MicroFlakeX::MfxSize::SetSize(const MfxSize* set)
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
MfxReturn MicroFlakeX::MfxSize::SetSIZE(const SIZE* set)
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
MfxReturn MicroFlakeX::MfxSize::SetGdipSize(const Gdiplus::Size* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetGdipSizeF(const Gdiplus::SizeF* set)
{
	SetWidth(set->Width);
	SetHeight(set->Height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetD2D1SizeF(const D2D1_SIZE_F* set)
{
	SetWidth(set->width);
	SetHeight(set->height);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetD2D1SizeU(const D2D1_SIZE_U* set)
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
MfxReturn MicroFlakeX::MfxSize::GetWidth(LONG* ret)const
{
	*ret = myWidth;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::GetHeight(LONG* ret)const
{
	*ret = myHeight;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::SetWidth(const LONG set)
{
	myMemberLock.WaitLock(&myWidth);

	myWidth = set;

	myMemberLock.UnLock(&myWidth);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxSize::SetHeight(const LONG set)
{
	myMemberLock.WaitLock(&myHeight);

	myHeight = set;

	myMemberLock.UnLock(&myHeight);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxSize::Inflate(const LONG setX, const LONG setY)
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
MfxReturn MicroFlakeX::MfxSize::IsEmpty(bool* ret)
{
	LONG tW = 0, tH = 0;

	GetWidth(&tW);
	GetHeight(&tH);

	*ret = (tW <= 0 || tH <= 0);

	return Mfx_Return_Fine;
}