#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxMove)
MfxObject_Init_1(MfxMove, EachFrame)
MfxAutoFunc_AutoEnum(MfxMove, \
	0 , EachFrame \
)
MfxObject_Init_2(MfxMove, MfxType);

MicroFlakeX::MfxMove::MfxMove()
{
	myTime_Now = myTime_End = myTime_Begin = time(NULL);
}

MicroFlakeX::MfxMove::MfxMove(MfxPoint* setBegin, MfxPoint* setEnd, time_t time_ms)
{

	myPoint_Now = myPoint_Begin = *setBegin;
	myPoint_End = *setEnd;

	myTime_Now = myTime_Begin = time(NULL);
	myTime_End = myTime_Begin + time_ms;
}

MicroFlakeX::MfxMove::MfxMove(MfxPoint* setBegin, MfxPoint* setEnd, time_t timeBegin, time_t timeEnd)
{
	myPoint_Now = myPoint_Begin = *setBegin;
	myPoint_End = *setEnd;

	myTime_Now = time(NULL);

	myTime_Begin = timeBegin;
	myTime_End = timeEnd;

}

MicroFlakeX::MfxMove::~MfxMove()
{
}

MfxReturn MicroFlakeX::MfxMove::Clone(MfxBase** ret)
{
	return MfxReturn();
}

MfxBase& MicroFlakeX::MfxMove::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

MfxMove& MicroFlakeX::MfxMove::operator=(MfxMove& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

BOOL MicroFlakeX::MfxMove::operator==(MfxBase& rhs)
{
	return 0;
}

BOOL MicroFlakeX::MfxMove::operator==(MfxMove& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxMove::MoveTo(MfxPoint* setEnd)
{
	myPoint_End = *setEnd;
	return RFine;
}

MfxReturn MicroFlakeX::MfxMove::EachFrame()
{
	myTime_Now = time(NULL);
	time_t tTime = myTime_Now - myTime_Begin;

	myPoint_Now.myY = myPoint_Begin.myY +
		((myPoint_End.myY - myPoint_Begin.myY) / (myTime_End - myTime_Begin)) * tTime;
	myPoint_Now.myX = myPoint_Begin.myX +
		((myPoint_End.myX - myPoint_Begin.myX) / (myTime_End - myTime_Begin)) * tTime;

	return RFine;
}

MfxReturn MicroFlakeX::MfxMove::GetPoint(MfxPoint* ret)
{
	*ret = myPoint_Now;
	return RFine;
}

MfxReturn MicroFlakeX::MfxMove::GetD2D1PointU(D2D1_POINT_2U* ret)
{
	return myPoint_Now.GetD2D1PointU(ret);
}

MfxReturn MicroFlakeX::MfxMove::GetD2D1PointF(D2D1_POINT_2F* ret)
{
	return myPoint_Now.GetD2D1PointF(ret);
}

MfxReturn MicroFlakeX::MfxMove::GetX(FLOAT* ret)
{
	return myPoint_Now.GetX(ret);
}

MfxReturn MicroFlakeX::MfxMove::GetY(FLOAT* ret)
{
	return myPoint_Now.GetY(ret);
}
