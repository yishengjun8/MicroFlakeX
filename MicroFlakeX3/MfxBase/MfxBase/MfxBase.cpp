#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;

std::map<MfxString, MfxFactoryHand*> MfxFactoryMap;
typedef std::map<MfxString, MfxFactoryHand*>::value_type MfxFactoryValue;

MfxReturn MicroFlakeX::MfxBaseFactory(MfxString object, MfxBase** ret)
{
	auto iter = MfxFactoryMap.find(object);
	if (iter != MfxFactoryMap.end())
	{
		return iter->second->Creat(ret);
	}
	return RFine;
}

MfxReturn __MicroFlakeX::MfxRemoveObject(MfxString object)
{
	auto tIter = MfxFactoryMap.find(object);
	if (tIter != MfxFactoryMap.end())
	{
		MfxFactoryMap.erase(tIter);
	}
	return RFine;
}

MfxReturn __MicroFlakeX::MfxRegisterObject(MfxString object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryMap.insert(MfxFactoryValue(object, hand));
	return ret.second ? RFine : RFail;
}

MicroFlakeX::MfxBase::MfxBase()
{
	InitializeCriticalSection(&myCriticalSection);
}

MicroFlakeX::MfxBase::~MfxBase()
{
	DeleteCriticalSection(&myCriticalSection);
}

MfxReturn MicroFlakeX::MfxBase::Clone(MfxBase** ret)
{
	*ret = new MfxBase;
	return RFine;
}

MfxBase& MicroFlakeX::MfxBase::operator=(MfxBase& rhs)
{
	return *this;
}

BOOL MicroFlakeX::MfxBase::operator==(MfxBase& rhs)
{
	return 0;
}

MfxReturn MicroFlakeX::MfxBase::AutoFunc(MfxString func ...)
{
	return RFine;
}

MfxReturn MicroFlakeX::MfxBase::FuncName(MfxString* ret)
{
	*ret = MfxText("");
	return RFine;
}

MfxReturn MicroFlakeX::MfxBase::ObjectName(MfxString* ret)
{
	*ret = MfxText("MfxBase");
	return RFine;
}

#include <fstream>
std::wofstream mycout("temp.txt");

__MicroFlakeX::MfxFactoryHand::MfxFactoryHand(MfxString object)
{
	myObjectName = object;
	MfxRegisterObject(myObjectName, this);
	std::wcout << MfxText("ClassHand <") << myObjectName << MfxText("> Is Register") << std::endl;
	mycout << MfxText("ClassHand <") << myObjectName << MfxText("> Is Register") << std::endl;
}


__MicroFlakeX::MfxFactoryHand::~MfxFactoryHand()
{
	MfxRemoveObject(myObjectName);
	std::wcout << MfxText("ClassHand <") << myObjectName << MfxText("> Is Remove") << std::endl;
	mycout << MfxText("ClassHand <") << myObjectName << MfxText("> Is Remove") << std::endl;
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
