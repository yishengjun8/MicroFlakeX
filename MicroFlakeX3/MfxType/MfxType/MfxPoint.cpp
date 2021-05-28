#include "pch.h"
#include "MfxType.h"

MfxObject_Init(MfxPoint)
MfxObject_EndInit(MfxPoint, MfxBase, \
	2, Reset, \
	\
	1, GetPoint, \
	\
	1, GetPOINT, \
	\
	1, GetGdipPoint, \
	1, GetGdipPointF, \
	\
	1, GetD2D1Point2L, \
	1, GetD2D1Point2U, \
	1, GetD2D1Point2F, \
	\
	\
	1, SetPoint, \
	\
	1, SetPOINT, \
	\
	1, SetGdipPoint, \
	1, SetGdipPointF, \
	\
	1, SetD2D1Point2L, \
	1, SetD2D1Point2U, \
	1, SetD2D1Point2F, \
	\
	\
	1, GetX, \
	1, GetY, \
	\
	1, SetX, \
	1, SetY, \
	\
	\
	2, Offset);


/**************************************************************
*
*
*
***************************************************************/
MicroFlakeX::MfxPoint::MfxPoint()
{
	LONG tSX = 0, tSY = 0;

	SetX(tSX);
	SetY(tSY);
}

MicroFlakeX::MfxPoint::MfxPoint(MfxBase& set)
{
	LONG tSX = 0, tSY = 0;

	set.AutoFunc(MfxText("GetX"), &tSX);
	set.AutoFunc(MfxText("GetY"), &tSY);

	SetY(tSY);
	SetX(tSX);
}

MicroFlakeX::MfxPoint::MfxPoint(const MfxRect* set)
{
	LONG tSX = 0, tSY = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);

	SetX(tSX);
	SetY(tSY);
}

MicroFlakeX::MfxPoint::MfxPoint(const MfxPoint* set)
{
	LONG tSX = 0, tSY = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);

	SetX(tSX);
	SetY(tSY);
}


MicroFlakeX::MfxPoint::MfxPoint(const LONG setX, const LONG setY)
{
	SetX(setX);
	SetY(setY);
}

