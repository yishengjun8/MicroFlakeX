#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __DeepSpace;

std::map<MfxStrW, MfxFactoryHand*> MfxFactoryMap;
typedef std::map<MfxStrW, MfxFactoryHand*>::value_type MfxFactoryValue;

MfxReturn MicroFlakeX::MfxBaseFactory(MfxStrW object, MfxBase** ret)
{
	auto iter = MfxFactoryMap.find(object);
	if (iter != MfxFactoryMap.end())
	{
		return iter->second->Creat(ret);
	}
	return MfxFAIL;
}

MfxReturn __DeepSpace::MfxRegisterObject(MfxStrW object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryMap.insert(MfxFactoryValue(object, hand));
	return ret.second ? MfxFINE : MfxFAIL;
}

MicroFlakeX::MfxBase::MfxBase()
{
	InitializeCriticalSection(&myCriticalSection);
	myFloor = 0;
}

MicroFlakeX::MfxBase::~MfxBase()
{
	MfxCODELOCK(this);
	DeleteCriticalSection(&myCriticalSection);
}

MfxReturn MicroFlakeX::MfxBase::Clone(MfxBase** ret)
{
	MfxCODELOCK(this);
	*ret = new MfxBase;
	(*ret)->myFloor = myFloor;
	return MfxFINE;
}

MfxBase& MicroFlakeX::MfxBase::operator=(MfxBase& rhs)
{
	MfxCODELOCK(this);
	myFloor = rhs.myFloor;
	return *this;
}

BOOL MicroFlakeX::MfxBase::operator==(MfxBase& rhs)
{
	return myFloor == rhs.myFloor;
}

MfxReturn MicroFlakeX::MfxBase::AutoFunc(MfxStrW func ...)
{
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBase::FuncName(MfxStrW* ret)
{
	MfxCODELOCK(this);
	*ret = L"";
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBase::FuncInfor(MfxStrW* ret)
{
	MfxCODELOCK(this);
	*ret = L"";
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBase::ObjectName(MfxStrW* ret)
{
	MfxCODELOCK(this);
	*ret = L"MfxBase";
	return MfxFINE;
}

MfxReturn MicroFlakeX::MfxBase::ObjectFloor(UINT* ret)
{
	MfxCODELOCK(this);
	*ret = myFloor;
	return MfxFINE;
}

__DeepSpace::MfxFactoryHand::MfxFactoryHand(MfxStrW object)
{
	MfxRegisterObject(object, this);
}

MicroFlakeX::MfxLock::MfxLock(MfxBase* object)
{
	myCriticalSection = &object->myCriticalSection;
	EnterCriticalSection(myCriticalSection);
}

MicroFlakeX::MfxLock::~MfxLock()
{
	LeaveCriticalSection(myCriticalSection);
}
