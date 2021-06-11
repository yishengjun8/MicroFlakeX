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

MicroFlakeX::MfxReturn MicroFlakeX::MfxFactory(MfxString object, pMfxBase* ret)
{
	auto iter = __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map.find(object);
	if (iter != __MicroFlakeX::MfxFactoryHand::MfxFactoryHand_Map.end())
	{
		return iter->second->Creat(ret);
	}

	return Mfx_Return_Fail;
}

MicroFlakeX::MfxReturn __MicroFlakeX::MfxFactoryHand::RemoveObject(MfxString object)
{
	auto tIter = MfxFactoryHand_Map.find(object);
	if (tIter != MfxFactoryHand_Map.end())
	{
		MfxFactoryHand_Map.erase(tIter);
	}
	return Mfx_Return_Fine;
}

MicroFlakeX::MfxReturn __MicroFlakeX::MfxFactoryHand::RegisterObject(MfxString object, MfxFactoryHand* hand)
{
	auto ret = MfxFactoryHand_Map.insert(MfxFactoryValue(object, hand));
	return ret.second ? Mfx_Return_Fine : Mfx_Return_Fail;
}