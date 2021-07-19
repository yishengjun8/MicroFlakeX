#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;

typedef std::unordered_map<MfxStringW, MicroFlakeX::__MfxFactoryHand*>::value_type MfxFactoryValue;

MicroFlakeX::__MfxFactoryHand::__MfxFactoryHand(MfxStringW object)
{
	myObjectName = object;
	RegisterObject(myObjectName, this);
}

MicroFlakeX::__MfxFactoryHand::~__MfxFactoryHand()
{
	RemoveObject(myObjectName);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxFactory(MfxStringW object, MfxBase** ret)
{
	auto iter = __MfxFactoryHand::__MfxFactoryHand_Map.find(object);
	if (iter != __MfxFactoryHand::__MfxFactoryHand_Map.end())
	{
		return iter->second->Creat(ret);
	}

	return MFX_RET_FAILED;
}

MFX_DLL_EXPORT MfxBase* MicroFlakeX::MfxFactory(MfxStringW object)
{
	MfxBase** ret = nullptr;
	auto iter = __MfxFactoryHand::__MfxFactoryHand_Map.find(object);
	if (iter != __MfxFactoryHand::__MfxFactoryHand_Map.end())
	{
		iter->second->Creat(ret);
	}

	return *ret;
}

MicroFlakeX::MfxReturn MicroFlakeX::__MfxFactoryHand::RemoveObject(MfxStringW object)
{
	auto tIter = __MfxFactoryHand_Map.find(object);
	if (tIter != __MfxFactoryHand_Map.end())
	{
		__MfxFactoryHand_Map.erase(tIter);
	}
	return MFX_RET_SECCESS;
}

MicroFlakeX::MfxReturn MicroFlakeX::__MfxFactoryHand::RegisterObject(MfxStringW object, __MfxFactoryHand* hand)
{
	auto ret = __MfxFactoryHand_Map.insert(MfxFactoryValue(object, hand));
	return ret.second ? MFX_RET_SECCESS : MFX_RET_FAILED;
}