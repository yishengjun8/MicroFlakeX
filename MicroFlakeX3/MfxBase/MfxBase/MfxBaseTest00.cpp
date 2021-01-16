#include "pch.h"
#include "MfxBaseTest00.h"

MfxOBJECT_INIT_0(MfxBaseTest00)
MfxOBJECT_AUTOFUNC_REG(MfxBaseTest00, SayHello, 1)
MfxOBJECT_AUTOFUNC_REG(MfxBaseTest00, SayGoodBy, 2)
MfxOBJECT_INIT_1(MfxBaseTest00)
MfxOBJECT_AUTOFUNC_CASE_1(MfxBaseTest00, MfxBase, SayHello, 1)
MfxOBJECT_AUTOFUNC_CASE_0(MfxBaseTest00, MfxBase, SayGoodBy, 2)
MfxOBJECT_INIT_2(MfxBaseTest00, MfxBase);

MicroFlakeX::MfxBaseTest00::MfxBaseTest00()
{
	MfxCODELOCK(this);
	myData = 0;
}

MicroFlakeX::MfxBaseTest00::~MfxBaseTest00()
{
	MfxCODELOCK(this);
}

MfxReturn MicroFlakeX::MfxBaseTest00::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	return MfxFINE;
}

MfxBase& MicroFlakeX::MfxBaseTest00::operator=(MfxBase& rhs)
{
	MfxCODELOCK(this);
	rhs.AutoFunc(L"SetData", myData);
	return *this;
}

BOOL MicroFlakeX::MfxBaseTest00::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SayHello(int set)
{
	MfxCODELOCK(this);
	std::cout << "Hello MfxBaseTest00 SayHello!" << myData << std::endl;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SayGoodBy()
{
	MfxCODELOCK(this);
	std::cout << "Hello MfxBaseTest00 SayGoodBy!" << myData << std::endl;
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBaseTest00::SetData(int set)
{
	MfxCODELOCK(this);
	myData = set;
	return MfxFINE;
}
