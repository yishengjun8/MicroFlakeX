#include "pch.h"
#include "MfxBase.h"

typedef std::unordered_map<MfxStringW, __MicroFlakeX::MfxFactoryHand*>::value_type MfxFactoryValue;

__MicroFlakeX::MfxFactoryHand::MfxFactoryHand(MfxStringW object)
{
	myObjectName = object;
	RegisterObject(myObjectName, this);
}

__MicroFlakeX::MfxFactoryHand::~MfxFactoryHand()
{
	RemoveObject(myObjectName);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxFactory(MfxStringW object, MfxBase** ret)
{
	auto iter = __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map.find(object);
	if (iter != __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map.end())
	{
		return iter->second->Creat(ret);
	}

	return MFXRET_FAILED;
}

MicroFlakeX::MfxReturn __MicroFlakeX::MfxFactoryHand::RemoveObject(MfxStringW object)
{
	auto tIter = MfxFactoryHand_Map.find(object);
	if (tIter != MfxFactoryHand_Map.end())
	{
		MfxFactoryHand_Map.erase(tIter);
	}
	return MFXRET_SECCESS;
}

MicroFlakeX::MfxReturn __MicroFlakeX::MfxFactoryHand::RegisterObject(MfxStringW object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryHand_Map.insert(MfxFactoryValue(object, hand));
	return ret.second ? MFXRET_SECCESS : MFXRET_FAILED;
}