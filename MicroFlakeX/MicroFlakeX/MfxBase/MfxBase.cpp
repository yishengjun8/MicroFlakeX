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
	MfxSignal::ReceiverDelete(this);
	MfxClient::ReceiverDelete(this);
	DeleteCriticalSection(&myCriticalSection);
}

MfxReturn MicroFlakeX::MfxBase::Clone(MfxBase** ret) const
{
	*ret = nullptr;

	return MfxReturn_Failed;
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
	return MfxReturn_Failed;
}

MfxReturn MicroFlakeX::MfxBase::GetObjectName(MfxString* ret)
{
	*ret = MfxText("MfxBase");
	return MfxReturn_Seccess;
}


