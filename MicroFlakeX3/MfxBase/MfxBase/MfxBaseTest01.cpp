#include "pch.h"
#include "MfxBaseTest01.h"

MfxObject_Init_0(MfxBaseTest01)
MfxObject_Init_1(MfxBaseTest01)
MfxObject_Init_2(MfxBaseTest01, MfxBaseTest00);

MicroFlakeX::MfxBaseTest01::MfxBaseTest01()
{
	MfxCodeLock(this);
	myData = 100;
}

MicroFlakeX::MfxBaseTest01::~MfxBaseTest01()
{
	MfxCodeLock(this);
}

MfxReturn MicroFlakeX::MfxBaseTest01::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	return MfxReturn();
}

MfxBase& MicroFlakeX::MfxBaseTest01::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	MfxCodeLock(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

BOOL MicroFlakeX::MfxBaseTest01::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest01::SayHello(int set)
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest01 SayHello!" << myData << std::endl;
	return RFine;
}

MfxReturn MicroFlakeX::MfxBaseTest01::SayGoodBy()
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest01 SayGoodBy!" << myData << std::endl;
	return RFine;
}

MfxReturn MicroFlakeX::MfxBaseTest01::SetData(int set)
{
	MfxCodeLock(this);
	myData = set;
	return RFine;
}
