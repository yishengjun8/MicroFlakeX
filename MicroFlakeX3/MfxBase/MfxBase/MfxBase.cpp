#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;


MicroFlakeX::MfxBase::MfxBase()
{
	InitializeCriticalSection(&myCriticalSection);
}

MicroFlakeX::MfxBase::~MfxBase()
{
	DeleteCriticalSection(&myCriticalSection);
}

MfxReturn MicroFlakeX::MfxBase::Clone(MfxBase** ret) const
{
	*ret = nullptr;

	return Mfx_Return_Fail;
}


/***************************************************************
*
*
*
****************************************************************/
MfxBase& MicroFlakeX::MfxBase::operator=(MfxBase& rhs)
{
	return *this;
}

bool MicroFlakeX::MfxBase::operator==(MfxBase& rhs)
{
	return false;
}


/***************************************************************
*
*
*
****************************************************************/
MfxReturn MicroFlakeX::MfxBase::AutoFunc(MfxString recvFunc ...)
{
	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxBase::FuncName(MfxString* ret)
{
	*ret = MfxText("");
	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxBase::ObjectName(MfxString* ret)
{
	*ret = MfxText("MfxBase");
	return Mfx_Return_Fine;
}


