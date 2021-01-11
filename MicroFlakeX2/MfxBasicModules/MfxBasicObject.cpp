#include "pch.h"
#include "MfxBasicModules.h"

void MicroFlakeX::MfxBasicObject::MfxInitBasicData()
{
}

MicroFlakeX::MfxBasicObject::MfxBasicObject()
{
	InitializeCriticalSection(&myCriticalSection);
}

MicroFlakeX::MfxBasicObject::~MfxBasicObject()
{
	MFXLOCK;
	DeleteCriticalSection(&myCriticalSection);
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxBasicObject::GetName(MfxStrW* ret)
{
	MFXLOCK;
	(*ret) = L"MfxBasicObject";
	return MfxFine;
}


MicroFlakeX::MfxReturn MicroFlakeX::MfxBasicObject::AutoFunc(MfxStrW funcName, ...)
{
	return MfxFail;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxBasicObject::GetAutoFuncName(MfxStrW& ret)
{
	MFXLOCK;
	for (auto i : myAutoFuncMap)
	{
		std::cout << "AutoFunc:" << i.first.c_str() << " Argv:" << i.second->myArgc << std::endl;
	}
	return MfxFine;
}
