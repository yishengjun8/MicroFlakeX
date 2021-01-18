#include "pch.h"
#include "MfxBaseTest00.h"

MfxObject_Init_0(MfxBaseTest00)
MfxObject_Register(MfxBaseTest00, SayHello, 1)
MfxObject_Register(MfxBaseTest00, SayGoodBy, 2)
MfxObject_Init_1(MfxBaseTest00)
MfxObject_Case_1(MfxBaseTest00, MfxBase, SayHello, 1)
MfxObject_Case_0(MfxBaseTest00, MfxBase, SayGoodBy, 2)
MfxObject_Init_2(MfxBaseTest00, MfxBase);

MicroFlakeX::MfxBaseTest00::MfxBaseTest00()
{
	MfxCodeLock(this);
	myData = 0;
}

MicroFlakeX::MfxBaseTest00::~MfxBaseTest00()
{
	MfxCodeLock(this);
}

MfxReturn MicroFlakeX::MfxBaseTest00::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	return RFine;
}

MfxBase& MicroFlakeX::MfxBaseTest00::operator=(MfxBase& rhs)
{
	MfxCodeLock(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

BOOL MicroFlakeX::MfxBaseTest00::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SayHello(int set)
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest00 SayHello!" << myData << std::endl;
	return RFine;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SayGoodBy()
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest00 SayGoodBy!" << myData << std::endl;
	return RFine;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SetData(int set)
{
	MfxCodeLock(this);
	myData = set;
	return RFine;
}
