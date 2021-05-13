#include "pch.h"
#include "MfxType.h"

MfxObject_Init_0(MfxType)
MfxObject_Init_1(MfxType, END)
MfxObject_Init_2(MfxType, MfxBase);


MfxReturn MicroFlakeX::MfxType::Clone(MfxBase** ret)
{
	*ret = nullptr;
	return Mfx_Return_Fine;
}

MfxBase& MicroFlakeX::MfxType::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

bool MicroFlakeX::MfxType::operator==(MfxBase& rhs)
{
	return 0;
}
