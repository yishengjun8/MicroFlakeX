#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;



void* MicroFlakeX::MfxCriticalLock::operator new(size_t)
{
	return nullptr;
}

void* MicroFlakeX::MfxCriticalLock::operator new[](size_t)
{
	return nullptr;
}

MicroFlakeX::MfxCriticalLock::MfxCriticalLock(CRITICAL_SECTION* set)
{
	myCriticalSection = set;
	EnterCriticalSection(myCriticalSection);
}

MicroFlakeX::MfxCriticalLock::~MfxCriticalLock()
{
	LeaveCriticalSection(myCriticalSection);
}
