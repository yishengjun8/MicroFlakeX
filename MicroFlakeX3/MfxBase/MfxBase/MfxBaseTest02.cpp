#include "pch.h"
#include "MfxBaseTest02.h"

MfxObject_Init_0(MfxBaseTest02)
MfxObject_Register(MfxBaseTest02, SayHello, 1)
MfxObject_Register(MfxBaseTest02, SayGoodBy, 2)
MfxObject_Init_1(MfxBaseTest02)
MfxObject_Case_1(MfxBaseTest02, MfxBaseTest01, SayHello, 1)
MfxObject_Case_0(MfxBaseTest02, MfxBaseTest01, SayGoodBy, 2)
MfxObject_Init_2(MfxBaseTest02, MfxBaseTest01);

MicroFlakeX::MfxBaseTest02::MfxBaseTest02()
{
	MfxCodeLock(this);
	myData = 200;
}

MicroFlakeX::MfxBaseTest02::~MfxBaseTest02()
{
	MfxCodeLock(this);
}

MfxReturn MicroFlakeX::MfxBaseTest02::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	return MfxReturn();
}

MfxBase& MicroFlakeX::MfxBaseTest02::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	MfxCodeLock(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

BOOL MicroFlakeX::MfxBaseTest02::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest02::SayHello(int set)
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest02 SayHello!" << set << std::endl;
	return RFine;
}

MfxReturn MicroFlakeX::MfxBaseTest02::SayGoodBy()
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest02 SayGoodBy!" << myData << std::endl;
	return RFine;
}

MfxReturn MicroFlakeX::MfxBaseTest02::SetData(int set)
{
	MfxCodeLock(this);
	myData = set;
	return RFine;
}
