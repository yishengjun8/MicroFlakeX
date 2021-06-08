#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;


void MicroFlakeX::MfxMemberLock::InsertMemberLock(void* resour)
{
	myMutexResour.insert(myResour(resour, CRITICAL_SECTION()));

	InitializeCriticalSection(&myMutexResour[resour]);
}

void MicroFlakeX::MfxMemberLock::WaitLock(void* const first)
{
	auto tFind = myMutexResour.find(const_cast<void*>(first));
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(const_cast<void*>(first));
		EnterCriticalSection(&myMutexResour[const_cast<void*>(first)]);
	}
	else
	{
		EnterCriticalSection(&tFind->second);
	}
}

bool MicroFlakeX::MfxMemberLock::TryLock(void* first)
{
	bool ret = false;
	auto tFind = myMutexResour.find(const_cast<void*>(first));
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(const_cast<void*>(first));
		ret = TryEnterCriticalSection(&myMutexResour[const_cast<void*>(first)]);
	}
	else
	{
		ret = TryEnterCriticalSection(&tFind->second);
	}

	return ret;
}

void MicroFlakeX::MfxMemberLock::UnLock(void* first)
{
	auto tFind = myMutexResour.find(const_cast<void*>(first));
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(const_cast<void*>(first));
	}
	else
	{
		LeaveCriticalSection(&myMutexResour[const_cast<void*>(first)]);
	}
}

MicroFlakeX::MfxMemberLock::~MfxMemberLock()
{
	for (auto iter : myMutexResour)
	{
		DeleteCriticalSection(&iter.second);
	}
}