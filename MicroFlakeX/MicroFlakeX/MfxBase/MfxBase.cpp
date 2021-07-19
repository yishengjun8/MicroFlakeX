#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace MicroFlakeX;


MicroFlakeX::MfxBase::MfxBase()
{
}

MicroFlakeX::MfxBase::~MfxBase()
{
	//MfxSignal::ReceiverDelete(this);
	//MfxClient::ReceiverDelete(this);
}

MfxReturn MicroFlakeX::MfxBase::Clone(MfxBase** ret) const
{
	*ret = nullptr;

	return MFX_RET_FAILED;
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
MfxReturn MicroFlakeX::MfxBase::Reflection(MfxStringW recvFunc ...)
{
	return MFX_RET_NOTFIND;
}

MfxReturn MicroFlakeX::MfxBase::GetObjectName(MfxStringW* ret)
{
	*ret = MFX_TXT_W("MfxBase");
	return MFX_RET_SECCESS;
}


