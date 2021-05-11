#include "pch.h"
#include "MfxBaseTest00.h"

MfxObject_Init_0(MfxBaseTest00)
MfxObject_Init_1(MfxBaseTest00, SayHello)
MfxAutoFunc_AutoEnum(MfxBaseTest00, 1, SayHello, 0, SayGoodBy, 1, SetData)
MfxObject_Init_2(MfxBaseTest00, MfxBase);

MicroFlakeX::MfxBaseTest00::MfxBaseTest00()
{
	MfxCodeLock(this);
	std::cout << "MfxBaseTest00 creat" << std::endl;
	myData = 0;
}

MicroFlakeX::MfxBaseTest00::~MfxBaseTest00()
{
	MfxCodeLock(this);
}

MfxReturn MicroFlakeX::MfxBaseTest00::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	return Mfx_Return_Fine;
}

MfxBase& MicroFlakeX::MfxBaseTest00::operator=(MfxBase& rhs)
{
	MfxCodeLock(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

void MicroFlakeX::MfxBaseTest00::Test(MfxBaseTest00* set, int a)
{
	std::cout << set->myData;
}

BOOL MicroFlakeX::MfxBaseTest00::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SayHello(int set)
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest00 SayHello! setNum = " << set << std::endl;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SayGoodBy()
{
	MfxCodeLock(this);
	std::cout << "Hello MfxBaseTest00 SayGoodBy! myData = " << myData << std::endl;
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SetData(int set)
{
	MfxCodeLock(this);
	myData = set;
	return Mfx_Return_Fine;
}
