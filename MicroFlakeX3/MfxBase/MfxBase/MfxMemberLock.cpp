#include "pch.h"
#include "MfxBase.h"

using namespace MicroFlakeX;
using namespace __MicroFlakeX;


void MicroFlakeX::MfxMemberLock::InsertMemberLock(void* resour)
{
	myMutexResour.insert(myResour(resour, CRITICAL_SECTION()));

	InitializeCriticalSection(&myMutexResour[resour]);
}

void MicroFlakeX::MfxMemberLock::WaitLock(void* first)
{
	auto tFind = myMutexResour.find(first);
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(first);
		EnterCriticalSection(&myMutexResour[first]);
	}
	else
	{
		EnterCriticalSection(&tFind->second);
	}
}

bool MicroFlakeX::MfxMemberLock::TryLock(void* first)
{
	bool ret = false;
	auto tFind = myMutexResour.find(first);
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(first);
		ret = TryEnterCriticalSection(&myMutexResour[first]);
	}
	else
	{
		ret = TryEnterCriticalSection(&tFind->second);
	}

	return ret;
}

void MicroFlakeX::MfxMemberLock::UnLock(void* first)
{
	auto tFind = myMutexResour.find(first);
	if (tFind == myMutexResour.end())
	{
		InsertMemberLock(first);
	}
	else
	{
		LeaveCriticalSection(&myMutexResour[first]);
	}
}

MicroFlakeX::MfxMemberLock::~MfxMemberLock()
{
	for (auto iter : myMutexResour)
	{
		DeleteCriticalSection(&iter.second);
	}
}