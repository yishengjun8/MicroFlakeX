#include "pch.h"
#include "MfxBaseTest02.h"

MfxOBJECT_INIT_0(MfxBaseTest02)
MfxOBJECT_AUTOFUNC_REG(MfxBaseTest02, SayHello, 1)
MfxOBJECT_AUTOFUNC_REG(MfxBaseTest02, SayGoodBy, 2)
MfxOBJECT_INIT_1(MfxBaseTest02)
MfxOBJECT_AUTOFUNC_CASE_1(MfxBaseTest02, MfxBaseTest01, SayHello, 1)
MfxOBJECT_AUTOFUNC_CASE_0(MfxBaseTest02, MfxBaseTest01, SayGoodBy, 2)
MfxOBJECT_INIT_2(MfxBaseTest02, MfxBaseTest01);

MicroFlakeX::MfxBaseTest02::MfxBaseTest02()
{
	MfxCODELOCK(this);
	myData = 200;
}

MicroFlakeX::MfxBaseTest02::~MfxBaseTest02()
{
	MfxCODELOCK(this);
}

MfxReturn MicroFlakeX::MfxBaseTest02::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	return MfxReturn();
}

MfxBase& MicroFlakeX::MfxBaseTest02::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	MfxCODELOCK(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

BOOL MicroFlakeX::MfxBaseTest02::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest02::SayHello(int set)
{
	MfxCODELOCK(this);
	std::cout << "Hello MfxBaseTest02 SayHello!" << myData << std::endl;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBaseTest02::SayGoodBy()
{
	MfxCODELOCK(this);
	std::cout << "Hello MfxBaseTest02 SayGoodBy!" << myData << std::endl;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBaseTest02::SetData(int set)
{
	MfxCODELOCK(this);
	myData = set;
	return MfxFINE;
}
