#include "pch.h"
#include "MfxBase.h"
using namespace MicroFlakeX;
using namespace __MicroFlakeX;

typedef std::unordered_map<MfxString, MfxFactoryHand*>::value_type MfxFactoryValue;

__MicroFlakeX::MfxFactoryHand::MfxFactoryHand(MfxString object)
{
	myObjectName = object;
	MfxRegisterObject(myObjectName, this);
}

__MicroFlakeX::MfxFactoryHand::~MfxFactoryHand()
{
	MfxRemoveObject(myObjectName);
}

MfxReturn MicroFlakeX::MfxFactory(MfxString object, MfxBase** ret)
{
	auto iter = __MicroFlakeX::MfxFactoryHand::MfxFactoryMap.find(object);
	if (iter != __MicroFlakeX::MfxFactoryHand::MfxFactoryMap.end())
	{
		return iter->second->Creat(ret);
	}

	return Mfx_Return_Fail;
}

MfxReturn __MicroFlakeX::MfxFactoryHand::MfxRemoveObject(MfxString object)
{
	auto tIter = MfxFactoryMap.find(object);
	if (tIter != MfxFactoryMap.end())
	{
		MfxFactoryMap.erase(tIter);
	}
	return Mfx_Return_Fine;
}

MfxReturn __MicroFlakeX::MfxFactoryHand::MfxRegisterObject(MfxString object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryMap.insert(MfxFactoryValue(object, hand));
	return ret.second ? Mfx_Return_Fine : Mfx_Return_Fail;
}