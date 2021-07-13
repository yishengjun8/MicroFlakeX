#include "pch.h"
#include "MfxBase.h"

typedef std::unordered_map<MfxString, __MicroFlakeX::MfxFactoryHand*>::value_type MfxFactoryValue;

__MicroFlakeX::MfxFactoryHand::MfxFactoryHand(MfxString object)
{
	myObjectName = object;
	RegisterObject(myObjectName, this);
}

__MicroFlakeX::MfxFactoryHand::~MfxFactoryHand()
{
	RemoveObject(myObjectName);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxFactory(MfxString object, MfxBase** ret)
{
	auto iter = __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map.find(object);
	if (iter != __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map.end())
	{
		return iter->second->Creat(ret);
	}

	return MfxReturn_Failed;
}

MicroFlakeX::MfxReturn __MicroFlakeX::MfxFactoryHand::RemoveObject(MfxString object)
{
	auto tIter = MfxFactoryHand_Map.find(object);
	if (tIter != MfxFactoryHand_Map.end())
	{
		MfxFactoryHand_Map.erase(tIter);
	}
	return MfxReturn_Seccess;
}

MicroFlakeX::MfxReturn __MicroFlakeX::MfxFactoryHand::RegisterObject(MfxString object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryHand_Map.insert(MfxFactoryValue(object, hand));
	return ret.second ? MfxReturn_Seccess : MfxReturn_Failed;
}