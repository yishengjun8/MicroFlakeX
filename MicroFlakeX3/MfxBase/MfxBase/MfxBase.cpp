#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;

/***************************************************************
*
*
*
****************************************************************/

__MicroFlakeX::MfxFactoryHand::MfxFactoryHand(MfxString object)
{
	myObjectName = object;
	MfxRegisterObject(myObjectName, this);
}


__MicroFlakeX::MfxFactoryHand::~MfxFactoryHand()
{
	MfxRemoveObject(myObjectName);
}


/***************************************************************
*
*
*
****************************************************************/
std::map<MfxString, MfxFactoryHand*> MfxFactoryMap;
typedef std::map<MfxString, MfxFactoryHand*>::value_type MfxFactoryValue;

MfxReturn MicroFlakeX::MfxFactory(MfxString object, MfxBase** ret)
{
	auto iter = MfxFactoryMap.find(object);
	if (iter != MfxFactoryMap.end())
	{
		return iter->second->Creat(ret);
	}

	return Mfx_Return_Fail;
}

MfxReturn __MicroFlakeX::MfxRemoveObject(MfxString object)
{
	auto tIter = MfxFactoryMap.find(object);
	if (tIter != MfxFactoryMap.end())
	{
		MfxFactoryMap.erase(tIter);
	}
	return Mfx_Return_Fine;
}

MfxReturn __MicroFlakeX::MfxRegisterObject(MfxString object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryMap.insert(MfxFactoryValue(object, hand));
	return ret.second ? Mfx_Return_Fine : Mfx_Return_Fail;
}


/***************************************************************
*
*
*
****************************************************************/
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


