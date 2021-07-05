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
	MfxSignal_Link::ReceiverDelete(this);
	MfxSignal_UnLink::ReceiverDelete(this);
	DeleteCriticalSection(&myCriticalSection);
}

MfxReturn MicroFlakeX::MfxBase::Clone(pMfxBase* ret) const
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
MfxReturn MicroFlakeX::MfxBase::Reflection(MfxString recvFunc ...)
{
	return Mfx_Return_Fail;
}

MfxReturn MicroFlakeX::MfxBase::GetObjectName(MfxString* ret)
{
	*ret = MfxText("MfxBase");
	return Mfx_Return_Fine;
}