MicroFlakeX::MfxPoint::~MfxPoint()
{
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::Clone(MfxBase** ret)const
{
	*ret = new MfxPoint(*this);

	return Mfx_Return_Fine;
}

MfxBase& MicroFlakeX::MfxPoint::operator=(MfxBase& rhs)
{
	LONG tRX = 0, tRY = 0;

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetX"), &tRX)))
	{
		SetX(tRX);
	}
	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetY"), &tRY)))
	{
		SetY(tRY);
	}
	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(const MfxRect* rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs->GetX(&tRX);
	rhs->GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(const MfxRect& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(const MfxRect&& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(const MfxPoint* rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs->GetX(&tRX);
	rhs->GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(const MfxPoint& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}

MfxPoint& MicroFlakeX::MfxPoint::operator=(const MfxPoint&& rhs)
{
	LONG tRX = 0, tRY = 0;

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	SetX(tRX);
	SetY(tRY);

	return *this;
}


/**************************************************************
*
*
*
***************************************************************/
bool MicroFlakeX::MfxPoint::operator==(MfxBase& rhs)
{
	LONG tX = 0, tY = 0;
	LONG tRX = 0, tRY = 0;

	GetX(&tX);
	GetY(&tY);

	if (Mfx_Seccess(rhs.AutoFunc(MfxText("GetX"), &tRX))
		&& Mfx_Seccess(rhs.AutoFunc(MfxText("GetY"), &tRY))
		)
	{
		return tX == tRX && tY == tRY;
	}

	return false;
}

bool MicroFlakeX::MfxPoint::operator==(const MfxPoint* rhs)const
{
	LONG tX = 0, tY = 0;
	LONG tRX = 0, tRY = 0;

	GetX(&tX);
	GetY(&tY);

	rhs->GetX(&tRX);
	rhs->GetY(&tRY);

	return tX == tRX && tY == tRY;
}

bool MicroFlakeX::MfxPoint::operator==(const MfxPoint& rhs)const
{
	LONG tX = 0, tY = 0;
	LONG tRX = 0, tRY = 0;

	GetX(&tX);
	GetY(&tY);

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	return tX == tRX && tY == tRY;
}

bool MicroFlakeX::MfxPoint::operator==(const MfxPoint&& rhs)const
{
	LONG tX = 0, tY = 0;
	LONG tRX = 0, tRY = 0;

	GetX(&tX);
	GetY(&tY);

	rhs.GetX(&tRX);
	rhs.GetY(&tRY);

	return tX == tRX && tY == tRY;
}

MicroFlakeX::MfxPoint::operator D2D1_POINT_2L()const
{
	D2D1_POINT_2L tD2D1_POINT_2L;

	GetD2D1Point2L(&tD2D1_POINT_2L);

	return tD2D1_POINT_2L;
}

MicroFlakeX::MfxPoint::operator D2D1_POINT_2U()const
{
	D2D1_POINT_2U tD2D1_POINT_2U;

	GetD2D1Point2U(&tD2D1_POINT_2U);

	return tD2D1_POINT_2U;
}

MicroFlakeX::MfxPoint::operator D2D1_POINT_2F()const
{
	D2D1_POINT_2F tD2D1_POINT_2F;

	GetD2D1Point2F(&tD2D1_POINT_2F);

	return tD2D1_POINT_2F;
}

MicroFlakeX::MfxPoint::operator Gdiplus::Point()const
{
	Gdiplus::Point tPoint;

	GetGdipPoint(&tPoint);

	return tPoint;
}

MicroFlakeX::MfxPoint::operator Gdiplus::PointF()const
{
	Gdiplus::PointF tPointF;

	GetGdipPointF(&tPointF);

	return tPointF;
}

/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::Reset(LONG setX, LONG setY)
{
	SetX(setX);
	SetY(setY);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::GetPoint(MfxPoint* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	return ret->Reset(tX, tY);
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::GetPOINT(POINT* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::GetGdipPoint(Gdiplus::Point* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::GetGdipPointF(Gdiplus::PointF* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->X = tX;
	ret->Y = tY;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::GetD2D1Point2L(D2D1_POINT_2L* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}
MfxReturn MicroFlakeX::MfxPoint::GetD2D1Point2U(D2D1_POINT_2U* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::GetD2D1Point2F(D2D1_POINT_2F* ret)const
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	ret->x = tX;
	ret->y = tY;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::SetPoint(const MfxPoint* set)
{
	LONG tSX = 0, tSY = 0;

	set->GetX(&tSX);
	set->GetY(&tSY);

	SetX(tSX);
	SetY(tSY);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::SetPOINT(const POINT* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::SetGdipPoint(const Gdiplus::Point* set)
{
	SetX(set->X);
	SetY(set->Y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::SetGdipPointF(const Gdiplus::PointF* set)
{
	SetX(set->X);
	SetY(set->Y);

	return Mfx_Return_Fine;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::SetD2D1Point2L(const D2D1_POINT_2U* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::SetD2D1Point2U(const D2D1_POINT_2U* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::SetD2D1Point2F(const D2D1_POINT_2F* set)
{
	SetX(set->x);
	SetY(set->y);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::SetX(const LONG set)
{
	myMutexLock.WaitLock(&myX);

	myX = set;

	myMutexLock.UnLock(&myX);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::SetY(const LONG set)
{
	myMutexLock.WaitLock(&myY);

	myY = set;

	myMutexLock.UnLock(&myY);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::GetX(LONG* ret)const
{
	*ret = myX;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxPoint::GetY(LONG* ret)const
{
	*ret = myY;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxPoint::Offset(const LONG setX, const LONG setY)
{
	LONG tX = 0, tY = 0;

	GetX(&tX);
	GetY(&tY);

	SetX(tX + setX);
	SetY(tY + setY);

	return Mfx_Return_Fine;
}