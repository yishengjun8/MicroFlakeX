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
	return RFail;
}

MfxReturn __DeepSpace::MfxRegisterObject(MfxStrW object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryMap.insert(MfxFactoryValue(object, hand));
	return ret.second ? RFine : RFail;
}

MicroFlakeX::MfxBase::MfxBase()
{
	InitializeCriticalSection(&myCriticalSection);
	myFloor = 0;
}

MicroFlakeX::MfxBase::~MfxBase()
{
	MfxCodeLock(this);
	DeleteCriticalSection(&myCriticalSection);
}

MfxReturn MicroFlakeX::MfxBase::Clone(MfxBase** ret)
{
	MfxCodeLock(this);
	*ret = new MfxBase;
	(*ret)->myFloor = myFloor;
	return RFine;
}

MfxBase& MicroFlakeX::MfxBase::operator=(MfxBase& rhs)
{
	MfxCodeLock(this);
	myFloor = rhs.myFloor;
	return *this;
}

BOOL MicroFlakeX::MfxBase::operator==(MfxBase& rhs)
{
	return myFloor == rhs.myFloor;
}

MfxReturn MicroFlakeX::MfxBase::AutoFunc(MfxStrW func ...)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxBase::FuncName(MfxStrW* ret)
{
	MfxCodeLock(this);
	*ret = L"";
	return RFine;
}

MfxReturn MicroFlakeX::MfxBase::FuncInfor(MfxStrW* ret)
{
	MfxCodeLock(this);
	*ret = L"";
	return RFine;
}

MfxReturn MicroFlakeX::MfxBase::ObjectName(MfxStrW* ret)
{
	MfxCodeLock(this);
	*ret = L"MfxBase";
	return RFine;
}

MfxReturn MicroFlakeX::MfxBase::ObjectFloor(UINT* ret)
{
	MfxCodeLock(this);
	*ret = myFloor;
	return RFine;
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
