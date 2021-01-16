#include "pch.h"
#include "MfxBaseTest01.h"

MfxOBJECT_INIT_0(MfxBaseTest01)
MfxOBJECT_INIT_1(MfxBaseTest01)
MfxOBJECT_INIT_2(MfxBaseTest01, MfxBaseTest00);

MicroFlakeX::MfxBaseTest01::MfxBaseTest01()
{
	MfxCODELOCK(this);
	myData = 100;
}

MicroFlakeX::MfxBaseTest01::~MfxBaseTest01()
{
	MfxCODELOCK(this);
}

MfxReturn MicroFlakeX::MfxBaseTest01::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	return MfxReturn();
}

MfxBase& MicroFlakeX::MfxBaseTest01::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	MfxCODELOCK(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

BOOL MicroFlakeX::MfxBaseTest01::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest01::SayHello(int set)
{
	MfxCODELOCK(this);
	std::cout << "Hello MfxBaseTest01 SayHello!" << myData << std::endl;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBaseTest01::SayGoodBy()
{
	MfxCODELOCK(this);
	std::cout << "Hello MfxBaseTest01 SayGoodBy!" << myData << std::endl;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBaseTest01::SetData(int set)
{
	MfxCODELOCK(this);
	myData = set;
	return MfxFINE;
}
