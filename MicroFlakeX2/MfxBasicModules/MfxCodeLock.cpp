#include "pch.h"
#include "MfxBasicModules.h"

MicroFlakeX::MfxCodeLock::MfxCodeLock(MfxBasicObject* object)
{
	myCriticalSection = &(object->myCriticalSection);
	EnterCriticalSection(myCriticalSection);
}

MicroFlakeX::MfxCodeLock::~MfxCodeLock()
{
	LeaveCriticalSection(myCriticalSection);
}
